@echo off
echo Compilando

:: codigo nasm ensamblado
nasm -f win64 rutinas.asm -o rutinas.obj

:: compilar c
gcc -c main.c -o main.obj
gcc -c juego.c -o juego.obj

:: obj
gcc main.obj juego.obj rutinas.obj -o BitQuest.exe

echo Compilado y ejecutando
BitQuest.exe
pause