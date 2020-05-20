pushd ./code > /dev/null

g++ main.cpp -g -o ../bin/main.out -lSDL2 -lGL -lGLEW 

popd > /dev/null
