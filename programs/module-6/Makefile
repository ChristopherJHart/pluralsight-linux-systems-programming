CC=gcc -Wall -Wextra
OTHER_USER=cjh

all: m6c4_persona m6c6_file_permissions m6c8_file_ownership

m6c4_persona: m6c4_persona.c
	$(CC) -o m6c4_persona $^
	sudo chown $(OTHER_USER) ./m6c4_persona
	sudo chgrp $(OTHER_USER) ./m6c4_persona
	sudo chmod 6775 ./m6c4_persona

m6c6_file_permissions: m6c6_file_permissions.c
	$(CC) -o m6c6_file_permissions $^

m6c8_file_ownership: m6c8_file_ownership.c
	$(CC) -o m6c8_file_ownership $^
	sudo chown root ./m6c8_file_ownership
	sudo chgrp root ./m6c8_file_ownership
	sudo chmod 6775 ./m6c8_file_ownership

clean:
	rm -f m6c4_persona
	rm -f m6c6_file_permissions
	rm -f m6c8_file_ownership
