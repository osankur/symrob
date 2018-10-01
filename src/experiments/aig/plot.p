set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

set key left above

set output "smo1.png"
plot "< sort -n a -k2 -t ';'" using ($2) title 'Symrob Mono1' with lines,\
"< sort -n b -k2 -t ';'" using ($2) title 'Uppaal Mono1' with lines

quit
