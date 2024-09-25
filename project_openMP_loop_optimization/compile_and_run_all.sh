#!/bin/bash

declare -a programs=("1_sequential_simple_loop.c"
                     "2_sequential_loop_unrolling.c"
                     "3_sequential_loop_fusion.c"
                     "4_sequential_combined_optimizations.c"
                     "5_parallel_simple_loop_openmp.c"
                     "6_parallel_loop_unrolling_openmp.c"
                     "7_parallel_loop_fusion_openmp.c"
                     "8_parallel_combined_optimizations_openmp.c")

mkdir -p results

for program in "${programs[@]}"; do
    output_name=$(basename "$program" .c)

    echo "Compilation of ${program} as ${output_name}"

    gcc -fopenmp -o "$output_name" "$program" performance_logger.c -lm

    if [ $? -ne 0 ]; then
        echo "Compilation failed for ${program}"
        exit 1
    fi

    mv -f "$output_name" results/

    echo "Exécution de ${output_name}"
    ./results/"$output_name"

    if [ $? -ne 0 ]; then
        echo "Execution failed for ${output_name}"
        exit 1
    fi

    echo "Execution of ${output_name} completed"
done

echo "All programs have been compiled and executed successfully."
