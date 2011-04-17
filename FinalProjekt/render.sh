#!/bin/bash
i=1;
video=$1;

./mirror $video 1 0
mv vystup.avi vysledky/$i.avi
i=$(( $i + 1 ));

./mirror $video 1 1 3
mv vystup.avi vysledky/$i.avi
i=$(( $i + 1 ));

./mirror $video 1 10 6
mv vystup.avi vysledky/$i.avi
i=$(( $i + 1 ));

./mirror $video 1 9
mv vystup.avi vysledky/$i.avi
i=$(( $i + 1 ));
