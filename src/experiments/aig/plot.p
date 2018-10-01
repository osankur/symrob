set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

set key left
set logscale y 10
set output "mono1.png"
set title "Monoprocess Scheduling"
plot "< sort -n tests/smo1 -k2 -t ';'" using ($2) title 'Symrob Mono1' with linespoints ls 1,\
"< sort -n tests/umo1 -k2 -t ';'" using ($2) title 'Uppaal Mono1' with linespoints lt 2

quit
