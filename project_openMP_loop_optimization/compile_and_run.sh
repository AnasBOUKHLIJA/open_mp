#!/bin/bash

declare -a programs=("1_simple_loop.c"
                     "2_loop_unrolling.c"
                     "3_loop_fusion.c"
                     "4_simple_loop_openmp.c"
                     "5_loop_unrolling_openmp.c"
                     "6_loop_fusion_openmp.c"
                     "7_combined_optimizations_openmp.c")

echo "Veuillez choisir un programme à compiler et exécuter :"
for i in "${!programs[@]}"; do
    printf "%d) %s\n" "$((i + 1))" "${programs[$i]}"
done

read -p "Entrez un numéro (1-${#programs[@]}): " user_input

index=$(($user_input - 1))
if [ "$index" -ge 0 ] && [ "$index" -lt "${#programs[@]}" ]; then
    program="${programs[$index]}"
    output_name=$(basename "$program" .c) # Extraire le nom du fichier sans l'extension .c

    echo "Compilation de ${program} en tant que ${output_name}"

    gcc -fopenmp -o "$output_name" "$program" performance_logger.c -lm

    if [ $? -ne 0 ]; then
        echo "La compilation a échoué pour ${program}"
        exit 1
    fi

    mkdir -p results

    mv -f "$output_name" results/

    echo "Exécution de ${output_name}"
    ./results/"$output_name"

else
    echo "Index invalide. Veuillez fournir un numéro entre 1 et ${#programs[@]}."
    exit 1
fi
