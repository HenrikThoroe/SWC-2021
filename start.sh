#!/bin/sh
chmod u+rwx ./dist/prodSWC-2021.out

blokusprod
./dist/prodSWC-2021.out "$@"