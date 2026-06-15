bits 64
default rel 

global contar_caracter
global validar_movimiento
global calcular_puntaje
global detectar_objeto
global contar_celdas_libres

section .text


;contar_caracter(char *mapa, int total_celdas, char caracter)
; RCX = mapa, EDX = total celdas, R8B = caracter

contar_caracter:
    xor eax, eax        ; contador en 0
    xor r9d, r9d        ; indice en 0
    test edx, edx
    jle .fin_contar

.bucle_contar:
    mov r10b, byte [rcx + r9] ; *1 porque es byte
    cmp r10b, r8b
    jne .siguiente_contar
    inc rax             ; aumentamos contador

.siguiente_contar:
    inc r9d
    cmp r9d, edx
    jl .bucle_contar

.fin_contar:
    ret


;validar_movimiento(char *mapa, int columnas, int fila, int columna)
; RCX = mapa, EDX = columnas, R8D = fila, R9D = columna

validar_movimiento:
    ; fila * columnas + columna
    mov eax, r8d
    imul eax, edx
    add eax, r9d

    ; Obtenemos la celda
    movsxd r10, eax
    mov r11b, byte [rcx + r10]

    ; Si es pared '#' (ASCII 35), bloqueamos
    cmp r11b, '#'
    je .bloqueado

    mov eax, 1          ; 1 movimiento valido
    ret

.bloqueado:
    xor eax, eax        ; 0 movimiento invalido
    ret


;calcular_puntaje(int monedas, int pasos, int niveles)
; ECX = monedas, EDX = pasos, R8D = niveles

calcular_puntaje:
    ; (monedas * 100) - pasos + (niveles * 1000)
    mov eax, ecx
    imul eax, 100       ; monedas * 100
    sub eax, edx        ; restar pasos

    mov r9d, r8d
    imul r9d, 1000      ; niveles * 1000
    add eax, r9d        ; sumar total

    ; no negativos validacion
    cmp eax, 0
    jge .fin_puntaje
    xor eax, eax        ; si es menor a 0 dejar en 0 para no negativos

.fin_puntaje:
    movsxd rax, eax     ; 64 bits para el return
    ret


; detectar_objeto(char *mapa, int columnas, int fila, int columna, char objeto)
; RCX = mapa, EDX = columnas, R8D = fila, R9D = columna
; objeto en la pila [rsp + 40]


detectar_objeto:
    ;indice = fila * columnas + columna
    mov eax, r8d
    imul eax, edx
    add eax, r9d

    ;celda actual
    movsxd r10, eax
    mov r11b, byte [rcx + r10]

    ;caracter a buscar desde la pila
    mov r10b, byte [rsp + 40]

    cmp r11b, r10b
    je .encontrado

    xor eax, eax        ; 0 no esta el objeto
    ret

.encontrado:
    mov eax, 1          ; 1 si esta el objeto
    ret


; contar_celdas_libres(char *mapa, int total_celdas)
; RCX = mapa, EDX = total_celdas

contar_celdas_libres:
    xor eax, eax        ; contador en 0
    xor r8d, r8d        ; indice en 0
    test edx, edx
    jle .fin_libres

.bucle_libres:
    mov r9b, byte [rcx + r8]
    cmp r9b, '.'        ; si es .
    jne .siguiente_libre
    inc rax

.siguiente_libre:
    inc r8d
    cmp r8d, edx
    jl .bucle_libres

.fin_libres:
    ret