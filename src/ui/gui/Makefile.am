SUBDIRS = entities components states

noinst_LTLIBRARIES = libgui.la

libgui_la_SOURCES = Animation.cpp Animation.hpp
libgui_la_SOURCES += Application.cpp Application.hpp
libgui_la_SOURCES += Music_Player.cpp Music_Player.hpp
libgui_la_SOURCES += Resource_Identifiers.hpp
libgui_la_SOURCES += Scene_Node.cpp Scene_Node.hpp
libgui_la_SOURCES += Sound_Node.cpp Sound_Node.hpp
libgui_la_SOURCES += Sound_Player.cpp Sound_Player.hpp
libgui_la_SOURCES += Sprite_Node.cpp Sprite_Node.hpp
libgui_la_SOURCES += Utility.cpp Utility.hpp
libgui_la_SOURCES += ../Utility.inl
libgui_la_SOURCES += World.cpp World.hpp

libgui_la_CPPFLAGS = $(SFML_System_CFLAGS)
libgui_la_CPPFLAGS += $(SFML_Window_CFLAGS)
libgui_la_CPPFLAGS += $(SFML_Graphics_CFLAGS)
libgui_la_CPPFLAGS += $(SFML_Audio_CFLAGS)
libgui_la_CPPFLAGS += $(SFML_Network_CFLAGS)
libgui_la_CPPFLAGS += -DSFML_STATIC

libgui_la_LIBADD = entities/libentities.a
libgui_la_LIBADD += states/libstates.la
libgui_la_LIBADD += components/libcomponents.a
