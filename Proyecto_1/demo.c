#include <stdio.h>
#include <stdlib.h>
#include "meteo.h"


int main(int argc, char* argv[]){
	Fecha date1, date2;
	WeatherStation *datos;// permite imprimir os elementos da liña deseada
	datos=malloc(sizeof(WeatherStation));//reservamos un numero de bytes para almacenar datos(paso por referencia)
	int controlador, *num_estaciones;

	num_estaciones = (int*)malloc(sizeof(int));
	datos = Funcion_3(argv[1], num_estaciones);

	while(1){
		printf("\n0.Temperatura max e min entre duas fechas\n");
		printf("1.Temperatura max e min media nunha fecha\n");
		printf("2.Cerrar el programa\n");
		printf("Que consulta quiere realizar?\n");
		scanf("%i",&controlador);
		switch(controlador){
		case 0:
			//programa para consultar datos

			printf("FECHA 1\n");
			date1 = leer_fecha();
			printf("FECHA 2\n");
			date2 = leer_fecha();
			Funcion_4(date1, date2, datos, *num_estaciones);
            //liberamos la memoria
			break;


			//consultar la precipitacion media
		case 1:


			printf("FECHA\n");
			date1 = leer_fecha();
			Funcion_5(date1, datos, *num_estaciones);

			break;

		case 2:
			printf("\n\nGracias por su consulta :)");
			free(datos);
			return 0;
		}
	}
}

