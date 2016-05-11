all: libutils.a
	gcc -pedantic -Wall -Werror -Wextra hoshell.c libutils.a

libutils.a:
	gcc -pedantic -Wall -Werror -Wextra -c utils/exit.c utils/inttostr.c utils/len.c utils/strcmp.c utils/strtoint.c utils/read_line.c utils/string_copy.c utils/string_split.c utils/utils.h
	ar -rc libutils.a exit.o inttostr.o strtoint.o len.o strcmp.o read_line.o string_copy.o string_split.o
	rm exit.o inttostr.o strtoint.o len.o strcmp.o read_line.o string_copy.o string_split.o

clean:
	rm a.out hoshell.o exit.o  inttostr.o  strtoint.o utils/utils.h.gch libutils.a
