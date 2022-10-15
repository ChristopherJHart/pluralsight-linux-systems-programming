CC=gcc -Wall -Wextra

all: m2c4_low_level_file_copy m2c5_low_level_random_access m2c5_low_level_random_access_edit m2c6_low_level_scatter_gather m2c7_low_level_memory_map m2c9_stream_file_copy m2c10_file_io_comparison

m2c4_low_level_file_copy: m2c4_low_level_file_copy.c
	$(CC) -o m2c4_low_level_file_copy $^

m2c5_low_level_random_access: m2c5_low_level_random_access.c
	$(CC) -o m2c5_low_level_random_access $^

m2c5_low_level_random_access_edit: m2c5_low_level_random_access_edit.c
	$(CC) -o m2c5_low_level_random_access_edit $^

m2c6_low_level_scatter_gather: m2c6_low_level_scatter_gather.c
	$(CC) -o m2c6_low_level_scatter_gather $^

m2c7_low_level_memory_map: m2c7_low_level_memory_map.c
	$(CC) -o m2c7_low_level_memory_map $^

m2c9_stream_file_copy: m2c9_stream_file_copy.c
	$(CC) -o m2c9_stream_file_copy $^

m2c10_file_io_comparison: m2c10_file_io_comparison.c
	$(CC) -o m2c10_file_io_comparison $^

clean:
	rm -f m2c4_low_level_file_copy
	rm -f m2c4_destination.txt
	rm -f m2c5_low_level_random_access
	rm -f employee_database
	rm -f m2c5_low_level_random_access_edit
	rm -f m2c6_low_level_scatter_gather
	rm -f employee_database_scatter_gather
	rm -f m2c7_low_level_memory_map
	rm -f employee_database_memory_map
	rm -f m2c9_stream_file_copy
	rm -f m2c9_destination.txt
	rm -f m2c10_file_io_comparison
