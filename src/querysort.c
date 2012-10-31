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

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "private.h"
#include "querysort.h"

#ifndef QS_VERSION
#  define QS_VERSION "dev"
#endif

/* extern functions */

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
	
	struct query_sort qs;
	
	qs.url = url;
	qs.clean = false;
	qs.destination = sorted_url;
	qs.copy = &copy_string;
	qs.append = &append_string;
	
	sort_query(&qs);
	
	return QS_OK;
}

extern int
qs_sort_clean(const char *url, char *sorted_url)
{
	if (url == NULL || sorted_url == NULL) {
		errno = EFAULT;
		return QS_ERROR;
	}
	
	struct query_sort qs;
	
	qs.url = url;
	qs.clean = true;
	qs.destination = sorted_url;
	qs.copy = &copy_string;
	qs.append = &append_string;
	
	sort_query(&qs);
	
	return QS_OK;
}

/* static functions */

static void
copy_string(struct query_sort *qs, const char *source, size_t length) {
	char *destination = (char*) qs->destination;
	strncpy(destination, source, length);
	qs->destination = &destination[length];
}

static void
append_string(struct query_sort *qs, const char *source) {
	char *destination = (char*) qs->destination;
	strcpy(destination, source);
	qs->destination = &destination[ strlen(source) ];
}


static void
sort_query(struct query_sort *qs)
{
	search_query(qs);

	if (qs->query_string == NULL) {
		qs->append(qs, qs->url);
		return;
	}
	
	qs->copy(qs, qs->url, qs->query_string - qs->url);

	if( EOQS(qs->query_string[0]) ) {
		// no params, append the end of the url
		qs->append(qs, qs->query_string);
	}
	else {
		/* count query parameters... */
		count_params(qs);
		
		/* ...in order to allocate an array on the stack */
		struct query_param params[qs->count];
		qs->params = params;
		
		/* search and sort the parameters */
		const char *eoqs = search_params(qs);
		qsort(params, qs->count, sizeof(struct query_param), compare_params);
		
		/* append the sorted parameters and the end of the url */
		append_params(qs);
		qs->append(qs, eoqs);
	}
}

static void
search_query(struct query_sort *qs)
{
	const char *url = qs->url;
	while ( ! EOQS(*url) ) {
		if (*url == '?') {
			qs->query_string = url + 1;
			return;
		}
		url++;
	}
	qs->query_string = NULL;
}

static void
count_params(struct query_sort *qs)
{
	qs->count = 1;
	for (const char *c = qs->query_string; ! EOQS(*c); c++) {
		qs->count += (*c == '&');
	}
}

static const char*
search_params(struct query_sort *qs)
{
	/* This function is responsible for tokenizing query_string. It fills
	 * indexes [0...count) in the params array with value and length.
	 * This function requires that count >= 1. */
	const char *value_start = qs->query_string;
	const char *c;
	int p = 0;
	for (c = value_start; ! EOQS(*c); c++) {
		if (*c == '&') {
			qs->params[p].value = value_start;
			qs->params[p].length = c - value_start;
			value_start = c + 1;
			p++;
		}
	}
	qs->params[p].value = value_start;
	qs->params[p].length = c - value_start;
	return c;
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

static void
append_params(struct query_sort *qs)
{
	bool add_separator = false;
	for (int p = 0; p < qs->count; p++) {
		if (qs->clean && qs->params[p].length == 0) {
			continue;
		}
		if (add_separator) {
			qs->append(qs, "&");
		}
		qs->copy(qs, qs->params[p].value, qs->params[p].length);
		add_separator = true;
	}
}

