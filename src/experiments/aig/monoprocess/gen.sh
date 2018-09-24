python ../make_ta.py ../amba3b5y.aag ../time 4 290 > amba3b5y_4L_290.xml # true
python ../make_pat_ta.py ../amba3b5y.aag ../time 4 290 > amba3b5y_4L_290.ta # true
python ../make_ta.py ../amba3b5y.aag ../time 4 200 > amba3b5y_4L_200.xml # true
python ../make_pat_ta.py ../amba3b5y.aag ../time 4 200 > amba3b5y_4L_200.ta # true
python ../make_ta.py ../amba3b5y.aag ../time 4 300 > amba3b5y_4L_300.xml # false
python ../make_ta.py ../amba3b5y.aag ../time 5 300 > amba3b5y_5L_300.xml # false
python ../make_ta.py ../amba3b5y.aag ../time 5 200 > amba3b5y_5L_200.xml # true
python ../make_ta.py ../amba3b5y.aag ../time 5 290 > amba3b5y_5L_290.xml # true
python ../make_ta.py ../genbuf5f5n.aag ../time 5 300 > genbuf5f5n_5L_300.xml
python ../make_ta.py ../genbuf5f5n.aag ../time 5 200 > genbuf5f5n_5L_200.xml
python ../make_ta.py ../genbuf5f5n.aag ../time 5 290 > genbuf5f5n_5L_290.xml

