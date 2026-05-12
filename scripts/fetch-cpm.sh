#!/usr/bin/env bash

#
# Fetch CMake module for CMake Package Manager (CPM) from GitHub and save it to the cmake/Modules directory
# https://github.com/cpm-cmake/cpm.cmake
#

set -euo pipefail

readonly repository_root=$(git rev-parse --show-toplevel)
readonly cpm_url="https://github.com/cpm-cmake/CPM.cmake.git"
readonly target_dir="cmake"
readonly target_file="${target_dir}/CPM.cmake"

# Check if the file already exists
if [ -f "$target_file" ]; then
  echo "$target_file already exists."
  echo "Do you want to update it? (y/n)"
  read -r answer
  if [[ "$answer" != "y" && "$answer" != "Y" ]]; then
    echo "Skipping update."
    exit 0
  fi
fi

# Create directory if it doesn't exist
mkdir -p "$target_dir"

# Download the file
wget -O "$target_file" https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake