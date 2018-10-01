#!/usr/bin/sh
python parse_log.py tests/results_13\:161538392587.txt -p uppaal > tests/umo1
python parse_log.py tests/results_13\:111538392271.txt -p symrob > tests/smo1
gnuplot plot.p
display mono1.png
