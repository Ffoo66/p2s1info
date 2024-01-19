#!/usr/local/bin/gnuplot -persist
cd ./L
gnuplot -persist <<-EOFMarker
	set terminal pngcairo  enhanced font "arial,10" fontscale 1.0 size 600, 400 
	set output 'histograms.png' #create or update a png file with the graph 
	#set the graph's type and appearance
 	set boxwidth 0.9 absolute 
	set style fill solid 1.00 border lt -1
	set key off
	set style histogram clustered gap 1 
	unset parametric
	set datafile missing '-'
 	set datafile separator ";"
	set style data histograms
 	#set the grid, ranges, tics and labels 
	set xtics out nomirror rotate by -45  autojustify
 	set xlabel "ID des trajets"
	set ylabel "Distance (km)"
	set mytics
	set ytics autojustify
	set xtics  norangelimit 
 	set grid xtics mxtics ytics mytics 
	set title "Distance par trajet" 
	set xrange [  * : * ] noreverse writeback
	set x2range [ * : * ] noreverse writeback
	set yrange [0:*] noreverse writeback
	set y2range [ * : * ] noreverse writeback
	set zrange [ * : * ] noreverse writeback
	set cbrange [ * : * ] noreverse writeback
	set rrange [ * : * ] noreverse writeback
	set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
	NO_ANIMATION = 1
	plot 'results.dat' using 2:xticlabels(1) #plot the graph
	pause -1 "\n"
	#replot in order to display the graph
 	unset output 
	unset terminal
	replot
EOFMarker
mv ./histograms.png ../images/
cd ../

