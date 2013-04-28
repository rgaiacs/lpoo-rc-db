default: all

include ../make.inc

OBJ = interface.o member.o
BINOBJ = main.o
BIN = ../lpoo-rc-db

all: $(OBJ)
	$(AR) $(LIBNAME) $(OBJ)

$(LIBNAME): $(OBJ)
	$(AR) $(LIBNAME) $(OBJ)

bin: $(OBJ) $(BINOBJ)
	$(CXX) -o $(BIN) $(BINOBJ) $(OBJ) $(CXXFLAGS) $(INC)

clean:
	$(RM) $(OBJ) $(BINOBJ)

purge: clean
	$(RM) $(LIBNAME) $(BIN)

%.o: ../src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INC)
