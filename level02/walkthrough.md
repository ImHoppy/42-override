# Level 02

```
level02@OverRide:~$ file level02
level02: setuid setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xf639d5c443e6ff1c50a0f8393461c0befc329e71, not stripped
```

Ici tous les buffers sont securises, pas contre un appel a printf est mal formate.
Nous allons donc essayer d'afficher le .pass qui a ete open par le programme et qui est dans la stack grace a un appel a read.

On peut donc afficher toutes les premieres adresses de la stack avec le script bash dans le dossier resources.

Nous remarquons que seul quelques adresse a la suite sont remplies.
On cherche les 5 a la suite du buffer, car 5 * 8 octets = 40 (la taille du buffer sans le null byte de fin)

On peut donc les decoder de hexa vers ascii, en inversant chaque byte du au little endian
