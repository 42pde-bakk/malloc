#!/usr/bin/env bash

RED=$'\e[1;31m'
GREEN=$'\e[1;32m'
MAGENTA=$'\e[1;35m'
CYN=$'\e[1;36m'
END=$'\e[0m'
set -e

mkdir -p bin
LIBRARY=$1
#export DYLD_LIBRARY_PATH=.
#export DYLD_INSERT_LIBRARIES="libft_malloc_x86_64_Darwin.so"
#export DYLD_FORCE_FLAT_NAMESPACE=1

function comp {
  c_file=tests/"$1"
  bin_file="$2"
  if [ "$(uname)" == "Linux" ]; then
    gcc "$c_file" "$LIBRARY" -o "$bin_file" -Iinclude -Wl,-R.
  elif [[ "$(uname)" == "Darwin" ]]; then
    gcc "$c_file" "$LIBRARY" -o "$bin_file" -Iinclude
  fi
}

function run_test {
  test_exec="bin/$1.out"
  comp "test_$1.c" "$test_exec"
  echo "compiled $test_exec"
  ./"$test_exec"
#  _=$(./"$test_exec") # execute the test
  echo "${MAGENTA}Ran ${test_exec}${END}"
}

#run_test allocation
#run_test double_free
#run_test free_invalid_ptr
run_test realloc_same_size
#run_test munmap
