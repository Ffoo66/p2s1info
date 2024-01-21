#!/usr/local/bin/gnuplot -persist
cd ./S
gnuplot -persist <<-EOFMarker
	set terminal pngcairo  enhanced font "arial,10" fontscale 1.0 size 600, 400 
	unset errorbars
	#set the graph's type and appearance, as well as the key's
	set key right box   
	unset parametric
	set style data lines   
 	set datafile missing '-'
 	set datafile separator ";"
  	#set the grid, ranges, tics and labels
   	set xtics nomirror rotate by -45  
	set ytics  norangelimit autofreq  
 	set mxtics
	set mytics 
	set title "Statistiques sur les étapes : distances minimales, maximales et moyennes par trajet" 
	set xlabel "Identifiant de trajet" 
 	set ylabel "Distance (km)" 
 	set grid xtics mxtics ytics mytics front
	set xrange [ * : *] noreverse writeback
	set x2range [ * : *] noreverse writeback
	set yrange [ 0.000 : 200.000 ] noreverse writeback
	set y2range [ * : * ] noreverse writeback
	set zrange [ * : * ] noreverse writeback
	set cbrange [ * : * ] noreverse writeback
	set rrange [ * : * ] noreverse writeback
	set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
	NO_ANIMATION = 1
	Shadecolor = "#80E0A080" 
	set term png
	set output 'statistiques.png' #create or update a png file with the graph 
	plot 'resultsS.dat' using 0:3:4:xticlabels(1) with filledcurve fc rgb Shadecolor \
 title "Intervalle des distances par trajet",'' using 0:2  smooth mcspline lw 2   title "Moyenne des distances par trajet" #plot the graph
	pause -1 "\n"
	#replot in order to display the graph
 	unset output 
	unset terminal
	replot
EOFMarker
mv ./statistiques.png ../images/
cd ../
