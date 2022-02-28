# Author: Dominik Pop
# Login: xpopdo00
# Date: 11.2.2021
# IPK project #1

CC=gcc
CFLAGS=-std=gnu99 -Wall -Werror
LIBRARIES=-lm
FILES= *.c *.h
NAME=hinfosvc
LOGIN=xpopdo00

$(NAME): $(FILES)
		$(CC) $(CFLAGS) -o $@ $(FILES) $(LIBRARIES)

clean:
	rm -f *.o $(NAME)

run:
	./$(NAME) 12345

zip:
	zip $(LOGIN).zip  $(FILES) Makefile Readme.md
