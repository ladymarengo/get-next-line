mv main.c.test main.c
gcc -Wall -Wextra -Werror main.c ../get_next_line.c ../libft/libft.a -o get_next_line
./get_next_line testfiles/test_bible.txt
./get_next_line testfiles/empty
./get_next_line testfiles/one_newline
./get_next_line testfiles/two_newlines
./get_next_line testfiles/random_test
./get_next_line testfiles/4char_1line
./get_next_line testfiles/4char_2line
./get_next_line testfiles/4char_5line
./get_next_line testfiles/16char_1line
./get_next_line testfiles/16char_2line
./get_next_line
rm get_next_line
mv main.c main.c.test
