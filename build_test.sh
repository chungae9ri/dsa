#! /bin/sh

set -e

CUR=$(dirname "$(realpath "${BASH_SOURCE[0]}")")

rm -rf ${CUR}/build
mkdir ${CUR}/build
cd ${CUR}/build
cmake ..
cmake --build .
#pytest -v ${CUR}/build/tests/dsa_test
${CUR}/build/tests/dsa_test