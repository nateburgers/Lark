# Makefile

SOURCES   = src/applications/m_lrkbld/m_lrkbld.m.cpp
CPP_FLAGS = -std=c++14 -fno-use-linker-plugin

TASK=bake

all :
	$(CPP) $(CPP_FLAGS) -x c++ $(SOURCES) -o $(TASK)
