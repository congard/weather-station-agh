#!/bin/bash

source init.sh

echo "Looking for npm..."

if ! which npm; then
  echo "npm cannot be found"
  exit 1
fi

function help() {
  echo "
  This script can be used to install frontend
  dependencies, deploy and flash it to the board.

  Available options:

  init    install dependencies
  build   create static build
  flash   flash previously built static build to the board

  Note: you can use multiple options at once, e.g.
    ./www.sh init build flash
  all 3 options will be executed one after another
  "
}

function init() {
  echo "Installing frontend dependencies..."

  cd www || exit
  npm install
  cd ../
}

function build() {
  echo "Preparing frontend for deployment..."

  cd www || exit

  # set build path & disable generation of
  # large js.map files

  BUILD_PATH='../data' \
  GENERATE_SOURCEMAP=false \
  npm run build

  cd ../
}

function flash() {
  echo "Flashing www partition..."

  "$PIO_BIN" run -t uploadfs
}

for arg in "$@"
do
  if [ "$arg" == "init" ]; then
    init
  elif [ "$arg" == "build" ]; then
    build
  elif [ "$arg" == "flash" ]; then
    flash
  else
    if [ "$arg" != "help" ]; then
      echo "Unknown argument '$arg'"
    fi
    help
  fi
done
