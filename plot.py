import matplotlib.pyplot as plt

x = [5, 7, 9, 12, 25, 50, 100, 200, 300, 400, 500]
time_para = [7.7, 3.2, 6.8, 11.1, 5.9, 6.7, 24.4, 19.9, 29.5, 43.0, 55.0]
time_seq = [10.7, 6.2, 13.1, 17.3, 23.5, 26.1, 94.1, 99.7, 163, 204.8, 259.5]

plt.plot(x, time_seq, label="Version séquentielle")
plt.plot(x, time_para, label="Version parallélisée")
plt.xlabel("Nombre de tâches")
plt.ylabel("Temps d'exécution en secondes")
plt.legend()
plt.title("Temps d'exécution de listes de tâches")
plt.savefig("Figure_1.png")
plt.show()

plt.close()
plt.plot(x, [time_seq[i] - time_para[i] for i in range(len(x))], label="Temps gagné par parallélisation")
plt.xlabel("Nombre de tâches")
plt.ylabel("Temps d'exécution en secondes")
plt.legend()
plt.title("Temps d'exécution de listes de tâches")
plt.savefig("Figure_2.png")
plt.show()
