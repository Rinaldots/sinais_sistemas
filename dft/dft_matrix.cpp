#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// Função para calcular W_N^n
// Wn(n, N) = e^(-2 * pi * j * n / N)
complex<double> Wn(int n, int N) {
    double angle = -2.0 * M_PI * n / N;
    return complex<double>(cos(angle), sin(angle));
}

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

// Função para mostrar matriz
void mostrarMatriz(const vector<vector<complex<double>>>& matriz, const string& titulo) {
    cout << titulo << ":" << endl;
    for (const auto& linha : matriz) {
        cout << "[";
        for (size_t i = 0; i < linha.size(); ++i) {
            cout << setw(8) << formatarNumeroComplexo(linha[i]);
            if (i < linha.size() - 1) cout << "  ";
        }
        cout << "]" << endl;
    }
    cout << endl;
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

// Função para multiplicar matriz por vetor
vector<complex<double>> multiplicarMatrizVetor(const vector<vector<complex<double>>>& matriz, 
                                              const vector<double>& vetor) {
    int N = matriz.size();
    vector<complex<double>> resultado(N, complex<double>(0, 0));
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            resultado[i] += matriz[i][j] * vetor[j];
        }
    }
    
    return resultado;
}

int main() {
    int N;
    cout << "Numero de pontos: ";
    cin >> N;
    
    vector<double> pontos(N);
    cout << "Digite os pontos:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "Digite o ponto " << (i + 1) << ": ";
        cin >> pontos[i];
    }
    
    // Cria a matriz nxn e preenche com Wn(n*k, N). Equivale a matrix de vandermonde
    vector<vector<complex<double>>> matriz_dft(N, vector<complex<double>>(N));
    for (int n = 0; n < N; ++n) {
        for (int k = 0; k < N; ++k) {
            matriz_dft[n][k] = Wn(n * k, N);
        }
    }
    
    // Multiplica a matriz de vandermonde pelo vetor de pontos de entrada
    vector<complex<double>> resultado = multiplicarMatrizVetor(matriz_dft, pontos);
    
    // Exibir resultados
    mostrarMatriz(matriz_dft, "Matriz DFT");
    
    // Formata os pontos de entrada como números complexos para usar na funçao mostrarVetor
    // Isso é necessário porque a função mostrarVetor espera um vetor de complex<double>
    vector<complex<double>> pontos_complex(N);
    for (int i = 0; i < N; ++i) {
        pontos_complex[i] = complex<double>(pontos[i], 0.0);
    }
    mostrarVetor(pontos_complex, "Vetor de entrada x(n)");
    
    mostrarVetor(resultado, "Resultado X(k) = DFT{x(n)}");
    
    return 0;
}
