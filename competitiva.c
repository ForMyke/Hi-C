#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//------DEFINICIÓN DE VARIABLES GLOBALES---------

//CUERPO DE MAIN:
int main(){
	char string[100]; //nombre de la variable solicitada para la resolución
	//del algoritmo denominada como "s" se nombrara a string 
	int longitud, i, j;
	int num_mayus, num_minus, num_espacios;
	
	
	/*comenzamos inicializando que valor de la longitud, que corresponde a 
	cadena que el usuario ingresa*/
	printf("\t\t\tSOLVING PROBLEM NO. 1\n");
	printf("\nCambiar entre may%csculas y min%csculas", 163, 163);
	printf("\nInserte la frase o palabra a acomodar: ");
	fgets(string, sizeof(string), stdin); //leemos la cadena de entrada 
	//sin necesidad de colocar un fflush
	
	//ALGORITMO DE RESOLUCIÓN DEL PROBLEMA:
	longitud= strlen(string);
	for(i=0; i<longitud; i++){ 
		if (isupper(string[i])){
			num_mayus++;
		}else if(islower(string[i])){
			num_minus++;
		}else if(string[i]==' '){
			num_espacios++;
		}
	}
	
	j=0;
	if(num_mayus==num_minus&& j<longitud){
		for(i=0; i<longitud; i++){
			string[i]=tolower(string[i]);
			j++;
		}	
				
	}else if(num_mayus>num_minus&&j<longitud){
		for(i=0; i<longitud; i++){
			string[i]=toupper(string[i]);
			j++;
		}
	}else if(num_mayus<num_minus&&j<longitud){
		for(i=0; i<longitud; i++){
			string[i]=tolower(string[i]);
			j++;
		}
	}
	
	printf("\nTu cadena de caracteres arreglada es: ");
	for(i=0; i < longitud ;i++){
		printf("%c", string[i]);
	}
	
	return 0;
	
	
}