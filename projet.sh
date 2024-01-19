#!bin/bash

if [ $# -lt 2 ]
then
	echo "You're dumb (not enough arguments)"
	exit 1
fi

if [ ! $1 == directory ]
then
	echo "You're dumb (first arg has to be the right directory (directory))"
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
		-d1)
		#grep ";1;" data01.csv  | cut -d";" -f6 | sort | uniq -c | sort -n -r | head -n10 > results.data
		
		awk -F';' '$2 == 1 { count[$6]++ } END { for (driver in count) print driver, count[driver] }' data/data.csv | sort -k3,3nr | head -n 10 > temp/results.data
		#pour creer un histogramme horizontal on tourne l'histogramme vertical 
		
		gnuplot -e "load 'hst.gnu'"
		cd ./images
		mogrify -rotate 90 "histogrammehoriz.png"
		
		tmparg=1 ;;
		
		-d2) echo "Option d2 (TBA)"
		
		LC_NUMERIC="C" awk -F';' '{sum[$6] += sprintf("%f", $5) } END { for (driver in sum) printf "%s %.3f\n",driver, sum[driver] }' data.csv | sort -k3,3nr | head -n 10 >results.data
		# to create a horizontale histogram turn the image by 90 degrees
		gnuplot -e "load 'hst2.gnu'"
		# convert is used to create new images while mogrify modifies the existing file
		mogrify -rotate 90 "graph.png"
		
		tmparg=1 ;;
		
		-l) echo "Option l (TBA)"
		cut -d';' -f1,5 --output-delimiter=' ' data/data.csv > temp/tempdata1.txt
		cd progc
		make
		cd ..
		tempdir1=`realpath temp/tempdata1.txt`
		./progc/c.exe 1 $tempdir1 | head -10 | sort -n > temp/resultsL.dat
		bash ../plotL.sh
		
		tmparg=1 ;;
		
		-t) echo "Option t (TBA)"
		cut -d';' -f1-3 --output-delimiter=' ' data/data.csv > temp/tempdata2.txt
		cut -d';' -f1,4 --output-delimiter=' ' data/data.csv > temp/tempdata3.txt
		cd progc
		make
		cd ..
		tempdir2=`realpath temp/tempdata2.txt`
		tempdir3=`realpath temp/tempdata3.txt`
		./progc/c.exe 2 $tempdir2 $tempdir3 | head -10 > temp/tempdata4.txt
		tempdir4=`realpath temp/tempdata4.txt`
		./progc/c.exe 3 $tempdir4 > temp/resultsT.dat
		bash ../plotT.sh
		
		tmparg=1 ;;
		
		-s) echo "Option s (TBA)"
		cut -d';' -f1,5 --output-delimiter=' ' data/data.csv > temp/tempdata5.txt
		cd progc
		make
		cd ..
		tempdir5=`realpath temp/tempdata5.txt`
		./progc/c.exe 4 $tempdir5 | head -50 > temp/resultsS.dat
		bash ../plotS.sh
		
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

echo "Is this real ?"

cd temp
rm *.txt
