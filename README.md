# Keygen.eARES


This keygen is designed to generate valid keys for an executable included in the eARES lab#5 that performs specific character checks on a file. The keygen was developed by reverse engineering the target executable to understand its algorithm before writing the keygen in C. 

# Key Checking Algorithem

The keygen generates keys that satisfy the following conditions required by the target executable. The executable performs the following checks on the file content:

## Check #1

  1. First and third characters are added.
  2. Second and fourth characters are added.
  3. Compare them, if equal we continue.

```asm

.text:00402E09 mov     eax, [ebp+Block]
.text:00402E0C xor     edx, edx
.text:00402E0E mov     dl, [eax] ;first char moved.
.text:00402E10 mov     ecx, [ebp+Block]
.text:00402E13 xor     eax, eax
.text:00402E15 mov     al, [ecx+2]; third char moved.
.text:00402E18 add     edx, eax ; add them
.text:00402E1A mov     ecx, [ebp+Block]
.text:00402E1D xor     eax, eax
.text:00402E1F mov     al, [ecx+1] ; second char moved.
.text:00402E22 mov     ecx, [ebp+Block]
.text:00402E25 movzx   ecx, byte ptr [ecx+3]; fourth char moved.
.text:00402E29 add     eax, ecx ; added the last two.
.text:00402E2B cmp     edx, eax ; comapre the value of the two sums.
.text:00402E2D jnz     InvalidDataExit ; break if not equal.
```
## Check #2

  1. Fifth and seventh characters are added.
  2. Sixth and eighth characters are added.
  3. Compare them, if equal we continue.

```asm

.text:00402E33 mov     eax, [ebp+Block]
.text:00402E36 xor     edx, edx
.text:00402E38 mov     dl, [eax+4]
.text:00402E3B mov     eax, [ebp+Block]
.text:00402E3E xor     ecx, ecx
.text:00402E40 mov     cl, [eax+6]
.text:00402E43 add     edx, ecx
.text:00402E45 mov     eax, [ebp+Block]
.text:00402E48 xor     ecx, ecx
.text:00402E4A mov     cl, [eax+5]
.text:00402E4D mov     eax, [ebp+Block]
.text:00402E50 movzx   eax, byte ptr [eax+7]
.text:00402E54 add     ecx, eax
.text:00402E56 cmp     edx, ecx
.text:00402E58 jnz     InvalidDataExit
```
## Check #3

  1. Ninth and tenth characters are added.
  2. Compare them to the 11th character, if equal we continue.

```asm

.text:00402E5E mov     edx, [ebp+Block]
.text:00402E61 xor     ecx, ecx
.text:00402E63 mov     cl, [edx+8]
.text:00402E66 mov     ebx, [ebp+Block]
.text:00402E69 xor     eax, eax
.text:00402E6B mov     al, [ebx+9]
.text:00402E6E add     ecx, eax
.text:00402E70 mov     edx, [ebp+Block]
.text:00402E73 xor     ebx, ebx
.text:00402E75 mov     bl, [edx+0Ah]
.text:00402E78 cmp     ecx, ebx
.text:00402E7A jnz     InvalidDataExit
```
## Check #4

  1. First and second characters must not be equal.

```asm

.text:00402E80 mov     eax, [ebp+Block]
.text:00402E83 mov     dl, [eax]
.text:00402E85 mov     ecx, [ebp+Block]
.text:00402E88 cmp     dl, [ecx+1]
.text:00402E8B jz      InvalidDataExit
```
## Check #5

 1. Fifth and sixth characters must not be equal.

```asm

.text:00402E91 mov     eax, [ebp+Block]
.text:00402E94 mov     dl, [eax+4]
.text:00402E97 mov     ecx, [ebp+Block]
.text:00402E9A cmp     dl, [ecx+5]
.text:00402E9D jz      InvalidDataExit
```
## Check #6

  1. 12th character must be more than 0x39 (ASCII for '9').

```asm

.text:00402EA3 mov     eax, [ebp+Block]
.text:00402EA6 xor     edx, edx
.text:00402EA8 mov     dl, [eax+0Bh]
.text:00402EAB cmp     edx, 39h ; '9'
.text:00402EAE jle     InvalidDataExit
```
## Check #7

  1. 12th character must be less than 0x41 (ASCII for 'A').

```asm

.text:00402EB4 mov     ecx, [ebp+Block]
.text:00402EB7 xor     eax, eax
.text:00402EB9 mov     al, [ecx+0Bh]
.text:00402EBC cmp     eax, 41h ; 'A'
.text:00402EBF jge     short InvalidDataExi
```
## Check #8

  1. 13th character must be greater than 0x5A (ASCII for 'Z').

```asm

.text:00402EC1 mov     edx, [ebp+Block]
.text:00402EC4 xor     ecx, ecx
.text:00402EC6 mov     cl, [edx+0Ch]
.text:00402EC9 cmp     ecx, 5Ah ; 'Z'
.text:00402ECC jle     short InvalidDataExi
```
## Check #9

  1. 13th character must be less than 0x61 (ASCII for 'a').

```asm

.text:00402ECE mov     eax, [ebp+Block]
.text:00402ED1 xor     edx, edx
.text:00402ED3 mov     dl, [eax+0Ch]
.text:00402ED6 cmp     edx, 61h ; 'a'
.text:00402ED9 jge     short InvalidDataExit
```
## Check #10

1. 14th character must be greater than 0x7A (ASCII for 'z').

```asm

.text:00402EDB mov     ecx, [ebp+Block]
.text:00402EDE xor     eax, eax
.text:00402EE0 mov     al, [ecx+0Dh]
.text:00402EE3 cmp     eax, 7Ah ; 'z'
.text:00402EE6 jle     short InvalidDataExit
```
## Check #11

  1. 14th character must be less than 0x7F (ASCII for 127).

```asm

.text:00402EE8 mov     edx, [ebp+Block]
.text:00402EEB xor     ecx, ecx
.text:00402EED mov     cl, [edx+0Dh]
.text:00402EF0 cmp     ecx, 7Fh
.text:00402EF3 jge     short InvalidDataExit
```
## Check #12

  1. 15th character must be greater than 0x7A (ASCII for 'z').

```asm

.text:00402EF5 mov     eax, [ebp+Block]
.text:00402EF8 xor     edx, edx
.text:00402EFA mov     dl, [eax+0Eh]
.text:00402EFD cmp     edx, 7Ah ; 'z'
.text:00402F00 jle     short InvalidDataExit
```
## Check #13

  1. 16th character is XOR-ed with the 15th character.
  2. The result must be 0x17.

```asm

.text:00402F02 mov     ecx, [ebp+Block]
.text:00402F05 mov     al, [ecx+0Eh]
.text:00402F08 mov     edx, [ebp+Block]
.text:00402F0B xor     al, [edx+0Fh]
.text:00402F0E xor     ecx, ecx
.text:00402F10 mov     cl, al
.text:00402F12 cmp     ecx, 17h
.text:00402F15 jnz     short InvalidDataExit
```
