CC=gcc -Wall -Wextra

all: m5c4_fork m5c7_shell m5c8_pipes m5c9_pipes m5c10_named_pipes

m5c4_fork: m5c4_fork.c
	$(CC) -o m5c4_fork $^

m5c7_shell: m5c7_shell.c
	$(CC) -o m5c7_shell $^

m5c8_pipes: m5c8_pipes.c
	$(CC) -o m5c8_pipes $^

m5c9_pipes: m5c9_pipes.c
	$(CC) -o m5c9_pipes $^

m5c10_named_pipes: m5c10_named_pipes.c
	$(CC) -o m5c10_named_pipes $^

clean:
	rm -f m5c4_fork
	rm -f m5c7_shell
	rm -f m5c8_pipes
	rm -f m5c9_pipes
	rm -f m5c10_named_pipes
	rm -f m5c10_pipe
