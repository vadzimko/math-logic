#!/usr/bin/env bash

cat output.txt | awk '{printf("\"%s\",\n", $1)}' > temp.txt