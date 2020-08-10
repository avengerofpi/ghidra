#!/bin/bash

# Compile all the C programs in the current directory,
# placing output binaries in the bin subdir
for cprog in *.c; do
  cprogName=${cprog/.c/};
  gcc ${cprog} -o bin/${cprogName}.out;
done;	
