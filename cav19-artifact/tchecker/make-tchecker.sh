#!/bin/bash

CXX=${CXX:-g++}

CPPFLAGS="-I/usr/include -I./uppaal/include \
-I./TChecker/src/include"

# Don't forget -DNDEBUG for efficiency, don't use -O3 (fddi cannot be compiled)
# Also -m32 to avoid wasting all available memory in large pointers
CXXFLAGS="-Wall -DNDEBUG -O2 -std=c++11 -U__STRICT_ANSI__"
LDFLAGS="-L/usr/lib64 -L./uppaal/lib \
-L./TChecker/src/.libs -ltchecker -ludbm"

# Check command line option
if [ "$#" -lt 1 ]; then
  echo "*** Usage: $0 filename";
  echo "       filename is a C++ description of a system";
  exit -1;
fi;

# Check that the file exists
if [ ! -f "$1" ]; then
  echo "*** File $1 does not exist";
  exit -1;
fi;

# Extract the executable file name from filename (i.e. $1)
EXE=${1%.*}

SOURCE_FILE=$1
echo "$CXX -o $EXE ${SOURCE_FILE} $CPPFLAGS $CXXFLAGS $LDFLAGS"
$CXX -o $EXE ${SOURCE_FILE} $CPPFLAGS $CXXFLAGS $LDFLAGS
