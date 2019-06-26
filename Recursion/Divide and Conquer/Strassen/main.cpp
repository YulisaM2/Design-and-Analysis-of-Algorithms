// Yulisa Medina
// A01570056
// Proyecto Final Ejercicio Strassen
#include <iostream>
#include <math.h>

using namespace std;

int contStrassen = 0;

void multiplyMat(int a[132][132], int b[132][132], int c[132][132]){
    for(int i = 0; i < 2;++i){
        for(int j = 0; j < 2; ++j){
            c[i][j] = 0;
            for(int part = 0; part < 2; ++part){
                // Renglon contra columna
                c[i][j] += a[i][part] * b[part][j];
                ++contStrassen;
            }
        }
    }
}

void addMat(int a[132][132], int b[132][132], int c[132][132], int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void subMat(int a[132][132], int b[132][132], int c[132][132], int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            c[i][j] = a[i][j] - b[i][j];
        }
    }
}

void reconstructC(int c[132][132], int c11[132][132], int c12[132][132], int c21[132][132], int c22[132][132], int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            c[i][j] = c11[i][j];
            c[i][j + n] = c12[i][j];
            c[i + n][j] = c21[i][j];
            c[i + n][j + n] = c22[i][j];
        }
    }
}

void strassen(int a[132][132], int b[132][132], int c[132][132], int n){
    if(n <= 2){
        // Calcular C = A x B de forma tradicional
        multiplyMat(a,b,c);
    }else{
        // Calcular M1 hasta M7 llamando Strassen
        // Partir en cuatro segmentos A y B

        int a11[132][132], a12[132][132], a21[132][132], a22[132][132];
        int b11[132][132], b12[132][132], b21[132][132], b22[132][132];
        int aFull[132][132], bFull[132][132];

        // Actualizar nuevos segmentos
        for(int i = 0; i < n/2; ++i){
            for(int j = 0; j < n/2; ++j){
                a11[i][j] = a[i][j];
                a12[i][j] = a[i][j + n/2];
                a21[i][j] = a[i + n/2][j];
                a22[i][j] = a[i + n/2][j + n/2];

                b11[i][j] = b[i][j];
                b12[i][j] = b[i][j + n/2];
                b21[i][j] = b[i + n/2][j];
                b22[i][j] = b[i + n/2][j + n/2];
            }
        }
        // Optimizacion con 7 matrices de operaciones basicas
        int m1[132][132]; // (A11 + A22) * (B11 + B22)
        addMat(a11, a22, aFull, n/2);
        addMat(b11, b22, bFull, n/2);
        strassen(aFull, bFull, m1, n/2);

        int m2[132][132]; // (A21 + A22) * B11
        addMat(a21, a22, aFull, n/2);
        strassen(aFull, b11, m2, n/2);

        int m3[132][132]; // (B12 - B22) * A11
        subMat(b12, b22, bFull, n/2);
        strassen(a11,bFull, m3, n/2);

        int m4[132][132]; // (B21 - B11) * A22
        subMat(b21,b11, bFull, n/2);
        strassen(a22, bFull, m4, n/2);

        int m5[132][132]; //(A11 + A12) * B22
        addMat(a11, a12, aFull, n/2);
        strassen(aFull, b22, m5, n/2);

        int m6[132][132]; // (A21 + A11) * (B11 + B12)
        subMat(a21, a11, aFull, n/2);
        addMat(b11, b12, bFull, n/2);
        strassen(aFull, bFull, m6, n/2);

        int m7[132][132]; // (A12 - A22) * (B21 + B22)
        subMat(a12, a22, aFull, n/2);
        addMat(b21, b22, bFull, n/2);
        strassen(aFull, bFull, m7, n/2);

        // [M6 + M5 + M4 - M2] [M1 + M2]
        //  [M3 + M4]           [M1 + M5 - M3 - M7]

        int c11[132][132]; // M1 + M4 + - M5 + M7
        addMat(m1,m4,aFull, n/2);
        subMat(m7, m5,bFull, n/2);
        addMat(aFull, bFull, c11, n/2);

        int c12[132][132]; // M3 + M5
        addMat(m3, m5, c12, n/2);

        int c21[132][132]; // M2 + M4
        addMat(m2, m4, c21, n/2);

        int c22[132][132]; // M1 - M2 + M3 + M6
        subMat(m1, m2, aFull, n/2);
        addMat(m3,m6, bFull, n/2);
        addMat(aFull, bFull, c22, n/2);

        reconstructC(c, c11, c12, c21, c22, n/2);
    }
}

void printMat(int mat[132][132], const int& n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){

    int dimensions;
    cin >> dimensions;

    int a[132][132], b[132][132];

    for(int i = 0; i < dimensions; ++i){
        for(int j = 0; j < dimensions; ++j){
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < dimensions; ++i){
        for(int j = 0; j < dimensions; ++j){
            cin >> b[i][j];
        }
    }

    int c[132][132]; // [M6 + M5 + M4 - M2] [M1 + M2]
                    //  [M3 + M4]           [M1 + M5 - M3 - M7]

    for(int i = 0; i < dimensions; ++i){
        for(int j = 0; j < dimensions; ++j){
            c[i][j] = 0;
        }
    }

    int scalar = pow(dimensions,3);
    cout << "Traditional Scalar Multiplications: " << scalar << endl;

    strassen(a,b,c,dimensions);

    cout << "Strassen Scalar Multiplications: " << contStrassen << endl;

    printMat(c,dimensions);

    return 0;
}
