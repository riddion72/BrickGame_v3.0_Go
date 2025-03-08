OS = $(shell uname)
CC = gcc
CXX = g++
GO = go build
GCOV = gcov
ifeq ("$(OS)","Linux")
	# LEAKS_RUN_TEST = valgrind --tool=memcheck --leak-check=yes --log-file=1.txt ./test
	# PKG =`pkg-config --cflags --libs gtest`
else
	# LEAKS_RUN_TEST = leaks -atExit -- ./test
	# PKG =`pkg-config --cflags --libs gtest gtest_main`
endif

CSTD = -std=c11
CXXSTD = -std=c++17
CFLAGS = -Wall -Werror -Wextra -pedantic
GOFLAGS = -buildmode=c-archive -o libs21_backend_race.a
CXXFLAGS = -std=c++11 -fPIC
LDFLAGS = -shared

TETRIS_PATH = brick_game/tetris/
SNAKE_PATH = brick_game/snake/
RACE_PATH = brick_game/race/
CLI_PATH = gui/cli/
CONTROLLER_PATH = brick_game/controller/
CONTROLLER_WRAPPER_PATH = brick_game/controller/wrapper/

EXTRA_LIBS = -lm -lncurses $(PKG)
BACKEND_C = $(wildcard $(TETRIS_PATH)*.c)
BACKEND_CC = $(wildcard $(SNAKE_PATH)*.cc)
BACKEND_GO = $(wildcard $(RACE_PATH)*.go)
FRONTEND_CLI = $(wildcard $(CLI_PATH)*.c)
CLI_ENGINE = $(wildcard $(CLI_PATH)*.cc)
CONTROLLER = $(wildcard $(CONTROLLER_PATH)*.cc)
WRAPPER = $(wildcard $(CONTROLLER_WRAPPER_PATH)*.cc)


TEST_LIB_C = $(BACKEND_C:.c=.o)
TEST_LIB_C_A = $(TEST_LIB_C:.o=.a)
TEST_LIB_CC = $(BACKEND_CC:.cc=.o) $(CONTROLLER:.cc=.o)
TEST_LIB_CC_A = $(TEST_LIB_CC:.o=.a)

OBJECTS_GCOV_C = $(addprefix gcov_obj/,$(TEST_LIB_C)) 
OBJECTS_GCOV_CC = $(addprefix gcov_obj/,$(TEST_LIB_CC))

all:  install install_cli

install:
	cd brick_game/race && $(GO) $(GOFLAGS)
	mkdir -p game/
	cd ./gui/desktop/Brick_game && qmake && make && cp ./Brick_game.app/Contents/MacOS/Brick_game ../../../game/Brick_game.exe
	

install_cli: $(FRONTEND_CLI:.c=.o) $(BACKEND_CC:.cc=.o) $(BACKEND_C:.c=.o) $(BACKEND_GO:.go=.a) $(CONTROLLER:.cc=.o)
	cd brick_game/race && $(GO) $(GOFLAGS)
	cd brick_game/race && mv libs21_backend_race.a ../../obj
	mkdir -p game/
	$(CXX) $(CFLAGS) $(CXXSTD) $(CLI_ENGINE) $(addprefix obj/,$(^F)) obj/libs21_backend_race.a -o game/cli_game.exe $(EXTRA_LIBS)

install_web:$(BACKEND_CC:.cc=.o) $(BACKEND_C:.c=.o) libs21_backend_race.a $(CONTROLLER:.cc=.o) $(WRAPPER:.cc=.o)
	$(CXX) $(LDFLAGS) obj/s21_*.o obj/*.a -o obj/libwrapper.so obj/wrapper.o
	mkdir -p game/
	go build -C brick_game/server -o ../../game/Server_game.exe main.go

play_desktop: install
	./game/Brick_game.exe

play_cli: install_cli
	./game/cli_game.exe

play_web: install_web
	./game/Server_game.exe

libs21_backend_race.a:
	cd brick_game/race && $(GO) $(GOFLAGS)
	cd brick_game/race && mv libs21_backend_race.a ../../obj

wrapper.o:
	$(CXX) $(CXXFLAGS) -c $(CONTROLLER_WRAPPER_PATH)wrapper.cc $(CONTROLLER_WRAPPER_PATH)wrapper.h -o obj/wrapper.o

%.a: %.o
	mkdir -p obj	
	ar rc obj/$(@F) obj/$(<F)
	ranlib obj/$(@F)

%.o: %.c
	mkdir -p obj
	$(CC) $(CSTD) $(CFLAGS) -g -c $< -o obj/$(@F)

%.o: %.cc
	mkdir -p obj
	$(CXX) $(CXXSTD) $(CFLAGS) -g -c $< -o obj/$(@F)

%.a: %.go
	cd brick_game/race && $(GO) $(GOFLAGS)
	cd brick_game/race && cp libs21_backend_race.a ../../obj

dvi:
	doxygen
	open ./html/index.html

dist:
	mkdir -p dist
	tar -czvf brick_game.tar ./
	mv brick_game.tar dist/

uninstall: clean
	rm -rf ./game


include ./Makefiles/gcov_report.mk
include ./Makefiles/test.mk
include ./Makefiles/utilites.mk