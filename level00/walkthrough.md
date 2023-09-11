# Level 00

Pour ce premier niveau, on nous donne un binaire, il va simple demande un mot de passe via `scanf` et check si le mot de passe est égal à `5276`.<br/>
Si ne n'est pas le cas il va afficher `Invalid Password!` et quitter le programme. Sinon il va afficher `Authenticated!` et exécuter la commande `/bin/sh`.<br/>

```asm
 80484de:       e8 ed fe ff ff          call   80483d0 <__isoc99_scanf@plt>		; Execute scanf with "%d" as format
 80484e3:       8b 44 24 1c             mov    eax,DWORD PTR [esp+0x1c]
 80484e7:       3d 9c 14 00 00          cmp    eax,5276							; Compare the input with 5276
 80484ec:       75 1f                   jne    804850d <main+0x79>				; If not equal jump to 804850d
 80484ee:       c7 04 24 39 86 04 08    mov    DWORD PTR [esp],0x8048639		; Else put "Authenticated!" in the stack
 80484f5:       e8 96 fe ff ff          call   8048390 <puts@plt>				; Call puts
 80484fa:       c7 04 24 49 86 04 08    mov    DWORD PTR [esp],0x8048649		; Put "/bin/sh" in the stack
 8048501:       e8 9a fe ff ff          call   80483a0 <system@plt>				; Call system
 8048506:       b8 00 00 00 00          mov    eax,0x0							; Put 0 in eax
 804850b:       eb 11                   jmp    804851e <main+0x8a>				; Quit the program with $eax
 804850d:       c7 04 24 51 86 04 08    mov    DWORD PTR [esp],0x8048651		; Put "Invalid Password!" in the stack
 8048514:       e8 77 fe ff ff          call   8048390 <puts@plt>				; Call puts

```

```
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ id
uid=1000(level00) gid=1000(level00) euid=1001(level01) egid=100(users) groups=1001(level01),100(users),1000(level00)
```
