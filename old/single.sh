#!/bin/sh

cp_lib_path=$HOME/Desktop/dev/cpp/cp_lib

touch single.cc
echo '// 276931LM' > single.cc

sed '/#include ".*"/d;/#pragma once/d' $cp_lib_path/mbgldef.h $cp_lib_path/basic.cc $cp_lib_path/memory.cc $cp_lib_path/array.cc $cp_lib_path/queue.cc $cp_lib_path/vector.cc $1 >> single.cc
