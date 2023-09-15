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
