
/*
AUTORES:
    CRISTIAN NOVOA GONZALEZ
    XAVIER PRIMOI MARTINEZ
    IVAN QUINTANS GONZALEZ
LUGAR: SANTIAGO DE COMPOSTELA
VERSION: GOTO
FECHA: 22/12/2021
COMPANIA: USC
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "meteo.h"


// FUNCIONES PRINCIPALES

//FUNCIONES MAXIMOS Y MINIMOS
void Funcion_5(Fecha fecha, WeatherStation *estaciones, int num_estaciones){
    int i;
    float summax=0, summin=0, max, min;
    for (i=0; i<num_estaciones; i++){ // Desde que i es la primera estación hasta que es la última
        if(!check_date(fecha, (estaciones+i)->datos)){ // Comprueba que la fecha es correcta
            printf("Data invalida para estacion %s\n", (estaciones+i)->estacion.nombre);
        }else{
            summax += tmax_date(fecha, (estaciones+i)->datos); // Suma de las temperaturas máximas
            summin += tmin_date(fecha, (estaciones+i)->datos); // Suma de las temperaturas mínimas
        }
    }
    // Hacemos las medias
    max = summax/i;
    min = summin/i;
    printf("\nMedia temperatura maxima: %f\nMedia temperatura minima: %f\n", max, min);
}

void Funcion_4(Fecha fecha1, Fecha fecha2, WeatherStation *estaciones, int num_estaciones){

    int i;
    float max = 0, min = 0;
    Station est_max, est_min;
    for(i=0; i<num_estaciones; i++) {
        if (max < max_bw_dates(fecha1, fecha2, (estaciones+i)->datos)){ // Si max es menor que el siguiente máximo
            max = max_bw_dates(fecha1, fecha2, (estaciones+i)->datos); // Cambiamos de máximo
            // Cambiamos de estación
            est_max.longitud = (estaciones+i)->estacion.longitud;
            est_max.latitude = (estaciones+i)->estacion.latitude;
            est_max.elevacion = (estaciones+i)->estacion.elevacion;

        }
        if (min > min_bw_dates(fecha1, fecha2, (estaciones+i)->datos)){ // Si min es mayor que el siguiente mínimo
            min = min_bw_dates(fecha1, fecha2, (estaciones+i)->datos); // Cambiamos de mínimo
            // Cambiamos de estación
            est_min.longitud = (estaciones+i)->estacion.longitud;
            est_min.latitude = (estaciones+i)->estacion.latitude;
            est_min.elevacion = (estaciones+i)->estacion.elevacion;

        }
    }
    printf("\nTemperatura minima: %f, Estacion: Long %f Lat %f Elev %f\n", min, est_min.longitud, est_min.latitude, est_min.elevacion);
    printf("\nTemperatura maxima: %f, Estacion: Long %f Lat %f Elev %f\n", max, est_max.longitud, est_max.latitude, est_max.elevacion);
}


// FUNCIONES CARGA DE DATOS
// Aportamos el número de estaciones para saber las iteraciones
WeatherStation *Funcion_3(char *archivo_nombres, int *num_estaciones){
    WeatherStation *zona_estaciones;
    FILE *archivo;
    int i;
    char nombre_csv[30], temp[30];

    if((archivo = fopen(archivo_nombres, "r")) == NULL){
        printf("Erro na abertura do arquivo de lectura (%s)!!\n", archivo_nombres);
        exit(1);
    }
    // Obter o número de archivos que hay
    while(feof(archivo) == 0){
        fscanf(archivo, "%s", &temp);
        i++;
    }
    *num_estaciones = i;
    zona_estaciones = (WeatherStation*)malloc(sizeof(WeatherStation)*i);
    rewind(archivo);

    i = 0;
    // Carga los datos de cada uno de los archivos csv
    while(feof(archivo) == 0){
        fscanf(archivo, "%s", &nombre_csv);
        *(zona_estaciones+i) = Funcion_2(nombre_csv);
        if(!(zona_estaciones+i)->estacion.latitude == 0) i++;
    }

    fclose(archivo);
    return zona_estaciones;
}

WeatherStation Funcion_2(char *archivo_csv){
    WeatherStation data;
    FILE *archivo;
    char *archivo_txt;
    int temp;

    archivo_txt = leer_csv(archivo_csv);
    if((archivo = fopen(archivo_txt, "r")) == NULL){
        printf("Erro na abertura do arquivo de lectura (%s)!!", archivo_csv);
        data.estacion.latitude = 0;
        return data;
    }

    data.estacion.nombre = (char*)malloc(sizeof(30));
    data.estacion.nombre = strtok(archivo_csv, ".");

    // Obtiene los datos de la estación
    fscanf(archivo, "%i", &temp);
    fscanf(archivo, "%i", &temp);
    fscanf(archivo, "%i", &temp);
    fscanf(archivo, "%f", &data.estacion.longitud);
    fscanf(archivo, "%f", &data.estacion.latitude);
    fscanf(archivo, "%f", &data.estacion.elevacion);
    rewind(archivo);
    data.datos = Funcion_1(archivo);

    // Elimina los archivos txt creados para la obtencion de datos
    remove(archivo_txt);
    free(archivo_txt);
    return data;
}

WeatherData *Funcion_1(FILE *archivo){
    WeatherData *data;
    int num_elementos = 0, i;
    float temp;
    char in[300];

    // Obtenemos el número de elementos WeatherData del archivo
    while(feof(archivo) == 0){

        for(i = 0; i<12; i++) fscanf(archivo, "%f", &temp);
        num_elementos++;
    }
    data = (WeatherData*)malloc(sizeof(WeatherData)*(num_elementos-1));
    rewind(archivo);
    leer_archivo(archivo, data, num_elementos-1);
    fclose(archivo);
    return data;

}



// FUNCIONES DE TRATA DE ARCHIVOS
char *leer_csv(char *csv){

    FILE *pin, *pout; //punteiro ao archivo de lectura (in) e ao de saida (out)
    char in[300];
    char *csv_simplified, *temp;
    int i;

    temp = (char*)malloc(30);
    csv_simplified = (char*)malloc(30);

    // Creamos o nome do archivo .txt cos datos
    strcpy(temp, csv);
    cambio_extension(temp, ".txt");
    strcpy(csv_simplified, temp);
    free(temp);

    //Abrir arquivos
    if((pin = fopen(csv, "r")) == NULL){
        printf("Erro na apertura de archivo csv (%s)!!\n", csv);
        return NULL;
    }else if((pout = fopen(csv_simplified, "w")) == NULL){
        printf("Erro na apertura de archivo txt de destino!!\n");
        return NULL;
    }else{
        //Lee a primeira linea do arquivo e olvidase dela
        fgets(in, 300, pin);
        // Cando todo o archivo sexa leido, feof(archivo) é distinto de 0
        while(feof(pin) == 0){
            //Lee linea a linea do arquivo
            fgets(in, 300, pin);

            //Lee o segundo dos CRLF
            fgetc(pin);
            rem_crlf(in);

            /*O caracter especial \0 delimita o fin do string
            Itera character a character por cada linea
            Elimina as comas, comillas e barras
            Escribeios no arquivo de destino
            */
            i = 0;
            while(in[i] != '\0'){
                if(in[i] == '\"' || in[i] == '/' || in[i] == ',') in[i] = ' ';
                fputc(in[i], pout);
                i++;
            }
        }
    }

    //Pechamos os archivos
    fclose(pin);
    fclose(pout);
    return csv_simplified;
}

