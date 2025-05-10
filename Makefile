CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC
LDFLAGS = -L. -lfunctions
INCLUDES = -I.

LIB_SRC = functions.cpp
LIB_OBJ = functions.o
LIB_SO  = libfunctions.so

MAINS = main1_printdb main2_search main3_export_csv main4_reload_blocks main5_menu
BINARIES = $(MAINS:=.out)

all: $(LIB_SO) $(BINARIES)

$(LIB_SO): $(LIB_OBJ)
	$(CXX) -shared -o $@ $^

$(LIB_OBJ): $(LIB_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o *.out *.so
