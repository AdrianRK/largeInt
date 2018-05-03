####################################################################################################
#                                     Make file LargeInt 	                                   #
####################################################################################################
CFLAGS:=-c -Wall --std=c++1y 
SOURCES:=main.cpp
OBJDIR:=../obj
BINDIR:=../bin
LIBDIR:=../lib
LDFLAGS:=
OBJECTS:=$(SOURCES:.cpp=.o)
CC:=g++
EXECUTABLE:=largeInt

all: clean MAKEDIR $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJDIR)/$(OBJECTS) -o $(BINDIR)/$@ 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

clean:
	rm -rf $(BINDIR)/$(EXECUTABLE) $(OBJDIR)/$(OBJECTS)

MAKEDIR:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)
