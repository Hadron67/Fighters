#makefile in ./src
INC+=../inc
CFLAGS+=-Wall -g -I$(INC) -ggdb
OBJ+=MainWindow.o fighter.o gamescene.o bullet.o packparser.o fighter1.o enemy1.o hitTestable.o enemy2.o enemy3.o resources.o wbox.o
all:src.a
src.a:$(OBJ)
	$(AR) rc $@ $(OBJ)
MainWindow.o:MainWindow.cpp $(INC)/MainWindow.hpp  $(INC)/gamescene.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
fighter.o:fighter.cpp $(INC)/fighter.hpp $(INC)/bullet.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
gamescene.o:gamescene.cpp $(INC)/gamescene.hpp $(INC)/fighter.hpp $(INC)/bullet.hpp $(INC)/enemy2.hpp $(INC)/fighter1.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
bullet.o:bullet.cpp $(INC)/bullet.hpp $(INC)/hitTestable.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
packparser.o:PackParser.cpp $(INC)/PackParser.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
fighter1.o:fighter1.cpp $(INC)/fighter1.hpp $(INC)/fighter.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
enemy1.o:enemy1.cpp $(INC)/enemy1.hpp $(INC)/fighter.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
hitTestable.o:hitTestable.cpp $(INC)/hitTestable.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
enemy2.o:enemy2.cpp $(INC)/enemy2.hpp $(INC)/fighter.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
enemy3.o:enemy3.cpp $(INC)/enemy3.hpp $(INC)/fighter.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
resources.o:resources.cpp $(INC)/resources.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
wbox.o:wbox.cpp $(INC)/wbox.hpp
	$(CXX) $(CFLAGS) -c -o $@ $<
clean:
	-rm $(OBJ) src.a
