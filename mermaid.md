<!--
mermaid.md
Sorgente per i grafi Mermaid per il progetto "btree"
Esame di Programmazione C++ 20/04/20
(c) 2020 - Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
Rilasciato sotto licenza MIT - Released under the MIT license
-->

> ***NOTA***<br>
> E' possibile che alcune parti di questo documento non vengano visualizzate correttamente, in quanto il processore Markdown di Doxygen e di GitHub non implementano l'estensione della sintassi Mermaid. Si prega di consultare il file [Readme](./Readme.md).

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
# test_bst_graph

```mermaid
graph TD; 6 -- l --> 3; 3 -- l --> 2; 3 -- r --> 4; 4 -- r --> 5; 6 -- r --> 9; 9 -- l --> 7; 7 -- r --> 8; 9 -- r --> 10; 10 -- r --> 11; 11 -- r --> 12;
```