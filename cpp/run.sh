#!/bin/bash

make clean
make -f Makefile-cliserv clean
make
make -f Makefile-cliserv
make -f Makefile-cliserv run-all
