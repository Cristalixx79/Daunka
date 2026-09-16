; =======================================
;  unldtsr.asm
;  Сборка:
;  > tasm.exe /l unldtsr.asm
;  > tlink unldtsr.obj
; =======================================

stack_seg segment para stack 'STACK'
    db 64 dup ('STACK   ')
stack_seg ends

data segment
    msg_noTSR   db 'Ошибка: Резидентная программа не найдена в памяти.', 10, 13, '$'
    msg_prompt  db 'Выгрузить резидентную программу? (y/n): $'
    msg_unld    db 10, 13, 'Успех: Резидентная программа и ее PSP выгружены из памяти.', 10, 13, '$'
    msg_abort   db 10, 13, 'Отмена: Выгрузка прервана пользователем.', 10, 13, '$'
data ends

code segment 'CODE'
    assume CS:code, DS:data, SS:stack_seg

start:
    ; Инициализация DS
    mov AX, data
    mov DS, AX

    ; Проверяем, загружен ли резидент (используем наш мультиплексор 2Fh)
    mov AH, 0FFh
    mov AL, 0
    int 2Fh
    cmp AH, 'i'                 ; Если вернулась 'i', значит TSR в памяти
    je _askConfirmation

    ; Если не загружен, выводим ошибку и выходим
    lea DX, msg_noTSR
    mov AH, 09h
    int 21h
    jmp _exit

_askConfirmation:
    ; Выводим запрос на выгрузку
    lea DX, msg_prompt
    mov AH, 09h
    int 21h

_waitInput:
    ; Ожидаем ввода символа с клавиатуры
    mov AH, 01h                 ; Функция 01h DOS - ввод символа с выводом на экран
    int 21h

    ; Проверяем, что ввел пользователь
    cmp AL, 'y'
    je _doUnload
    cmp AL, 'Y'
    je _doUnload
    cmp AL, 'n'
    je _abort
    cmp AL, 'N'
    je _abort
    
    ; Если ввели любой другой символ (не Y и не N), 
    ; считаем это отменой (можно было бы зациклить, но так безопаснее)
    jmp _abort

_doUnload:
    ; Отправляем команду резиденту на самовыгрузку (AL = 1)
    mov AH, 0FFh
    mov AL, 1
    int 2Fh

    ; Выводим сообщение об успехе
    lea DX, msg_unld
    mov AH, 09h
    int 21h
    jmp _exit

_abort:
    ; Выводим сообщение об отмене
    lea DX, msg_abort
    mov AH, 09h
    int 21h

_exit:
    ; Завершение программы и возврат в DOS
    mov AX, 4C00h
    int 21h

code ends
end start