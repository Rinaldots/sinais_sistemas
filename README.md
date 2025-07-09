# Transformada Discreta de Fourier (DFT) e Transformada Rápida de Fourier (FFT)

Este projeto implementa algoritmos para calcular a Transformada Discreta de Fourier (DFT) e sua versão otimizada, a Transformada Rápida de Fourier (FFT), em C++.

## 📁 Estrutura do Projeto

```
sinais_sistemas/
├── dft/
│   ├── dft_matrix.cpp      # Implementação da DFT usando matriz de Vandermonde
│   └── Makefile   
├── fft/
│   ├── fft.cpp             # Implementação da FFT usando algoritmo divide-e-conquista
│   └── Makefile            # Arquivo de compilação para FFT
└── README.md               # Este arquivo
```

## 🔍 Algoritmos Implementados

### DFT (Transformada Discreta de Fourier)
- **Localização**: `dft/dft_matrix.cpp`
- **Método**: Implementação direta usando matriz de Vandermonde
- **Complexidade**: O(N²)
- **Características**:
  - Calcula a matriz DFT completa
  - Multiplica matriz por vetor de entrada
  - Exibe matriz de transformação e resultado

### FFT (Transformada Rápida de Fourier)
- **Localização**: `fft/fft.cpp`
- **Método**: Algoritmo Cooley-Tukey (divide-e-conquista)
- **Complexidade**: O(N log N)
- **Características**:
  - Algoritmo recursivo
  - Separação em índices pares e ímpares
  - Requer N como potência de 2

## 🛠️ Compilação e Execução

### Para FFT:
```bash
cd fft/
make
make run
```

### Para DFT:
```bash
cd dft/
g++ -std=c++11 -Wall -Wextra -O2 -o dft_matrix dft_matrix.cpp
./dft_matrix
```

## 📊 Exemplo de Uso

### Entrada de Dados
```
Numero de pontos: 4
Digite os pontos:
Digite o ponto 1: 1
Digite o ponto 2: 2
Digite o ponto 3: 3
Digite o ponto 4: 4
```

### Saída Esperada (FFT)
```
Valor N: 4
X_pares:
[       1        3]

X_impares:
[       2        4]

Resultado da FFT:
[      10       -2+2j       -2       -2-2j]
```

## 🧮 Fundamentos Matemáticos

### Fórmula da DFT
```
X(k) = Σ(n=0 to N-1) x(n) * W_N^(nk)
```

Onde:
- `W_N^(nk) = e^(-2πj*nk/N)` (fator twiddle)
- `x(n)` é o sinal de entrada
- `X(k)` é o resultado da transformada

### Algoritmo FFT (Cooley-Tukey)
1. **Dividir**: Separar em índices pares e ímpares
2. **Conquistar**: Aplicar FFT recursivamente
3. **Combinar**: Usar fatores twiddle para combinar resultados

## 🎯 Funcionalidades

### Funções Auxiliares
- `formatarNumeroComplexo()`: Formatação elegante de números complexos
- `mostrarVetor()`: Exibição formatada de vetores
- `mostrarMatriz()`: Exibição formatada de matrizes
- `Wn()`: Cálculo do fator twiddle W_N^n

### Validações
- **FFT**: Verifica se N é potência de 2
- **DFT**: Aceita qualquer valor de N
- Tratamento de casos especiais (N=1)

## 📈 Comparação de Performance

| Algoritmo | Complexidade | Melhor para |
|-----------|-------------|-------------|
| DFT       | O(N²)       | N pequeno, fins educacionais |
| FFT       | O(N log N)  | N grande, aplicações práticas |

## 🔧 Requisitos

- Compilador C++ com suporte a C++11 ou superior
- Sistema operacional Unix/Linux (para Makefile)
- Bibliotecas padrão: `<complex>`, `<vector>`, `<cmath>`

## 📝 Notas de Implementação

- Os números complexos são exibidos no formato `a+bj` ou `a-bj`
- Valores muito pequenos (< 1e-10) são tratados como zero
- A FFT mostra o processo de divisão recursiva
- Ambas implementações suportam entrada de números reais

## 👨‍💻 Autor

Projeto desenvolvido para estudos de processamento de sinais digitais.
