#!/bin/bash
i=1;
video=$1;

./vidload $video 1 0
mv vystup.avi $i.avi
i=$(( $i + 1 ));

./vidload $video 1 1
mv vystup.avi $i.avi
i=$(( $i + 1 ));

./vidload $video 1 2 
mv vystup.avi $i.avi
i=$(( $i + 1 ));

./vidload $video 1 3
mv vystup.avi $i.avi
i=$(( $i + 1 ));


