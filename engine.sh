#!/bin/bash

number="$1"  

./main "prepare" "$number"

./copy_tmp
./main "sort" "$number"
./delete_copy

