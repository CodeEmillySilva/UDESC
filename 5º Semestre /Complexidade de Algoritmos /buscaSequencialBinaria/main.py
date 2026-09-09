from sequencial import sequencialSearch
from binaria import binariaSearch
from time import perf_counter
import matplotlib.pyplot as plt

experimentos = [5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 500, 1000,
                10000]
tempo_sequencial=[]
tempo_binario=[]

for experimento in experimentos:

    lista=list(range(experimento))
    alvo=-1

    #Sequencial
    inicioContagem=perf_counter()
    sequencialSearch(lista,alvo)
    fimContagem=perf_counter()
    tempo_sequencial.append(fimContagem-inicioContagem)

    #Binária
    inicioContagem=perf_counter()
    binariaSearch(lista,alvo)
    fimContagem=perf_counter()
    tempo_binario.append(fimContagem-inicioContagem)

print(f"Experimentos feitos: {experimentos}")
print(f"Tempos sequenciais realizados: {tempo_sequencial}")
print(f"Tempos binários realizados: {tempo_binario}")

plt.plot(experimentos,tempo_sequencial, label='Sequencial')
plt.plot(experimentos, tempo_binario, label='Binária')

plt.xlabel("Tamanho da entrada (n)")
plt.ylabel("Tempo (s)")
plt.title("Comparação - Sequencial e Binária")
plt.legend()
plt.yscale("log")
plt.xscale("log")

plt.savefig('grafico.png')
