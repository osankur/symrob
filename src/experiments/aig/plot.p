set term png size 600, 400 crop
set datafile separator ";"
set pointsize 2

#set logscale y 10

set yrange [0:1800]
set output "multi.png"
set title "Multiprocess Scheduling"
plot "< sort -n cav-tests/multi_symrob100 -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n cav-tests/multi_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 3,\
"< sort -n cav-tests/multi_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 4,\
"< sort -n cav-tests/multi_pat100 -k2 -t ';'" using ($2) title 'PAT-bdd' with linespoints lt 5

set key left
set output "mono.png"
set title "Monoprocess Scheduling"
plot "< sort -n cav-tests/mono_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n cav-tests/mono_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 3,\
"< sort -n cav-tests/mono_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 4,\
"< sort -n cav-tests/mono_pat10 -k2 -t ';'" using ($2) title 'PAT-bdd' with linespoints lt 5

set output "wave.png"
set title "Asynchronous Computation"
plot "< sort -n cav-tests/wave_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n cav-tests/wave_tchecker -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints lt 3,\
"< sort -n cav-tests/wave_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints lt 4,\
"< sort -n cav-tests/wave_pat -k2 -t ';'" using ($2) title 'PAT-bdd' with linespoints lt 5

set output "csma.png"
set title "CSMA/CD"
plot "< sort -n cav-tests/csma_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n cav-tests/csma_enumerative -k2 -t ';'" using ($2) title 'Abs-enumerative' with linespoints ls 3,\
"< sort -n cav-tests/csma_uppaal -k2 -t ';'" using ($2) title 'Uppaal' with linespoints ls 4,\


set output "mono-factors.png"
set title "Monoprocess Scheduling"
plot "< sort -n cav-tests/mono_symrob -k2 -t ';'" using ($2) title 'Abs-symbolic' with linespoints ls 1,\
"< sort -n cav-tests/mono_pat -k2 -t ';'" using ($2) title 'PAT-bdd x1' with linespoints lt 3,\
"< sort -n cav-tests/mono_pat10 -k2 -t ';'" using ($2) title 'PAT-bdd x10' with linespoints lt 4

quit
