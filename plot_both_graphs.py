#!/bin/python3

import matplotlib.pyplot as plt
import sys

# Verifica se o número correto de argumentos foi fornecido
if len(sys.argv) != 3:
    print("Uso: ./script.py <arquivo_sequencial> <arquivo_paralelo>")
    sys.exit(1)

# Nomes dos arquivos de entrada fornecidos pela linha de comando
arquivo_sequencial = sys.argv[1]
arquivo_paralelo = sys.argv[2]

# Função para processar um arquivo e retornar dados
def processar_arquivo(nome_arquivo):
    cidades = []
    medias = []
    desvios_padrao = []

    # Lê os dados do arquivo
    with open(nome_arquivo, 'r') as arquivo:
        linhas = arquivo.readlines()[1:]  # Ignora a primeira linha (cabeçalho)
        for linha in linhas:
            campos = linha.strip().split(';')
            if len(campos) == 3:
                num_cidades, media, desvio_padrao = campos
                cidades.append(int(num_cidades))
                medias.append(float(media))
                desvios_padrao.append(float(desvio_padrao))
    
    return cidades, medias, desvios_padrao

# Processa os arquivos sequencial e paralelo
cidades_sequencial, medias_sequencial, desvios_padrao_sequencial = processar_arquivo(arquivo_sequencial)
cidades_paralelo, medias_paralelo, desvios_padrao_paralelo = processar_arquivo(arquivo_paralelo)

# Cria o gráfico comparativo
plt.figure(figsize=(10, 6))
plt.plot(cidades_sequencial, medias_sequencial, marker='o', label='Sequencial')
plt.errorbar(cidades_sequencial, medias_sequencial, yerr=desvios_padrao_sequencial, fmt='o', capsize=5)

plt.plot(cidades_paralelo, medias_paralelo, marker='o', label='Paralelo')
plt.errorbar(cidades_paralelo, medias_paralelo, yerr=desvios_padrao_paralelo, fmt='o', capsize=5)

plt.xlabel('Número de Cidades')
plt.ylabel('Tempo de Execução')
plt.title('Tempo de Execução Sequencial vs. Paralelo em Relação ao Número de Cidades')
plt.legend()
plt.grid(True)

# Defina os intervalos inteiros no eixo X
plt.xticks(range(min(cidades_sequencial), max(cidades_sequencial) + 1))

# Salva o gráfico em um arquivo PNG
plt.savefig('grafico_tempo_comparativo.png')

# Mostra o gráfico
plt.show()

print("Gráfico comparativo salvo em grafico_tempo_comparativo.png")
