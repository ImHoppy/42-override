# Level06

Ici un appel a ptrace détecte gdb:
```
level06@OverRide:~$ gdb ./level06
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/users/level06/level06...(no debugging symbols found)...done.
(gdb) r
Starting program: /home/users/level06/level06
***********************************
*               level06           *
***********************************
-> Enter Login: BBBBBBB
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 0
.---------------------------.
| !! TAMPERING DETECTED !!  |
'---------------------------'
[Inferior 1 (process 2279) exited with code 01]
```

On va donc mettre un breakpoint a l'instruction
suivante pour modifier la valeur de eax et contourner ce bloquage.

Lancer le programme avec gdb, mettre un break point sur ptrace que le trouve en
désassemblant le main et la fonction auth appelé a l'intérieur.

```
(gdb) disass auth
Dump of assembler code for function auth:
   0x08048748 <+0>:     push   %ebp
   0x08048749 <+1>:     mov    %esp,%ebp
   0x0804874b <+3>:     sub    $0x28,%esp
   0x0804874e <+6>:     movl   $0x8048a63,0x4(%esp)
   0x08048756 <+14>:    mov    0x8(%ebp),%eax
   0x08048759 <+17>:    mov    %eax,(%esp)
   0x0804875c <+20>:    call   0x8048520 <strcspn@plt>
   0x08048761 <+25>:    add    0x8(%ebp),%eax
   0x08048764 <+28>:    movb   $0x0,(%eax)
   0x08048767 <+31>:    movl   $0x20,0x4(%esp)
   0x0804876f <+39>:    mov    0x8(%ebp),%eax
   0x08048772 <+42>:    mov    %eax,(%esp)
   0x08048775 <+45>:    call   0x80485d0 <strnlen@plt>
   0x0804877a <+50>:    mov    %eax,-0xc(%ebp)
   0x0804877d <+53>:    push   %eax
   0x0804877e <+54>:    xor    %eax,%eax
   0x08048780 <+56>:    je     0x8048785 <auth+61>
   0x08048782 <+58>:    add    $0x4,%esp
   0x08048785 <+61>:    pop    %eax
   0x08048786 <+62>:    cmpl   $0x5,-0xc(%ebp)
   0x0804878a <+66>:    jg     0x8048796 <auth+78>
   0x0804878c <+68>:    mov    $0x1,%eax
   0x08048791 <+73>:    jmp    0x8048877 <auth+303>
   0x08048796 <+78>:    movl   $0x0,0xc(%esp)
   0x0804879e <+86>:    movl   $0x1,0x8(%esp)
   0x080487a6 <+94>:    movl   $0x0,0x4(%esp)
   0x080487ae <+102>:   movl   $0x0,(%esp)
   0x080487b5 <+109>:   call   0x80485f0 <ptrace@plt>	; appel de ptrace
   0x080487ba <+114>:   cmp    $0xffffffff,%eaxi		; breakpoint ici pour modifier eax
```

```
level06@OverRide:~$ gdb ./level06
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/users/level06/level06...(no debugging symbols found)...done.
(gdb) b *0x080487ba
Breakpoint 1 at 0x80487ba
(gdb) r
Starting program: /home/users/level06/level06
***********************************
*               level06           *
***********************************
-> Enter Login: BBBBBB
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 0

Breakpoint 1, 0x080487ba in auth ()
(gdb) s
Single stepping until exit from function auth,
which has no line number information.
[Inferior 1 (process 2273) exited with code 01]
(gdb) c
The program is not being run.
```

