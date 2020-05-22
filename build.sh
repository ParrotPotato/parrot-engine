pushd ./code > /dev/null

g++ main.cpp -g -o ../bin/engine.out -lSDL2 -lGL -lGLEW 

popd > /dev/null
