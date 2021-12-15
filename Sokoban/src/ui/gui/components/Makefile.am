include $(top_srcdir)/common.mk

noinst_LIBRARIES = libcomponents.a

libcomponents_a_SOURCES = Component.cpp Component.hpp
libcomponents_a_SOURCES += Container.cpp Container.hpp
libcomponents_a_SOURCES += Button.cpp Button.hpp
libcomponents_a_SOURCES += Label.cpp Label.hpp

libcomponents_a_CPPFLAGS = $(SFML_System_CFLAGS)
libcomponents_a_CPPFLAGS += $(SFML_Window_CFLAGS)
libcomponents_a_CPPFLAGS += $(SFML_Graphics_CFLAGS)
libcomponents_a_CPPFLAGS += $(SFML_Audio_CFLAGS)
libcomponents_a_CPPFLAGS += $(SFML_Network_CFLAGS)
libcomponents_a_CPPFLAGS += -DSFML_STATIC
