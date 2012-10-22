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

Name:           querysort
Version:        1.1.0
Release:        1%{?dist}
Summary(en_US): RFC 1866 querystring sorting library
Summary(fr_FR): Bibliothèque de tri de querystring de la RFC 1866

License:        FreeBSD
Group:          System Environment/Base
URL:            http://github.com/dridi/querysort
Source0:        %{name}-%{version}.tar.gz

Requires:       uriparser
BuildRequires:  uriparser-devel check-devel >= 0.9.5


%description -l en_US
QuerySort is an RFC 1866 compliant URI query-string sorting library written
in C. The QuerySort command line interface validates URIs with uriparser.
QuerySort is licensed under the FreeBSD license, and uriparser under the New BSD
license.


%description -l fr_FR
QuerySort est une bibliothèque de tri de query-string conforme à la RFC 1866,
écrite en C. L'interface en ligne de commande s'appuie sur uriparser pour
valider les URI à trier. QuerySort est distribué sous la licence FreeBSD, et
uriparser sous la licence New BSD.


%package lib
Summary(en_US): Library for %{name}
Summary(fr_FR): Bibliothèque pour %{name}
Group:          System Environment/Libraries


%description lib -l en_US
Library for QuerySort. QuerySort is an RFC 1866 compliant URI query-string
sorting library written in C.


%description lib -l fr_FR
Bibliothèque pour QuerySort. QuerySort est une bibliothèque de tri de
query-string conforme à la RFC 1866 et écrite en C.


%package devel
Summary(en_US): Header for %{name}
Summary(fr_FR): Header pour %{name}
Group:          System Environment/Libraries
Requires:       %{name}-lib = %{version}-%{release}
Autoreq:        no


%description devel -l en_US
Header for QuerySort. QuerySort is an RFC 1866 compliant URI query-string sorting
library written in C.


%description devel -l fr_FR
Header pour QuerySort. QuerySort est une bibliothèque de tri de query-string
conforme à la RFC 1866 et écrite en C.


%clean
%{__rm} -rf %{buildroot}
%{__make} clean


%prep
%setup -q
%configure


%build
%{__make} %{?_smp_mflags}


%check
%{__make} check


%install
%{__rm} -rf %{buildroot}
%{__make} DESTDIR=%{buildroot} install
%{__rm} -f %{buildroot}/%{_libdir}/lib%{name}.a
%{__rm} -f %{buildroot}/%{_libdir}/lib%{name}.la


%files
%{_bindir}/%{name}
%{_mandir}/man1/%{name}.1.gz
%doc LICENSE* CONTRIBUTORS CHANGELOG


%files lib
%{_libdir}/lib%{name}.so.*
%doc LICENSE* CONTRIBUTORS CHANGELOG


%files devel
%{_libdir}/lib%{name}_nonshared.a
%{_libdir}/lib%{name}.so
%{_mandir}/man3/%{name}.3.gz
%{_includedir}/%{name}.h
%doc LICENSE* CONTRIBUTORS CHANGELOG


%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig


%changelog
* Mon Oct 22 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.1-1
- Adapted the spec for autotools

* Thu Aug 30 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.1.0-1
- Bumped version to 1.1.0

* Tue Aug 28 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.1-1
- Added a brand new check section
- Bumped version to 1.0.1

* Sun Jul 29 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Minor changes

* Mon Jul 02 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Turned Autoreq off for the devel package
- This spec now builds and installs correctly on x86_64 architecture

* Tue Jun 12 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Added man pages files
- Switched to the makeinstall macro in the install scriptlet

* Mon Jun 11 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Added a lib package for the shared object only

* Tue Jun 05 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Added fr_FR summaries and descriptions

* Sun Jun 03 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Added shared object providing in the main package
- Added strict version for devel dependencies
- Uncommented project URL

* Sat May 26 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Added versionned shared objects
- Moved unversionned shared object to the devel package
- Moved post and postun from devel to the main package

* Wed May 23 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Moved header in a sub-directory

* Tue May 22 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Added uriparser requirement
- Added ldconfig execution in post and postun scriptlets
- Moved shared object from devel to the main package
- Added packages descriptions
- Added filenames instead of only generic directories

* Sat May 19 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Initial spec

