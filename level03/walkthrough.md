Script for finding correct condition
```
for ((i=-22;i<2;i++)); do echo $i; python -c "print 322424845 + $i" | ltrace ./level03 2>&1 | grep ^rand; done
```
