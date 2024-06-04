#!/bin/bash

# This script initializes basic environment.
# Do not use this script manually!

curr_dir="$PWD"
dir_name=$(basename -- "$curr_dir")

echo "Current directory: $curr_dir"

if [ "$dir_name" == "scripts" ]; then
  new_dir=$(realpath "$curr_dir/..")
  echo "Changing directory to $new_dir"
  cd "$new_dir" || exit
fi

if [ -z "${VAR}" ]; then
  PIO_BIN="$HOME/.platformio/penv/bin/pio"
fi

echo "PIO_BIN=$PIO_BIN"

if [ ! -f "$PIO_BIN" ]; then
  echo "Error: '$PIO_BIN' cannot be found"
  exit 1
fi