# Makefile for Thriving colony
# Created by Mario Gonzalez and Julian Garcia

# Name of the executable created
TARGET = libaabbtree.so
# Project root
PROJECTROOT = .
# Path for the executable
BINPATH = bin
# Path for the .o files
BUILDPATH = obj
# Path for the source files
SOURCEPATHS = src
#C++ compiler
CXX = clang++
#C++ debugger
DBG = lldb

####
# FLAGS
####
# Include paths
CPPFLAGS = -I/usr/include -I$(PROJECTROOT)/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
# Compiler params
CPPFLAGS += -g -Wall -MMD -MP -D_CRT_SECURE_NO_WARNINGS -DDEBUG -std=c++11 -fPIC
# Lib paths
LDFLAGS = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/X11 -L$(PROJECTROOT)/lib -Wl,-R -Wl,$(PROJECTROOT)/lib
# Libs
LIBS = -lm

######## DON'T EDIT ANYTHING BELOW THIS LINE
EXECUTABLE := $(BINPATH)/$(TARGET)

rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRC_DIRS := $(foreach DIR,$(SOURCEPATHS),$(shell find $(DIR) -type d))
OBJ_DIRS := $(foreach DIR,$(SOURCEPATHS),$(patsubst %, $(BUILDPATH)/%,$(shell find $(DIR) -type d ! -path .)))

SRC_FILES := $(foreach DIR,$(SRC_DIRS),$(wildcard $(DIR)/*.cpp))
OBJ_FILES := $(foreach FILE,$(SRC_FILES),$(patsubst %.cpp, $(BUILDPATH)/%.o, $(FILE)))

INCLUDE_DIRS := $(foreach DIR,$(SOURCEPATHS),$(patsubst %, -I%, $(DIR)))
CPPFLAGS += $(INCLUDE_DIRS)

#MAKE OPTIONS
.PHONY: all run debug clean cleanfolder

all: $(BUILDPATH) $(OBJ_FILES)
	$(info =================================)
	$(info Creando el ejecutable $(Target)...)
	$(info =================================)
	gcc -shared $(OBJ_FILES) -o $(EXECUTABLE)
#	@$(CXX) $(CPPFLAGS) $(OBJ_FILES) -o $(EXECUTABLE) $(LDFLAGS) $(LIBS)
    
$(BUILDPATH)/%.o: %.cpp
	$(info Creando el binario para el archivo $<...)
	@$(CXX) $(CPPFLAGS) -c $< -o $@

$(BUILDPATH):
	$(info =================================)
	$(info Creando la estructura de carpetas...)
	$(info =================================)
	@mkdir -p $(OBJ_DIRS)
	@mkdir -p $(BINPATH)

clean:
	$(info =================================)
	$(info Limpiando todo el proyecto...)
	$(info =================================)
	@$(RM) $(EXECUTABLE)
	@$(RM) -r $(OBJ_DIRS)
	@$(RM) -r $(BUILDPATH)

cleanfolder:
	$(info =================================)
	$(info Limpiando la carpeta $(FOLDER)...)
	$(info =================================)
	@$(RM) $(EXECUTABLE)
	@$(RM) -r $(BUILDPATH)/$(FOLDER)

run: all
	$(info =================================)
	$(info Ejecutando...)
	$(info =================================)
	@$(EXECUTABLE)

debug: all
	$(info =================================)
	$(info Ejecutando...)
	$(info =================================)
	@$(DBG) $(EXECUTABLE)
