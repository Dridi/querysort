Name:           querysort
Version:        1.0
Release:        1%{?dist}
Summary:        RFC 1866 querystring sorting library

License:        FreeBSD
Group:          System Environment/Base
#URL:            http://github.com/dridi/querysort
Source0:        %{name}.tar.gz

Requires:       uriparser >= 0.7.5
BuildRequires:  uriparser-devel >= 0.7.5


%description
QuerySort is an RFC 1866 compliant URI querystring sorting library written
in C. The QuerySort library comes with a command line program, which validates
first URIs with uriparser. QuerySort is licensed under the FreeBSD license, and
uriparser under the New BSD license.


%package devel
Summary:        Header for %{name}
Group:          System Environment/Libraries


%description devel
Header for QuerySort. QuerySort is an RFC 1866 compliant URI querystring sorting
library written in C.


%clean
rm -rf %{buildroot}
%{__make} mrproper


%prep
%setup -q -n %{name}


%build
%{__make} build %{?_smp_mflags}


%install
rm -rf %{buildroot}
%{__make} install DESTDIR=%{buildroot}


%files
%{_bindir}
%{_libdir}
%doc LICENSE


%files devel
%{_includedir}


%post devel -p /sbin/ldconfig


%postun devel -p /sbin/ldconfig


%changelog
* Tue May 22 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0
- Added uriparser requirement
- Added ldconfig execution in post and postun macros
- Moved shared object from devel to the main package
- Added packages descriptions

* Sat May 19 2012 Dridi Boukelmoune <dridi.boukelmoune@gmail.com> - 1.0
- Initial spec

