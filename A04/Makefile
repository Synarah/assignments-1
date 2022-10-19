CC=gcc
% :: %.c
	$(CC) -g -Wall -Wvla -Werror $< -o $@

test_ppm: test_ppm.c read_ppm.c 
	$(CC) -g -Wall -Wvla -Werror test_ppm.c read_ppm.c -o $@
all : test_ppm ascii_image

clean :
	rm test_ppm ascii_image 2> /dev/null
