#main makefile
CFLAGS+=-I./inc -g -ggdb
LDFLAGS+=-lsfml-graphics -lsfml-window -lsfml-system

OBJ+=main.o
LIBOBJ+=./src/src.a
all:main
main:$(OBJ) $(LIBOBJ)
	$(CXX) $(OBJ) $(LIBOBJ) -o $@ $(LDFLAGS)  
main.o:main.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<
src/src.a:src/*.cpp
	$(MAKE) -C ./src src.a 
clean:
	-rm main $(OBJ) $(LIBOBJ) 
	$(MAKE) -C ./src clean
rebuild:clean all
