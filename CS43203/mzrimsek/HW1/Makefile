all: cp1 who4
clean:
	rm -f cp1 who4
cp1: cp1.c
	cc -o cp1 cp1.c
who4: who4.c utmplib.c
	cc -o who4 who4.c utmplib.c
