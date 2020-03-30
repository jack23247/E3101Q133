# Makefile
# Specifica di GNU Make per il progetto "bst"
# (c) 2020 - Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
# Rilasciato sotto licenza MIT - Released under MIT license

.DEFAULT_GOAL := debug

# Flag per il compilatore
DBGFLAGS=-Og -ggdb -DDEBUG
RELFLAGS=-O3
CXXFLAGS=-std=c++0x -Wall

# Sottodirettrici per i file oggetto ed eseguibile
DBG=.build/debug
REL=.build/release

# Target "debug" - Build con simboli di Debug
debug: $(DBG)/../../bst

$(DBG):
	mkdir -p $@

$(DBG)/main.o: main.cpp bst.hpp | $(DBG)
	$(CXX) $(CXXFLAGS) $(DBGFLAGS) -c $< -o $@

$(DBG)/../../bst: $(DBG)/main.o
	$(CXX) $(CXXFLAGS) $(DBGFLAGS) $^ -o $@

# Target "release" - Build pulita
release: $(REL)/../../bst clean

$(REL):
	mkdir -p $@

$(REL)/main.o: main.cpp bst.hpp | $(REL)
	$(CXX) $(CXXFLAGS) $(RELFLAGS) -c $< -o $@

$(REL)/../../bst: $(REL)/main.o
	$(CXX) $(CXXFLAGS) $(RELFLAGS) $^ -o $@

# Target "clean" - Operazione di pulizia
.PHONY: clean test

clean:
	rm -rf .build

# Target "check" - Operazione di controllo dei memory leak
check:
	valgrind --leak-check=full ./bst

# EOF