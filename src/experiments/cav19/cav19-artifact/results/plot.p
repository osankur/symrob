set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

set output "multi.png"
set title "Multiprocess Scheduling"
plot "< sort -n multi_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n multi_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 2,\
"< sort -n multi_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n multi_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

set key left
set output "mono.png"
set title "Monoprocess Scheduling"
plot "< sort -n mono_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n mono_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 2,\
"< sort -n mono_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n mono_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

set output "wave.png"
set title "Asynchronous Computation"
plot "< sort -n wave_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n wave_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints lt 2,\
"< sort -n wave_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 3,\
"< sort -n wave_pat -k2 -t ';'" using ($2) title 'PAT' with linespoints lt 4

quit
