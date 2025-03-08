FREE_TEST_C = rm -rf test.c test.o 
TEST_CC = $(wildcard ./tests/*.cc)
TEST_FLAGS = -lgtest_main

test.o:
	mkdir -p obj
	$(CXX) $(CXXSTD) $(CFLAGS) -g -c $(TEST_CC) -o ./obj/test.o 

test: clean test.o $(BACKEND_CC:.cc=.o) $(BACKEND_C:.c=.o) $(CONTROLLER:.cc=.o)
	$(CXX) $(CFLAGS) $(CXXSTD) $(wildcard ./obj/*.o) -o test $(EXTRA_LIBS)
	./test


leak_test: clean test.o $(TEST_LIB_C_A) $(TEST_LIB_CC_A)
	$(CXX) $(CFLAGS) $(CXXSTD) $(wildcard ./obj/*.o) -o test $(EXTRA_LIBS)
	$(LEAKS_RUN_TEST)
	$(FREE_TEST)
