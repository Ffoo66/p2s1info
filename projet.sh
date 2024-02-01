#!bin/bash

if [ $# -lt 2 ]
then
	echo "Not enough arguments."
	exit 1
fi

if [ ! $1 == directory ]
then
	echo "First arg has to be the right directory (directory)"
	exit 2
fi

for i in `seq 2 $#`
do
	if [ ${!i} == '-h' ] || [ ${!i} == '--help' ]
	then
		echo "Showing the help.
		You must type the right directory as first argument (directory).
		You must have at least one other valid argument:
		- The -h or --help argument displays this help and cancels the other arguments.
		- The -c or --create argument merges the files in the data directory to create the data.csv file and to make the c executable. You must use this argument at least once before using the other arguments. It doesn't cancel the other arguments. It takes a while (roughly one minute) so you should only use this option once.
		- The -d1 argument shows the d1 option.
		- The -d2 argument shows the d2 option.
		- The -l argument shows the l option.
		- The -t argument shows the t option.
		- The -s argument shows the s option."
		exit 3
	fi
done

tmparg=0
tmpc=0
cd $1

for i in `seq 2 $#`
do
	if [ ${!i} == '-c' ] || [ ${!i} == '--create' ] && [ $tmparg -le 0 ]
	then
		for j in `ls data`
		do
			if [ $j == "data.csv" ]
			then
				rm data/data.csv
			fi
		done
		for j in `ls data`
		do
			if [ $j != "data00.csv" ]
			then
				cat data/$j >> data/data.csv
			fi
		done
		cd progc
		make > ../temp/tempgcc.txt
		if [ ! $? -eq 0 ]
		then
			echo "Gcc error"
			exit 4
		fi
		cd ..
		tmparg=1
		tmpc=1
	fi
done

tmpimage=0

for j in `ls`
do
	if [ $j == progc ]
	then
		for k in `ls progc`
		do
			if [ $k == c.exe ]
			then
				tmpc=1
			fi
		done
	fi
	if [ $j == temp ]
	then
		rm -r temp
	fi
	if [ $j == images ]
	then
		tmpimage=1
	fi
done

mkdir temp

if [ $tmpc -le 0 ]
then
	cd progc
	make > ../temp/tempgcc.txt
	if [ ! $? -eq 0 ]
	then
		echo "Gcc error"
		exit 5
	fi
	cd ..
fi

if [ $tmpimage -le 0 ]
then
	mkdir images
fi

for arg in `seq 2 $#`
do
	case ${!arg} in
		-d1) echo "Executing the d1 option"
		
		awk -F';' '$2 == 1 { count[$6]++ } END { for (driver in count) print driver, count[driver] }' data/data.csv | sort -k3,3nr | head -n 10 > temp/results.data
		# to create an horizontal histogram, we rotate a vertical one
		cd temp
		gnuplot <<-EOFMarker
			reset
			# Using stats to obtain statistics on data
			data="results.data"
			stats data using 3 nooutput
			
			set terminal png size 800,1400
			set output "histogramhorizd1.png"
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
			set xtics norangelimit
			set ytics autojustify rotate by 90
			
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
		EOFMarker
		
		mogrify -rotate 90 "histogramhorizd1.png"
		
		mv histogramhorizd1.png ../images
		
		cd ..
		
		xdg-open images/histogramhorizd1.png
		
		tmparg=1 ;;
		
		-d2) echo "Executing the d2 option"
		
		LC_NUMERIC="C" awk -F';' '{sum[$6] += sprintf("%f", $5) } END { for (driver in sum) printf "%s %.3f\n",driver, sum[driver] }' data/data.csv | sort -k3,3nr | head -n 10 > temp/results.data
		# to create a horizontale histogram turn the image by 90 degrees
		
		cd temp
		
		gnuplot <<-EOFMarker
			reset
			# Using stats to obtain statistics on data
			data="results.data"
			stats data using 3 nooutput
			set terminal png size 800,1200
			set output "graphd2.png"
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
		
		mogrify -rotate 90 "graphd2.png"
		
		mv graphd2.png ../images
		
		cd ..
		
		xdg-open images/graphd2.png
		
		tmparg=1 ;;
		
		-l) echo "Executing the l option"
		
		cut -d';' -f1,5 --output-delimiter=' ' data/data.csv > temp/tempdata1.txt
		cd progc
		make
		cd ..
		tempdir1=`realpath temp/tempdata1.txt`
		./progc/c.exe 1 $tempdir1 | head -10 | sort -n > temp/resultsL.dat
		
		cd temp
		gnuplot -persist <<-EOFMarker
			set terminal pngcairo  enhanced font "arial,10" fontscale 1.0 size 600, 400 
			set output 'histogramsL.png' #create or update a png file with the graph 
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
		 	set xlabel "Route ID"
			set ylabel "Distance(km)"
			set mytics
			set ytics autojustify
			set xtics  norangelimit 
		 	set grid xtics mxtics ytics mytics 
			set title "Distance by route" 
			set xrange [  * : * ] noreverse writeback
			set x2range [ * : * ] noreverse writeback
			set yrange [0:*] noreverse writeback
			set y2range [ * : * ] noreverse writeback
			set zrange [ * : * ] noreverse writeback
			set cbrange [ * : * ] noreverse writeback
			set rrange [ * : * ] noreverse writeback
			set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
			NO_ANIMATION = 1
			plot 'resultsL.dat' using 2:xticlabels(1) #plot the graph
			pause -1 "\n"
			#replot in order to display the graph
		 	unset output 
			unset terminal
			replot
		EOFMarker
		mv ./histogramsL.png ../images/
		cd ../
		
		tmparg=1 ;;
		
		-t) echo "Executing the t option"
		
		cut -d';' -f1-3 --output-delimiter=' ' data/data.csv > temp/tempdata2.txt
		cut -d';' -f1,4 --output-delimiter=' ' data/data.csv > temp/tempdata3.txt
		cd progc
		make
		cd ..
		tempdir2=`realpath temp/tempdata2.txt`
		tempdir3=`realpath temp/tempdata3.txt`
		./progc/c.exe 2 $tempdir2 $tempdir3 | head -10 > temp/tempdata4.txt
		tempdir4=`realpath temp/tempdata4.txt`
		echo "Number of routes;Number of departures" > temp/resultsT.dat
		./progc/c.exe 3 $tempdir4 >> temp/resultsT.dat
		
		cd temp
		gnuplot -persist <<-EOFMarker
			set terminal pngcairo  enhanced font "arial,10" fontscale 1.0 size 600, 400 
			set output 'histogramsclusteredT.png' #create or update a png file with the graph 
		 	#set the graph's type and appearance, as well as the key's
			set boxwidth 0.9 absolute
			set style fill solid 1.00 border lt -1
			set key right  noenhanced autotitle columnheader box 
			set style histogram clustered gap 1 
			unset parametric
			set datafile missing '-'
			set datafile separator ";"
			set style data histograms
			#set the grid, ranges, tics and labels 
			set xtics nomirror rotate by -45  autojustify 
			set xtics  norangelimit 
			set mytics
			set grid xtics mxtics ytics mytics 
			set title "Number of routes and departures by town" 
			set xrange [ * : * ] noreverse writeback
			set x2range [ * : * ] noreverse writeback
			set yrange [ 0 : * ] noreverse writeback
			set y2range [ * : * ] noreverse writeback
			set zrange [ * : * ] noreverse writeback
			set cbrange [ * : * ] noreverse writeback
			set rrange [ * : * ] noreverse writeback
			set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
			NO_ANIMATION = 1
			plot for [COL=1:2] 'resultsT.dat' using COL:xticlabels(3) #plot the graph
			pause -1 "\n"
		 	#replot in order to display the graph
			unset output 
			unset terminal
			replot
		EOFMarker
		mv ./histogramsclusteredT.png ../images/
		cd ../
		
		tmparg=1 ;;
		
		-s) echo "Executing the s option"
		
		cut -d';' -f1,5 --output-delimiter=' ' data/data.csv > temp/tempdata5.txt
		cd progc
		make
		cd ..
		tempdir5=`realpath temp/tempdata5.txt`
		./progc/c.exe 4 $tempdir5 | head -50 > temp/resultsS.dat
		
		cd temp
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
		   	set xtics nomirror rotate by -90
			set ytics  norangelimit autofreq  
		 	set mxtics
			set mytics 
			set title " Minimum, maximum eand average distance by route" 
			set xlabel "Route ID" 
		 	set ylabel "Distance(km)" 
		 	set grid xtics mxtics ytics mytics front
			set xrange [ * : *] noreverse writeback
			set x2range [ * : *] noreverse writeback
			set yrange [ 0.000 : * ] noreverse writeback
			set y2range [ * : * ] noreverse writeback
			set zrange [ * : * ] noreverse writeback
			set cbrange [ * : * ] noreverse writeback
			set rrange [ * : * ] noreverse writeback
			set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
			NO_ANIMATION = 1
			Shadecolor = "#80E0A080" 
			set term png
			set output 'statsS.png' #create or update a png file with the graph 
			plot 'resultsS.dat' using 0:3:4:xticlabels(1) with filledcurve fc rgb Shadecolor \
		 title "Maximum and minimum distance by route",'' using 0:2  smooth mcspline lw 2   title "Average distance by route" #plot the graph
			pause -1 "\n"
			#replot in order to display the graph
		 	unset output 
			unset terminal
			replot
		EOFMarker
		mv ./statsS.png ../images/
		cd ../
		
		tmparg=1 ;;
		
	esac
done

if [ $tmparg -le 0 ]
then
	echo "No valid argument, try -h or --help to get help"
	exit 6
fi

tmpdata=0

for i in `ls data`
do
	if [ $i == "data.csv" ]
	then
		tmpdata=1
	fi
done

if [ $tmpdata -le 0 ]
then
	echo "data.csv wasn't created yet, please add a -c argument to create data.csv"
	exit 7
fi



cd temp
rm *.dat
rm *.txt
