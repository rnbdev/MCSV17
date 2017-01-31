CUDD_ROOT = /home/ranadeep/cmi/MCSV17/CUDD/cudd-3.0.0
CUDD_DIRS = . cudd st epd mtr util cplusplus
CUDD_LIBS = cudd
CXX = g++
CC = gcc
INCLUDE = $(addprefix -I$(CUDD_ROOT)/,$(CUDD_DIRS))
LIBDIR = $(addsuffix /.libs,$(addprefix -L$(CUDD_ROOT)/,$(CUDD_LIBS)))
LIBS = $(addprefix -l,$(CUDD_LIBS))

all:
	@echo CC $(INCLUDE) $(LIBDIR) $(LIBS)

.c:
	$(CC) -w $(INCLUDE) $(LIBDIR) $(LIBS) -o $@ $<

.cpp:
	$(CXX) -w $(INCLUDE) $(LIBDIR) $(LIBS) -o $@ $<

clean:
	-rm *.o