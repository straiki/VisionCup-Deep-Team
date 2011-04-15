CC = g++
CFLAGS=`pkg-config --cflags opencv` `pkg-config --libs opencv`

proj=MYmirror

EXEC=$(proj)

OBJ=
SRC=
HEAD=

.PHONY: build
.PHONY: clean

build: $(OBJ)
	$(CC) $(CFLAGS) -o $(proj) $(OBJ)

clean:
	rm -rf *.o $(EXEC)

