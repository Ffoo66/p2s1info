#!/usr/local/bin/gnuplot -persist
gnuplot -persist <<-EOFMarker
	set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 600, 400 
	set output 'histograms.png'
	set boxwidth 0.9 absolute
	set style fill solid 1.00 border lt -1
	set key right autotitle columnheader box
	set style histogram clustered gap 1 
	unset parametric
	set datafile missing '-'
	set style data histograms
	set xtics nomirror rotate by -45  autojustify
	set xtics  norangelimit 
	set title "Nombre d'étapes et de de départs par ville" 
	set xrange [ * : * ] noreverse writeback
	set x2range [ * : * ] noreverse writeback
	set yrange [ * : * ] noreverse writeback
	set y2range [ * : * ] noreverse writeback
	set zrange [ * : * ] noreverse writeback
	set cbrange [ * : * ] noreverse writeback
	set rrange [ * : * ] noreverse writeback
	set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
	NO_ANIMATION = 1
	plot for [COL=2:3] 'results.dat' using COL:xticlabels(1)
	pause -1 "\n"
EOFMarker


