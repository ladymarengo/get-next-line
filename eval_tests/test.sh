mv main.c.test main.c
make -C ../libft/
gcc -Wall -Wextra -Werror main.c ../get_next_line.c ../libft/libft.a -o get_next_line
./get_next_line test
rm get_next_line
make -C ../libft/ fclean
mv main.c main.c.test
