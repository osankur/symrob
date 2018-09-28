TIMEOUT=600
limit:
	ulimit -Sv 4000000
symrob_mono_1:
	./launch_test.py  -b 0 -p 0 -f 1 --timeout $(TIMEOUT) > smo1.result 2> smo1.log
symrob_mono_10:
	./launch_test.py  -b 0 -p 0 -f 10 --timeout $(TIMEOUT) > smo10.result 2> smo10.log
symrob_mono_100:
	./launch_test.py  -b 0 -p 0 -f 100 --timeout $(TIMEOUT) > smo100.result 2> smo100.log

uppaal_mono_1:
	./launch_test.py  -b 0 -p 1 -f 1 --timeout $(TIMEOUT) > umo1.result 2> umo1.log
uppaal_mono_10:
	./launch_test.py  -b 0 -p 1 -f 10 --timeout $(TIMEOUT) > umo10.result 2> umo10.log
uppaal_mono_100:
	./launch_test.py  -b 0 -p 1 -f 100 --timeout $(TIMEOUT) > umo100.result 2> umo100.log

symrob_multi_1:
	./launch_test.py  -b 0 -p 0 -f 1 --timeout $(TIMEOUT) > smu1.result 2> smu1.log
symrob_multi_10:
	./launch_test.py  -b 0 -p 0 -f 10 --timeout $(TIMEOUT) > smu10.result 2> smu10.log
symrob_multi_100:
	./launch_test.py  -b 0 -p 0 -f 100 --timeout $(TIMEOUT) > smu100.result 2> smu100.log

uppaal_multi_1:
	./launch_test.py  -b 0 -p 1 -f 1 --timeout $(TIMEOUT) > umu1.result 2> umu1.log
uppaal_multi_10:
	./launch_test.py  -b 0 -p 1 -f 10 --timeout $(TIMEOUT) > umu10.result 2> umu10.log
uppaal_multi_100:
	./launch_test.py  -b 0 -p 1 -f 100 --timeout $(TIMEOUT) > umu100.result 2> umu100.log
all1: limit symrob_mono_1 uppaal_mono_1 symrob_multi_1 uppaal_multi_1
all10: limit symrob_mono_10 uppaal_mono_10 symrob_multi_10 uppaal_multi_10
all100: limit symrob_mono_100 uppaal_mono_100 symrob_multi_10 uppaal_multi_10
