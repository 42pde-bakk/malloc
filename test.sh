#!/usr/bin/env bash

MAGENTA=$'\e[1;35m'
END=$'\e[0m'
set -e

mkdir -p bin

function comp {
  c_file=tests/"$1"
  bin_file="$2"
  if [ "$(uname)" == "Linux" ]; then
    gcc "$c_file" libft_malloc.so -o "$bin_file" -Iinclude -Wl,-R. -pthread
  elif [[ "$(uname)" == "Darwin" ]]; then
    gcc "$c_file" libft_malloc.so -o "$bin_file" -Iinclude
  fi
}

function run_test {
  test_exec="bin/$1.out"
  comp "test_$1.c" "$test_exec"
  echo "compiled $test_exec"
  ./"$test_exec"
  echo "${MAGENTA}Ran ${test_exec}${END}"
}

run_test allocation
run_test double_free
run_test free_invalid_ptr
run_test realloc_same_size
run_test munmap
run_test mix
run_test multithreaded
if [ "$(uname)" == "Darwin" ]; then
  run_test rlimit
fi
