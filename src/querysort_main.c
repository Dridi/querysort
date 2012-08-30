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

#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<uriparser/Uri.h>

#include "querysort.h"

int
print_version();

int
main(const int argc, const char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage : %s URI\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	if (strcmp(argv[1], "--version") == 0) {
		return print_version();
	}

	UriParserStateA state;
	UriUriA uri;
	
	state.uri = &uri;

	if (uriParseUriA(&state, argv[1]) != URI_SUCCESS) {
		fprintf(stderr, "Invalid URI : <%s>\n", argv[1]);
		uriFreeUriMembersA(&uri);
		return EXIT_FAILURE;
	}

	uriFreeUriMembersA(&uri);

	int uri_length = strlen(argv[1]);
	char sorted_uri[uri_length + 1];

	if (qs_sort_clean(argv[1], sorted_uri) != QS_OK) {
		fprintf(stderr, "An error occured (errno %d : %s)\n", errno, strerror(errno));
		return EXIT_FAILURE;
	}

	if (strlen(argv[1]) > strlen(sorted_uri)) {
		fprintf(stderr, "Invalid URI was cleaned <%s>\n", argv[1]);
	}

	puts(sorted_uri);

	return EXIT_SUCCESS;
}

int
print_version()
{
	printf(
		"QuerySort %s\n"
		"Copyright (C) 2012 Dridi Boukelmoune\n"
		"License FreeBSD: 2-clause BSD license <http://www.freebsd.org/copyright/freebsd-license.html>\n"
		"This is free software: you are free to change and redistribute it.\n"
		"There is NO WARRANTY, to the extent permitted by law.\n"
	, qs_version());
	return EXIT_SUCCESS;
}