void leer_archivo(FILE *file, WeatherData *data, int num_elementos){
    int i = 0;
    float temp;
    for(i; i<num_elementos; i++){
        fscanf(file, "%i", &(data+i)->fecha.mes);
        fscanf(file, "%i", &(data+i)->fecha.dia);
        fscanf(file, "%i", &(data+i)->fecha.year);
        fscanf(file, "%f", &temp);
        fscanf(file, "%f", &temp);
        fscanf(file, "%f", &temp);
        fscanf(file, "%f", &(data+i)->max_t);
        fscanf(file, "%f", &(data+i)->min_t);
        fscanf(file, "%f", &(data+i)->precipitacion);
        fscanf(file, "%f", &(data+i)->viento);
        fscanf(file, "%f", &(data+i)->humedad);
        fscanf(file, "%f", &(data+i)->solar);
    }
}

// elimina o retorno de carro e o salto de linea
void rem_crlf(char *array){
    int i = 0;
    while(*(array+i) != 13 && *(array+i) != 10){
        i++;
    }
    *(array+i) = '\0';
}

// Cambia o nome dun archivo e gardaio nunha varible
void cambio_extension(char *archivo, char *extension){
    char *temp, delimitador[] = ".";
    if((strtok(archivo, delimitador)) == NULL){
        printf("ERRO non se introduciu nome\n");
    }else if((strtok(NULL, delimitador)) == NULL){
        printf("ERRO non se introduciu extension\n");
    }else strcat(archivo, extension);

}


