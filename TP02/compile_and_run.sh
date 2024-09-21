#!/bin/bash

# List of actual program file names (without prefixes)
declare -a programs=("sequential_program.c"
                     "parallel_program.c"
                     "parallel_program_num_threads.c"
                     "parallel_program_loop_interne.c"
                     "parallel_program_loop_order.c"
                     "parallel_program_demission_M_N.c")

# Check if an index is provided
if [ -z "$1" ]; then
    echo "Please provide an index (1-${#programs[@]})"
    exit 1
fi

# Validate the provided index
index=$(($1 - 1))
if [ "$index" -ge 0 ] && [ "$index" -lt "${#programs[@]}" ]; then
    program="${programs[$index]}"
    output_name="program_${index}"

    echo "Compiling ${program} as ${output_name}"

    # Compile the selected program
    gcc -fopenmp -o "$output_name" "$program" -lm

    # Check if the compilation was successful
    if [ $? -ne 0 ]; then
        echo "Compilation failed for ${program}"
        exit 1
    fi

    # Create the results directory if it doesn't exist
    mkdir -p results

    # Move the compiled binary to the results directory (replace if it exists)
    mv -f "$output_name" results/

    # Run the compiled program
    echo "Running ${output_name}"
    ./results/"$output_name"

else
    echo "Invalid index. Please provide a number between 1 and ${#programs[@]}."
    exit 1
fi
