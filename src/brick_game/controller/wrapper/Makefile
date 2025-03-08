CXX = g++

CXXFLAGS = -std=c++11 -fPIC
LDFLAGS = -shared

all: libwrapper.so

libwrapper.so: wrapper.o s21_controller.o
	$(CXX) $(LDFLAGS) ../../obj/*.o ../../obj/*.a -o $@ $^

wrapper.o: wrapper.cc wrapper.h 
	$(CXX) $(CXXFLAGS) -c $@ $^

s21_controller.o: s21_controller.cc s21_controller.h
	$(CXX) $(CXXFLAGS) -c $@ $^
clean:
	rm -f *.o *.so