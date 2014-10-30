TARGET	= ./xshot

# -------------------------------------------------------------------------------------------

SOURCES = main.cpp
HEADERS =

# -------------------------------------------------------------------------------------------

CXX          = smp-g++
CXX_FLAGS    = -c -Wall -Wextra -std=c++11  -O3 
LINK_FLAGS   = -lX11


OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(HEADERS) $(TARGET) Makefile
	rm -f $(OBJECTS)

$(TARGET): $(OBJECTS) $(HEADERS)  Makefile
	$(CXX) $(OBJECTS) $(LINK_FLAGS) $(API_LIBS) -o $@

.cpp.o: $(SOURCES)  $(HEADERS)
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)



