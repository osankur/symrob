set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

set key left
#set logscale y 10


set output "multi.png"
set title "Multiprocess Scheduling"
plot "< sort -n tests/smu1 -k2 -t ';'" using ($2) title 'Symrob' with linespoints ls 1,\
"< sort -n tests/umu1 -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 2

set output "mono.png"
set title "Monoprocess Scheduling"
plot "< sort -n tests/smo1 -k2 -t ';'" using ($2) title 'Symrob' with linespoints ls 1,\
"< sort -n tests/umo1 -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 2

set output "wave.png"
set title "Wave"
plot "< sort -n tests/ws -k2 -t ';'" using ($2) title 'Symrob' with linespoints ls 1,\
"< sort -n tests/wu -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 2

set output "wave_sat.png"
set title "Wave Sat"
plot "< sort -n tests/ws_b -k2 -t ';'" using ($2) title 'SymrobWave' with linespoints ls 1,\
"< sort -n tests/wu_b -k2 -t ';'" using ($2) title 'UppaalWave' with linespoints lt 2

set output "wave_unsat.png"
set title "Wave Unsat"
plot "< sort -n tests/ws_a -k2 -t ';'" using ($2) title 'Symrob' with linespoints ls 1,\
"< sort -n tests/wu_a -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 2
quit
