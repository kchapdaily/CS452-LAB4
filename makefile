run: main.cpp
	g++ main.cpp -lglut -lGL -lGLU -lGLEW -lm -lSDL2 -g
clean:
	rm -f *.out *~run
