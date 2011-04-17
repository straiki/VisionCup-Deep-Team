#!/bin/bash
i=1;
video=$1;

echo $video

./vidload $video 1 0
mv vystup.avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 1
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload $video 1 2
mv vystup.avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 3
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 4
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 5
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 6
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 7
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 8
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 9
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 10
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 2 1
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 2 3
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 3 1
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 0 3
mv vystup.$avi $i.avi
i=$(( $i + 1 ));

./vidload video 1 4 3
mv vystup.$avi $i.avi
i=$(( $i + 1 ));
