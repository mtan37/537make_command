# cs537_proj3

A simple make file that could parse basic Makefile, understand the dependencies and execute the command

```
target: dependence1 dependence2 ... dependencen
	command1 ...
	command2 ...
	...
	commandm
```

user could specify tset file with a customized path using the -f option

```
537make -f test <target>
```
