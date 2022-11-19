CC=gcc -Wall -Wextra

all: m4c2_argc_argv m4c4_getopt m4c5_env m4c7_strftime m4c8_strftime_locales m4c9_process_time

m4c2_argc_argv: m4c2_argc_argv.c
	$(CC) -o m4c2_argc_argv $^

m4c4_getopt: m4c4_getopt.c
	$(CC) -o m4c4_getopt $^

m4c5_env: m4c5_env.c
	$(CC) -o m4c5_env $^

m4c7_strftime: m4c7_strftime.c
	$(CC) -o m4c7_strftime $^

m4c8_strftime_locales: m4c8_strftime_locales.c
	$(CC) -o m4c8_strftime_locales $^

m4c9_process_time: m4c9_process_time.c
	$(CC) -o m4c9_process_time $^

clean:
	rm -f m4c2_argc_argv
	rm -f m4c4_getopt
	rm -f m4c5_env
	rm -f m4c7_strftime
	rm -f m4c8_strftime_locales
	rm -f m4c9_process_time
