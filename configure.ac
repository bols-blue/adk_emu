#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT(Android_ADK_emulator, 0.1.0, bols-blue@lnc.jp)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([libusb_adk.c])
AC_CONFIG_HEADERS([config.h])
AC_CHECK_TOOL([RANLIB], [ranlib], [:])


# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(usb,usb_control_msg )

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset sleep])

dnl Some operating system include canna libraries by default.
dnl Use that pathname by default.
dnl for freebsd2.*, order DOES matter.  don't bother.
case "$host" in
	Linux-ubuntu)
		vi_cannapath="/usr/contrib/";;
	freebsd2.2*|freebsd3*)
		vi_cannapath="/usr/local";;
	freebsd2*)
		vi_cannapath="/usr/local/canna";;
	*)
		vi_cannapath="/usr/libusb-1.2.4.0";;
esac

if test "$vi_cannapath" != "yes"; then
	CFLAGS="-I$vi_cannapath/include $CFLAGS"
	LDFLAGS="-L$vi_cannapath/lib $LDFLAGS"
fi

dnl we use AC_TRY_COMPILE not AC_CHECK_HEADER, to avoid unnecessery
dnl use of CPPFLAGS. (why?)
AC_MSG_CHECKING(for usb.h)
AC_CACHE_VAL(vi_cv_cannahdrcheck, [dnl
				   AC_TRY_COMPILE([#include <usb.h>], struct libusb_device_handle* handle;,
						  [vi_cv_cannahdrcheck="yes"], [vi_cv_cannahdrcheck="no"])])
AC_MSG_RESULT($vi_cv_cannahdrcheck)
if test "$vi_cv_cannahdrcheck" = "no"; then
	echo -n "Fatal error: no libusb header in suggested path"
	if test "$vi_cannapath" != "yes"; then
		echo ", $vi_cannapath/include."
		echo "$host_os:$hostname:$ac_hostname:$host"
	else
		echo "."
	fi
	exit 1
fi

#AC_SEARCH_LIBS(sleep,c Kernel32,
#	     [sleep_libcheck="yes"], [sleep_libcheck="no"])
#if test "$sleep_libcheck" = "no"; then
#	echo "$hostname:$ac_hostname:$host"
#	echo "Fatal error: no sleep function"
#	exit 1
#fi

#AC_SEARCH_LIBS(usb_control_msg,libusb usb usb-1.0 libusb-1.0,
#	     [vi_cv_cannalibcheck="yes"], [vi_cv_cannalibcheck="no"])
#if test "$vi_cv_cannalibcheck" = "no"; then
#	echo "Fatal error: no usb library in suggested path"
#	if test "$vi_cannapath" != "yes"; then
#		echo ", $vi_cannapath/lib."
#		echo "$hostname:$ac_hostname:$host"
#	else
#		echo "."
#	fi
#	exit 1
#fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
