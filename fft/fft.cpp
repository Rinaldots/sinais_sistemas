#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// Transformada Rapida de Fourier (FFT) é uma versão otimizada da DFT
// requer menor numero de operações

// ----- Funções de apoio ----- //
// Função para formatar número complexo
string formatarNumeroComplexo(complex<double> valor) {
    double real = valor.real();
    double imag = valor.imag();
    
    // Tratar casos especiais para exibição mais limpa
    if (abs(real) < 1e-10) real = 0;
    if (abs(imag) < 1e-10) imag = 0;
    
    if (real == 0 && imag == 0) {
        return "0";
    } else if (real == 0) {
        if (abs(imag - 1) < 1e-10) {
            return "j";
        } else if (abs(imag + 1) < 1e-10) {
            return "-j";
        } else {
            ostringstream oss;
            oss << fixed << setprecision(0) << imag << "j";
            return oss.str();
        }
    } else if (imag == 0) {
        if (abs(real - 1) < 1e-10) {
            return "1";
        } else if (abs(real + 1) < 1e-10) {
            return "-1";
        } else {
            ostringstream oss;
            oss << fixed << setprecision(0) << real;
            return oss.str();
        }
    } else {
        ostringstream oss;
        
        // Parte real
        if (abs(real - 1) < 1e-10) {
            oss << "1";
        } else if (abs(real + 1) < 1e-10) {
            oss << "-1";
        } else {
            oss << fixed << setprecision(0) << real;
        }
        
        // Parte imaginária
        if (abs(imag - 1) < 1e-10) {
            oss << "+j";
        } else if (abs(imag + 1) < 1e-10) {
            oss << "-j";
        } else if (imag > 0) {
            oss << "+" << fixed << setprecision(0) << imag << "j";
        } else {
            oss << fixed << setprecision(0) << imag << "j";
        }
        
        return oss.str();
    }
}
// Função para mostrar vetor
void mostrarVetor(const vector<complex<double>>& vetor, const string& titulo) {
    cout << titulo << ":" << endl;
    cout << "[";
    for (size_t i = 0; i < vetor.size(); ++i) {
        cout << setw(8) << formatarNumeroComplexo(vetor[i]);
        if (i < vetor.size() - 1) cout << "  ";
    }
    cout << "]" << endl << endl;
}
// ---------------------------- //

// função para calcular W_N^n
// Wn(n, N) = e^(-2 * pi * j * n / N)
complex<double> Wn(int n, int N) {
    double angle = -2.0 * M_PI * n / N;
    return complex<double>(cos(angle), sin(angle));
}

void dividir(const vector<complex<double>>& x, vector<complex<double>>* pares, vector<complex<double>>* impares) {
    int N = x.size();
    // redimensionar os vetores para o tamanho correto
    pares->resize(N / 2);
    impares->resize(N / 2);

    for (int i = 0; i < N / 2; ++i) {
        (*pares)[i] = x[i * 2];        // índices 0, 2, 4, 6...
        (*impares)[i] = x[i * 2 + 1];  // índices 1, 3, 5, 7...
    }
    cout << "Valor N: " << N << endl;
    mostrarVetor(*pares, "X_pares");
    mostrarVetor(*impares, "X_impares");
}

void conquistar(const vector<complex<double>>& pares, const vector<complex<double>>& impares, vector<complex<double>>* resultado) {
    int N = pares.size() + impares.size();
    resultado->resize(N);
    
    for (int k = 0; k < N / 2; ++k) {
        complex<double> W = Wn(k, N);
        (*resultado)[k] = pares[k] + W * impares[k];
        (*resultado)[k + N / 2] = pares[k] - W * impares[k];
    }
}

vector<complex<double>> fft(const vector<complex<double>>& x) {
    int N = x.size();
    if (N == 1)
        return x;

    vector<complex<double>> pares, impares;
    dividir(x, &pares, &impares);

    // recursão continua ate chegar ao caso base
    vector<complex<double>> fft_pares = fft(pares);
    vector<complex<double>> fft_impares = fft(impares);

    // a função conquistar combina os resultados das partes pares e ímpares
    vector<complex<double>> resultado;
    conquistar(fft_pares, fft_impares, &resultado);

    return resultado;
}

int main() {
    // entrada de pontos
    int N;
    cout << "Numero de pontos (Deve ser potencia de 2): ";
    cin >> N;
    // verifica se N é uma potência de 2
    if (N <= 0 || (N & (N - 1)) != 0) {
        cout << "N deve ser uma potência de 2." << endl;
        return 1;
    }
    vector<complex<double>> pontos(N);
    cout << "Digite os pontos:" << endl;
    for (int i = 0; i < N; ++i) {
        double valor;
        cout << "Digite o ponto " << (i + 1) << ": ";
        cin >> valor;
        pontos[i] = complex<double>(valor, 0);
    }
    
    vector<complex<double>> pares;
    vector<complex<double>> impares;
    vector<complex<double>> resultado = fft(pontos);
    mostrarVetor(resultado, "Resultado da FFT");

    return 0;
}

