CC = g++
CFLAGS=`pkg-config --cflags opencv` `pkg-config --libs opencv`
SUF=-I /usr/include/opencv -L /usr/local/lib -lm -lcv -lhighgui -lcvaux

proj=MYmirror

EXEC=$(proj)

OBJ=MYdetektor.o MYdisplay.o MYmaska.o MYoblicej.o
SRC=MYdetektor.cpp MYdisplay.cpp MYmaska.cpp MYoblicej.cpp
HEAD=MYdetektor.h MYdisplay.h MYmaska.h MYoblicej.h

.PHONY: build
.PHONY: clean

build: $(OBJ)
	$(CC) $(CFLAGS) -o $(proj) $(OBJ) $(SUF)

clean:
	rm -rf *.o $(EXEC)

