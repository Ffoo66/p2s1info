reset
set terminal png size 800,1400
set output "graph.png"
set xlabel "DRIVERS NAMES" rotate by 180
set ylabel "NB ROUTES"
set style data histogram
set style fill solid
set boxwidth 0.9 relative
set style fill solid 1.00 border lt -1
set key off
set style histogram clustered gap 1
unset parametric
set datafile missing '-'
set style data histograms

# Ajuster la rotation et l'espacement des étiquettes d'axe x
set xtics autojustify rotate by 90 
set mytics
set ytics autojustify rotate by 90
set xtics norangelimit
set xrange [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback

# Ajuster la plage et l'origine de l'axe y
set yrange [ -0.3 : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback
set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback

set xlabel font ",15"
set ylabel font ",20"
set xtics font ",10"  # Ajuster la taille de la police des étiquettes d'axe x
set ytics font ",30"

# Déplacer l'ensemble de l'axe x vers le haut d'une unité de la taille de la police
set offsets 0, 0, 0, 2


set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front noinvert bdefault
NO_ANIMATION = 1

plot 'results.data' using  3:xticlabels(stringcolumn(1). ' '. stringcolumn(2)) with boxes linecolor rgb "green" title "Nombre total de trajets"
