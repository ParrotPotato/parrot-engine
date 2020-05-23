pushd ./code > /dev/null

if [ "$1" == "release" ]
then
	echo "building release binary ..."
	g++ main.cpp -O2 -o ../bin/engine.out -lSDL2 -lGL -lGLEW 
else 
	echo "building debug binary ..."
	g++ main.cpp -g -o ../bin/engine.out -lSDL2 -lGL -lGLEW 
fi

popd > /dev/null
