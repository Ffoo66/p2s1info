This program compiles data from a voluminous csv file on the statistics of drivers and routes and produces more legible graphs presenting some of these statistics according to the selected options.

The following instructions need to be respected in order for the program to function correctly.

Make sure the path to the directory (directory included) in which you put the files does not contain spaces or special characters (for example *), otherwise some of the options will not work.

Make sure the files you want to process are in .csv and that they have a header line which does not contain any data. You have to put those files in the same directory as project.sh and 'directory'. The separator between each column has to be ';'. The columns have to be in this order: route ID;step ID;departure town;arrival town;distance.
The towns' names mustn't be above 38 characters.

To launch the program use "bash project.sh directory" followed by the desired options.

Amongst the available options are -c (or --create) to create a data.csv file in the right directory, to compile the C file and create the executable. One should use -c on the first execution to ensure the data file and the executable exist.

Other options are -h or --help to display help. If selected it will cancel other arguments. 

The -d1 option creates a horizontal histogram displaying the number of routes by driver for the 10 drivers having done the most routes.

The -d2 option creates a horizontal histogram displaying the total distance by driver for the 10 drivers having the highest total distances.

The -l option creates a vertical histogram displaying the distance by route ID for the 10 longest routes.

The -t option creates a vertical clustered histogram displaying the number of routes passing through and the number of routes starting from towns for the 10 towns with the most passages.

The -s option creates a graph displaying the minimum, maximum, and average distances of steps by route for the 50 first routes ordered decreasingly according to the "max - min" value.

The graphs created by the execution can be found in the images directory (found at ./directory/images in the program's main directory). 
A graph in the images directory will be replaced by a new version upon a new call of the corresponding option.

The demo directory contains examples of the program's results (both graphs and the corresponding compiled data).
