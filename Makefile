CC = g++
CFLAGS="-I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann"

proj=MYmirror

EXEC=$(proj)

OBJ=MYdetektor.o MYdisplay.o MYmaska.o MYoblicej.o
SRC=MYdetektor.cpp MYdisplay.cpp MYmaska.cpp MYoblicej.cpp
HEAD=MYdetektor.h MYdisplay.h MYmaska.h MYoblicej.h

.PHONY: build
.PHONY: clean

build: $(OBJ)
	$(CC) -I/home/intel/opencv/include/opencv -L/home/intel/opencv/lib -lcv -lhighgui -lstdc++ $(CFLAGS) -o $(proj) $(OBJ)

clean:
	rm -rf *.o $(EXEC)

