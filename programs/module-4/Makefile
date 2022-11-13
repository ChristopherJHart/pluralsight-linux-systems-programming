CC=gcc -Wall -Wextra

all: m4c2_argc_argv m4c4_getopt m4c5_env

m4c2_argc_argv: m4c2_argc_argv.c
	$(CC) -o m4c2_argc_argv $^

m4c4_getopt: m4c4_getopt.c
	$(CC) -o m4c4_getopt $^

m4c5_env: m4c5_env.c
	$(CC) -o m4c5_env $^

clean:
	rm -f m4c2_argc_argv
	rm -f m4c4_getopt
	rm -f m4c5_env
