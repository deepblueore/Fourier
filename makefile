all: test
test: complex.o matrices.o functions.o fourier.o test.o
	g++ complex.o test.o matrices.o functions.o fourier.o -lgmp -lgmpxx -o test
fourier.o: fourier.cpp
	g++ -c fourier.cpp -o fourier.o
functions.o: functions.cpp
	g++ -c functions.cpp -o functions.o
matrices.o: matrices.cpp
	g++ -c matrices.cpp -o matrices.o
complex.o: complex.cpp
	g++ -c complex.cpp -o complex.o
clean:
	rm -rf dft. *.o
