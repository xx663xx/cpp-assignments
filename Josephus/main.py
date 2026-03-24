import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv')
n_real = df['N'].values
time_real = df['Time'].values

C = np.mean(time_real / (n_real**2))
print(f"Коэффициент C = {C:.2e}")

max_n = n_real[-1]
n_pred = np.array([max_n * 2, max_n * 4, max_n * 8])
time_pred = C * (n_pred**2)

print("\nПредсказание:")
for n, t in zip(n_pred, time_pred):
    print(f"N = {n} {t:.2f} сек")

plt.figure(figsize=(10, 6))

plt.scatter(n_real, time_real, color='blue', label='Реальные данные', zorder=5)

n_dense = np.linspace(0, max_n, 100)
plt.plot(n_dense, C * (n_dense**2), 'g--', label=f'Теория (C * N^2, C={C:.1e})')

n_full_pred = np.linspace(max_n, n_pred[-1], 100)
plt.plot(n_full_pred, C * (n_full_pred**2), 'r--', alpha=0.6)
plt.scatter(n_pred, time_pred, color='red', marker='s', label='Предсказание')

for n, t in zip(n_pred, time_pred):
    plt.annotate(f'{t:.1f}s', (n, t), textcoords="offset points", xytext=(0,10), ha='center')

plt.title('Зависимость времени выполнения задачи Иосифа от N (O(N²))')
plt.xlabel('N (количество элементов)')
plt.ylabel('Время (секунды)')
plt.legend()
plt.grid(True, linestyle=':', alpha=0.7)
plt.ticklabel_format(style='plain', axis='x')
plt.show()