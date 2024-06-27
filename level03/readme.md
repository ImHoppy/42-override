# Level03

Quand on exécute le programme, il nous demande un mot de passe. Il faut donc trouver ce mot de passe.
```
$ ./level03
***********************************
*               level03         **
***********************************
Password:42

Invalid Password
```
On va procéder au reverse engineering du programme pour comprendre et trouver le mot de passe.

La fonction `decrypt`, va prendre notre nombre que la fonction `test` avait soustrait précédemment. Sur chaque caractère de la string ```
Q}|u`sfg~sf{}|a3```, elle va faire un xor avec le nombre qu'on lui a donné.

```
>>> bytes.fromhex("757c7d51")[::-1]
b'Q}|u'
>>> bytes.fromhex("67667360")[::-1]
b'`sfg'
>>> bytes.fromhex("7b66737e")[::-1]
b'~sf{'
>>> bytes.fromhex("33617c7d")[::-1]
b'}|a3'
```
La nouvelle chaîne de charactères est comparée avec la chaîne ```Congratulations!```. Si elle est égale, alors le programme lance un shell.

Comme on sait que la fonction `decrypt` est lancée seulement si le nombre donné est entre (0x1 et 0x9) et (0x10 et 0x15), on va faire un script pour trouver le bon nombre.

Ce script va tout simplement boucler sur les nombres entre 0x1 et 0x15 et nous afficher sur quel nombre le programme lance `system`.
```
for ((i=-22;i<2;i++)); do
	python -c "print(322424845 + $i, $i)";
	python -c "print(322424845 + $i)" | ltrace ./level03 2>&1 | grep -E '^rand|system';
done
```
