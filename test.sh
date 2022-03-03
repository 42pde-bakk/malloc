#!/usr/bin/env bash

RED=$'\e[1;31m'
GREEN=$'\e[1;32m'
MAGENTA=$'\e[1;35m'
CYN=$'\e[1;36m'
END=$'\e[0m'
make -s
set -e
LIBRARY=libft_malloc_x86_64_Darwin.so
#export DYLD_LIBRARY_PATH=.
#export DYLD_INSERT_LIBRARIES="libft_malloc_x86_64_Darwin.so"
#export DYLD_FORCE_FLAT_NAMESPACE=1

function comp {
  c_file=tests/"$1"
  bin_file="$2"
  gcc "$c_file" $LIBRARY -o "$bin_file" -Iinclude
}

function test_outcome {
  test_exec="$1.out"
  comp "test_$1.c" "$test_exec"
  expected_result="$2"
  text_output=$(./"$test_exec") # execute the test
  outcome=$?
  echo "text_output=$text_output, outcome=$outcome"
  if [[ $outcome == "$expected_result" ]]; then
    echo "$MAGENTA [OK] $END. './$1' correctly returned $outcome"
  else
    echo "$RED [KO] $END. './$1' incorrectly returned $outcome"
  fi
}

test_outcome double_free 0
test_outcome free_invalid_ptr 0
test_outcome allocation 0
