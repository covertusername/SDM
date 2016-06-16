#!/bin/sh
while true; do
    dd if=/dev/urandom of=image.sdm count=1 bs=4096
    ./sdm image.sdm
    more sim.log
done
