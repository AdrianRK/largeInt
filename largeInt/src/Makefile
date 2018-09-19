####################################################################################################
#                                     Make file LargeInt 	                                   #
####################################################################################################
CFLAGS:=-c -Wall --std=c++1y -fPIC
SOURCES:=largeInt.cpp
OBJDIR:=../../obj
BINDIR:=../../bin
LIBDIR:=../../lib
LDFLAGS:= -shared -fPIC
OBJECTS:=$(SOURCES:.cpp=.o)
CC:=g++
#EXECUTABLE:=largeInt
MAJOR:= 0
MINOR:= 1
NAME:= largeInt
VERSION := $(MAJOR).$(MINOR)

all: clean MAKEDIR $(SOURCES) lib install

lib: lib$(NAME).so.$(VERSION)

lib$(NAME).so.$(VERSION): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJDIR)/$(OBJECTS) -o $(LIBDIR)/$@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

clean:
	rm -rf $(LIBDIR)/lib$(NAME).so* $(OBJDIR)/$(OBJECTS)

MAKEDIR:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)

install:
	ln -sf lib$(NAME).so.$(VERSION) $(LIBDIR)/lib$(NAME).so.$(MAJOR)
	ln -sf lib$(NAME).so.$(VERSION) $(LIBDIR)/lib$(NAME).so
	sudo cp $(LIBDIR)/lib$(NAME).so /usr/lib/
	sudo cp $(LIBDIR)/lib$(NAME).so.$(VERSION) /usr/lib/
	sudo cp $(LIBDIR)/lib$(NAME).so.$(MAJOR) /usr/lib/
	export LD_LIBRARY_PATH=$(shell pwd)/$(LIBDIR):$(echo $LD_LIBRARY_PATH)
