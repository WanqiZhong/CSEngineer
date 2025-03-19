#!/bin/bash

# 编译程序
echo "Compiling program..."
make

# 创建测试目录
mkdir -p data

# 1. 测试帮助信息
echo -e "\n1. Testing help information..."
./main -h

# 2. 测试文本文件读取 (-tr)
echo -e "\n2. Testing text file reading (-tr)..."
./main -tr data/students.txt

# 3. 测试文本文件读写 (-tw)
echo -e "\n3. Testing text file reading and writing (-tw)..."
./main -tw data/students.txt data/students_output.txt
echo "Output file contents:"
cat data/students_output.txt

# 4. 测试浮点和字符数组文件写操作 (-fw)
echo -e "\n4. Testing float and char array file writing (-fw)..."
./main -fw data

# 5. 测试浮点数组二进制文件读取 (-fr)
echo -e "\n5. Testing float array binary file reading (-fr)..."
./main -fr data/float_bin.dat

# 6. 测试结构体数组二进制文件写操作 (-sw)
echo -e "\n6. Testing struct array binary file writing (-sw)..."
./main -sw data/structure_bin.dat

# 7. 测试结构体数组二进制文件读取 (-sr)
echo -e "\n7. Testing struct array binary file reading (-sr)..."
./main -sr data/structure_bin.dat

echo -e "\nAll tests completed!" 