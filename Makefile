output: fractal.o
	g++ fractal.o -o fractal -lncurses

fractal.o: fractal.cpp
	g++ -c fractal.cpp -lncurses

clean:
	rm *.o fractal *.ppm