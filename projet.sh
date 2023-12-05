#!bin/bash

if [ $# -lt 2 ]
then
	echo "You're dumb (not enough arguments)"
	exit 1
fi

if [ ! -d  $1 ]
then
	echo "You're dumb (first arg has to be a directory)"
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

for arg in `seq 2 $#`
do
	case ${!arg} in
		-d1) echo "Option d1 (TBA)";;
		
		-d2) echo "Option d2 (TBA)";;
		
		-l) echo "Option l (TBA)";;
		
		-t) echo "Option t (TBA)";;
		
		-s) echo "Option s (TBA)";;
		
		*) 
		echo "Failure (TBA)";;
	esac
done

tmpc=0
tmpimage=0

for j in `ls $1`
do
	echo $j
	if [ $j == c.exe ]
	then
		tmpc=$((tmpc + 1))
	fi
	if [ $j == temp ]
	then
		rm -r temp
	fi
	if [ $j == images ]
	then
		tmpimage=$((tmpimage + 1))
	fi
done

mkdir temp

echo $tmpc $tmpimage

if [ $tmpc -le 0 ]
then
	gcc -o c.exe c.c 2> temp/tempgccerr.txt > temp/tempgcc.txt
fi

if [ $tmpimage -le 0 ]
then
	mkdir images
fi

