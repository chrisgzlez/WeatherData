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

typedef struct  Fecha{
    int mes , dia , year;
}Fecha;

typedef struct WeatherData{
    Fecha fecha;
    float max_t, min_t;
    float precipitacion, viento, humedad, solar;
}WeatherData;

typedef struct Station{
    char *nombre;
    float longitud, latitude, elevacion;
}Station;

typedef struct WeatherStation{
    WeatherData *datos;
    Station estacion;
}WeatherStation;

// FUNCIONS PRINCIPAIS

/*
PRECONDICION:
    Un punteiro a un archivo txt xa aberto
POSTCONDICION:
    Un punteiro a unha estructura WeatherData cos datos cargados do archivo
*/
WeatherData *Funcion_1(FILE *archivo);

/*
PRECONDICION:
    Nome do archivo csv a abrir, no mesmo directorio que o executable
POSTCONDICION:
    Un WeatherStation cos datos cargados de ese csv
*/
WeatherStation Funcion_2(char *archivo_csv);

/*
PRECONDICION:
    O nome dun archivo txt cos nome dos archivos csv separados por espacios o saltos de lineas
    Un punteiro inicializado de tipo int
POSTCONDICION:
    Numero de estacions no archivo txt, almacenadas no punteiro int
    Un punteiro WeatherStation cos datos meteoroloxicos de todas as estacions
*/
WeatherStation *Funcion_3(char *archivo_nomes, int *num_estaciones);

/*
PRECONDICION:
    Duas estructuras fechas validas
    Un punteiro WeatherStation inicializado e cos datos cargados
    O numero de estacions
POSTCONDICION:
    Maximo das temperaturas maximas dos archivos nun intervalo de tempo
    Minimo das temperaturas minimas dos archivos nun intervalo de tempo
*/
void Funcion_4(Fecha fecha1, Fecha fecha2, WeatherStation *estaciones, int num_estaciones);

/*
PRECONDICION:
    Unha estructura fecha valida
    Un punteiro WeatherStation inicializado e cos datos cargados
    O numero de estacions
POSTCONDICION:
    Media das temperaturas maximas e minimas dos archivos dunha data concreta
*/
void Funcion_5(Fecha fecha, WeatherStation *estacion, int num_estaciones);

// FUNCIONS PARA TRATAR ARCHIVOS

/*
PRECONDICION:
    Nome dun archivo csv guardado no mesmo directorio que o executable
POSTCONDICION:
    Un archivo txt limpio (sin comas, barras y comillas) cos datos do csv separado por espacios
    Nome do archivo txt
*/
char *leer_csv(char *csv);

/*
PRECONDICION:
    Un punteiro a un archivo txt aberto
    Un punteiro a una estructura WeatherData inicializada
    O numero de estructuras WeatherData do archivo txt
POSTCONDICION:
    O punteiro a estructura WeatherData cos datos do archivo cargados
*/
void leer_archivo(FILE *file, WeatherData *data, int num_elementos);

/*
PRECONDICION:
    Un punteiro a char equivalente a unha linha do archivo csv
POSTCONDICION:
    Un punteiro a char equivalente a unha linha sen retorno de carro o salto de linha
*/
void rem_crlf(char *array);

/*
PRECONDICION:
    Un punteiro a char que contenha o nome do archivo e a extension
    Un punteiro a char que contenha a extension deseada
POSTCONDICION:
    Un punteiro a char que contenha o nome do archivo coa nova extension
*/
void cambio_extension(char *archivo, char *extension);

// FUNCIONS PARA TRATAR FECHAS

/*
PRECONDICION:
    Unha fecha introducida por teclado formada por 3 int
POSTCONDICION:
    Unha estructura fecha valida
*/
Fecha leer_fecha(void);

/*
PRECONDICION:
    Unha estructura fecha valida
    Un punteiro WeatherData xa inicializado con datos cargados
POSTCONDICION:
    Un int que representa o indice do punteiro WeatherData ao que fai referencia a fecha
*/
int indice(Fecha fecha, WeatherData *datos);

/*
PRECONDICION:
    Una estructura fecha válida
POSTCONDICION:
    Un int que represente o ordinal da fecha dentro do mesmo ano
*/
int ordinal(Fecha fecha);

/*
PRECONDICION:
    Un int que represente un ano
POSTCONDICION:
    Un int con valor 0 si non e bixesto e 1 se o e
*/
int bixesto(int year);

/*
PRECONDICION:
    Unha estructura fecha valida
    Un punteiro WeatherData xa inicializado con datos cargados
POSTCONDICION:
    Un int con valor 0 se a fecha e anterior a primeira fecha do WeatherData
    Un int con valor 1 se non o e
*/
int check_date(Fecha fecha, WeatherData *datos);

// FUNCIONES CALCULO DE MAXIMOS Y MINIMOS

/*
PRECONDICION:
    Duas estructuras fecha validas (feecha2 > fecha1)
    Un punteiro WeatherData xa inicializado con datos cargados
POSTCONDICION:
    O minimo das temperaturas minimas nese intervalo de tempo
*/
float min_bw_dates(Fecha fecha1, Fecha fecha2, WeatherData *datos);

/*
PRECONDICION:
    Duas estructuras fecha validas (feecha2 > fecha1)
    Un punteiro WeatherData xa inicializado con datos cargados
POSTCONDICION:
    O maximo das temperaturas minimas nese intervalo de tempo
*/
float max_bw_dates(Fecha fecha1, Fecha fecha2, WeatherData *datos);

/*
PRECONDICION:
    Unha estructura fecha valida
    Un punteiro WeatherData xa inicializado con datos cargados
POSTCONDICION:
    Temperatura minima da fecha dada
*/
float tmin_date(Fecha fecha, WeatherData *datos);

/*
PRECONDICION:
    Unha estructura fecha valida
    Un punteiro WeatherData xa inicializado con datos cargados
POSTCONDICION:
    Temperatura minima da fecha dada
*/
float tmax_date(Fecha fecha, WeatherData *datos);
