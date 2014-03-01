run: example6.cpp
	g++ example6.cpp InitShader.cpp -lglut -lGL -lGLU -lGLEW -lm -lSDL2 -g
clean:
	rm -f *.out *~run
