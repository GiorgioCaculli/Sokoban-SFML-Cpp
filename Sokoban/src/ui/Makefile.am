include $(top_srcdir)/common.mk

SUBDIRS = gui

noinst_LTLIBRARIES = libui.la

libui_la_SOURCES = Menu.cpp Menu.hpp
libui_la_SOURCES += Category.hpp
libui_la_SOURCES += Resource_Holder.hpp
libui_la_SOURCES += Resource_Holder.inl

libui_la_LIBADD = gui/libgui.la
