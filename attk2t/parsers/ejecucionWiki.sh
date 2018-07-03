#!/bin/bash


echo 'Ordenando  las aristas por tipo'
#cat $1/rdbms_refs_title.csv | grep BABEL > $1/rdbms_refs_title_babel.csv
#cat $1/rdbms_refs_title.csv | grep -v BABEL > $1/rdbms_refs_title_ref.csv
#cat $1/rdbms_refs_title_ref.csv $1/rdbms_refs_title_babel.csv > $1/rdbms_refs_title_ord.csv

echo 'Creando archivos de entrada estandar para attk2t ...'

bin/parser_wiki $1/rdbms_titles.csv $1/rdbms_images.csv $1/rdbms_refs_image.csv $1/rdbms_refs_title_ord.csv graph

echo 'Construyendo grafo en formato attk2t ...'

echo 'Consultando grafo en formato attk2t...'



