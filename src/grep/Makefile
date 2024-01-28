s21_grep: clean
	@gcc -g -c libs_grep.c -o libs_grep.o -Wall -Werror -Wextra
	@gcc -g grep.c libs_grep.o -o s21_grep -Wall -Werror -Wextra
clean:
	@rm -rf s21_grep
	@rm -rf libs_grep.o
	@rm -rf test
test_grep: s21_grep test_c
	@grep banana ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep banana ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test - ../common/1.txt ../common/2.txt
	@grep -e banana -e Hello ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -e banana -e Hello ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -e ../common/1.txt ../common/2.txt
	@grep -i BaNaNa ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -i BaNaNa ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -i ../common/1.txt ../common/2.txt
	@grep -v banana ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -v banana ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -v ../common/1.txt ../common/2.txt
	@grep -c banana ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -c banana ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -c ../common/1.txt ../common/2.txt
	@grep -l banana ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -l banana ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -l ../common/1.txt ../common/2.txt
	@grep -n banana ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -n banana ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -n ../common/1.txt ../common/2.txt
	@grep -h banana ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -h banana ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -h ../common/1.txt ../common/2.txt
	@grep -s banana ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -s banana ../common/file.txt ggg ../common/file2.txt > ../common/2.txt
	@./test -s ../common/1.txt ../common/2.txt
	@grep -f ../common/patern.txt ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -f ../common/patern.txt ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -f ../common/1.txt ../common/2.txt
	@grep -o na ../common/file.txt ../common/file2.txt > ../common/1.txt
	@./s21_grep -o na ../common/file.txt ../common/file2.txt > ../common/2.txt
	@./test -o ../common/1.txt ../common/2.txt
test_c:
	@gcc -g ../common/test.c -o test
.PHONY: s21_grep
