.. querysort - RFC 1866 querystring sorting library

   Copyright (C) 2012, Dridi Boukelmoune <dridi.boukelmoune@gmail.com>
   All rights reserved.

   Redistribution  and use in source and binary forms, with or without
   modification,  are permitted provided that the following conditions
   are met:

   1. Redistributions   of  source   code   must   retain  the   above
      copyright  notice, this  list of  conditions  and the  following
      disclaimer.
   2. Redistributions   in  binary  form  must  reproduce  the   above
      copyright  notice, this  list of  conditions and  the  following
      disclaimer   in  the   documentation   and/or  other   materials
      provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT  NOT
   LIMITED  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS
   FOR  A  PARTICULAR  PURPOSE ARE DISCLAIMED. IN NO EVENT  SHALL  THE
   COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
   INCIDENTAL,    SPECIAL,   EXEMPLARY,   OR   CONSEQUENTIAL   DAMAGES
   (INCLUDING,  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT  LIABILITY,  OR  TORT (INCLUDING  NEGLIGENCE  OR  OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
   OF THE POSSIBILITY OF SUCH DAMAGE.

=========
querysort
=========

------------------------------------
RFC 1866 querystring sorting library
------------------------------------

:Version: 1.1.0
:Manual section: 3

SYNOPSIS
========

::

    #include <querysort.h>

    enum {
        QS_OK,
        QS_ERROR,
        QS_CLEANED
    };

    char * qs_version();

    char * qs_sort_copy(const char*);

    int qs_sort(const char*, char*);
    int qs_sort_clean(const char*, char*);

    int qs_fsort(const char*, FILE*);
    int qs_fsort_clean(const char*, FILE*);

DESCRIPTION
===========

This page summarizes the functions provided by the querysort library.

char \* qs_version()
--------------------

Returns the current version of the library.

char \* qs_sort_copy(const char \*url)
--------------------------------------

Create a copy of the given *url* with its querystring sorted. The URI is assumed
to be valid. If the URI doesn't have a querystring, a simple copy is returned.

A returned non-NULL URI must be freed by the caller.

int qs_sort(const char \*url, char \*destination)
-------------------------------------------------

Writes the given *url* with its querystring sorted to the *destination*. The URI
is assumed to be valid. If the URI doesn't have a querystring, a simple copy is
made.


int qs_sort_clean(const char \*url, char \*destination)
-------------------------------------------------------

Writes the given *url* with its querystring sorted to the *destination*. The URI
is assumed to be valid. If the URI doesn't have a querystring, a simple copy is
made. This function discards empty parameters in the querystring, if any.

int qs_fsort(const char \*url, FILE \*stream)
---------------------------------------------

Writes the given *url* with its querystring sorted to the *stream*. The URI is
assumed to be valid. If the URI doesn't have a querystring, a simple copy is
made.


int qs_fsort_clean(const char \*url, FILE \*stream)
---------------------------------------------------

Writes the given *url* with its querystring sorted to the *stream*. The URI is
assumed to be valid. If the URI doesn't have a querystring, a simple copy is
made. This function discards empty parameters in the querystring, if any.

RETURN VALUE
============

| Functions that return pointers return **NULL** on error, and set errno to the corresponding error-code returned by functions returning an integer.
  Functions that return an integer return one of the following error codes:

QS_OK
-----
    The function succeeded.

QS_ERROR
--------
    An error occurred (see errno).

QS_CLEANED
----------
    The function succeeded but empty parameters where removed.

EXAMPLES
========

Basic invocation
----------------

::

    char *sorted_url = qs_sort_copy("http://localhost/?some=thing&an=other");
    if (sorted_url != NULL) {
        puts(sorted_url);
        free(sorted_url);
    }

Write to a file
---------------

::

    qs_fsort("http://localhost/?some=thing&an=other", stdout);

AUTHOR
======

Written by Dridi Boukelmoune.

COPYRIGHT
=========

| Copyright © 2012 Dridi Boukelmoune. License FreeBSD: BSD 2-clause license <**http://www.freebsd.org/copyright/freebsd-license.html**>.
  This is free software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law.

SEE ALSO
========

**querysort**\ (1)

