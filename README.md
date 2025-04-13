# Combinaciones en Orden Lexicográfico
*Autor: Mario Alberto Ocejo Quijada*

Programa en C++ que consigue todas las combinaciones de n en r de un conjunto de la forma {1, 2, 3, ..., n}.

Después, todas estas combinaciones son impresas en un archivo csv.

# Requisitos del sistema:

- **C++**
- **GCC (GNU Compiler Collection)**
- **g++**

# Instrucciones de compilación y ejecución:

1. Clonar el repositorio
``` sh
git clone https://github.com/mocejo/Evaluacion-de-Polinomios.git
```
2. Entrar al directorio del proyecto
```sh
cd Evaluacion-de-Polinomios
```
3. Compilar el código 
```sh
g++ "Archivo CPP/EvaluacionDePolinomios.cpp" -o EvaluacionDePolinomios
```
4. Ejecutar código
```sh
./EvaluacionDePolinomios
```
**Forma práctica:**  

Descargar el archivo ```EvaluacionDePolinomios.cpp``` y compilar desde un IDE a su preferencia.


# Explicación del algoritmo

El algoritmo genera todas las combinaciones posibles de un conjunto de `n` elementos tomados de `r` en `r` (es decir, combinaciones de tamaño `r`). Utiliza un enfoque iterativo basado en índices para generar las combinaciones en orden lexicográfico.

### **Pasos del Algoritmo**
1. **Validación de Entrada**:
   - Si `r > n` o `r < 0`, se muestra un mensaje de error y se termina la ejecución.
   - Si `r == 0`, se imprime el símbolo del conjunto vacío (`∅`) y se termina la ejecución.

2. **Inicialización**:
   - Se crea un arreglo dinámico `s` de tamaño `r` para almacenar los índices actuales de la combinación.
   - Se inicializan los índices de la primera combinación como `{0, 1, 2, ..., r-1}`.

3. **Generación de Combinaciones**:
   - Se utiliza un bucle `do-while` para generar combinaciones de manera iterativa.
   - En cada iteración:
     - Se imprime la combinación actual utilizando los índices almacenados en `s`.
     - Se busca el índice más a la derecha (`m`) que pueda ser incrementado sin exceder los límites del conjunto.
     - Si no se encuentra tal índice (`m < 0`), significa que se han generado todas las combinaciones posibles, y el bucle termina.
     - Si se encuentra un índice válido, se incrementa y se actualizan los índices a la derecha de `m` para mantener el orden lexicográfico.

4. **Finalización**:
   - Se imprime el número total de combinaciones generadas.
   - Se libera la memoria dinámica utilizada para el arreglo `s`.


# Orden Lexicográfico:

### **¿Qué es el Orden Lexicográfico?**

El **orden lexicográfico** es un método de ordenar elementos de manera similar a cómo se ordenan las palabras en un diccionario. En este orden, los elementos se comparan uno a uno, siguiendo una secuencia predefinida, y se determina cuál es "menor" o "mayor" según su posición relativa.

## Definición Formal

Dadas dos secuencias `[a₁, a₂, ..., aₖ]` y `[b₁, b₂, ..., bₖ]`, se dice que:

```
[a₁, a₂, ..., aₖ] < [b₁, b₂, ..., bₖ]
```

si existe un índice `k` tal que:

- `aₖ < bₖ`, y
- `aᵢ = bᵢ` para todo `i < k`.
  
El código genera combinaciones en **orden lexicográfico** siguiendo un enfoque basado en índices. Aquí está el desglose de cómo lo hace:

---

### **1. Representación de Combinaciones con Índices**
El algoritmo utiliza un arreglo `s` de tamaño `r` para representar las combinaciones. Cada elemento de `s` es un índice que apunta a un elemento del conjunto original `A`.

---

### **2. Inicialización**
El arreglo `s` se inicializa con los índices de la primera combinación:
```cpp
for (int i = 0; i < r; ++i) {
    s[i] = i;
}
```
Esto asegura que la primera combinación generada sea `{A[0], A[1], ..., A[r-1]}`, que es la combinación más pequeña en orden lexicográfico.

---

### **3. Generación Iterativa**
El algoritmo utiliza un bucle `do-while` para generar las combinaciones de manera iterativa. En cada iteración:
1. **Imprime la combinación actual**:
   - Utiliza los índices en `s` para acceder a los elementos de `A` y generar la combinación correspondiente.

2. **Encuentra el índice más a la derecha (`m`) que pueda ser incrementado**:
   ```cpp
   int m = r - 1;
   while (m >= 0 && s[m] == n - r + m) {
       --m;
   }
   ```
   - Este paso asegura que el índice `s[m]` no exceda su límite permitido. Por ejemplo:
     - Si `n = 4`, `r = 2`, y `s = {2, 3}`, no se puede incrementar `s[1]` porque ya está en su límite (`3`).

3. **Incrementa el índice `s[m]` y ajusta los índices a la derecha**:
   ```cpp
   ++s[m];
   for (int j = m + 1; j < r; ++j) {
       s[j] = s[j - 1] + 1;
   }
   ```
   - Esto asegura que los índices a la derecha de `m` sean consecutivos y mayores que `s[m]`.

---

### **4. Condición de Terminación**
El bucle termina cuando no se puede encontrar un índice `m` que pueda ser incrementado:
```cpp
if (m < 0) {
    break;
}
```
Esto ocurre cuando `s` alcanza su última configuración posible.


# Validación de entrada:    

El programa solicita al usuario que ingrese los valores de n (tamaño del conjunto) y de r (tamaño de combinaciones), para esto, estas variables se han limitado a los siguientes valores: 

### **Para n (tamaño del conjunto):**
- Límite inferior: n > 1 (el conjunto necesita al menos un elemento)
- Límite superior: n ≤ 22

Mótivo: 
- Prevenir archivos CSV muy grandes
- Evitar el límite de 1,048,576 filas en Microsoft Excel

### **Para r (tamaño de combinaciones):**
- Límite inferior: r ≥ 0
- Límite superior: r ≤ n (No puede haber más combinaciones que el tamaño del conjunto)

# Formato de salida: 

El programa genera las combinaciones en un archivo CSV con el siguiente formato: 

- **Nombre del archivo:** Combinaciones.csv
- **Para cada combinación:** Se imprime cada combinación en filas, yendo desde la combinación más chica a la más grande.

# Verificación C(n,r): 

### Verificación de resultados

Al finalizar la ejecución, el programa **verifica** que el número de combinaciones contadas durante el experimento coincida con el número de combinaciones calculadas mediante la fórmula matemática:


C(n, r) = n! / ( r! (n - r)! )

Esta verificación asegura que los resultados obtenidos sean correctos y consistentes con la teoría combinatoria.










