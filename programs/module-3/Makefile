CC=gcc -Wall -Wextra

all: m3c4_file_metadata m3c8_traverse_directory m3c10_inotify_api

m3c4_file_metadata: m3c4_file_metadata.c
	$(CC) -o m3c4_file_metadata $^

m3c8_traverse_directory: m3c8_traverse_directory.c
	$(CC) -o m3c8_traverse_directory $^

m3c10_inotify_api: m3c10_inotify_api.c
	$(CC) -o m3c10_inotify_api $^

clean:
	rm -f m3c4_file_metadata
	rm -f m3c8_traverse_directory
	rm -f m3c10_inotify_api
