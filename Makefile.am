#test is skelton code 
bin_PROGRAMS=adk_init\
	     adk_com\
	     lsusb
#test_CFLAGS is test package C compiler option
#test_CXXFLAGS is test package C++ compiler option
#InitAccessoryMode_LDADD=libusb-1.0
#AccessoryDataCom_LDADD=libusb-1.0
#libtest_LIBRARIES is libtest package define
#libtest_a_SOURCES is libtest package source files
#test_SOURCES= is test package sourcefiles
adk_init_SOURCES=libusb_adk.c adk_init.c
lsusb_SOURCES=lsusb.c libusb_adk.c libusb_adk.h
#nodist_lsusb_HEADERS=libusb_adk.h
adk_com_SOURCES=libusb_adk.c adk_com.c
InitAccessoryMode_LDFULGS=-static-libgcc -static-libusb-1.0
