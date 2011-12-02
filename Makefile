CXX=g++
CFLAGS=-Wall -g -I../ -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC

OBJS=Level.o Tank.o Missile.o collide.o TankGameModel.o TankGameView.o TankGameController.o KeyboardController.o
LIBNAME=libtanks.a

all: $(LIBNAME)

clean:
	rm -rf $(LIBNAME) $(OBJS)

$(LIBNAME): $(OBJS)
	ar -cvq $(LIBNAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<
