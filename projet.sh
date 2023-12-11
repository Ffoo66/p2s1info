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
	if [ ${!i} == '-h' ]
	then
		echo "Voici l'aide qui est nécessaire et totalement utile"
		exit 3
	fi
done

tmparg=0

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

if [ $tmparg -le 0 ]
then
	echo "No valid argument, try -h or --help to get help"
	exit 4
fi

cd $1

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
		exit 5
	fi
fi

echo "Is this real ?"

if [ $tmpimage -le 0 ]
then
	mkdir images
fi

cd data

for k in `ls`
do
	if [ $k == "data.csv" ]
	then
		rm data.csv
	fi
done

for k in `ls`
do
	cat $k >> data.csv
done
