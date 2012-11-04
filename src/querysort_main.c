/*
 * querysort - RFC 1866 querystring sorting library
 *
 * Copyright (C) 2012, Dridi Boukelmoune <dridi.boukelmoune@gmail.com>
 * All rights reserved.
 *
 * Redistribution  and use in source and binary forms, with or without
 * modification,  are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions   of  source   code   must   retain  the   above
 *    copyright  notice, this  list of  conditions  and the  following
 *    disclaimer.
 * 2. Redistributions   in  binary  form  must  reproduce  the   above
 *    copyright  notice, this  list of  conditions and  the  following
 *    disclaimer   in  the   documentation   and/or  other   materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT  NOT
 * LIMITED  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS
 * FOR  A  PARTICULAR  PURPOSE ARE DISCLAIMED. IN NO EVENT  SHALL  THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL,    SPECIAL,   EXEMPLARY,   OR   CONSEQUENTIAL   DAMAGES
 * (INCLUDING,  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT  LIABILITY,  OR  TORT (INCLUDING  NEGLIGENCE  OR  OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <config.h>

#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <uriparser/Uri.h>

#include "querysort.h"

static int  sort_file();
static void sort_stream(FILE*);
static int  sort_string(const char*);
static void get_options(int, char**);
static void print_help();
static void print_version();

static int  verbose_flag = 0;
static int  no_clean_flag = 0;
static char delimiter = '\n';

static const char* command;
static const char* input_file = NULL;

static struct option long_options[] = {
	{"delimiter", required_argument, NULL, 'd'},
	{"file",      required_argument, NULL, 'f'},
	{"no-clean",  no_argument,       NULL, 'n'},
	{"verbose",   no_argument,       NULL, 'v'},
	{0, 0, 0, 0}
};

int
main(int argc, char **argv)
{
	command = argv[0];
	get_options(argc, argv);
	
	if (input_file == NULL) {
		return sort_string(argv[optind]);
	}

	return sort_file();
}

static int
sort_file()
{
	FILE *stream = (strcmp(input_file, "-") == 0)
		? stdin
		: fopen(input_file, "r");

	if (stream == NULL) {
		error(0, errno, "%s", input_file);
		return EXIT_FAILURE;
	}

#if HAVE_POSIX_FADVISE
	posix_fadvise(fileno(stream), 0, 0, POSIX_FADV_SEQUENTIAL);
#endif

	sort_stream(stream);

	if (ferror(stream)) {
		error(0, errno, "%s", input_file);
		return EXIT_FAILURE;
	}
	
	if (strcmp(input_file, "-") == 0) {
		clearerr(stream);
	}

	if (fclose(stream) == EOF) {
		error(0, errno, "%s", input_file);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

static void
sort_stream(FILE *stream)
{
	char *string = NULL;
	size_t length = 0;

	while ( ! feof(stream) ) {
		ssize_t read_length = getdelim(&string, &length, delimiter, stream);
		if (read_length <= 0) {
			continue;
		}
		ssize_t length_without_delimiter = read_length - 1;
		if (strnlen(string, read_length) < length_without_delimiter) {
			error(0, 0, "invalid uri <%s...>", string);
			continue;
		}
		string[read_length - 1] = '\0';
		sort_string(string);
	}
}

static int
sort_string(const char *string) {
	UriParserStateA state;
	UriUriA uri;

	state.uri = &uri;

	if (uriParseUriA(&state, string) != URI_SUCCESS) {
		uriFreeUriMembersA(&uri);
		error(0, 0, "invalid uri <%s>", string);
		return EXIT_FAILURE;
	}

	uriFreeUriMembersA(&uri);

	int return_code = no_clean_flag
		? qs_fsort(string, stdout)
		: qs_fsort_clean(string, stdout);

	switch (return_code) {
		case QS_OK:
			putchar('\n');
			break;
		case QS_ERROR:
			error(0, errno, "an error occured");
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

static void
get_options(int argc, char **argv)
{
	if (argc == 2 && strcmp(argv[1], "--version") == 0) {
		print_version();
		exit(EXIT_SUCCESS);
	}

	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		print_help(command);
		exit(EXIT_SUCCESS);
	}

	int c;
	bool delimiter_option = false;
	while ((c = getopt_long(argc, argv, "d:f:nv", long_options, NULL)) != -1) {
		switch (c) {
			case  0:
				break;

			case 'd':
				if(optarg[0] != '\0' && optarg[1] != '\0') {
					error(EXIT_FAILURE, 0, "the delimiter must be a single character");
				}
				delimiter_option = true;
				delimiter = optarg[0];
				break;

			case 'f':
				input_file = optarg;
				break;

			case 'n':
				no_clean_flag = 1;
				break;

			case 'v':
				verbose_flag = 1;
				break;

			case '?':
				break;

			default:
				abort();
		}
	}

	int non_option_argc = argc - optind;

	if (non_option_argc > 1 || (non_option_argc == 1 && input_file != NULL)) {
		print_help();
		abort();
	}

	if (non_option_argc == 0  && input_file == NULL) {
		input_file = "-";
	}

	if (delimiter_option && input_file == NULL) {
		error(EXIT_FAILURE, 0, "a delimiter can only be used with a file");
	}
}

static void
print_help()
{
	fprintf(stderr,
	        "Usage : %s [-nv] URI\n"
	        "        %s [-dnv] [-f FILE]\n",
	        command, command
	);

	puts(
		"Print URIs with their query-strings sorted.\n"
		"\n"
		"Mandatory arguments to long options are mandatory for short options too.\n"
		"  -d, --delimiter=DELIM   use DELIM instead of EOL for field delimiter\n"
		"  -f, --file=FILE         read URIs from FILE\n"
		"  -n, --no-clean          do not clean the URIs (remove empty parameters)\n"
		"  -v, --verbose           provide more detailed information\n"
		"\n"
		"      --help     display this help and exit\n"
		"      --version  output version information and exit\n"
		"\n"
		"You can use a delimiter only when reading URIs from a file.\n"
		"With no URI, or when FILE is -, read standard input.\n"
	);
}

static void
print_version()
{
	printf(
		"QuerySort %s\n"
		"Copyright (C) 2012 Dridi Boukelmoune\n"
		"License FreeBSD: 2-clause BSD license <http://www.freebsd.org/copyright/freebsd-license.html>\n"
		"This is free software: you are free to change and redistribute it.\n"
		"There is NO WARRANTY, to the extent permitted by law.\n"
	, qs_version());
}

