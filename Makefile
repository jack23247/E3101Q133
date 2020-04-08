# Makefile
# Specifica di GNU Make per il progetto "btree"
# Esame di Programmazione C++ 20/04/20
# Copyright (c) 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>

.DEFAULT_GOAL := debug

# Flag per il compilatore
DBGFLAGS=-Og -ggdb
RELFLAGS=-O3
CXXFLAGS=-std=c++0x -Wall -Wextra -pedantic

# Sottodirettrici per i file oggetto ed eseguibile
DBG=.build/debug
REL=.build/release

# Target "debug" - Build con simboli di Debug
debug: $(DBG)/../../btree

$(DBG):
	mkdir -p $@

$(DBG)/main.o: main.cpp btree.hpp | $(DBG)
	$(CXX) $(CXXFLAGS) $(DBGFLAGS) -c $< -o $@

$(DBG)/../../btree: $(DBG)/main.o
	$(CXX) $(CXXFLAGS) $(DBGFLAGS) $^ -o $@

# Target "check" - Operazione di controllo dei memory leak
check: debug

	valgrind --leak-check=full ./btree
# Target "release" - Build pulita
release: $(REL)/../../btree autoclean

$(REL):
	mkdir -p $@

$(REL)/main.o: main.cpp btree.hpp | $(REL)
	$(CXX) $(CXXFLAGS) $(RELFLAGS) -c $< -o $@

$(REL)/../../btree: $(REL)/main.o
	$(CXX) $(CXXFLAGS) $(RELFLAGS) $^ -o $@

# Target "clean" - Operazione di pulizia
.PHONY: clean autoclean

clean:
	rm -rf .build

autoclean:
	rm -rf .build/release

# EOF