// FUNCIONES DE MANEJO DE FECHAS
int indice(Fecha fecha, WeatherData *datos){
    int i, indice = 0;
    int dias_mes[12] = {31, 28 + bixesto(fecha.year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Calculo diferencia en dias desde o ano 0 (2000) ata o da fecha
    for(i = datos->fecha.year; i < fecha.year; i++){
        if (bixesto(i))
            indice += 1;
        indice += 365;
    }

    indice += ordinal(fecha);
    return indice - ordinal(datos->fecha);
}

int ordinal(Fecha fecha){

    int i = 0, ordinal = 0;
    int dias_mes[12] = {31, 28 + bixesto(fecha.year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for(i; i < (fecha.mes - 1); i++) ordinal += dias_mes[i];

    /* Sumamos o dia do mes actual
    para considerar o 1 de xaneiro como 0 */
    ordinal += fecha.dia-1;
    return(ordinal);
}

int bixesto(int year){
    return (!(year % 400) || (!(year % 4) && (year % 100)));
}

Fecha leer_fecha(void){
    Fecha fecha;
    int dias_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    do{
        printf("Introduce unha data (mm/dd/yyyy):");
        scanf("%i %i %i", &fecha.mes, &fecha.dia, &fecha.year);
        dias_mes[1] = 28 + bixesto(fecha.year);
    }while(fecha.dia > dias_mes[fecha.mes - 1] || fecha.mes > 12 ||
    fecha.dia <= 0 || fecha.mes <= 0);
    return fecha;
}

// Comproba que a fecha sexa valida
int check_date(Fecha fecha, WeatherData *datos){
    if(fecha.year < (datos)->fecha.year ||
    (fecha.year == (datos)->fecha.year && ordinal(fecha) < ordinal((datos)->fecha))){
        return 0;
    }
    return 1;
}

// FUNCIONES CALCULO DE MAXIMOS Y MINIMOS
// Retorna o maximo de unha fecha
float tmax_date(Fecha fecha, WeatherData *datos){
    return (datos+indice(fecha, datos))->max_t;
}

// Retorna o minimo de unha fecha
float tmin_date(Fecha fecha, WeatherData *datos){
    return (datos+indice(fecha, datos))->min_t;
}

// Retorna o maximo nun intervalo de duas fechas
float max_bw_dates(Fecha fecha1, Fecha fecha2, WeatherData *datos){
    int i;
    float max = 0;
    for(i=indice(fecha1, datos); i<=indice(fecha2, datos); i++) {
        if (max < (datos+i)->max_t) max = (datos+i)->max_t;
    }
    return max;
}

// Retorna o minimo nun intervalo de duas fechas
float min_bw_dates(Fecha fecha1, Fecha fecha2, WeatherData *datos){
    int i;
    float min = 0;
    for(i=indice(fecha1, datos); i<=indice(fecha2, datos); i++) {
        if (min > (datos+i)->min_t) min = (datos+i)->min_t;
    }
    return min;
}


