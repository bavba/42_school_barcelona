; This file contains assembly code that opens the Windows calculator application using ShellExecuteA function.

section .text
    global _start
    
_start:
    ; Clearing registers
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    
    ; Opening the Windows Calculator
    mov ebx, 0x7e3d0c33 ; Address of the ShellExecuteA function
    sub ebx, 0x7e100000 ; Adjusting for the base address of kernel32.dll
    mov eax, fs:[ebx]
    mov eax, [eax + 0x1c] ; Address of the kernel32.dll function address table
    mov eax, [eax + 0x8] ; Address of the GetProcAddress function
    
    push edx ; Parameter 4: hwnd
    push edx ; Parameter 3: lpOperation
    push 0x736c6163 ; Parameter 2: lpFile (calc)
    push 0x616c652f ; Parameter 1: lpDirectory (/ela)
    mov ecx, esp ; Pointer to the parameters
    
    push edx ; Parameter 5: nShowCmd (SW_SHOW)
    push ecx ; Pointer to the parameters
    call eax ; Call GetProcAddress to obtain the address of ShellExecuteA
    
    ; Clearing registers again
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    
    ; Jumping to the address of the ShellExecuteA function
    jmp eax