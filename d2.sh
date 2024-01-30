LC_NUMERIC="C" awk -F';' '{sum[$6] += sprintf("%f", $5) } END { for (driver in sum) printf "%s %.3f\n",driver, sum[driver] }' data.csv | sort -k3,3nr | head -n 10 >results.data
# to create a horizontale histogram turn the image by 90 degrees
gnuplot <<-EOFMarker
	reset
	# Using stats to obtain statistics on data
	data="results.data"
	stats data using 3 nooutput
	set terminal png size 800,1200
	set output "graph.png"
	set label "Option-d2: Distance=f(Driver)" at screen 0.02, 0.5 rotate by 90 center font ",16" tc rgb "black"
	set xlabel "DRIVERS NAMES" rotate by 180  offset 0,1 center
	set ylabel "DISTANCE(Km)" offset 3,0.5 center
	set style data histogram
	set style fill solid
	set boxwidth 0.6 relative
	set key off
	set style histogram clustered gap 1

	# adjustement of x and y due to rotation
	set xtics autojustify rotate by 90 
	set ytics autojustify rotate by 90

	# * means the range will be automatically determined.
	set xrange [ * : * ] noreverse writeback
	set x2range [ * : * ] noreverse writeback
	set yrange [ 0 : * ] noreverse writeback
	set y2range [ * : * ] noreverse writeback
	set zrange [ * : * ] noreverse writeback
	set cbrange [ * : * ] noreverse writeback
	set rrange [ * : * ] noreverse writeback
	
	# Font size
	set xlabel font ",10"
	set ylabel font ",10"
	set xtics font ",10"  
	set ytics font ",10"
	
	# Calculating offset as 1/6 of biggest y 
	maxy=STATS_max  
	offset_value = maxy / 6.0
	
	# Applying offset to x-axis
	set offsets 0, 0, 0, offset_value
	set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front noinvert bdefault
	plot 'results.data' using  3:xticlabels(stringcolumn(1). ' '. stringcolumn(2)) with boxes linecolor rgb "green"  
EOFMarker
# convert is used to create new images while mogrify modifies the existing file
mogrify -rotate 90 "graph.png"

