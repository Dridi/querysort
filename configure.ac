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

AC_PREREQ(2.60)

AC_COPYRIGHT([Copyright (c) 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com>])
AC_INIT(querysort, 1.1.0, https://github.com/dridi/querysort/issues)

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

AC_USE_SYSTEM_EXTENSIONS

AC_LANG(C)

AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_STDC
if test "x$ac_cv_prog_cc_c99" = "xno" ; then
	AC_MSG_ERROR([Could not find a C99 compatible compiler])
fi

AC_PROG_LN_S
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET

AC_CHECK_PROGS(
	PYTHON,
	[python3 python3.1 python3.2 python2.7 python2.6 python2.5 python2 python],
	[AC_MSG_ERROR([Python is needed to build the manual pages.])]
)

AC_CHECK_PROGS(
	RST2MAN,
	[rst2man rst2man.py],
	[AC_MSG_ERROR([rst2man is needed to build the manual pages.])]
)

# Checks for header files.
AC_CHECK_HEADERS([check.h errno.h fcntl.h stdio.h stdlib.h string.h uriparser/Uri.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([fileno posix_fadvise strchr strerror])

AC_OUTPUT([Makefile src/Makefile man/Makefile test/Makefile])

