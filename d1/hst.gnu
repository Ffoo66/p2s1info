reset
# Using stats to obtain statistics on data
data="results.data"
stats data using 3 nooutput

set terminal png size 800,1400
set output "graph.png"
set label "Option-d1: Nb routes=f(Driver)" at screen 0.02, 0.5 rotate by 90 center font ",16" tc rgb "black"
set xlabel "DRIVERS NAMES" rotate by 180
set ylabel "NB ROUTES"
set style data histogram
set style fill solid
set boxwidth 0.9 relative
set key off
set style histogram clustered gap 1


# adjustement of x and y due to rotation
set xtics autojustify rotate by 90 
set mytics
set ytics autojustify rotate by 90
set xtics norangelimit
set xrange [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback

# * means the range will be automatically determined.
set yrange [ 0 : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback
set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback

# Font size
set xlabel font ",10"
set ylabel font ",10"
set xtics font ",10"  # Ajuster la taille de la police des étiquettes d'axe x
set ytics font ",10"

# Calculating offset as 1/6 of biggest y 
maxy=STATS_max  
offset_value = maxy / 6.0

# Applying offset to x-axis
set offsets 0, 0, 0, offset_value


set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front noinvert bdefault


plot 'results.data' using  3:xticlabels(stringcolumn(1). ' '. stringcolumn(2)) with boxes linecolor rgb "green"
