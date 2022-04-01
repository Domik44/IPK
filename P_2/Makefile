# Author: Dominik Pop
# Login: xpopdo00
# Date: 11.2.2021
# IPK project #1

CC=gcc
CFLAGS=-std=gnu99 -Wall
LIBRARIES=-lpcap
FILES= *.c *.h
NAME=ipk-sniffer
LOGIN=xpopdo00

$(NAME): $(FILES)
		$(CC) $(CFLAGS) -o $@ $(FILES) $(LIBRARIES)

clean:
	rm -f *.o $(NAME)

run:
	sudo ./$(NAME) -i enp0s3 -t -n 5

run1:
	./$(NAME) -i

run2:
	sudo ./$(NAME) -i enp0s3 --icmp -n 5

run3:
	sudo ./$(NAME) -i enp0s3 --arp -n 5

run4:
	sudo ./$(NAME) -i enp0s3 --udp -n 10

zip:
	zip $(LOGIN).zip  $(FILES) Makefile Readme.md
