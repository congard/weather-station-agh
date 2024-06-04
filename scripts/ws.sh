#!/bin/bash

source init.sh

function help() {
  echo "
  This script can be used to build, monitor and
  flash to the board the Weather Station backend.

  Available arguments:

  upload    (build and) upload application to the board
  monitor   monitor board's stdout
  run       upload + monitor
  "
}

function upload() {
  echo "Uploading..."
  "$PIO_BIN" run -t upload
}

function monitor() {
  echo "Starting monitor..."
  "$PIO_BIN" device monitor
}

function run() {
  echo "Running..."
  "$PIO_BIN" run -t upload -t monitor
}

if [ "$#" -ne 1 ]; then
  echo "Illegal number of parameters: expected 1, got $#"
  help
  exit 1
fi

if [ "$1" == "upload" ]; then
  upload
elif [ "$1" == "monitor" ]; then
  monitor
elif [ "$1" == "run" ]; then
  run
else
  if [ "$1" != help ]; then
    echo "Unknown argument '$1'"
  fi
  help
fi
