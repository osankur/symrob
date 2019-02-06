set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

#set logscale y 10


set output "multi.png"
set title "Multiprocess Scheduling"
plot "< sort -n tests/cav/multi_symrob100 -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n tests/cav/multi_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 2,\
"< sort -n tests/cav/multi_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n tests/cav/multi_pat100 -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

set key left
set output "mono.png"
set title "Monoprocess Scheduling"
plot "< sort -n tests/cav/mono_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n tests/cav/mono_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 2,\
"< sort -n tests/cav/mono_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n tests/cav/mono_pat10 -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

set output "wave.png"
set title "Asynchronous Computation"
plot "< sort -n tests/cav/wave_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n tests/cav/wave_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints lt 2,\
"< sort -n tests/cav/wave_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n tests/cav/wave_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4


set output "mono-factors.png"
set title "Monoprocess Scheduling"
plot "< sort -n tests/cav/mono_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n tests/cav/mono_pat -k2 -t ';'" using ($2) title 'PAT x1' with linespoints lt 2,\
"< sort -n tests/cav/mono_pat10 -k2 -t ';'" using ($2) title 'PAT x10' with linespoints lt 3

quit
