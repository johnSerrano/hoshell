all: libutils.a
	gcc -pedantic -Wall -Werror -Wextra hoshell.c libutils.a -o hoshell

libutils.a:
	gcc -pedantic -Wall -Werror -Wextra -c utils/exit.c utils/free_command.c utils/inttostr.c utils/len.c utils/strcmp.c utils/strtoint.c utils/env.c utils/read_line.c utils/string_copy.c utils/string_split.c utils/utils.h
	ar -rc libutils.a exit.o inttostr.o strtoint.o len.o strcmp.o read_line.o free_command.o string_copy.o string_split.o env.o
	rm exit.o inttostr.o strtoint.o len.o strcmp.o read_line.o string_copy.o string_split.o free_command.o env.o

clean:
	rm hoshell utils/utils.h.gch libutils.a
