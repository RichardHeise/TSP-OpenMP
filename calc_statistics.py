#!/bin/python3

import sys
import statistics

def print_usage():
    print("Uso: ./rodaTestes.py <N>")
    print("<N> é o número de entradas a serem inseridas posteriormente.")

# Verifica o número correto de argumentos na linha de comando
if len(sys.argv) != 2:
    print_usage()
    sys.exit(1)

try:
    # Lê o número N da linha de comando
    N = int(sys.argv[1])

    if N <= 0:
        print("Erro: N deve ser um número inteiro positivo.")
        sys.exit(1)

    # Lê as entradas da entrada padrão
    entradas = []
    for i in range(N):
        entrada = input()
        entradas.append(float(entrada))

    if len(entradas) != N:
        print("Erro: Número incorreto de entradas fornecido.")
        sys.exit(1)

    # Calcula a média e o desvio padrão das entradas
    media = statistics.mean(entradas)
    desvio_padrao = statistics.stdev(entradas)

    # Imprime os resultados
    print(f"Média: {media:.2f}")
    print(f"Desvio Padrão: {desvio_padrao:.2f}")

except ValueError:
    print("Erro: Forneça um valor inteiro válido para N e números válidos como entradas.")
    print_usage()
except Exception as e:
    print(f"Erro inesperado: {str(e)}")
    print_usage()
