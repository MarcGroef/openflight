all:
	g++ --std=c++11 -Wall -g  src/*/*.cc -o build/openflight_test -lccore -lm -lGL -lglut -lGLU -lGLEW 

windows:
	i586-mingw32msvc-g++ -Wall -g -O3 src/*/*.cc -o build/openflight_test -lccor$

