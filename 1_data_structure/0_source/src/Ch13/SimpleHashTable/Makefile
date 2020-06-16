NAME=libft_print.a

GCC=gcc -Wall -Wextra -Werror -g -fsanitize=address

HEAD=$(wildcard *.h)

SRC=$(wildcard *.c)

OBJ=$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SRC) $(HEAD)
	$(GCC) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	$(GCC) -o main $(NAME) $(HEAD)

clean:
	rm -f $(OBJ) main

fclean: clean
	rm -f $(NAME)

re: fclean all
