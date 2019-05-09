set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

set output "multi.png"
set title "Multiprocess Scheduling"
plot "< sort -n output/multi_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n output/multi_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n output/multi_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

set key left
set output "mono.png"
set title "Monoprocess Scheduling"
plot "< sort -n output/mono_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n output/mono_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n output/mono_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

set output "wave.png"
set title "Asynchronous Computation"
plot "< sort -n output/wave_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n output/wave_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n output/wave_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

quit
