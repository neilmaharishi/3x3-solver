MYDEFS = -g -Wall -std=c++17 

cube:
	g++ ${MYDEFS} -o cube cube.cpp main.cpp

clean:
	rm -f *.o cube

