#! /bin/sh

CUR=$(dirname "$(realpath "${BASH_SOURCE[0]}")")

rm -rf ${CUR}/build
mkdir ${CUR}/build
cd ${CUR}/build
cmake ..
cmake --build .