CC= g++
CFLAGS= -Wall -Werror -Wextra -g -std=c++17 
PROJECT= matrix_oop
TESTFLAGS = -lgtest -lpthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
OPEN_CMD = xdg-open
else
OPEN_CMD = open
endif

all: clean $(PROJECT).a test

$(PROJECT).a:
	$(CC) $(CFLAGS) -c matrix_oop.cc
	ar rvs matrix_oop.a matrix_oop.o
	# ar rcs matrix_oop.a matrix_oop.o
	rm -f *.o

test: clean matrix_oop.a
	$(CC) tests/tests_main.cc $(CFLAGS) $(TESTFLAGS) -o test -L. matrix_oop.a 
	# valgrind --tool=memcheck --leak-check=yes  ./test
	./test

gcov_report: clean matrix_oop.a
	$(CC) $(CFLAGS) -c matrix_oop.cc $(GCOV_FLAGS) 
	$(CC) $(CFLAGS) -c tests/tests_main.cc $(TESTFLAGS)
	$(CC) $(CFLAGS)  matrix_oop.o tests_main.o -o test $(TESTFLAGS) $(GCOV_FLAGS)
	./test
	lcov -c -d . -t "app_coverage" -o app_coverage.info --exclude '/usr/*'
	genhtml -o report app_coverage.info
	$(OPEN_CMD) report/index.html

check_style:
	clang-format -n --style=Google *.cc *.h tests/*.cc

fix_style:
	clang-format -i --style=Google *.cc *.h tests/*.cc

clean:
	rm -rf *.o ./report *.dSYM *.a *.out *.gcov *.info *.gcda *.gcno *.o *.gch test

# try:
# 	g++ -Wall -Wextra -Werror *.cc && valgrind ./a.out
# try_v:
# 	g++ -Wall -Wextra -Werror *.cc && valgrind --tool=memcheck --leak-check=yes ./a.out
# try_l:
# 	g++ -Wall -Wextra -Werror *.cc && leaks -atExit -- ./a.out 
# db: 
# 	g++ -g *.cc