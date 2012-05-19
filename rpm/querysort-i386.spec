Name:           querysort
Version:        1.0
Release:        1%{?dist}
Summary:        RFC 1866 querystring sorting program

License:        FreeBSD
Group:          System Environment/Base
#URL:            http://github.com/dridi/querysort
Source0:        %{name}.tar.gz

BuildRequires:  uriparser-devel >= 0.7.5


%description


%package devel
Summary:        Library for %{name}
Group:          System Environment/Libraries
Requires:       %{name}


%description devel


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
%doc LICENSE


%files devel
%{_libdir}
%{_includedir}


%changelog


