import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")
print(df)
plt.figure()
plt.plot(df["N"], df["Time"], marker='o')
plt.xlabel("N")
plt.ylabel("Time (seconds)")
plt.title("Зависимость времени от N")
plt.grid()
plt.show()