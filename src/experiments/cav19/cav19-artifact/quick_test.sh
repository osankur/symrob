#!/bin/bash
#
# Script to launch a *quick* test with given tool and benchmark
# The script is similar to full_test.sh but executes a preselected list of benchmarks
# and writes the results to the output directory
#
# Usage:
# ./full_test.sh benchmark toolname 
#
# where benchmark in {monoprocess, multiprocess, async, csma}
# and   toolname  in {symrob, tchecker, uppaal, pat}
#
# Here symrob implements the symbolic algorithm in the paper
#      tchecker implements the enumerative algorithm in the paper
#
# Uppaal and pat are not provided since we cannot distribute them.
# For Uppaal, it suffices to install it and add the directory containing verifyta to the PATH
# For PAT, just set PAT_DIR to the installation directory

DIR=`dirname $0`/

PAT_DIR=~/PAT

# Time limit in seconds:
TIME_LIMIT=180
# Memory limit in kB:
MEMORY_LIMIT=4000000

# The directory where the benchmarks are located:
BM_DIR="."

TIMESTAMP=`date +%d_%m_%R%s`

SYMROB_MONO=(
bs16y.aag_4L_100
bs16y.aag_4L_150
bs16y.aag_4L_200
cnt5y.aag_4L_200
cnt5y.aag_4L_300
amba3b5y.aag_4L_200
amba3b5y.aag_4L_290
amba3b5y.aag_4L_300
amba3b5y.aag_5L_290
amba3b5y.aag_5L_300
amba3b5y.aag_6L_290
amba4c7y.aag_4L_200
amba4c7y.aag_4L_300
amba4c7y.aag_5L_200
genbuf2b3unrealy.aag_6L_300
genbuf5f5n.aag_5L_300
moving_obstacle_8x8_1glitches.aag_4L_150
moving_obstacle_8x8_1glitches.aag_4L_300
moving_obstacle_8x8_1glitches.aag_5L_150
moving_obstacle_8x8_1glitches.aag_6L_150
)

TCHECKER_MONO=(
bs16y.aag_4L_100
bs16y.aag_4L_150
bs16y.aag_4L_200
cnt5y.aag_4L_200
cnt5y.aag_4L_300
genbuf2b3unrealy.aag_6L_300
genbuf5f5n.aag_5L_300
moving_obstacle_8x8_1glitches.aag_4L_150
moving_obstacle_8x8_1glitches.aag_4L_300
moving_obstacle_8x8_1glitches.aag_5L_150
moving_obstacle_8x8_1glitches.aag_6L_150
)

MULTI=(
10
1
20
22
25
31
32
34
4
7
)

WAVE=(
a0_f
a1_f
a2_f
a6_f
a7_f
b0_150_t
b0_50_f
b1_150_f
b1_50_f
)

CSMA=(
csma3
csma4
csma5
		)

benchmark=$1
mc=$2
spec=""
tchecker_label="err"
if [ "$benchmark" == "multiprocess" ]; then
    spec="$1/multi.q"
	  FILES=(${MULTI[@]})
elif [ "$benchmark" == "monoprocess" ]; then
    spec="$1/mono.q"
	  FILES=(${TCHECKER_MONO[@]})
elif [ "$benchmark" == "wave" ]; then
		spec="$1/wave.q"
	  FILES=(${WAVE[@]})
elif [ "$benchmark" == "csma" ]; then
	  spec="$1/csma.q"
	  FILES=(${CSMA[@]})
	  tchecker_label="error,transm"
else
    echo "Unknown benchmark"
    exit 1
fi
if [ $mc == "symrob" ]; then
    CALL_MC="symrob --silent -c"
elif [ $mc == "uppaal" ]; then
    CALL_MC="verifytga"
elif [ $mc == "pat" ]; then
	CALL_MC="wine $PAT_DIR/PAT3.Console.exe -ta -engine 7"
elif [ $mc == "tchecker" ]; then
	echo "tchecker"
else
    echo "Unknown model checker"
    exit 1
fi


if [ $mc == "symrob" ] && [ $benchmark == "monoprocess" ]; then
	FILES=(${SYMROB_MONO[@]})
elif [ $mc == "tchecker" ] && [ $benchmark == "monoprocess" ]; then
	FILES=(${TCHECKER_MONO[@]})
fi

ulimit -m ${MEMORY_LIMIT} -v ${MEMORY_LIMIT} -t ${TIME_LIMIT}
RES_TXT_FILE="${DIR}output/${benchmark}_${mc}.txt"
RES_CSV_FILE="${DIR}output/${benchmark}_${mc}.csv"
echo "" > ${RES_TXT_FILE}
echo "" > ${RES_CSV_FILE}
DIR="$BM_DIR/$1/"
GNU_TIME="time"

for filename in "${FILES[@]}"
do
	echo "Checking file ${filename}..."
	echo "-BEGIN-" 1>> $RES_TXT_FILE
  echo "=====================  $filename =====================" 1>> $RES_TXT_FILE
	if [ $mc == "uppaal" ] || [ $mc == "symrob" ]; then
	   echo "${GNU_TIME} --output=${RES_TXT_FILE} -a -f \"Time: %e sec (Real time) / %U sec (User CPU time)\" ${CALL_MC} $1/$filename.xml $spec >> ${RES_TXT_FILE}"
	   ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ${CALL_MC} $1/$filename.xml $spec >> ${RES_TXT_FILE}
     exit_code=$?
	elif [ $mc == "pat" ]; then
		 	 [ -d foo ] || mkdir foo
			 [ -d /tmp/`dirname $filename` ] || mkdir /tmp/`dirname $filename`
	     ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ${CALL_MC} $1/$filename.ta /tmp/$filename.out >> ${RES_TXT_FILE}
     exit_code=$?
	elif [ -x $1/$filename ] && [ ! -d $1/$filename ] ; then
	    echo "${GNU_TIME} --output=${RES_TXT_FILE} -a -f \"Time: %e sec (Real time) / %U sec (User CPU time)\" ./$1/$filename empty -a Shigh -l \"${tchecker_label}\""
	    ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ./$1/$filename empty -a Shigh -l "${tchecker_label}" >> ${RES_TXT_FILE}
	    exit_code=$?
	    if [ $exit_code != 0 ]; then
		     echo "timeout or error" >> $RES_TXT_FILE
	    fi
  fi
  if [ $exit_code != 0 ]; then
     echo "timeout or error" >> $RES_TXT_FILE
  fi
	python parse_log.py -p $mc ${RES_TXT_FILE} > ${RES_CSV_FILE}
done
