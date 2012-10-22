#
# querysort - RFC 1866 querystring sorting library
#
# Copyright (C) 2012, Dridi Boukelmoune <dridi.boukelmoune@gmail.com>
# All rights reserved.
#
# Redistribution  and use in source and binary forms, with or without
# modification,  are permitted provided that the following conditions
# are met:
#
# 1. Redistributions   of  source   code   must   retain  the   above
#    copyright  notice, this  list of  conditions  and the  following
#    disclaimer.
# 2. Redistributions   in  binary  form  must  reproduce  the   above
#    copyright  notice, this  list of  conditions and  the  following
#    disclaimer   in  the   documentation   and/or  other   materials
#    provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT  NOT
# LIMITED  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS
# FOR  A  PARTICULAR  PURPOSE ARE DISCLAIMED. IN NO EVENT  SHALL  THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL,    SPECIAL,   EXEMPLARY,   OR   CONSEQUENTIAL   DAMAGES
# (INCLUDING,  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT  LIABILITY,  OR  TORT (INCLUDING  NEGLIGENCE  OR  OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#

CFLAGS = --pedantic -Wall -std=c99 -O3 -DQS_VERSION=\"$(VERSION)\"

lib_LIBRARIES = libquerysort_nonshared.a
libquerysort_nonshared_a_SOURCES = querysort.c querysort.h
libquerysort_nonshared_a_CFLAGS = $(AM_FLAGS)

lib_LTLIBRARIES = libquerysort.la
libquerysort_la_SOURCES = querysort.c
libquerysort_la_LDFLAGS = -version-info 0:0:0

include_HEADERS = querysort.h

bin_PROGRAMS = querysort
querysort_SOURCES = querysort_main.c
querysort_LDFLAGS = -luriparser
querysort_LDADD = libquerysort_nonshared.a

