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
#include<stdlib.h>
#include<string.h>

#include "querysort.h"

#ifndef QS_VERSION
#  define QS_VERSION "dev"
#endif

// End Of QueryString
#define EOQS(c) (c == '\0' || c == '#')

struct query_param {
	const char *value;
	short length;
};

static const char* search_query(const char *url);
static int          search_eoqs(const char *url, int position);

static int    sort_params(const char *url, const int position, char *sorted_url);
static int   count_params(const char *url, const int position);
static void search_params(const char *query_string, const int count, struct query_param params[]);
static int compare_params(const void *a, const void *b);
static int   apply_params(const struct query_param params[], const int count, char *sorted_url, int position);

extern char *
qs_version()
{
	return QS_VERSION;
}

extern char *
qs_sort_copy(const char *url)
{
	if (url == NULL) {
		errno = EFAULT;
		return NULL;
	}
	
	char *sorted_url = malloc(strlen(url) + 1);

	if (sorted_url == NULL) {
		return NULL;
	}

	if (qs_sort(url, sorted_url) != QS_OK) {
		free(sorted_url);
		return NULL;
	}

	return sorted_url;
}

extern int
qs_sort(const char *url, char *sorted_url)
{
	if (url == NULL || sorted_url == NULL) {
		errno = EFAULT;
		return QS_ERROR;
	}

	strcpy(sorted_url, url);
	const char *query_string = search_query(sorted_url);

	if(query_string != NULL && ! EOQS(query_string[1])) {
		int position = &query_string[1] - sorted_url;
		sort_params(url, position, sorted_url);
	}

	return QS_OK;
}

extern int
qs_sort_clean(const char *url, char *sorted_url)
{
	if (url == NULL || sorted_url == NULL) {
		errno = EFAULT;
		return QS_ERROR;
	}

	const char *query_string = search_query(url);

	if (query_string == NULL) {
		strcpy(sorted_url, url);
		return QS_OK;
	}
	
	int position = &query_string[1] - url;
	strncpy(sorted_url, url, position);

	if(query_string != NULL && ! EOQS(query_string[1])) {
		position = sort_params(url, position, sorted_url);
		sorted_url[position] = '\0';
	}
	else {
		sorted_url[position] = '\0';
	}
	
	int eoqs_position = search_eoqs(url, position);
	
	while (sorted_url[position - 1] == '&') {
		sorted_url[position - 1] = '\0';
		position--;
	}
	
	if (url[eoqs_position] == '#') {
		strcpy(&sorted_url[position], &url[eoqs_position]);
	}

	return QS_OK;
}

static const char*
search_query(const char *url)
{
	while ( ! EOQS(*url) ) {
		if (*url == '?') {
			return url;
		}
		url++;
	}
	return NULL;
}


static int
search_eoqs(const char *url, int position)
{
	while ( ! EOQS(url[position]) ) {
		position++;
	}
	return position;
}

static int
sort_params(const char *url, const int position, char *sorted_url)
{
	int count = count_params(url, position);
	struct query_param params[count];

	search_params(&url[position], count, params);
	qsort(params, count, sizeof(struct query_param), compare_params);
	return apply_params(params, count, sorted_url, position);
}

static int
count_params(const char *url, const int position)
{
	int count = 1;
	for (int i = position; ! EOQS(url[i]); i++) {
		count += (url[i] == '&');
	}
	return count;
}

static void
search_params(const char *query_string, const int count, struct query_param params[])
{
   /* This function is responsible for tokenizing query_string.  It fills
    * indexes [0...count) in the params array with value and length.
    * This function requires that count >= 1. */
    const char* value_start = query_string;
    const char* ch;
    int p = 0;
    for (ch = query_string; !EOQS(*ch); ++ch) {
        if (*ch == '&') {
            params[p].value = value_start;
            params[p].length = ch - value_start;
            value_start = ch + 1;
            ++p;
        }
    }
    params[p].value = value_start;
    params[p].length = ch - value_start;
}

static int
compare_params(const void *a, const void *b)
{
	const struct query_param *x = (const struct query_param *) a;
	const struct query_param *y = (const struct query_param *) b;
	
	if (x->length == 0 || y->length == 0) {
		return y->length - x->length;
	}
	
	int min_length = (x->length < y->length) ? x->length : y->length;
	int compare = strncmp(x->value, y->value, min_length);
	return (compare == 0) ? x->length - y->length : compare;
}

static int
apply_params(const struct query_param params[], const int count, char *sorted_url, int position)
{
	for (int p = 0; p < count; p++) {
		if (p > 0) {
			sorted_url[position++] = '&';
		}
		
		memcpy(&sorted_url[position], params[p].value, params[p].length);
		position += params[p].length;
	}
	return position;
}

