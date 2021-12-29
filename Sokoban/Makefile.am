include $(top_srcdir)/common.mk

ACLOCAL_AMFLAGS = -I m4 --install

SUBDIRS = src

bin_PROGRAMS = sokoban

sokoban_SOURCES = src/main.cpp src/main.hpp

sokoban_CPPFLAGS = $(BOOST_CPPFLAGS)
sokoban_CPPFLAGS += -DSFML_STATIC

sokoban_LDADD = src/ui/libui.la
sokoban_LDADD += $(top_srcdir)/libs/sokoban-linux/libsokoban_core.a
sokoban_LDADD += $(top_srcdir)/libs/util-linux/libutil_logger.a
sokoban_LDADD += $(top_srcdir)/libs/util-linux/libutil_serialize.a
sokoban_LDADD += src/ui/gui/libgui.la
sokoban_LDADD += src/ui/gui/states/libstates.la
sokoban_LDADD += src/ui/gui/components/libcomponents.a
sokoban_LDADD += src/ui/gui/entities/libentities.a
sokoban_LDADD += $(SFML_System_LIBS)
sokoban_LDADD += $(SFML_Window_LIBS)
sokoban_LDADD += $(SFML_Graphics_LIBS)
sokoban_LDADD += $(SFML_Audio_LIBS)
sokoban_LDADD += $(SFML_Network_LIBS)
sokoban_LDADD += $(BOOST_LDFLAGS)
sokoban_LDADD += $(BOOST_DATE_TIME_LIB)
sokoban_LDADD += $(BOOST_FILESYSTEM_LIB)
sokoban_LDADD += $(BOOST_LOCALE_LIB)
sokoban_LDADD += $(BOOST_LOG_LIB)
sokoban_LDADD += $(BOOST_LOG_SETUP_LIB)
sokoban_LDADD += $(BOOST_SYSTEM_LIB)
sokoban_LDADD += $(BOOST_THREAD_LIB)
