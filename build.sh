#!/bin/bash

build_dir=$(pwd)
build_type="release"
cmake_build_type="Release"

show_help() {
  cat << EOF
Usage: ${0##*/} [-d] [-h]

Options:
  -d            Set build type to Debug (default is Release)
  -h            Show this help message and exit

Description:
  This script configures the build type for a project.
  If the -d flag is provided, the build type will be Debug.
  Otherwise, it defaults to Release.
EOF
}

while getopts "dh" opt; do
  case ${opt} in
    d )
      build_type="debug" 
      ;;
    h )
      show_help
      exit 0
      ;;
    \? )
      echo "Invalid option: -$OPTARG" >&2
      show_help
      exit 1
      ;;
  esac
done

if [[ $build_type == "debug" ]]; then
  cmake_build_type="Debug"
fi

cmake_build_dir=$build_dir/target
mkdir -p $cmake_build_dir

cd $cmake_build_dir

cmake -G Ninja -DCMAKE_BUILD_TYPE=$cmake_build_type -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
ninja -v -j 8
build_status=$?

cd $build_dir

echo ""
if [[ "$build_status" -ne 0 ]]; then
  echo "BUILD FAILED"
else
  echo "BUILD SUCCESS"
fi
