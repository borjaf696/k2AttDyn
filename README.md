# k2AttDyn

Repository with:
- Attk2Tree: static compressed graph representation for regular graphs
- k2AttDynTree: dynamic compressed graph representation for regular graphs

## Attk2Tree:
Static compressed graph representation for regular graph (parallel edges, label edges/nodes, different types of edges/nodes)
### Usage:
#### Building phase:</br>
cd attk2t/buildattk2t</br>
make</br>
./bin/buildtree <basename></br>
#### Query phase:
cd attk2t/queryattk2t</br>
make</br>
##### QueryGen:    
./bin/query_gen \<basename\> \<queriesdir\> \<numqueries\></br>
##### QueryTest:  
./bin/query \<basename\> \<queriesdir\> \<numqueries\></br>
## Attk2DynTree
Dynamic compressed graph representation for regular graph (parallel edges, label edges/nodes, different types of edges/nodes)
### Usage:
Building/Query phase:</br>
cd src</br>
make</br>
./bin/main \<basename\> \<queriesdir\> \<numqueries\></br>

## Input Format
