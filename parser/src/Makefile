####################################################################################################
#                                     Make file LargeInt 	                                   #
####################################################################################################
CFLAGS:=-c -Wall --std=c++1y -D__DEBUG__D
SOURCES:=main.cpp
OBJDIR:=../../obj
BINDIR:=../../bin
LIBDIR:=../../lib
LDFLAGS:=-L$(LIBDIR) 
OBJECTS:=$(SOURCES:.cpp=.o)
CC:=g++
EXECUTABLE:=parser
LIBRARIES:= -llargeInt

all: clean MAKEDIR $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJDIR)/$(OBJECTS) -o $(BINDIR)/$@ $(LIBRARIES)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@

clean:
	rm -rf $(BINDIR)/$(EXECUTABLE) $(OBJDIR)/$(OBJECTS)

MAKEDIR:
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)


