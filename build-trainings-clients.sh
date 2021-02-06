#!/bin/bash

shopt -s extglob

ARCHS=(x86-64 skylake broadwell haswell)

for arch in "${ARCHS[@]}" 
do
    rm -f "./dist/${arch}.out"
    blokusbuild -f="${arch}" -e="-march=${arch} -DDEBUG" -n &
done

wait
