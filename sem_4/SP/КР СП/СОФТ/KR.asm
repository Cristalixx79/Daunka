; =======================================
;  kr.asm (Резидентная часть)
;  Сборка:
;  > tasm.exe /l kr.asm
;  > tlink /t /x kr.obj
; =======================================

code segment 'code'
    assume  CS:code, DS:code
    org 100h

_start:
    jmp _initTSR                                ; на начало программы

    translateFrom               DB 'T;PBR'      ; заменяемые клавиши (англ. раскладка для ЕЖЗИК)
    translateTo                 DB 'ЕЖЗИК'      ; символы, на которые будет происходить замена
    translateLength             DB 5            ; длина строки (теперь 5 символов)
    translateEnabled            DB 0            ; флаг функции перевода (F1)

    russianOnlyEnabled          DB 0            ; флаг ограничения ввода: только русские буквы (F2)

    signaturePrintingEnabled    DB 0            ; флаг вывода подписи (F8)
    counter                     DW 0
    printDelay                  EQU 7           ; задержка перед выводом "подписи" в секундах

    signatureLineLength         DW  52          ; длина одной строчки подписи
    signatureLine1              DB  179, 'ФИО: Дейнеко Артем Вадимович                      ', 179
    signatureLine2              DB  179, 'Группа: ИУ5-45Б                                   ', 179
    signatureLine3              DB  179, 'Вариант: 5                                        ', 179
    tableTop                    DB  '┌', 50 dup ('─'), '┐'
    tableBottom                 DB  '└', 50 dup ('─'), '┘'

    helpMsg     DB '> kr.com [/?] ' , 10, 13
                DB ' [/?] - вывод данной справки', 10, 13
                DB '  F8  - вывод ФИО и группы по таймеру вверху экрана (7 сек)', 10, 13
                DB '  F9  - включение/отключение курсивного вывода русской буквы З', 10, 13
                DB '  F1  - включение/отключение частичной русификации: ЕЖЗИК', 10, 13
                DB '  F2  - включение/отключение ограничения ввода (только русские буквы)', 10, 13
                DB ' Для выгрузки используйте утилиту UNLDTSR.EXE', 10, 13, 0

    commandLineResult           DB 0

    cursiveEnabled              DB 0            ; флаг перевода символа в курсив (F9)
    cursiveSymbol               DB 00000000b    ; курсивный вариант буквы "З"
                                DB 00000000b 
                                DB 00011110b  
                                DB 00110011b  
                                DB 00000110b  
                                DB 00001110b  
                                DB 00000110b  
                                DB 00110011b  
                                DB 00011110b  
                                DB 00000000b  
                                DB 00000000b  
                                DB 00000000b  
                                DB 00000000b  
                                DB 00000000b  
                                DB 00000000b  
                                DB 00000000b   

    charToCursiveIndex          DB 'З'          ; символ для замены (теперь 'З')
    savedSymbol                 DB 16 dup(0FFh) ; переменная для хранения старого символа

    old_int9hOffset             DW  ?           ; адрес старого обработчика int 9h
    old_int9hSegment            DW  ?           ; сегмент старого обработчика int 9h
    old_int1ChOffset            DW  ?           ; адрес старого обработчика int 1Ch
    old_int1ChSegment           DW  ?           ; сегмент старого обработчика int 1Ch
    old_int2FhOffset            DW  ?           ; адрес старого обработчика int 2Fh
    old_int2FhSegment           DW  ?           ; сегмент старого обработчика int 2Fh

    installedMsg                DB  'Резидент успешно загружен.', 10, 13, '$'
    alreadyInstalledMsg         DB  'Ошибка: Резидент уже загружен в память!', 10, 13, '$'

    true                        EQU 0FFh

    new_int9h proc far
        push SI AX BX CX DX ES DS
        push BP
        push CS
        pop DS

        pushf
        call dword ptr CS:[old_int9hOffset]     ; вызываем стандартный обработчик

        mov AX, 40h                             ; 40h - сегмент состояния клавиатуры
        mov ES, AX
        mov BX, ES:[1Ch]                        ; адрес хвоста буфера
        sub BX, 2h
        cmp BX, 1Eh
        jae _go
        mov BX, 3Ch                             ; хвост вышел за пределы
    _go:
        mov DX, ES:[BX]                         ; в DX: DH - сканкод, DL - ASCII

    _test_Fx:
    _F1:
        cmp DH, 3Bh                             ; F1 - Частичная русификация
        jne _F2
        not translateEnabled
        mov ES:[1Ch], BX
        jmp _quit
    _F2:
        cmp DH, 3Ch                             ; F2 - Только русские буквы
        jne _F8
        not russianOnlyEnabled
        mov ES:[1Ch], BX
        jmp _quit
    _F8:
        cmp DH, 42h                             ; F8 - Вывод ФИО и группы
        jne _F9
        not signaturePrintingEnabled
        mov ES:[1Ch], BX                        ; скрываем нажатие из буфера
        jmp _quit
    _F9:
        cmp DH, 43h                             ; F9 - Курсивная 'З'
        jne _checkRussianOnly
        mov ES:[1Ch], BX
        not cursiveEnabled
        call toggleCursive
        jmp _quit

    _checkRussianOnly:
        cmp russianOnlyEnabled, true            ; Режим ограничения ввода включен?
        jne _checkTranslate

        cmp DL, 20h                             ; Разрешаем управляющие символы и пробел (<= 20h)
        jbe _checkTranslate

        cmp DL, 0F0h                            ; Буква Ё в CP866
        je _checkTranslate
        cmp DL, 0F1h                            ; Буква ё в CP866
        je _checkTranslate

        cmp DL, 80h                             ; Проверка диапазона А-Я (80h - 9Fh)
        jb _blockKey
        cmp DL, 9Fh
        jbe _checkTranslate

        cmp DL, 0A0h                            ; Проверка диапазона а-п (A0h - AFh)
        jb _blockKey
        cmp DL, 0AFh
        jbe _checkTranslate

        cmp DL, 0E0h                            ; Проверка диапазона р-я (E0h - EFh)
        jb _blockKey
        cmp DL, 0EFh
        jbe _checkTranslate

    _blockKey:
        mov ES:[1Ch], BX                        ; Удаляем запрещенный символ из буфера
        jmp _quit

    _checkTranslate:
        cmp translateEnabled, true              ; Режим русификации включен?
        jne _quit

        mov SI, 0
        mov CL, translateLength

    _checkTranslateLoop:
        cmp DL, translateFrom[SI]               ; Есть ли символ в списке перевода?
        je _translate
        inc SI
        loop _checkTranslateLoop
        jmp _quit

    _translate:
        mov DL, translateTo[SI]                 ; Выполняем замену
        mov ES:[BX], DX

    _quit:
        pop BP
        pop DS ES DX CX BX AX SI
        iret
    new_int9h endp

    toggleCursive proc
        push ES AX
        push CS
        pop ES

        cmp cursiveEnabled, true
        jne _restoreSymbol

        call saveFont
        mov CL, charToCursiveIndex
    _shiftTable:
        add BP, 16
        loop _shiftTable

        push DS
        pop AX
        push ES
        pop DS
        push AX
        pop ES
        push AX

        mov SI, BP
        lea DI, savedSymbol

        mov CX, 16
        rep movsb
        pop DS

        mov CX, 1
        mov DH, 0
        mov DL, charToCursiveIndex
        lea BP, cursiveSymbol
        call changeFont
        jmp _exitToggleCursive

    _restoreSymbol:
        mov CX, 1
        mov DH, 0
        mov DL, charToCursiveIndex
        lea BP, savedSymbol
        call changeFont

    _exitToggleCursive:
        pop AX
        pop ES
        ret
    toggleCursive endp

    changeFont proc
        push AX BX DX
        mov AX, 1100h
        mov BX, 1000h
        int 10h
        pop DX BX AX
        ret
    changeFont endp

    saveFont proc
        push AX BX DX
        mov AX, 1130h
        mov BX, 0600h
        int 10h
        pop BX AX DX
        ret
    saveFont endp

    ; INT 2Fh для проверки и выгрузки утилитой
    new_int2Fh proc
        cmp AH, 0FFh                            ; наш мультиплексор?
        jne _2Fh_default
        cmp AL, 0                               ; проверка загрузки
        je  _alreadyInstalled2Fh
        cmp AL, 1                               ; запрос на выгрузку (от UNLDTSR.EXE)
        je  _uninstall
        jmp _2Fh_default

    _2Fh_default:
        jmp dword ptr CS:[old_int2FhOffset]

    _alreadyInstalled2Fh:
        mov AH, 'i'                             ; отдаем сигнатуру
        iret

    _uninstall:
        push DS ES DX BX
        xor BX, BX

        push CS
        pop ES

        mov AX, 2509h
        mov DX, ES:old_int9hOffset
        mov DS, ES:old_int9hSegment
        int 21h

        mov AX, 251Ch
        mov DX, ES:old_int1ChOffset
        mov DS, ES:old_int1ChSegment
        int 21h

        mov AX, 252Fh
        mov DX, ES:old_int2FhOffset
        mov DS, ES:old_int2FhSegment
        int 21h

        mov ES, CS:2Ch                          ; выгрузка PSP (окружения)
        mov AH, 49h
        int 21h

        push CS
        pop ES                                  ; выгрузка самого резидента
        mov AH, 49h
        int 21h

        pop BX DX ES DS
        iret
    new_int2Fh endp

    new_int1Ch proc far
        push AX
        push CS
        pop DS

        pushf
        call dword ptr CS:[old_int1ChOffset]

        cmp signaturePrintingEnabled, true
        jne _notToPrint

        cmp counter, printDelay*1000/55 + 1     ; расчет 7 секунд
        je _letsPrint

        jmp _dontPrint

    _letsPrint:
        not signaturePrintingEnabled
        mov counter, 0
        call printSignature

    _dontPrint:
        inc counter

    _notToPrint:
        pop AX
        iret
    new_int1Ch endp

    printSignatureLine proc
        push DX
        mov CX, signatureLineLength
        mov BL, 0111b
        mov AX, 1301h
        int 10h
        pop DX
        inc DH
        ret
    printSignatureLine endp

    printSignature proc
        push AX DX CX BX ES SP BP SI DI

        xor AX, AX
        xor BX, BX
        xor DX, DX

        mov AH, 03h
        int 10h
        push DX

        mov DX, 000Eh                           ; Вывод ВВЕРХУ экрана (строка 0, столбец 14)

    _actualPrint:
        mov AH, 0Fh
        int 10h

        push CS
        pop ES

        lea BP, tableTop
        call printSignatureLine
        lea BP, signatureLine1
        call printSignatureLine
        lea BP, signatureLine2
        call printSignatureLine
        lea BP, signatureLine3
        call printSignatureLine
        lea BP, tableBottom
        call printSignatureLine

        pop DX
        mov AH, 02h
        int 10h

        pop DI SI BP SP ES BX CX DX AX
        ret
    printSignature endp

    _initTSR:
        call commandParamsParser
        cmp commandLineResult, 2
        je _exit

        mov AH, 0FFh
        mov AL, 0
        int 2Fh
        cmp AH, 'i'                             ; Уже загружен?
        je _alreadyLoaded

        mov AX, 3509h
        int 21h
        mov word ptr CS:old_int9hOffset, BX
        mov word ptr CS:old_int9hSegment, ES
        mov AX, 2509h
        mov DX, offset new_int9h
        int 21h

        mov AX, 351Ch
        int 21h
        mov word ptr CS:old_int1ChOffset, BX
        mov word ptr CS:old_int1ChSegment, ES
        mov AX, 251Ch
        mov DX, offset new_int1Ch
        int 21h

        mov AX, 352Fh
        int 21h
        mov word ptr CS:old_int2FhOffset, BX
        mov word ptr CS:old_int2FhSegment, ES
        mov AX, 252Fh
        mov DX, offset new_int2Fh
        int 21h

        mov AH, 09h
        lea DX, installedMsg
        int 21h

        mov DX, offset _initTSR
        int 27h

    _alreadyLoaded:
        mov AH, 09h
        lea DX, alreadyInstalledMsg
        int 21h
        jmp _exit

    _exit:
        int 20h

    commandParamsParser proc
        push CS
        pop ES

        mov SI, 80h
        lodsb
        or AL, AL
        jz _paramParsingEnd

    _nextChar:
        inc SI
        cmp [SI], BYTE ptr 0
        je _paramParsingEnd
        lodsw
        cmp AX, '?/'
        je _displayHelp
        jmp _paramParsingEnd

    _displayHelp:
        lea BX, helpMsg
        call printStr
        mov commandLineResult, 2
    _paramParsingEnd:
        ret
    commandParamsParser endp

    printChar proc
        mov AH, 0EH
        int 010H
        ret
    printChar endp

    printStr proc
        push DX AX
        mov AX, [BX]
    _printStrLoop:
        cmp AL, 0
        je _printStrEnd
        call printChar
        inc BX
        mov AX, [BX]
        jmp _printStrLoop
    _printStrEnd:
        pop AX DX
        ret
    printStr endp

code ends
end _start