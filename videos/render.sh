#!/bin/bash
i=1;

./vidload "L2 - RK.avi" 1 0
mv vystup.avi $i.avi
i=$(( $i + 1 ));


./vidload "L2 - RK.avi" 1 1
mv vystup.avi $i.avi
i=$(( $i + 1 ));

./vidload "L2 - RK.avi" 1 2 3
mv vystup.avi $i.avi
i=$(( $i + 1 ));


