Script for finding correct condition
```
for ((i=-22;i<2;i++)); do
	echo $i;
	python -c "print 322424845 + $i" | ltrace ./level03 2>&1 | grep -E '^rand|system';
done
```

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
