Name:           querysort
Version:        1.0
Release:        1%{?dist}
Summary:        RFC 1866 querystring sorting library

License:        FreeBSD
Group:          System Environment/Libraries
#URL:            
Source0:        %{name}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  uriparser-devel >= 0.7.5
#Requires:       uriparser

%description


%prep
%setup -q -n %{name}

%build
%{__make} build %{?_smp_mflags}


%install
#rm -rf %{buildroot}
#%{__make} install DESTDIR=%{buildroot}


%files
#%doc



%changelog

