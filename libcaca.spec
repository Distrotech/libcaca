%define name  libcaca
%define version 0.6
%define release 1

Name: %{name}
Version: %{version}
Release: %{release}
URL: http://sam.zoy.org/projects/libcaca/
Source: http://sam.zoy.org/projects/libcaca/%{name}-%{version}.tar.bz2
License: GPL
Group: System/Libraries
Packager: Sam Hocevar (RPM packages) <sam+rpm@zoy.org>
BuildRoot: %{_tmppath}/%{name}-buildroot
Prefix: %{_prefix}
Buildrequires: XFree86-devel, ncurses-devel >= 5, slang-devel
Buildrequires: imlib2-devel
Buildrequires: doxygen, tetex-latex

Summary: Text mode graphics library
%description
libcaca is the Colour AsCii Art library. It provides high level functions
for colour text drawing, simple primitives for line, polygon and ellipse
drawing, as well as powerful image to text conversion routines.

%package -n %{name}-devel
Summary: Development files for libcaca
Group: Development/C
Requires: XFree86-devel, ncurses-devel >= 5, slang-devel
Provides: %{name}-devel = %{version}-%{release}
%description -n %{name}-devel
libcaca is the Colour AsCii Art library. It provides high level functions
for colour text drawing, simple primitives for line, polygon and ellipse
drawing, as well as powerful image to text conversion routines.

This package contains the header files and static libraries needed to
compile applications or shared objects that use libcaca.

%package -n caca-utils
Summary: Text mode graphics utilities
Group: Graphics
%description -n caca-utils
This package contains utilities and demonstration programs for libcaca, the
Colour AsCii Art library.

cacaview is a simple image viewer for the terminal. It opens most image
formats such as JPEG, PNG, GIF etc. and renders them on the terminal using
ASCII art. The user can zoom and scroll the image, set the dithering method
or enable anti-aliasing.

cacafire is a port of AALib's aafire and displays burning ASCII art flames.

cacademo is a simple application that shows the libcaca rendering features
such as line and ellipses drawing, triangle filling, and sprite blitting.

caca-spritedit is a simple sprite viewer for libcaca.

%prep
case "${RPM_COMMAND:-all}" in
all)
%setup -q
;;esac

%build
case "${RPM_COMMAND:-all}" in
all)
./configure --prefix=%{_prefix} \
  --libdir=%{_libdir} \
  --bindir=\${prefix}/bin \
  --mandir=\${prefix}/share/man \
  --infodir=\${prefix}/share/info \
  --enable-slang --enable-ncurses --enable-x11 --enable-imlib2
;;esac
make 

%install
rm -rf %{buildroot}
%makeinstall
mv %{buildroot}/%{_prefix}/share/doc/libcaca-dev %{buildroot}/%{_prefix}/share/doc/libcaca-devel
mkdir %{buildroot}/%{_prefix}/share/doc/caca-utils
cp `find %{buildroot}/%{_prefix}/share/doc/libcaca-devel/ -name '[A-Z]*'` %{buildroot}/%{_prefix}/share/doc/caca-utils/

%clean
rm -rf %{buildroot}

%files -n %{name}-devel
%defattr(-,root,root)
%{_libdir}/*
%{_prefix}/bin/caca-config
%{_prefix}/include/*
%{_prefix}/share/doc/libcaca-devel/*
%{_prefix}/share/man/man1/caca-config.1*
%{_prefix}/share/man/man3/*

%files -n caca-utils
%defattr(-,root,root)
%{_prefix}/bin/cacademo
%{_prefix}/bin/cacafire
%{_prefix}/bin/cacaview
%{_prefix}/bin/caca-spritedit
%{_prefix}/share/doc/caca-utils/*
%{_prefix}/share/libcaca/*
%{_prefix}/share/man/man1/cacademo.1*
%{_prefix}/share/man/man1/cacafire.1*
%{_prefix}/share/man/man1/cacaview.1*
%{_prefix}/share/man/man1/caca-spritedit.1*

%changelog
* Sat Jan 3 2004 Sam Hocevar (RPM packages) <sam+rpm@zoy.org> 0.6-1
- new release

* Mon Dec 29 2003 Richard Zidlicky <rz@linux-m68k.org> 0.5-1
- created specfile

