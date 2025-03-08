CLANG_FORMAT = ../materials/linters/.clang-format

clang:
	clang-format --style=file:$(CLANG_FORMAT) -i $(TETRIS_PATH)*.c \
	$(TETRIS_PATH)*.h $(SNAKE_PATH)*.cc $(SNAKE_PATH)*.h \
	$(CLI_PATH)*.c $(CLI_PATH)*.cc $(CLI_PATH)*.h \
	$(CONTROLLER_PATH)*.cc $(CONTROLLER_PATH)*.h \
	gui/desktop/*.cc gui/desktop/*.h

clang_check:
	clang-format --style=file:$(CLANG_FORMAT) -n $(TETRIS_PATH)*.c \
	$(TETRIS_PATH)*.h $(SNAKE_PATH)*.cc $(SNAKE_PATH)*.h \
	$(CLI_PATH)*.c $(CLI_PATH)*.cc $(CLI_PATH)*.h \
	$(CONTROLLER_PATH)*.cc $(CONTROLLER_PATH)*.h

check:
	cppcheck -q --enable=warning,portability --check-level=exhaustive --inconclusive ./

#.PHONY: all clean rebuild clang check

clean:
	rm -rf $(LIBS) $(TEST_LIB) *.o *.so *.a *.out *.gcda *.gcno *.info test test.c test_gcov report obj gcov_obj tetris
	rm -rf ./html ./latex
	rm -f *.txt
	rm -f ./brick_game/controller/wrapper/*.h.gch
	rm -f ./brick_game/race/*.h
	rm -f ./brick_game/race/*.a
	rm -rf ./dist
	rm -rf ./gui/desktop/Brick_game/Brick_game.app
	rm -f ./gui/desktop/Brick_game/*.o
	rm -f ./gui/desktop/Brick_game/Makefile ./gui/desktop/Brick_game/snake.pro.user ./gui/desktop/Brick_game/moc_predefs.h ./gui/desktop/Brick_game/ui_mainwindow.h ./gui/desktop/Brick_game/ui_secondwindow.h ./gui/desktop/Brick_game/.qmake.stash
	

rebuild: clean all