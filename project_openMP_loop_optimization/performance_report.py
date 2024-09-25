import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('performance_snapshot.csv', delimiter='|')

sequential_mapping = {
    'parallel_simple_loop_openmp': 'sequential_simple_loop',
    'parallel_loop_unrolling_openmp': 'sequential_loop_unrolling',
    'parallel_loop_fusion_openmp': 'sequential_loop_fusion',
    'parallel_combined_optimizations_openmp': 'sequential_combined_optimizations'
}

speedup = []
efficiency = []
work = []

for index, row in df.iterrows():
    program_name = row['program_name']
    threads_count = row['threads_count']
    
    if program_name in sequential_mapping:
        
        seq_program = sequential_mapping[program_name]
        seq_time = df[(df['program_name'] == seq_program) & (df['threads_count'] == 1)]['execution_time'].values[0]
        
        # Speedup 
        speed = round(seq_time / row['execution_time'], 2)
        speedup.append(speed)
        
        # Efficiency 
        eff = round(speed / threads_count, 2)
        efficiency.append(eff)
        
        # Work 
        work_done = round(row['execution_time'] * threads_count, 2)
        work.append(work_done)
    else:
        # NaN for sequential programs
        speedup.append(None)
        efficiency.append(None)
        work.append(None)

# Add the calculated values to the DataFrame
df['speedup'] = speedup
df['efficiency'] = efficiency
df['work'] = work

df.to_csv('performance_report.csv', index=False)

print(df)

plt.figure(figsize=(10, 6))
for program in df['program_name'].unique():
    if 'parallel' in program:
        subset = df[df['program_name'] == program]
        plt.plot(subset['threads_count'], subset['speedup'], marker='o', label=f"Speedup - {program}")

plt.title("SpeedUp des programmes parallèles par rapport aux versions séquentielles")
plt.xlabel("Nombre de threads")
plt.ylabel("SpeedUp")
plt.legend()
plt.grid(True)
plt.show()


plt.figure(figsize=(10, 6))
for program in df['program_name'].unique():
    if 'parallel' in program:
        subset = df[df['program_name'] == program]
        plt.plot(subset['threads_count'], subset['efficiency'], marker='o', label=f"Efficiency - {program}")

plt.title("Efficacité des programmes parallèles par rapport aux versions séquentielles")
plt.xlabel("Nombre de threads")
plt.ylabel("Efficacité")
plt.legend()
plt.grid(True)
plt.show()

plt.figure(figsize=(10, 6))
for program in df['program_name'].unique():
    if 'parallel' in program:
        subset = df[df['program_name'] == program]
        plt.plot(subset['threads_count'], subset['work'], marker='o', label=f"Work - {program}")

plt.title("Work des programmes parallèles")
plt.xlabel("Nombre de threads")
plt.ylabel("Work (Temps d'exécution * Nombre de threads)")
plt.legend()
plt.grid(True)
plt.show()

