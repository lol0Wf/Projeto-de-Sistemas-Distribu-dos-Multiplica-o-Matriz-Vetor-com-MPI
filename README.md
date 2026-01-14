# README — Multiplicação de Matriz por Vetor (Sequencial e MPI)

Este projeto implementa o problema matriz × vetor em duas versões:

- **Versão sequencial em C++**
- **Versão distribuída usando MPI**

O objetivo é medir tempo de execução, speedup, eficiência e escalabilidade.

---

## 1. Requisitos

### Para compilar e rodar

- **GCC / G++**
- **OpenMPI instalado**
- **WSL2 recomendado** (Linux)

### Verificar se MPI está instalado

```bash
mpirun --version
mpicc --version
```

---

## 2. Compilar os códigos

### Versão Sequencial

```bash
g++ seq_matvec.cpp -O2 -o seq
```

### Versão MPI

```bash
mpic++ mpi_matvec.cpp -O2 -o mpi_matvec  (killed)
```

---

## 3. Executar os programas

### Sequencial

```bash
./seq 1000
```

Onde `1000` é o tamanho N da matriz (N×N) e do vetor.

### MPI

```bash
mpirun -np <processos> ./mpi_matvec <N>
```
````bash
mpirun -np (P)  --oversubscribe ./mpi_matvec (N)
```

**Exemplos:**

```bash
mpirun -np 1 ./mpi_matvec 1000
mpirun -np 2 ./mpi_matvec 1000
mpirun -np 4 ./mpi_matvec 1000
mpirun -np 8 ./mpi_matvec 1000
```

---

## 📌 4. Sobre "-np"

O parâmetro:

```bash
-np X
```

significa **quantos processos paralelos MPI** serão criados.

**Exemplos:**

- `-np 1` → código roda igual ao sequencial
- `-np 2` → 2 processos MPI
- `-np 4` → 4 processos MPI
- `-np 8` → 8 processos MPI

---

## 5. Aviso sobre limites de processos no WSL

**WSL geralmente permite até 8 processos MPI** sem travar ou falhar.

Mais que isso tende a dar erro:

- Falta de memória
- Limitação de CPU virtual
- Falta de slots no OpenMPI do WSL

Por isso os testes são feitos com:

- **1, 2, 4, 8 processos**

---

## 6. Como medir o tempo e gerar métricas

Para cada valor de N (ex.: 500, 1000, 2000):

1. **Rode 5 vezes o sequencial**
2. **Calcule a média**

Depois:

1. **Rode MPI com:**
   - `np = 1, 2, 4, 8`
2. **Para cada np, rode 5 vezes**
3. **Calcule a média**

---

## 7. Métricas para o relatório

### Speedup

$$S = \frac{T_{seq}}{T_{par}}$$

### Eficiência

$$E = \frac{S}{p}$$

### Escalabilidade

Comparar o speedup com diferentes valores de p.

---

## 8. Recomendações de teste

### Use tamanhos:

- `N = 500`
- `N = 1000`
- `N = 2000`

### Processos:

- `1, 2, 4, 8`
