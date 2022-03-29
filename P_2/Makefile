# Author: Dominik Pop
# Login: xpopdo00
# Date: 11.2.2021
# IPK project #1

CC=gcc
CFLAGS=-std=gnu99 -Wall -Werror
LIBRARIES=-lm
FILES= *.c *.h
NAME=ipk-sniffer
LOGIN=xpopdo00

$(NAME): $(FILES)
		$(CC) $(CFLAGS) -o $@ $(FILES) $(LIBRARIES)

clean:
	rm -f *.o $(NAME)

run:
	./$(NAME) -i eth0 -p 23 -t -n 10

run1:
	./$(NAME) -i

run2:
	./$(NAME) -i eth0 -p 23 -u -n 10

run3:
	./$(NAME) -i eth0 -p 23 --arp -n 10

run4:
	./$(NAME) -i eth0 -p 23 --icmp -n 10

zip:
	zip $(LOGIN).zip  $(FILES) Makefile Readme.md
