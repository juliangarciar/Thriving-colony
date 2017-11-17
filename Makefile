# Makefile for Thriving colony
# Created by Mario Gonzalez and Julian Garcia

# Name of the executable created
TARGET = ThrivingColony
# Path for the executable
BINPATH = bin
# Path for the .o files
BUILDPATH = obj
# Path for the source files
SOURCEPATH = src
#Directories
SOURCE_DIRS = . graphics IA

####
# FLAGS
####
# Include paths
CPPFLAGS = -I/usr/include -I/usr/local/include -I/usr/local/include/irrlicht
# Compiler params
CXXFLAGS = -O3 -ffast-math -g -Wall
# Lib paths
LDFLAGS = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/X11 -L/usr/local/lib
# Libs
LIBS = -lGL -lXxf86vm -lXext -lX11 -lXcursor -lIrrlicht

######## DON'T EDIT ANYTHING BELOW THIS LINE
EXECUTABLE = $(BINPATH)/$(TARGET)
SRC := $(foreach DIR,$(SOURCE_DIRS),$(wildcard $(SOURCEPATH)/$(DIR)/*.cpp))
OBJ_DIRS := $(foreach DIR,$(SOURCE_DIRS),$(patsubst %, $(BUILDPATH)/%, $(DIR)))
OBJ := $(patsubst $(SOURCEPATH)/%.cpp, $(BUILDPATH)/%.o, $(SRC))

#MAKE OPTIONS
.PHONY: all clean

all: prepare $(OBJ)
	$(warning Creando el ejecutable $(Target)...)
	
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $(OBJ) -o $(EXECUTABLE)
    
$(BUILDPATH)/%.o: $(SOURCEPATH)/%.cpp
	$(warning Creando el binario $@...)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

prepare:
	$(warning Creando la estructura de carpetas)
	mkdir -p $(BINPATH)
	mkdir -p $(BUILDPATH)
	mkdir -p $(OBJ_DIRS)

clean:
	$(warning Cleaning...)
	@$(RM) $(EXECUTABLE)
	@$(RM) $(OBJ)