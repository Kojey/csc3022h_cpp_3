#Makefile for compiling work
#(C) Benjamin Hugo, 2015
#You are free to modify and reuse this in your own practicals
#This file is in the public domain

CPP=g++
CPPFLAGS=-fPIC -shared -std=c++11 #must output a shared library here
LIB_NAME=libhuffmanlib.so
#define a generic rule: to go from .cpp to .o files make should invoke the c++ compiler
#the syntax tells make to invoke the compiler without linking (-c), outputting a .o file reading a .cpp file, additionally specifying flags
%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)
#the next rule will tell make link together our shared library object (.so file / in windows this will be a DLL file) from the compiled objects
$(LIB_NAME): huffmanTree.o huffmanTree.h catch.hpp
	$(CPP) -o $(LIB_NAME) huffmanTree.o catch.hpp $(CPPFLAGS) 

#Never submit binaries to your git repo or vula, so create a rule for cleaning up the binary objects just leaving your source code behind
clean:
	@rm *.o *.so
