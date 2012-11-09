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
:Manual section: 1

SYNOPSIS
========

| **querysort** [-nv] *URI*
  **querysort** [-dnv] [-f *FILE*]
  **querysort** --version
  **querysort** --help

DESCRIPTION
===========

Sort the fields of an URI's querystring in compliance with the RFC 1866. The RFC
3986 defines the form of a URI, but not the form of a URI's query. What
QuerySort sorts is the fields of an \`application/x-www-form-urlencoded' query,
a form, as defined in HTML 2.0 RFC 1866. Any other part of the URI is kept
untouched.

It is a common case that the fields order of a query string is not relevant.
What usually matter is the key/value aspect of the query, and therefore the
values of the keys. If you manipulate URLs, a query and its fields permutations
might actually point to the same resource.

Mandatory arguments to long options are mandatory for short options too.

**\-d**,
**--delimiter**\=\ *DELIM*

 use *DELIM* instead of EOL for field delimiter

**\-f**,
**--file**\=\ *FILE*

 read URIs from *FILE*

**-n**, **--no-clean**

 do not discard empty parameters in URIs

**-v**, **--verbose**

 provide more detailed information

| 
| You can use a delimiter only when reading URIs from a file.
  With no URI, or when FILE is -, read standard input.

EXAMPLES
========

You can use querysort in two modes, the first one sorts a single URI from the
command line, the other one sorts a batch of URIs from a file.

Using the command line
----------------------

| $ **querysort** *'localhost/?some=thing&an=other'*
  localhost/?an=other&some=thing

| $ **querysort** *localhost/?*
  localhost/?

| $ **querysort** *'localhost/?some=thing&an=other#fragment'*
  localhost/?an=other&some=thing#fragment

Reading from a file
-------------------

You can for instance read a URI from the standard input.

| 
| $ **echo** *'localhost/?some=thing&an=other'* | **querysort**
  localhost/?an=other&some=thing

It is also possible to read multiple URIs from a file, the default delimiter is
the **EOL** character.

| 
| $ **echo** -e *'localhost/?a&b\\nlocalhost/?b&a'* | **querysort**
  localhost/?a&b
  localhost/?a&b

AUTHOR
======

Written by Dridi Boukelmoune.

COPYRIGHT
=========

| Copyright © 2012 Dridi Boukelmoune. License FreeBSD: BSD 2-clause license <**http://www.freebsd.org/copyright/freebsd-license.html**>.
  This is free software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law.

NOTES
=====

| The QuerySort command line interface uses **uriparser** for URI validation.
  The **uriparser** project <**http://uriparser.sourceforge.net/**> is distributed under the New BSD license.

