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

CC=gcc
CFLAGS=-std=c99 -pedantic -fPIC
LDFLAGS=-l uriparser
VERSION=0.0.0
LIBVERSION=$(shell echo '$(VERSION)' | cut -d . -f 1)
LIB=lib$(PROJECT).so
EXEC=$(PROJECT) $(LIB).$(VERSION)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)


all: build

install: all
	$(INSTALL) -d $(DESTDIR)$(bindir)/ $(DESTDIR)$(libdir)/ $(DESTDIR)$(includedir)/$(PROJECT)/
	$(INSTALL_PROGRAM) $(PROJECT)        $(DESTDIR)$(bindir)/
	$(INSTALL_DATA) -s $(LIB).$(VERSION) $(DESTDIR)$(libdir)/
	$(INSTALL_DATA)    $(PROJECT).h      $(DESTDIR)$(includedir)/$(PROJECT)/
	ln -s $(LIB).$(VERSION)    $(DESTDIR)$(libdir)/$(LIB).$(LIBVERSION)
	ln -s $(LIB).$(LIBVERSION) $(DESTDIR)$(libdir)/$(LIB)

build: $(EXEC)

$(PROJECT): querysort_main.o $(LIB).$(VERSION)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIB).$(VERSION): $(PROJECT).o
	ld -shared -soname $(LIB).$(LIBVERSION) -o $@ $^ -lc

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -f $(OBJ)

mrproper: clean
	@rm -f $(EXEC)

