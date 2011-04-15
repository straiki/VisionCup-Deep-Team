CC = g++
<<<<<<< HEAD
CFLAGS="-I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann"
=======
CFLAGS=`pkg-config --cflags opencv` `pkg-config --libs opencv`
SUF=-I /usr/include/opencv -L /usr/local/lib -lm -lcv -lhighgui -lcvaux
>>>>>>> 7ec6aed9aa65ad4e5ed20f8bafa868f1148af625

proj=MYmirror

EXEC=$(proj)

OBJ=MYdetektor.o MYdisplay.o MYmaska.o MYoblicej.o
SRC=MYdetektor.cpp MYdisplay.cpp MYmaska.cpp MYoblicej.cpp
HEAD=MYdetektor.h MYdisplay.h MYmaska.h MYoblicej.h

.PHONY: build
.PHONY: clean

build: $(OBJ)
<<<<<<< HEAD
	$(CC) -I/home/intel/opencv/include/opencv -L/home/intel/opencv/lib -lcv -lhighgui -lstdc++ $(CFLAGS) -o $(proj) $(OBJ)
=======
	$(CC) $(CFLAGS) -o $(proj) $(OBJ) $(SUF)
>>>>>>> 7ec6aed9aa65ad4e5ed20f8bafa868f1148af625

clean:
	rm -rf *.o $(EXEC)

