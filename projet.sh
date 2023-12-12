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
		- The -c or --create argument merges the files in the data directory to create the data.csv file. You must use this argument at least once before using the other arguments. It doesn't cancel the other arguments.
		- The -d1 argument shows the d1 option.
		- The -d2 argument shows the d2 option.
		- The -l argument shows the l option.
		- The -t argument shows the t option.
		- The -s argument shows the s option."
		exit 3
	fi
done

tmparg=0
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
			cat data/$j >> data/data.csv
		done
		tmparg=1
	fi
done

tmpdata=0

for arg in `seq 2 $#`
do
	case ${!arg} in
		-d1) echo "Option d1 (TBA)"
		tmparg=1 ;;
		
		-d2) echo "Option d2 (TBA)"
		tmparg=1 ;;
		
		-l) echo "Option l (TBA)"
		tmparg=1 ;;
		
		-t) echo "Option t (TBA)"
		tmparg=1 ;;
		
		-s) echo "Option s (TBA)"
		tmparg=1 ;;
	esac
done

for i in `ls data`
do
	if [ $i == "data.csv" ]
	then
		tmpdata=1
	fi
done


if [ $tmparg -le 0 ]
then
	echo "No valid argument, try -h or --help to get help"
	exit 4
fi

if [ $tmpdata -le 0 ]
then
	echo "data.csv wasn't created yet, please add a -c argument to create data.csv"
	exit 5
fi

tmpc=0
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

echo $tmpc $tmpimage

if [ $tmpc -le 0 ]
then
	gcc -o progc/c.exe progc/c.c 2> temp/tempgccerr.txt > temp/tempgcc.txt
	if [  ]
	then
		echo "Gcc error"
		exit 6
	fi
fi

echo "Is this real ?"

if [ $tmpimage -le 0 ]
then
	mkdir images
fi
