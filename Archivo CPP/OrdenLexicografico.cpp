#include <iostream>
#include <limits>
#include <fstream>


using namespace std;

long double Factorial (int n);
long double Combinaciones (int n, int r);
void generarCombinaciones(int* A, int n, int r);
void capturarNumero ( int &num, const char solicitud[]);

int main() {

    int n, r;

    cout << "Este es un programa que calcula las combinaciones de n elementos tomados de r en r.\n" << endl;
    cout << "Considere el valor de n como el tamaño del conjunto y el valor de r como el tama\244o de la combinacion.\n" << endl;
    cout << "De forma en que el conjunto sera {1, 2, 3, ..., n}.\n" << endl;

    capturarNumero(n, "Ingrese el tama\244o del conjunto en un rango de [1, 22]: ");
    while (n <= 0 || n > 22) { // Limitar el tamaño del conjunto a un máximo de 22 
        cout << "El tama\244o del conjunto debe ser un número positivo menor o igual a 2. Intente nuevamente.\n";
        capturarNumero(n, "Ingrese el tama\244o del conjunto en un rango de [1, 22]: ");
    }

    capturarNumero(r, "Ingrese el tama\244o de la combinacion: ");
    while (r < 0 || r > n) {
        cout << "El tama\244o de la combinacion debe estar entre 0 y " << n << ". Intente nuevamente.\n";
        capturarNumero(r, "Ingrese el tama\244o de la combinacion (r): ");
    }

    

    int *Conjunto = new int[n]; // Crear un arreglo dinámico para el conjunto

    for (int i = 0; i < n; ++i) {
        Conjunto[i] = i + 1; // Llenar el conjunto con los valores {1, 2, ..., n}
    }

    cout << "Todas las combinaciones del conjunto son: \n";
    generarCombinaciones(Conjunto, n, r); // Generar combinaciones
    cout << "\nMientras el total de combinaciones de forma teorica es de: " << Combinaciones(n, r) << endl; // Imprimir el total de combinaciones

    delete [] Conjunto; // Liberar memoria del arreglo dinámico


    return 0;
}


long double Factorial (int n) {
    if (n <= 1 ) {
        return 1;
    }
    return n * Factorial(n - 1);
}

long double Combinaciones (int n, int r) {
    return Factorial(n) / (Factorial(r) * Factorial(n - r));
}

void generarCombinaciones(int* A, int n, int r) {
    if (r > n || r < 0) {
        cerr << "El valor de r debe estar entre 0 y " << n << ".\n";
        return;
    }

    if (r == 0) {
        // Caso especial: combinación vacía
        cout  << u8"\u2205" << endl; // Imprimir el símbolo de conjunto vacío
        cout << "Solo se puede generar la combinacion vacia.\n";
        return;
    }

    int* s = new int[r]; // Arreglo dinámico para almacenar los índices de la combinación actual
    int contador = 0; // Contador para las combinaciones generadas

    // Abrir el archivo CSV para escritura
    ofstream archivo("Combinaciones.csv");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir las combinaciones.\n";
        delete[] s;
        return;
    }

    // Escribir el encabezado
    archivo << "Combinaciones:\n";

    // Inicializar con los índices de la primera combinación
    for (int i = 0; i < r; ++i) {
        s[i] = i; // Se inicia desde 1 para evitar el índice 0
    }

    // Procesar/Imprimir la primera combinación
    do {
        for (int i = 0; i < r; ++i) {
            archivo << A[s[i]]; // Escribir el número en el archivo
            if (i < r - 1) {
                archivo << ","; // Separar los números con comas
            }
        }
        archivo << "\n"; // Nueva línea para la siguiente combinación

        ++contador; // Incrementar el contador de combinaciones generadas

        // Encontrar el índice 'm' más a la derecha que se pueda incrementar
        int m = r - 1; 
        while (m >= 0 && s[m] == n - r + m) {
            --m;
        }

        if (m < 0) {
            break; // Terminar si ya se generó la última combinación
        }

        // Incrementar el índice en la posición m encontrada
        ++s[m];

        // Actualizar los índices a la derecha de m
        for (int j = m + 1; j < r; ++j) {
            s[j] = s[j - 1] + 1;
        }

    } while (true);

    cout << "\nSe generaron " << contador << " combinaciones.\n"; // Imprimir el total de combinaciones generadas

    if (contador == Combinaciones(n, r)) {
        cout << "Todas las combinaciones fueron generadas correctamente.\n";
    }

    // Cerrar el archivo
    archivo.close();

    delete[] s; // Liberar memoria del arreglo dinámico
}

void capturarNumero ( int &num, const char solicitud[]) {
    std::cout << solicitud;
    std::cin >> num;
    while (std::cin.fail()){
        std::cin.clear();
        std ::cin.ignore (std::numeric_limits <int>::max(), '\n');
        std::cout << solicitud;
        std ::cin >> num;
    }
}
