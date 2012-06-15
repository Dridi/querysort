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

CFLAGS=-std=c99 -pedantic -fPIC -D QS_VERSION=\"$(VERSION)\"
LDLIBS=-luriparser
LIB=lib$(PROJECT).so
EXEC=$(PROJECT) $(LIB).$(VERSION)
SRC=$(wildcard *.c)


all: build

install: all
	$(INSTALL_PROGRAM) -D $(PROJECT)        $(DESTDIR)$(bindir)/$(PROJECT)
	$(INSTALL_DATA) -s -D $(LIB).$(VERSION) $(DESTDIR)$(libdir)/$(LIB).$(VERSION)
	$(INSTALL_DATA)    -D $(PROJECT).h      $(DESTDIR)$(includedir)/$(PROJECT)/$(PROJECT).h
	ln -s $(LIB).$(VERSION)       $(DESTDIR)$(libdir)/$(LIB).$(VERSION_MAJOR)
	ln -s $(LIB).$(VERSION_MAJOR) $(DESTDIR)$(libdir)/$(LIB)

build: $(EXEC)

$(PROJECT): querysort_main.o $(LIB).$(VERSION)
	$(CC) $(LDLIBS) -o $@ $^

$(LIB).$(VERSION): $(PROJECT).o
	$(LD) -shared -soname $(LIB).$(VERSION_MAJOR) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(COMPILE.c) $< -o $@

.PHONY: clean mrproper

clean:
	$(RM) $(SRC:.c=.o)

mrproper: clean
	$(RM) $(EXEC)

