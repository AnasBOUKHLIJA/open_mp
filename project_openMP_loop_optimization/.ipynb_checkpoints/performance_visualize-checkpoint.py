import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('performance_snapshot.csv', delimiter='|')

plt.figure(figsize=(10, 6))

for program in df['program_name'].unique():
    subset = df[df['program_name'] == program]
    plt.plot(subset['threads_count'], subset['execution_time'], marker='o', label=program)

plt.title("Performance du programme avec différents nombres de threads")
plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (secondes)")
plt.legend()
plt.grid(True)

plt.show()