On place ensuite un break aux endroits ou le programme modifie notre buffer pour comprendre ce qu'il en fait:
```
 0x080487b5 <+109>:   call   0x80485f0 <ptrace@plt>
   0x080487ba <+114>:   cmp    $0xffffffff,%eax
   0x080487bd <+117>:   jne    0x80487ed <auth+165>
   0x080487bf <+119>:   movl   $0x8048a68,(%esp)
   0x080487c6 <+126>:   call   0x8048590 <puts@plt>
   0x080487cb <+131>:   movl   $0x8048a8c,(%esp)
   0x080487d2 <+138>:   call   0x8048590 <puts@plt>
   0x080487d7 <+143>:   movl   $0x8048ab0,(%esp)
   0x080487de <+150>:   call   0x8048590 <puts@plt>
   0x080487e3 <+155>:   mov    $0x1,%eax
   0x080487e8 <+160>:   jmp    0x8048877 <auth+303>
   0x080487ed <+165>:   mov    0x8(%ebp),%eax
   0x080487f0 <+168>:   add    $0x3,%eax
   0x080487f3 <+171>:   movzbl (%eax),%eax
   0x080487f6 <+174>:   movsbl %al,%eax
   0x080487f9 <+177>:   xor    $0x1337,%eax				; Xor ici
   0x080487fe <+182>:   add    $0x5eeded,%eax
   0x08048803 <+187>:   mov    %eax,-0x10(%ebp)
   0x08048806 <+190>:   movl   $0x0,-0x14(%ebp)
   0x0804880d <+197>:   jmp    0x804885b <auth+275>
   0x0804880f <+199>:   mov    -0x14(%ebp),%eax
   0x08048812 <+202>:   add    0x8(%ebp),%eax
   0x08048815 <+205>:   movzbl (%eax),%eax
   0x08048818 <+208>:   cmp    $0x1f,%al
   0x0804881a <+210>:   jg     0x8048823 <auth+219>
   0x0804881c <+212>:   mov    $0x1,%eax
   0x08048821 <+217>:   jmp    0x8048877 <auth+303>
   0x08048823 <+219>:   mov    -0x14(%ebp),%eax
   0x08048826 <+222>:   add    0x8(%ebp),%eax
   0x08048829 <+225>:   movzbl (%eax),%eax
   0x0804882c <+228>:   movsbl %al,%eax
   0x0804882f <+231>:   mov    %eax,%ecx
   0x08048831 <+233>:   xor    -0x10(%ebp),%ecx
   0x08048834 <+236>:   mov    $0x88233b2b,%edx
   0x08048839 <+241>:   mov    %ecx,%eax
   0x0804883b <+243>:   mul    %edx
   0x0804883d <+245>:   mov    %ecx,%eax
   0x0804883f <+247>:   sub    %edx,%eax
   0x08048841 <+249>:   shr    %eax
```

```
(gdb) b *0x080487ba
Breakpoint 1 at 0x80487ba
(gdb) b *0x080487fe
Breakpoint 2 at 0x80487fe
(gdb)
(gdb) b *0x08048803
Breakpoint 3 at 0x8048803

(gdb) r
Starting program: /home/users/level06/level06
***********************************
*               level06           *
***********************************
-> Enter Login: BBBBBB
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 0

Breakpoint 1, 0x080487ba in auth ()
(gdb) set $eax=0
(gdb) c
Continuing.

Breakpoint 2, 0x080487fe in auth ()
(gdb) info register
eax            0x1375   4981
ecx            0x0      0
edx            0xffffffc8       -56
ebx            0xf7fceff4       -134418444
esp            0xffffd610       0xffffd610
ebp            0xffffd638       0xffffd638
esi            0x0      0
edi            0x0      0
eip            0x80487fe        0x80487fe <auth+182>
eflags         0x202    [ IF ]
cs             0x23     35
ss             0x2b     43
ds             0x2b     43
es             0x2b     43
fs             0x0      0
gs             0x63     99
(gdb) n
Single stepping until exit from function auth,
which has no line number information.

Breakpoint 3, 0x08048803 in auth ()
(gdb) info register
eax            0x5f0162 6226274
ecx            0x0      0
edx            0xffffffc8       -56
ebx            0xf7fceff4       -134418444
esp            0xffffd610       0xffffd610
ebp            0xffffd638       0xffffd638
esi            0x0      0
edi            0x0      0
eip            0x8048803        0x8048803 <auth+187>
eflags         0x10212  [ AF IF RF ]
cs             0x23     35
ss             0x2b     43
ds             0x2b     43
es             0x2b     43
fs             0x0      0
gs             0x63     99
```

On réalise l'encryption sur le 4eme char du buffer pour avoir la valeur de depart
qui sera écrasé a chaque tour de boucle pour produire le résultat final.

```
$ python
Python 2.7.18 (default, Jul  1 2022, 12:27:04)
[GCC 9.4.0] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> ord("B") ^ 0x1337
4981
>>> 4981 + 0x5eeded
6226274
```

Maintenant nous pouvons lancer notre script python présent dans le dossier resources
qui fera autant de tour de boucle que la taille de la chaine pour reproduire le meme 
comportement que le programme.
Celui ci nous fournis le serial number pour le login "BBBBBB"

```
$ ./decrypt.py
6231544
```

```
level06@OverRide:~$ ./level06
***********************************
*               level06           *
***********************************
-> Enter Login: BBBBBB
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6231544
Authenticated!
$ id
uid=1006(level06) gid=1006(level06) euid=1007(level07) egid=100(users) groups=1007(level07),100(users),1006(level06)
$ cd ../level07
$ cat .pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
