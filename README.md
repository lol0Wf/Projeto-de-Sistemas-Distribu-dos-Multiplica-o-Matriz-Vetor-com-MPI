# Multiplicação Matriz-Vetor Distribuída com MPI

## Descrição do Projeto

Este projeto consiste na implementação de um algoritmo de **multiplicação matriz-vetor**, desenvolvido inicialmente de forma **sequencial** e posteriormente adaptado para uma versão **distribuída**, utilizando a biblioteca **MPI (Message Passing Interface)** em **C/C++**.

O objetivo principal foi explorar conceitos de **computação distribuída**, avaliando o impacto da paralelização na performance do algoritmo por meio da análise de **speedup, eficiência e escalabilidade**, considerando diferentes tamanhos de entrada e quantidades de processos.

---

## Funcionalidades

- Implementação sequencial da multiplicação matriz-vetor  
- Implementação distribuída utilizando MPI  
- Distribuição de carga entre processos  
- Comunicação entre processos via troca de mensagens  
- Execução com diferentes números de processos  
- Medição de tempo de execução  
- Cálculo de speedup, eficiência e escalabilidade  

---

## Tecnologias Utilizadas

- Linguagem C/C++  
- MPI (Message Passing Interface)  
- Computação distribuída  
- Programação paralela  

---

## Metodologia

O desenvolvimento do projeto seguiu as seguintes etapas:

1. Implementação da versão sequencial do algoritmo  
2. Identificação das regiões paralelizáveis  
3. Implementação da versão distribuída com MPI  
4. Execução de testes com diferentes tamanhos de entrada  
5. Execução com múltiplos processos (1, 2, 4, 8, ...)  
6. Coleta de métricas de desempenho  
7. Análise de speedup, eficiência e escalabilidade  

---

## Compilação

Para compilar o projeto, é necessário ter uma implementação de MPI instalada (como OpenMPI ou MPICH).

```bash
mpicc matriz_vetor.c -o matriz_vetor
