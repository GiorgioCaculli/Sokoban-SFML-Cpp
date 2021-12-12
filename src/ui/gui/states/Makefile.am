noinst_LTLIBRARIES = libstates.la

libstates_la_SOURCES = State.cpp State.hpp
libstates_la_SOURCES += State_Game.cpp State_Game.hpp
libstates_la_SOURCES += State_Menu.cpp State_Menu.hpp
libstates_la_SOURCES += State_Pause.cpp State_Pause.hpp
libstates_la_SOURCES += State_Settings.cpp State_Settings.hpp
libstates_la_SOURCES += State_Title.cpp State_Title.hpp
libstates_la_SOURCES += State_Stack.cpp State_Stack.hpp
libstates_la_SOURCES += State_Identifiers.hpp

libstates_la_CPPFLAGS = $(SFML_System_CFLAGS)
libstates_la_CPPFLAGS += $(SFML_Window_CFLAGS)
libstates_la_CPPFLAGS += $(SFML_Graphics_CFLAGS)
libstates_la_CPPFLAGS += $(SFML_Audio_CFLAGS)
libstates_la_CPPFLAGS += $(SFML_Network_CFLAGS)
libstates_la_CPPFLAGS += -DSFML_STATIC

libstates_la_LIBADD = ../components/libcomponents.a
