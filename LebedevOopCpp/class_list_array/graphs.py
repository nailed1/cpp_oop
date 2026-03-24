import csv
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# Чтение данных из CSV
N = []
time_sec = []

with open('results.csv', 'r', encoding='utf-8') as f:
    reader = csv.DictReader(f)
    for row in reader:
        N.append(int(row['N']))
        time_sec.append(float(row['Время расчета (сек)']))

N = np.array(N)
time_sec = np.array(time_sec)

# Теоретическая сложность: O(N) при k=2
# Строим линейную регрессию для проверки
slope, intercept, r_value, p_value, std_err = stats.linregress(N, time_sec)

# Предсказанные значения для линейной модели
linear_fit = slope * N + intercept

# Также проверим квадратичную модель O(N^2) для сравнения
N_squared = N ** 2
slope_quad, intercept_quad, r_value_quad, _, _ = stats.linregress(N_squared, time_sec)
quadratic_fit = slope_quad * N_squared + intercept_quad

# R² для линейной модели
r_squared = r_value ** 2
r_squared_quad = r_value_quad ** 2

print(f"Анализ временной сложности:")
print(f"=" * 50)
print(f"Линейная модель O(N):")
print(f"  Уравнение: t = {slope:.2e} * N + {intercept:.2e}")
print(f"  R² = {r_squared:.6f}")
print()
print(f"Квадратичная модель O(N²):")
print(f"  Уравнение: t = {slope_quad:.2e} * N² + {intercept_quad:.2e}")
print(f"  R² = {r_squared_quad:.6f}")
print()
print(f"Вывод: {'O(N) подтверждается' if r_squared > r_squared_quad else 'O(N²) подтверждается'}")

# Построение графиков
fig, axes = plt.subplots(1, 2, figsize=(14, 5))

# График 1: Время от N с линейной аппроксимацией
axes[0].scatter(N, time_sec, color='blue', label='Эксперимент', s=60, zorder=3)
axes[0].plot(N, linear_fit, 'r-', label=f'Линейная аппроксимация (O(N))\nR² = {r_squared:.4f}', linewidth=2)
axes[0].plot(N, quadratic_fit, 'g--', label=f'Квадратичная (O(N²))\nR² = {r_squared_quad:.4f}', linewidth=2, alpha=0.7)
axes[0].set_xlabel('N (кол-во элементов)', fontsize=12)
axes[0].set_ylabel('Время (сек)', fontsize=12)
axes[0].set_title('Зависимость времени от N', fontsize=14)
axes[0].legend(fontsize=10)
axes[0].grid(True, alpha=0.3)

# График 2: Логарифмическая шкала для проверки степенной зависимости
log_N = np.log(N)
log_time = np.log(time_sec)

slope_log, intercept_log, r_value_log, _, _ = stats.linregress(log_N, log_time)
log_fit = slope_log * log_N + intercept_log

axes[1].scatter(log_N, log_time, color='blue', label='Эксперимент (log-log)', s=60, zorder=3)
axes[1].plot(log_N, log_fit, 'r-', label=f'Аппроксимация: slope = {slope_log:.3f}\n(теория: 1.0 для O(N))', linewidth=2)
axes[1].axhline(y=intercept_log + 1.0 * log_N.mean(), color='green', linestyle=':', label='Теоретический наклон O(N)', alpha=0.7)
axes[1].set_xlabel('log(N)', fontsize=12)
axes[1].set_ylabel('log(Время)', fontsize=12)
axes[1].set_title('Логарифмический график (проверка степени)', fontsize=14)
axes[1].legend(fontsize=10)
axes[1].grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('complexity_graph.png', dpi=150, bbox_inches='tight')
plt.show()

print(f"\nГрафик сохранён в complexity_graph.png")
