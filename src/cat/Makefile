s21_cat: clean
	@gcc -c libs_cat.c -o libs_cat.o -Wall -Werror -Wextra
	@gcc -Wall -Wextra -Werror -std=c11 cat.c libs_cat.o -o s21_cat
clean:
	@rm -rf s21_cat
	@rm -rf libs_cat.o
	@rm -rf test
test_cat: s21_cat test_c
	@cat ../common/file.txt > ../common/1.txt
	@./s21_cat ../common/file.txt > ../common/2.txt
	@./test - ../common/1.txt ../common/2.txt
	@cat -b ../common/file.txt > ../common/1.txt
	@./s21_cat -b ../common/file.txt > ../common/2.txt
	@./test -b ../common/1.txt ../common/2.txt
	@cat -e ../common/file.txt > ../common/1.txt
	@./s21_cat -e ../common/file.txt > ../common/2.txt
	@./test -e ../common/1.txt ../common/2.txt
	@cat -s ../common/file.txt > ../common/1.txt
	@./s21_cat -s ../common/file.txt > ../common/2.txt
	@./test -s ../common/1.txt ../common/2.txt
	@cat -t ../common/file.txt > ../common/1.txt
	@./s21_cat -t ../common/file.txt > ../common/2.txt
	@./test -t ../common/1.txt ../common/2.txt
	@cat -n ../common/file.txt > ../common/1.txt
	@./s21_cat -n ../common/file.txt > ../common/2.txt
	@./test -n ../common/1.txt ../common/2.txt
	@cat --number-nonblank ../common/file.txt > ../common/1.txt
	@./s21_cat --number-nonblank ../common/file.txt > ../common/2.txt
	@./test --number-nonblank ../common/1.txt ../common/2.txt
	@cat --number ../common/file.txt > ../common/1.txt
	@./s21_cat --number ../common/file.txt > ../common/2.txt
	@./test --number ../common/1.txt ../common/2.txt
	@cat --squeeze-blank ../common/file.txt > ../common/1.txt
	@./s21_cat --squeeze-blank ../common/file.txt > ../common/2.txt
	@./test --squeeze-blank ../common/1.txt ../common/2.txt
test_c:
	@gcc ../common/test.c -o test
.PHONY: s21_cat
