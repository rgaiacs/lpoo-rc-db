default: all

ROOTDIR = ..
include ../make.inc

OBJ = interface.o member.o

all: $(OBJ)
	$(AR) $(LIBNAME) $(OBJ)

$(LIBNAME): $(OBJ)
	$(AR) $(LIBNAME) $(OBJ)

clean:
	$(RM) $(OBJ)

purge: clean
	$(RM) $(LIBNAME)

%.o: ../src/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INC)
