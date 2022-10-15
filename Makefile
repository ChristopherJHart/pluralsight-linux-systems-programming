CC=gcc -Wall -Wextra

all: module2

module2:
	make -C programs/module-2

clean:
	make -C programs/module-2 clean
