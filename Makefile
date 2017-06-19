all:
	g++ --std=c++11 -Wall -g  src/*/*.cc -o build/openflight_test -lccore -lm -lGL -lglut -lGLU -lGLEW 


