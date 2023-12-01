#!/bin/bash

SCRIPT_DIR=$(pwd)
YEAR=2023

# Day number.
if [ -z "$1" ]; then
  echo "Day number is not specified"
  echo "usage: ./setup_cpp.sh <day_number>"
  exit 1
fi

# Day directory.
if [ ! -d "$SCRIPT_DIR/$1" ]; then
  cp -r "$SCRIPT_DIR/template/cpp" "$SCRIPT_DIR/$1"
  echo "Created day directory from C++ template $SCRIPT_DIR/$1"
fi

# Input file.
if ! command -v aocdl &> /dev/null
then
  echo "aocdl could not be found to fetch input"
  exit 1
fi

if [ ! -f "$SCRIPT_DIR/$1/input.txt" ]; then
  aocdl -force -output $SCRIPT_DIR/$1/input.txt -day $1 -year $YEAR -wait
fi
