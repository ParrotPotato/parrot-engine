SRC_DIR := ./code
OBJ_DIR := ./bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cc)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC_FILES))
LDFLAGS :=  -lSDL2 -lGLEW -lGLU -lGL
CPPFLAGS := -g -D_REENTRANT -I/usr/include/SDL2 -I/usr/include/libdrm -L/usr/local/lib
CXXFLAGS := 

$(OBJ_DIR)/engine.out: $(OBJ_FILES)
	g++ -o $@ $^ $(CPPFLAGS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	g++ -c -o $@ $^ $(CPPFLAGS) $(LDFLAGS) $(CXXFLAGS)

clean: 
	rm bin/*.o bin/*.out 2> /dev/null

