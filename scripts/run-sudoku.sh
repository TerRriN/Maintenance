#!/bin/bash

# Usage: ./run-sudoku.sh 9|16|25 [threads]

if [ $# -lt 1 ]; then
    echo "Usage: $0 <board_size: 9|16|25> [threads]"
    exit 1
fi

N=$1
N_threads=${2:-4}   # default 4 threads if not given

case $N in
    9)   files=(input/txt9/*) ;;
    16)  files=(input/txt16/*) ;;
    25)  files=(input/txt25/*) ;;
    *) 
        echo "Unsupported board size: $N (use 9, 16, or 25)"
        exit 1
        ;;
esac

if [ ${#files[@]} -eq 0 ]; then
    echo "No files found for size $N"
    exit 0
fi

total_time=0
file_count=0

for file in "${files[@]}"; do
    output=$(./sudoku "$file" $N $N_threads)
    echo "$output"
    time=$(echo "$output" | grep -oP '(?<=Time: )[0-9.]+' | awk '{print $1}')
    if [ -n "$time" ]; then
        total_time=$(awk "BEGIN {print $total_time + $time}")
        ((file_count++))
    fi
done

if [ "$file_count" -gt 0 ]; then
    average_time=$(awk "BEGIN {print $total_time / $file_count}")
    echo "Average time for ${file_count} files (size ${N}): ${average_time}s"
else
    echo "No files with time information found."
fi
