all: ttable

ttable: ttable.o stack.o
	clang -o ttable ttable.o stack.o -Wextra -Wall -g

ttable.o: ttable.c ttable.h stack.h
	clang -c ttable.c -Wextra -Wall -g

stack.o: stack.c stack.h
	clang -c stack.c -Wextra -Wall -g

clean:
	rm -f ttable *.o