import csv
import math
import matplotlib.pyplot as plt

n_values = []
time_values = []

with open("results.csv", "r", encoding="utf-8") as file:
    reader = csv.DictReader(file)
    for row in reader:
        n_values.append(int(row["N"]))
        time_values.append(float(row["Time"]))

models = {
    "O(N)": [],
    "O(N log N)": [],
    "O(N^2)": [],
    "O(N^3)": []
}

for n in n_values:
    models["O(N)"].append(n)
    models["O(N log N)"].append(n * math.log(n))
    models["O(N^2)"].append(n * n)
    models["O(N^3)"].append(n * n * n)

best_name = ""
best_a = 0
best_b = 0
best_error = -1

for name in models:
    x = models[name]
    y = time_values
    count = len(x)

    sum_x = sum(x)
    sum_y = sum(y)
    sum_x2 = 0
    sum_xy = 0

    for i in range(count):
        sum_x2 += x[i] * x[i]
        sum_xy += x[i] * y[i]

    a = (count * sum_xy - sum_x * sum_y) / (count * sum_x2 - sum_x * sum_x)
    b = (sum_y - a * sum_x) / count

    error = 0
    for i in range(count):
        t = a * x[i] + b
        error += (y[i] - t) ** 2

    if best_error == -1 or error < best_error:
        best_error = error
        best_name = name
        best_a = a
        best_b = b

future_n = []
current = 1000
limit = n_values[-1] * 2

while current <= limit:
    future_n.append(current)
    current *= 2

if future_n[-1] < limit:
    future_n.append(limit)

future_x = []

for n in future_n:
    if best_name == "O(N)":
        future_x.append(n)
    elif best_name == "O(N log N)":
        future_x.append(n * math.log(n))
    elif best_name == "O(N^2)":
        future_x.append(n * n)
    elif best_name == "O(N^3)":
        future_x.append(n * n * n)

predicted_time = []
for value in future_x:
    predicted_time.append(best_a * value + best_b)

print("Лучшая модель:", best_name)

plt.figure(figsize=(10, 6))
plt.plot(n_values, time_values, "bo-", label="Фактическое время")
plt.plot(future_n, predicted_time, "r--", label="Прогноз " + best_name)
plt.xlabel("N")
plt.ylabel("Время")
plt.title("График зависимости времени от N")
plt.grid(True)
plt.legend()
plt.show()