# Compile and link flags
CXX          =  g++
CFLAGS       = -Wall -g
#
# # Compilation (add flags as needed)
CXXFLAGS    += `pkg-config opencv --cflags`
#
# # Linking (add flags as needed)
LDFLAGS     += `pkg-config opencv --libs`
# 
proj=MYmirror

EXEC=$(proj)

OBJ=MYdetektor.o MYdisplay.o MYmaska.o MYoblicej.o
SRC=MYdetektor.cpp MYdisplay.cpp MYmaska.cpp MYoblicej.cpp
HEAD=MYdetektor.h MYdisplay.h MYmaska.h MYoblicej.h

.PHONY: build
.PHONY: clean

build: $(OBJ)
	$(CC) $(INCPATH) $(LIBATH) $(OPTIONS) $(CFLAGS) -o $(proj) $(OBJ)
	
clean:
	rm -rf *.o $(EXEC)

