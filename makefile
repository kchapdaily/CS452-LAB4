run: example6.cpp
	g++ example6.cpp InitShader.cpp properties.cpp -lglut -lGL -lGLU -lGLEW -lm -g
clean:
	rm -f *.out *~run
