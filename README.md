# BitQuest-Chafa
Proyecto final de la materia de Lenguaje Ensamblador, desarollado con C y NASM.
Este repositorio contiene el código fuente del videojuego BitQuest, desarrollado con programación híbrida en C y Ensamblador (NASM de 64 bits).

## Requisitos previos
Para poder compilar y ejecutar el juego en Windows, se necesita tener instalados y configuradas las variables de entorno:
-GCC(MinGW-w64)
-NASM

## Instrucciones de Compilación y Ejecución
El proyecto incluye un script automatizado para compilar todo el código de una sola vez de forma sencilla en Windows.

### Usando build.bat
1. Abre una terminal (Símbolo del sistema o PowerShell) en la carpeta raíz del proyecto.
2. Ejecuta el archivo batch escribiendo el siguiente comando:
   .\build.bat
3. El script ensamblará automáticamente las rutinas en NASM, compilará los archivos en C, y abrirá el juego.

### Compilación manual
Para compilar paso a paso desde la terminal, ejecuta estos comandos en orden:
1. Ensamblar las funciones obligatorias de NASM:
   nasm -f win64 rutinas.asm -o rutinas.obj
2. Compilar los archivos C y enlazarlos con el objeto de NASM:
   gcc main.c juego.c rutinas.obj -o BitQuest.exe
3. Iniciar el juego:
   .\BitQuest.exe

# Controles Básicos
- W:Mover arriba
- A:Mover a la izquierda
- S:Mover abajo
- D:Mover a la derecha
- Q:Salir del juego
