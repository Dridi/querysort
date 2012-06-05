Name:           querysort
Version:        1.0.0
Release:        1%{?dist}
Summary(en_US): RFC 1866 querystring sorting library
Summary(fr_FR): Bibliothèque de tri de querystring de la RFC 1866

License:        FreeBSD
Group:          System Environment/Base
URL:            http://github.com/dridi/querysort
Source0:        %{name}.tar.gz

Provides:       libquerysort.so.1 = %{version}-%{release}
Requires:       uriparser >= 0.7.5
BuildRequires:  uriparser-devel >= 0.7.5


%description -l en_US
QuerySort is an RFC 1866 compliant URI query-string sorting library written
in C. The QuerySort library comes with a command line program, which validates
first URIs with uriparser. QuerySort is licensed under the FreeBSD license, and
uriparser under the New BSD license.


%description -l fr_FR
QuerySort est une bibliothèque de tri de query-string conforme à la RFC 1866. La
bibliothèque, écrite en C, s'accompagne d'un programme en ligne de commande qui
valide en amont les URI à l'aide d'uriparser. QuerySort est distribué sous la
licence FreeBSD, et uriparser sous la licence New BSD.


%package devel
Summary(en_US): Header for %{name}
Summary(fr_FR): Header pour %{name}
Group:          System Environment/Libraries
Requires:       %{name} = %{version}-%{release}


%description devel -l en_US
Header for QuerySort. QuerySort is an RFC 1866 compliant URI query-string sorting
library written in C.


%description devel -l fr_FR
Header pour QuerySort. QuerySort est une bibliothèque de tri de query-string
conforme à la RFC 1866 et écrite en C.


%clean
rm -rf %{buildroot}
%{__make} mrproper


%prep
%setup -q -n %{name}


%build
%{__make} build VERSION=%{version} %{?_smp_mflags}


%install
rm -rf %{buildroot}
%{__make} install DESTDIR=%{buildroot} VERSION=%{version}


%files
%{_bindir}/%{name}
%{_libdir}/lib%{name}.so.*
%doc LICENSE


%files devel
%{_libdir}/lib%{name}.so
%{_includedir}/%{name}/


%post -p /sbin/ldconfig


%postun -p /sbin/ldconfig


%changelog
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
- Added ldconfig execution in post and postun macros
- Moved shared object from devel to the main package
- Added packages descriptions
- Added filenames instead of only generic directories

* Sat May 19 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0.0-1
- Initial spec

