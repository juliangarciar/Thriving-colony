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
SOURCE_DIRS = . GraphicEngine GUIEngine IOEngine SoundEngine IAEngine PathPlanner WorldGeometry
#C++ compiler
CXX = clang++

####
# FLAGS
####
# Include paths
CPPFLAGS = -I/usr/include -I/usr/local/include  -I/usr/include/eigen3 -I/usr/local/include/irrlicht -I/usr/local/include/fmod -I/usr/local/include/nanovg -I./$(SOURCEPATH)
# Compiler params
CPPFLAGS += -O3 -ffast-math -g -Wall -std=c++11 -m64 -pthread -DGL_GLEXT_PROTOTYPES
# Lib paths
LDFLAGS = -L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/X11
# Libs
LIBS = -lGL -lXxf86vm -lXext -lX11 -lXcursor -lXrandr -lXinerama -lXi -lpthread -ldl -lrt -lglfw -lIrrlicht -lnanogui -lfmod -lfmodstudio
###-lfmodex_vc.lib -lfmod -lfmodasdL

######## DON'T EDIT ANYTHING BELOW THIS LINE
EXECUTABLE := $(BINPATH)/$(TARGET)
SRC := $(foreach DIR,$(SOURCE_DIRS),$(wildcard $(SOURCEPATH)/$(DIR)/*.cpp))
OBJ_DIRS := $(foreach DIR,$(SOURCE_DIRS),$(patsubst %, $(BUILDPATH)/%, $(DIR)))
OBJ := $(patsubst $(SOURCEPATH)/%.cpp, $(BUILDPATH)/%.o, $(SRC))

#MAKE OPTIONS
.PHONY: all clean cleanfolder

all: prepare $(OBJ)
	$(warning Creando el ejecutable $(Target)...)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(EXECUTABLE) $(LDFLAGS) $(LIBS)
    
$(BUILDPATH)/%.o: $(SOURCEPATH)/%.cpp
	$(warning Creando el binario $@...)
	$(CXX) $(CPPFLAGS) -c $< -o $@

prepare:
	$(warning Creando la estructura de carpetas)
	mkdir -p $(BINPATH)
	mkdir -p $(BUILDPATH)
	mkdir -p $(OBJ_DIRS)

clean:
	$(warning Cleaning...)
	@$(RM) $(EXECUTABLE)
	@$(RM) $(OBJ)

cleanfolder:
	$(warning Cleaning $(FOLDER)...)
	@$(RM) $(EXECUTABLE)
	@$(RM) $(BUILDPATH)/$(FOLDER)/*.o
