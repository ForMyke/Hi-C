
void imprimirSolucionOptima(int **dinamica, int *pesos, int *valores, int n, int capacidad);

// ------------ CUERPO DE MAIN --------------
int main() {
    int capacidad, numObjetos, sumaPesos, opcion;
    int *pesos, *valores;
    int **dinamica;
    
    printf("\t\t\tPROBLEMA DE LA MOCHILA ENTERA \n");
    printf("Eliga alguna de las opciones que se presentan a continuaci%cn: \n", 162);
    printf("1. Inserci%cn manual de los datos\n", 162);
    printf("2. Inserci%cn de datos randomizados autom%cticos con un l%cmite de peso m%cximo\n", 162, 160, 161, 160);
    printf("3. Inserci%cn de datos randomizada y asigne valor dependiendo de los pesos aleatorios\n", 162);
    printf ("Digite la opci%cn seleccionada: ", 162);
    scanf("%d", &opcion);

    printf("Ingrese el numero de objetos: ");
    scanf("%d", &numObjetos);
    
    pesos = (int *)malloc(numObjetos * sizeof(int));
    valores = (int *)malloc(numObjetos * sizeof(int));

    sumaPesos = 0;
    capacidad = 0;
    
    if(opcion== 1){
    	printf("Ingrese el peso maximo de la mochila: ");
    	scanf("%d", &capacidad);
    	for (int i = 0; i < numObjetos; i++) {
    	printf("Ingrese el peso del objeto %d: ", i+1);
    	scanf("%d", &pesos[i]);
    	printf("Ingrese el valor del objeto %d: ", i+1);
    	scanf("%d", &valores[i]);
        sumaPesos += pesos[i];
        if (numObjetos < 50) {
            printf("|Objeto %d: %dkg, $%d|\n", i + 1, pesos[i], valores[i]);
        }
      }	
    	
	} else if(opcion == 2){
		printf("Ingrese el peso maximo de la mochila: ");
   		scanf("%d", &capacidad);
		for (int i = 0; i < numObjetos; i++) {
        pesos[i] = rand() % capacidad + 1;
        valores[i] = rand() % 50 + 1;
        sumaPesos += pesos[i];
        if (numObjetos < 50) {
            printf("Objeto %d: %dkg, $%d\n", i + 1, pesos[i], valores[i]);
        }
      }	
	}else if(opcion == 3){
		for (int i = 0; i < numObjetos; i++) {
        pesos[i] = rand() % 30 + 1;
        valores[i] = rand() % 50 + 1;
        sumaPesos += pesos[i];
        if (numObjetos < 50) {
            printf("Objeto %d: %dkg, $%d\n", i + 1, pesos[i], valores[i]);
       }
       	
	 }
	}else if (opcion != 1 || opcion != 2 || opcion != 3){
		printf ("La opci%cn no es v%clida, se finaliza el programa. \n", 162, 160);
	}
    
    if (capacidad ==0){
    	printf("Ingrese el peso maximo de la mochila: ");
    	scanf("%d", &capacidad);
	}

    if (capacidad > sumaPesos) {
        printf("El peso maximo rebasa la suma total de los pesos de los objetos.\n");
    } else {
        dinamica = (int **)malloc((numObjetos + 1) * sizeof(int *));
        for (int i = 0; i <= numObjetos; i++) {
            dinamica[i] = (int *)malloc((capacidad + 1) * sizeof(int));
        }

        for (int i = 0; i <= numObjetos; i++) {
            for (int w = 0; w <= capacidad; w++) {
                if (i == 0 || w == 0) {
                    dinamica[i][w] = 0;
                } else if (pesos[i - 1] <= w) {
                    dinamica[i][w] = (valores[i - 1] + dinamica[i - 1][w - pesos[i - 1]]) > dinamica[i - 1][w] ? (valores[i - 1] + dinamica[i - 1][w - pesos[i - 1]]) : dinamica[i - 1][w];
                } else {
                    dinamica[i][w] = dinamica[i - 1][w];
                }
            }
        }
        printf("Solucion:\n");
        imprimirSolucionOptima(dinamica, pesos, valores, numObjetos, capacidad);

        for (int i = 0; i <= numObjetos; i++) {
            free(dinamica[i]);
        }
        free(dinamica);
    }

    free(pesos);
    free(valores);

    return 0;
}

void imprimirSolucionOptima(int **dinamica, int *pesos, int *valores, int n, int capacidad) {
    int i = n;
    int w = capacidad;
    int pesosT = 0, valoresT = 0;

    while (i > 0 && w > 0) {
        if (dinamica[i][w] != dinamica[i - 1][w]) {
            int pesoObjeto = pesos[i - 1];
            int valorObjeto = valores[i - 1];
            printf("Objeto %d: %dkg, $%d\n", i, pesoObjeto, valorObjeto);
            pesosT += pesoObjeto;
            valoresT += valorObjeto;
            w -= pesoObjeto;
        }
        i--;
    }
    printf("Peso total de la solucion optima: %dkg\n", pesosT);
    printf("Valor total de la solucion optima: $%d\n", valoresT);