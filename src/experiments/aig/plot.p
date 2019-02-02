set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

set key left
#set logscale y 10


set output "multi.png"
set title "Multiprocess Scheduling"
plot "< sort -n tests/multi_symrob100 -k2 -t ';'" using ($2) title 'Symrob' with linespoints ls 1,\
"< sort -n tests/multi_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 2,\
"< sort -n tests/multi_pat100 -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 3

set output "mono.png"
set title "Monoprocess Scheduling"
plot "< sort -n tests/mono_symrob -k2 -t ';'" using ($2) title 'Symrob' with linespoints ls 1,\
"< sort -n tests/mono_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 2,\
"< sort -n tests/mono_pat10 -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 3

set output "wave.png"
set title "Wave"
plot "< sort -n tests/wave_symrob -k2 -t ';'" using ($2) title 'Symrob' with linespoints ls 1,\
"< sort -n tests/wave_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 2,\
"< sort -n tests/wave_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 3


set output "mono-factors.png"
set title "Monoprocess Scheduling"
plot "< sort -n tests/mono_symrob -k2 -t ';'" using ($2) title 'Symrob' with linespoints ls 1,\
"< sort -n tests/mono_pat -k2 -t ';'" using ($2) title 'PAT x1' with linespoints lt 2,\
"< sort -n tests/mono_pat10 -k2 -t ';'" using ($2) title 'PAT x10' with linespoints lt 3

quit
