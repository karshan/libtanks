CXX=g++
CFLAGS=-Wall -g -I../

OBJS=Level.o Tank.o Missile.o TankGameModel.o TankGameView.o
LIBNAME=libtanks.a

all: $(LIBNAME)

clean:
	rm -rf $(LIBNAME) $(OBJS)

$(LIBNAME): $(OBJS)
	ar -cvq $(LIBNAME) $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<
