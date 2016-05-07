all: lclnt3 lserv3
clean:
	rm -f lclnt3 lserv3
lclnt3: lclnt3.c
	cc -w -o lclnt3 lclnt3.c
lserv3: lserv3.c
	cc -w -o lserv3 lserv3.c lserv_funcs3.c dgram.c
