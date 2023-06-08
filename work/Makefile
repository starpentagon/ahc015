CC = ccache g++
#CFLAGS = -g -Wall -std=c++17 -O0 -fsanitize=undefined,address -DLOCAL
# core dump出力用
#CFLAGS = -g -Wall --std=c++17 -O0 -DLOCAL

CFLAGS = -Wall --std=c++17 -O2 -DLOCAL
#CFLAGS = -pg -g -Wall --std=c++17 -O0

ALL: main.o Parameter.o XorShift.o BoxState.o SolveOneDir.o SolveGreedy.o SolvePattern.o
	$(CC) $(CFLAGS) -o main \
	main.o \
	XorShift.o \
	Parameter.o \
	SolveOneDir.o \
	SolveGreedy.o \
	SolvePattern.o \
	BoxState.o
	
clean:
	rm main *.o

run:
	./main

.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<
