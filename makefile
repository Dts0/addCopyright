SRCS    = $(wildcard *.cpp)
OBJS    = $(patsubst %.cpp, %.o, $(SRCS))
HEADS	= $(wildcard *.hpp)

CC      = g++
CFLAGS  = -g -Wall -O0 $(EXT_SO_CC) -std=c++11

TARGET      = ./bin/addCopyright
INC_PATH    = -I./include/
LIB_PATH    = -L./lib/

EXT_LIB     = #./lib/libreply.a
EXT_SO		= -L. -Wl,--rpath=./lib/
EXT_SO_CC	= -fPIC

all:$(TARGET)

$(TARGET):$(OBJS)
	if [ ! -d "bin/" ];then mkdir bin;fi
	$(CC) $(LIB_PATH) $(CFLAGS) -o $@ $^ $(EXT_LIB) $(EXT_SO)

%.o:%.cpp
	$(CC) $(INC_PATH) $(CFLAGS) -c -o $@ $<
%.o:%.c
	$(CC) $(INC_PATH) $(CFLAGS) -c -o $@ $<

run:$(TARGET)
	$(TARGET)

.PHONY:clean
clean:
	rm -rf $(TARGET) $(OBJS) test1.hpp test2.hpp copyright.txt
clear:
	rm -rf $(OBJS)
addCopyright:
	make
	bin/addCopyright $(SRCS) $(HEADS) -c default
install:
	make
	cp bin/addCopyright /bin/addCopyright
uninstall:
	rm -rf /bin/addCopyright
test:
	make
	echo "there is code.file1." > test1.hpp
	echo "there is code.file2." > test2.hpp
	echo "/*copyright*/" > copyright.txt
	bin/addCopyright test1.hpp test2.hpp -c copyright.txt
	cat copyright.txt

	cat test1.hpp

	cat test2.hpp
