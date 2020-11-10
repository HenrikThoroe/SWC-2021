#!/bin/sh
chmod u+rwx ./dist/prod.out
./dist/prod.out "$@"
