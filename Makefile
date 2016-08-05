# Makefile                                                        -*-GNUMake-*-

#@PURPOSE:
#
#@SEE_ALSO:
#
#@DESCRIPTION:
#

SOURCE_DIR = devsrc
BUILD_DIR  = build
OBJECT_DIR = build/objects

HEADER_FILES = $(wildcard $(SOURCE_DIR)/*.h)
SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
TEST_FILES   = $(wildcard $(SOURCE_DIR)/*.t.cpp)

HEADER_NAMES = $(foreach HEADER_FILE, $(HEADER_FILES), \
			             $(patsubst $(SOURCE_DIR)/%, %, $(HEADER_FILE)))
SOURCE_NAMES = $(foreach SOURCE_FILE, $(SOURCE_FILES), \
			             $(patsubst $(SOURCE_DIR)/%, %, $(SOURCE_FILE)))
TEST_NAMES   = $(foreach TEST_FILE,   $(TEST_FILES  ), \
			             $(patsubst $(SOURCE_DIR)/%, %, $(TEST_FILE  )))
OBJECT_NAMES = $(foreach SOURCE_NAME, $(SOURCE_NAMES), \
			             $(patsubst %.cpp, %.o, $(SOURCE_NAME)))

OBJECT_FILES = $(foreach OBJECT_NAME, $(OBJECT_NAMES), \
			             $(patsubst %, $(OBJECT_DIR)/%, $(OBJECT_NAME)))

CPP_COMPILER       = gcc-6
CPP_COMPILER_FLAGS = -I$(SOURCE_DIR) \
					 -nostdlib       \
					 -fno-exceptions \
					 -fno-rtti       \
					 -std=c++14      \
					 -Wall           \
					 -Werror

all : $(OBJECT_FILES)

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(OBJECT_DIR) : $(BUILD_DIR)
	mkdir -p $(OBJECT_DIR)

$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.h $(OBJECT_DIR)
	$(CPP_COMPILER) $(CPP_COMPILER_FLAGS) -c $< -o $@
