CXX = g++
CFLAGS = -g -Wall
LIBS = -l stdc++ -lm
SDIR = src
BDIR = bin
ODIR = obj
DEPS = $(SDIR)/physics.h

_OBJ = vector.o object.o wall.o simulation.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

bonk: $(OBJ)
		$(CXX) $(CFLAGS) $(LIBS) $^ -o $(BDIR)/$@

nuke:
		del $(ODIR)\*.o
		del $(BDIR)\*.exe

clean:
		del $(ODIR)\*.o
