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

#include<stdlib.h>
#include<string.h>

#include "querysort.h"

// End Of QueryString
#define EOQS(c) (c == '\0' || c == '#')

char *
querysort(const char *url)
{
	char *sorted_url = malloc(strlen(url) + 1);
	
	if (sorted_url == NULL) {
		return NULL;
	}
	
	strcpy(sorted_url, url);
	char *query_string = strchr(sorted_url, '?');

	if(query_string != NULL && ! EOQS(query_string[1])) {
		int position = &query_string[1] - sorted_url;
		sort_params(url, position, sorted_url);
	}

	return sorted_url;
}

static void
sort_params(const char *url, const int position, char *sorted_url)
{
	int count = count_params(url, position);
	param params[count];
	search_params(&url[position], count, params);
	qsort(params, count, sizeof(param), compare_params);
	apply_params(params, count, sorted_url, position);
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
search_params(const char *query_string, const int count, param params[])
{
	int i = 0, p = 0;
	do {
		params[p].value = &query_string[i];
		params[p].length = 0;
		
		while (query_string[i] != '&' && ! EOQS(query_string[i])) {
			params[p].length++;
			i++;
		}
		
		p++;
		i += (query_string[i] == '&');
	} while ( ! EOQS(query_string[i]) );
}

static int
compare_params(const void *a, const void *b)
{
	const param *x = (const param *) a;
	const param *y = (const param *) b;
	
	int min_length = (x->length < y->length) ? x->length : y->length;
	int compare = strncmp(x->value, y->value, min_length);
	return (compare == 0) ? x->length - y->length : compare;
}

static void
apply_params(const param params[], const int count, char *sorted_url, int position)
{
	for (int p = 0; p < count; p++) {
		memcpy(&sorted_url[position], params[p].value, params[p].length);
		position += params[p].length;
		
		if (! EOQS(sorted_url[position]) ) {
			sorted_url[position++] = '&';
		}
	}
}

