LC_NUMERIC="C" awk -F';' '{sum[$6] += sprintf("%f", $5) } END { for (driver in sum) printf "%s %.3f\n",driver, sum[driver] }' data.csv | sort -k3,3nr | head -n 10 >results.data
# to create a horizontale histogram turn the image by 90 degrees
gnuplot -e "load 'hst.gnu'"
# convert is used to create new images while mogrify modifies the existing file
mogrify -rotate 90 "graph.png"


