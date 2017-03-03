MINISATROOT = ../minisat-master

INCLUDES = -I$(MINISATROOT)
LIBDIR = -L$(MINISATROOT)/build/release/lib
LIB = -lminisat -lz

.cpp:
	$(CXX) -w $< -o $@ $(INCLUDES) $(LIBDIR) $(LIB)
