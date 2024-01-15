#!/bin/bash

#grep ";1;" data01.csv  | cut -d";" -f6 | sort | uniq -c | sort -n -r | head -n10 > results.data

awk -F';' '$2 == 1 { count[$6]++ } END { for (driver in count) print driver, count[driver] }' data.csv | sort -k3,3nr | head -n 10 >results.data
#pour creer un histogramme horizontal on tourne l'histogramme vertical et on inverse les valeurs

gnuplot -e "load 'hst.gnu'"
mogrify -rotate 90 "histogrammehoriz.png"
