#!/bin/sh

# Set the build mode variable based on the argument (default is 'debug')
if [ $# -gt 0 ]; then
  if [ "$1" = "release" ]; then
    export BUILD_MODE="release"
  else
    export BUILD_MODE="debug"
  fi
else
  export BUILD_MODE="debug"
fi

# Clean and build with the specified mode
make clean
make
if [ $? -eq 0 ]; then
  echo "Build successful"
  build/./Cheltoni
else
  echo "Build failed"
fi
