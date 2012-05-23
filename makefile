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

export PROJECT=querysort
export INSTALL=install
export INSTALL_PROGRAM=$(INSTALL)
export INSTALL_DATA=$(INSTALL) -m 644

export bindir=/usr/bin
export libdir=/usr/lib
export includedir=/usr/include

MAKE_SRC=$(MAKE) -C src $@

RPMBUILD=rpmbuild
RPMFLAGS=

all: build

install: all mkinstalldirs
	$(MAKE_SRC)

mkinstalldirs:
	mkdir -p $(DESTDIR)$(bindir)
	mkdir -p $(DESTDIR)$(libdir)
	mkdir -p $(DESTDIR)$(includedir)

build:
	$(MAKE_SRC)

rpm: dist
	$(RPMBUILD) -bb rpm/$(PROJECT)-i386.spec $(RPMFLAGS) --define "_sourcedir $(shell pwd)"

dist: $(PROJECT).tar.gz

%.tar.gz:
	@git archive -o $@ --prefix=$*/ HEAD

.PHONY: clean mrproper

clean:
	$(MAKE_SRC)

cleandist:
	@rm -f $(PROJECT).tar.gz

mrproper: clean cleandist
	$(MAKE_SRC)

