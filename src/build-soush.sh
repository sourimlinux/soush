#!/bin/bash

. ../config.sh

CSRC=`find *.c`
COUT=""

for prog in $CSRC; do
    while [[ `jobs | wc -l` -ge `nproc` ]]; do sleep 1; done

    echo -e " CC\t$prog"
    OUT="../$OUTDIR/${prog/.c/.o}"
    COUT+="$OUT "

    $CC_COMPILER -c $CC_FLAGS $prog -o $OUT &
done
wait

$CC_COMPILER $LD_FLAGS $COUT -o ../$EXEC