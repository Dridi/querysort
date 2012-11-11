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

#ifndef _QUERYSORT_H
#define _QUERYSORT_H	1

#include <stdio.h>
#include <features.h>

__BEGIN_DECLS

// End Of QueryString
#define EOQS(c) (c == '\0' || c == '#')

/**
 * Return values for querysort functions.
 */
enum {
	QS_OK,
	QS_ERROR,
	QS_CLEANED
};

/**
 * Create a copy of the given URI with its querystring sorted. The URI is
 * assumed to be valid. If the URI doesn't have a querystring, a simple copy is
 * returned.
 * 
 * A returned non-NULL URI must be freed by the caller.
 * 
 * @param uri the given URI to sort
 */
char *
qs_sort_copy(const char *uri);

/**
 * Writes the given URI with its querystring sorted to the destination. The URI
 * is assumed to be valid. If the URI doesn't have a querystring, a simple copy
 * is made.
 * 
 * @param uri the given URI to sort
 * @param destination the placeholder for the sorted URI
 */
int
qs_sort(const char *uri, char *destination);

/**
 * Writes the given URI with its querystring sorted to the destination. The URI
 * is assumed to be valid. If the URI doesn't have a querystring, a simple copy
 * is made. This function discards empty parameters in the querystring, if any.
 * 
 * This function returns QS_CLEANED when it succeeds but had to remove empty
 * parameters.
 * 
 * @param uri the given URI to sort
 * @param destination the placeholder for the sorted URI
 */
int
qs_sort_clean(const char *uri, char *destination);

/**
 * Writes the given URI with its querystring sorted to the stream. The URI is
 * assumed to be valid. If the URI doesn't have a querystring, a simple copy is
 * made.
 * 
 * @param uri the given URI to sort
 * @param stream the stream where the sorted URI is appened
 */
int
qs_fsort(const char *uri, FILE *stream);

/**
 * Writes the given URI with its querystring sorted to the stream. The URI is
 * assumed to be valid. If the URI doesn't have a querystring, a simple copy is
 * made. This function discards empty parameters in the querystring, if any.
 * 
 * This function returns QS_CLEANED when it succeeds but had to remove empty
 * parameters.
 * 
 * @param uri the given URI to sort
 * @param stream the stream where the sorted URI is appened
 */
int
qs_fsort_clean(const char *uri, FILE *stream);

/**
 * Returns the current version of the library.
 */
char *
qs_version();

__END_DECLS

#endif // _QUERYSORT_H

