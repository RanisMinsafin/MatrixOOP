CC = g++ -std=c++17
SOURCE = matrix_oop.cc
OBJECT = $(patsubst %matrix_oop.cc, %*.o,  ${SOURCE})
TEST_FLAGS =-lgtest -pthread

ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 ADD_LIB =
 TEST_FLAGS =-lgtest
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 ADD_LIB = -lgtest -lm -lrt -lpthread
 TEST_FLAGS =-lpthread -lgtest -pthread -lrt -lm -lc++
endif

all: clean matrix_oop.a

matrix_oop.a:$(SOURCE)
	$(CC) -c $(SOURCE)
	@ar rcs matrix_oop.a $(OBJECT)

test: matrix_oop.a
	$(CC) unit_test.cc matrix_oop.a $(TEST_FLAGS) -o unit-test
	./unit-test

clang:
	clang-format -style=Google -n *.cc  *.h

clean:
	@rm -rf *.o *.a a.out unit-test