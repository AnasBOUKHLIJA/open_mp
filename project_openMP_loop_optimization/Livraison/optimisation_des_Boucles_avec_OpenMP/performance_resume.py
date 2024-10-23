import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('performance_report.csv')

data = data.drop(columns=['thread_times'], errors='ignore')
data = data.drop(columns=['start_date'], errors='ignore')
data = data.drop(columns=['end_date'], errors='ignore')

parallel_data = data[data['program_name'].str.startswith('parallel')]
sequential_data = data[data['program_name'].str.startswith('sequential')]

print("Tableau des performances :")
print(data)

fig, ax = plt.subplots(figsize=(10, len(data) * 0.5))

ax.axis('tight')
ax.axis('off')

table = ax.table(cellText=data.values, colLabels=data.columns, cellLoc='center', loc='center')

table.auto_set_font_size(False)
table.set_fontsize(10)

plt.savefig('performance_report_table.png', bbox_inches='tight', dpi=300)
plt.show()
