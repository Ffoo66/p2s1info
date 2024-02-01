Make sure the directory in which you put the files does not contain spaces or special characters (for example *), otherwise some of the options will not work.

To launch the program use "bash projet.sh directory" followed by the desired options.

Amongst the available options are -c to create a data.csv file if one does not already exist. One should use -c on the first execution to ensure the data file exist.

Other options are -h or --help to display help. If selected it will cancel other arguments. 

The -d1 option creates a horizontal histogram displaying the number of routes by driver for the 10 drivers having done the most routes.

The -d2 option creates a horizontal histogram displaying the total distance by driver for the 10 drivers having the greatest totals.

The -l option creates a vertical histogram displaying the distance by route for the 10 longest routes.

The -t option creates a vertical clustered histogram displaying the number of routes passing by and the number of routes starting from towns for the 10 towns with the most passages.

The -s option creates a graph displaying the minimum, maximum, and average distance by route for the 50 first routes ordered decreasingly according to the "max - min" value.

The graphs created by the latest execution can be found in the directory images (found at ./directory/images from the program's main directory). 
A graph in the images directory will be replaced by a new version upon a new call of the corresponding option.

The demo directory countains examples of the program's results (both graphs and the corresponding data).
