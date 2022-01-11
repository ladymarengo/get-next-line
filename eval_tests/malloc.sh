mv main.c.test main.c
gcc -Wall -Wextra -Werror -g main.c ../get_next_line.c ../libft/libft.a -o get_next_line
valgrind --leak-check=yes ./get_next_line testfiles/4char_5line
rm get_next_line
mv main.c main.c.test