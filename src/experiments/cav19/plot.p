set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

#set logscale y 10


set output "multi.png"
set title "Multiprocess Scheduling"
plot "< sort -n log/multi_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n log/multi_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 2,\
"< sort -n log/multi_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n log/multi_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

set key left
set output "mono.png"
set title "Monoprocess Scheduling"
plot "< sort -n log/mono_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n log/mono_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 2,\
"< sort -n log/mono_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n log/mono_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

set output "wave.png"
set title "Asynchronous Computation"
plot "< sort -n log/wave_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n log/wave_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints lt 2,\
"< sort -n log/wave_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n log/wave_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

quit
