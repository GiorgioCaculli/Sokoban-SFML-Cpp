include $(top_srcdir)/common.mk

AM_LDFLAGS = $(BOOST_LDFLAGS)

noinst_LIBRARIES = libutil.a

libutil_a_SOURCES = Logger.cpp Logger.hpp

libutil_a_CPPFLAGS = $(BOOST_CPPFLAGS)
libutil_a_CPPFLAGS += -DBOOST_ALL_NO_LIB
libutil_a_CPPFLAGS += -DBOOST_ALL_DYN_LINK
libutil_a_CPPFLAGS += -DBOOST_LOG_DYN_LINK


