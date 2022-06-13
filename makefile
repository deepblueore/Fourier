all: test
test: complex.o matrices.o test.o
	g++ complex.o test.o -lgmp -lgmpxx -o test
functions.o: functions.cpp
	g++ -c functions.cpp -o functions.o
matrices.o: matrices.cpp
	g++ -c matrices.cpp -o matrices.o
complex.o: complex.cpp
	g++ -c complex.cpp -o complex.o
clean:
	rm -rf dft. *.o
