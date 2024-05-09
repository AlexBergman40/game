#OBJS specifies which files to compile as part of the project
OBJS = main.cpp game.cpp texture.cpp gameobject.cpp map.cpp boardrep.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using.
COMPILER_FLAGS = -w -I"./include" -L"./lib"

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =  -lmingw32 -lSDL2main -lSDL2  -lSDL2_image

#OBJ_NAME specifies the name of our executable
OBJ_NAME = game

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
