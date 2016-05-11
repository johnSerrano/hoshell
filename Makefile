all: libutils.a
	gcc -pedantic -Wall -Werror -Wextra hoshell.c libshell/libshell.a libutils.a

libutils.a:
	gcc -pedantic -Wall -Werror -Wextra -c utils/exit.c utils/inttostr.c utils/len.c utils/strcmp.c utils/strtoint.c utils/env.c utils/utils.h
	ar -rc libutils.a exit.o inttostr.o strtoint.o len.o strcmp.o env.o
	rm exit.o inttostr.o strtoint.o len.o strcmp.o env.o

clean:
	rm a.out hoshell.o exit.o  inttostr.o  strtoint.o env.o utils/utils.h.gch libutils.a
