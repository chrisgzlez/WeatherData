# AUTORES:
    CRISTIAN NOVOA GONZALEZ
    XAVIER PRIMOI MARTINEZ
    IVAN QUINTANS GONZALEZ
    
# INFORMACION:
    LUGAR: SANTIAGO DE COMPOSTELA
    FECHA: 22/12/2021
    COMPANIA: USC
    
# NOTA:
  ## [1]
    La realización del proyecto fué entre los tres. La parte desarrollada por mi (Cristian Novoa Gonzalez) fué la que 
    envuelve las funciones 3,4,5 así como el diseño del programa en sí y su estructura en los que participamos los 3.
  ## [2]
    Existe una pequeña perdida de memoria por falta de un free el cuál no se pudo corregir antes de la versión final. No afecta 
    a la ejecución del programa, solo a su manejo de memoria.

# Sumario del Proyecto
    Sumario del Proyecto original tal cual se nos fué entregado
# CARPETA PROYECTO_1:
    Se encuentran los siguientes archivos:
  ## CODIGO
    demo.c (o codigo fuente da nosa demo)
    meteo.c (codigo da libreria)
    meteo.h (a cabecera da libreria)
  ## PRACTICA
    demo.exe (o executable creado en cmd[1]): toma un argumento na linea de comandos
    archivos.csv (cos datos metereoloxicos)
    archivo.txt (cos nomes dos archivos csv)
    
# CARPETA PROYECTO_2:
  Se encuentran los siguientes archivos:
  # CODIGO
    demo.c (o codigo fuente da nosa demo)
    libmeteo.a (libreria compilada)
    meteo.h (a cabecera da libreria)
  ## PRACTICA
    demo.exe (o executable creado en cmd[2]): toma un argumento na linea de comandos
    archivos.csv (cos datos metereoloxicos)
    archivo.txt (cos nomes dos archivos csv)

# COMANDOS CMD EMPREGADOS:
  ## [1]	
    gcc -c demo.c meteo.c	// Creacion dos obxetos
    gcc -o demo demo.o meteo.o // Creacion do executable co nome demo
    demo.exe datos.txt // Execucion do programa demo.exe cos argumentos precisos
  ## [2]
    gcc -c demo.c // Creacion do obxecto
    ar rcs libmeteo.a meteo.o // Creacion da libreria
    gcc demo.c -lmeteo -L. -o demo // Creacion do executable co nome demo a partir da libreria compilada
    demo.exe datos.txt // Execucion do programa demo.exe cos argumentos precisos
