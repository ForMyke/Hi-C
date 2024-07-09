#include <stdio.h>
#include <string.h>
#include <math.h>

//----Prototzipo de Funciones----
long long multiplica(long long X, long long Y, int n);
void multiplicacionPar();
void multiplicacionImpar();
void multiplicacionDiferentes(long long X, long long Y);
void menu();

//-------CUERPO DE MAIN-------
int main(){
    //LLamamos el menu
    menu();
    return 0;
}

//--------Función Menu--------
void menu(){
    int opcion;
    
    do {
        printf("\n--------------- Men%c ---------------\n",151);
        printf("1. Entradas iguales de tama%co par\n",164);
        printf("2. Entradas iguales de tama%co impar\n",164);
        printf("3. Entradas con diferente tama%co\n",164);
        printf("4. Salir\n");
        printf("\n-----------------------------------\n",151);
        printf("Ingrese su opci%cn: ",162);
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                multiplicacionPar();
                break;
            case 2:
                multiplicacionImpar();
                break;
            case 3:
                {
                long long X, Y;
                printf("Ingrese el primer n%cmero: ", 163);
                scanf("%lld", &X); // Usar %lld para long long
                printf("Ingrese el segundo n%cmero: ", 163);
                scanf("%lld", &Y); // Usar %lld para long long
                multiplicacionDiferentes(X, Y);
                }
                break;

            case 4:
                printf("Adi%cs\n",162);
                break;
            default:
                printf("Digite una opci%cn correcta\n",162);
        }
    } while (opcion != 4);
}

//----Funciones de multiplicaciones----
//FUNCIÓN MULTIPLICA PRINCIPAL
long long multiplica(long long X, long long Y, int n) {
    if (n < 10) {
        return X * Y;
    }
    else {
        n= fmax(log10(X) + 1, log10(Y) + 1);
        long long potencia = n / 2;
        long long xi = X / pow(10, potencia);
        long long xd = X % (long long)pow(10, potencia);
        long long yi = Y / pow(10, potencia);
        long long yd = Y % (long long)pow(10, potencia);

        long long z1 = multiplica(xi, yi, potencia);
        long long z2 = multiplica(xi + xd, yi + yd, potencia);
        long long z3 = multiplica(xd, yd, potencia);

        long long resultado = (long long)pow(10, n) * z1 + (long long)pow(10, potencia) * (z2 - z1 - z3) + z3;

        return resultado;
    }
}

//FUNCIÓN MULTIPLICA CON ENTRADAS DIFERENTES
void multiplicacionDiferentes(long long X, long long Y){
    int n1 = log10(X) + 1;
    int n2 = log10(Y) + 1;
    int n = (n1 > n2) ? n1 : n2;
    long long resultado = multiplica(X, Y, n);
    printf("El resultado de la multiplicaci%cn es: %lld\n", 162, resultado); // Usar %lld para long long
}

//FUNCIÓN MULTIPLICA NÚMEROS PARES
void multiplicacionPar() {
    long long X, Y; // Cambiar int a long long
    // Ingreso de los numeros de parte del usario 
    printf("Ingrese el primer n%cmero debe ser Par: ",163);
    scanf("%lld", &X); // Usar %lld para long long
    printf("Ingrese el segundo n%cmero debe ser Par: ",163);
    scanf("%lld", &Y); // Usar %lld para long long
    int n = log10(X) + 1;

    if (n % 2 == 0) { // Si es par
        long long resultado = multiplica(X, Y, n);
        printf("El resultado de la multiplicaci%cn es: %lld\n", 162, resultado); // Usar %lld para long long
    } else {
        printf("El tamaño de los n%cmeros no es par.\n",163);
    }
}

//FUNCIÓN MULTIPLICA NÚMEROS IMPARES
void multiplicacionImpar() {
    long long X, Y; // Cambiar int a long long
    // Ingreso de los numeros de parte del usario 
    printf("Ingrese el primer n%cmero debe ser Impar: ",163);
    scanf("%lld", &X); // Usar %lld para long long
    printf("Ingrese el segundo n%cmero debe ser Impar: ",163);
    scanf("%lld", &Y); // Usar %lld para long long
    int n = log10(X) + 1;

    if (n % 2 != 0) { // Si es impar
        long long resultado = multiplica(X, Y, n);
        printf("El resultado de la multiplicaci%cn es: %lld\n",162, resultado); // Usar %lld para long long
    } else {
        printf("El tamaño de los n%cmeros no es impar.\n",163);
    }
}