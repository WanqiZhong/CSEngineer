#!/bin/bash

# Compile the program
echo "Compiling..."
make

# Test sorting algorithms
echo -e "\nTesting sorting algorithms and data types..."

# Data sizes
SIZES=("1000" "10000")

# Data types
DATA_TYPES=("-i" "-f" "-d" "-s")
DATA_TYPE_NAMES=("Integer" "Float" "Double" "Structure")

# Sorting algorithms
SORT_ALGOS=("-s" "-b" "-i" "-m" "-q" "-h")
SORT_ALGO_NAMES=("Select" "Bubble" "Insert" "Merge" "Quick" "Heap")

# Create table header
echo -e "\nResults:"
echo "==============================================="
echo "| Size | Data Type | Algorithm | Time (sec) |"
echo "==============================================="

# Test small datasets
for size in "${SIZES[@]}"; do
 for i in {0..3}; do
   for j in {0..5}; do
     result=$(./runsort $size ${DATA_TYPES[$i]} ${SORT_ALGOS[$j]})
     time=$(echo "$result" | grep "在" | awk '{print $2}')
     
     printf "| %-4s | %-9s | %-9s | %-10s |\n" "$size" "${DATA_TYPE_NAMES[$i]}" "${SORT_ALGO_NAMES[$j]}" "$time"
   done
 done
 echo "-----------------------------------------------"
done


# Test large datasets
echo -e "\nLarge dataset test..."

# Large dataset sizes
LARGE_SIZES=("1000000")

# Data types
LARGE_DATA_TYPES=("-f")
LARGE_DATA_TYPE_NAMES=("Float")

# Sorting algorithms
SORT_ALGOS=("-m" "-q" "-h" "-i")
SORT_ALGO_NAMES=("Merge" "Quick" "Heap" "Insert")

# Create table header
echo -e "\nLarge dataset test:"
echo "==============================================="
echo "| Size | Data Type | Algorithm | Time (sec) |"
echo "==============================================="

# Test small datasets
for size in "${LARGE_SIZES[@]}"; do
 for i in {0..0}; do
   for j in {0..3}; do
     result=$(./runsort $size ${LARGE_DATA_TYPES[$i]} ${SORT_ALGOS[$j]})
     time=$(echo "$result" | grep "在" | awk '{print $2}')
     
     printf "| %-4s | %-9s | %-9s | %-10s |\n" "$size" "${LARGE_DATA_TYPE_NAMES[$i]}" "${SORT_ALGO_NAMES[$j]}" "$time"
   done
 done
 echo "-----------------------------------------------"
done

echo -e "\nAll tests completed!"