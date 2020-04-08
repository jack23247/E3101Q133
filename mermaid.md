<!--
mermaid.md
Sorgente per i grafi Mermaid per il progetto "btree"
Esame di Programmazione C++ 20/04/20
Copyright (c) 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
-->

> ***NOTA***<br>
> Questo documento contiene le definizioni, generate automaticamente o manualmente, dei grafi utilizzati nel file Readme.md: e' possibile che alcune parti di questo documento non vengano visualizzate correttamente, in quanto Doxygen e di GitHub non implementano l'estensione della sintassi Mermaid. Si prega di consultare il file [Readme](./Readme.md).

# filesys_graph

```mermaid
graph TD;
/ --> .build
.build --> debug
debug --> dbg_main.o[main.o]
release --> rel_main.o[main.o]
.build --> release
/ --> html
/ --> .gitignore
/ --> btree
/ --> btree.hpp
/ --> btexcept.hpp
/ --> Doxyfile
/ --> main.cpp
/ --> Makefile
/ --> mermaid.md
/ --> Readme.md
```
# test_int_graph

```mermaid
graph TD; 6 -- l --> 3; 3 -- l --> 2; 3 -- r --> 4; 4 -- r --> 5; 6 -- r --> 9; 9 -- l --> 7; 7 -- r --> 8; 9 -- r --> 10; 10 -- r --> 11; 11 -- r --> 12;
```

# test_labeled_idx_graph

```mermaid
graph TD; 1:Mazda_787B; 1:Mazda_787B -- r --> 3:Jaguar_XJR-12; 3:Jaguar_XJR-12 -- l --> 2:Jaguar_XJR-12; 3:Jaguar_XJR-12 -- r --> 4:Jaguar_XJR-12; 4:Jaguar_XJR-12 -- r --> 5:Mercedes-Benz_C11; 5:Mercedes-Benz_C11 -- r --> 6:Mazda_787B; 6:Mazda_787B -- r --> 7:Porsche_962C; 7:Porsche_962C -- r --> 8:Mazda_787; 8:Mazda_787 -- r --> 9:Porsche_962CK6;
```