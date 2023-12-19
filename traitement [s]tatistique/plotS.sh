#!/usr/local/bin/gnuplot -persist

gnuplot -persist <<-EOFMarker
	set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 600, 400 
	unset errorbars
	set key right box   
	set grid layerdefault
	unset parametric
	set style data lines   
	set mxtics default
	set ytics  norangelimit autofreq  
	set mytics default
	set title "Statistiques sur les étapes : distances minimales, maximales et moyennes par trajet" 
	set xlabel "Identifiant de trajet" 
	set xrange [ * : *] noreverse writeback
	set x2range [ * : *] noreverse writeback
	set ylabel "Distance (km)" 
	set yrange [ 0.000 : 100.0 ] noreverse writeback
	set y2range [ * : * ] noreverse writeback
	set zrange [ * : * ] noreverse writeback
	set cbrange [ * : * ] noreverse writeback
	set rrange [ * : * ] noreverse writeback
	set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
	NO_ANIMATION = 1
	Shadecolor = "#80E0A080" 
	set term png
	set output 'statistiques.png'
	plot 'results.dat' using 1:3:4:xticlabels(1) with filledcurve fc rgb Shadecolor title "Intervalle des distances par trajet",'' using 1:2  smooth mcspline lw 2   title "Moyenne des distances par trajet"
	pause -1 "\n"
EOFMarker
