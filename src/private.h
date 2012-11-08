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

#include <stdio.h>
#include <stdbool.h>

struct query_param {
	const char *value;
	short length;
};

struct query_sort {
	const char *url;
	const char *query_string;
	bool clean;
	void *destination;
	int count;
	struct query_param *params;
	void (*copy)   (struct query_sort*, const char*, size_t);
	void (*append) (struct query_sort*, const char*);
};

static int  sort(const char*, char*, bool);
static int fsort(const char*, FILE*, bool);

static void   copy_string(struct query_sort*, const char*, size_t);
static void append_string(struct query_sort*, const char*);

static void   fcopy_string(struct query_sort*, const char*, size_t);
static void fappend_string(struct query_sort*, const char*);

static       int      sort_query(struct query_sort*);
static       void   search_query(struct query_sort*);
static       void   count_params(struct query_sort*);
static const char* search_params(struct query_sort*);
static       bool  append_params(struct query_sort*);

static int compare_params(const void*, const void*);

