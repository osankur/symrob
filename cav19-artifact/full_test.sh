#!/bin/bash
#
# Script to launch tests with given tool and benchmark
#
# Usage:
# ./full_test.sh benchmark toolname 
#
# where benchmark in {monoprocess, multiprocess, async, csma}
# and   toolname  in {symrob, tchecker, uppaal, pat}
#
# The output will be written to the output directory
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
TIME_LIMIT=1800
# Memory limit in kB:
MEMORY_LIMIT=8000000

# The directory where the benchmarks are located:
BM_DIR="."

CALL_MC="symrob --silent -c "
TIMESTAMP=`date +%d_%m_%R%s`
#RES_DIR="${DIR}tests/results_${TIMESTAMP}/"
#mkdir -p "${DIR}tests/"
#mkdir -p ${RES_DIR}

benchmark=$1
mc=$2
spec="mono.q"
tchecker_label="err"
if [ "$benchmark" == "multiprocess" ]; then
    spec="$1/multi.q"
elif [ "$benchmark" == "monoprocess" ]; then
    spec="$1/mono.q"
elif [ "$benchmark" == "wave" ]; then
		spec="$1/wave.q"
elif [ "$benchmark" == "csma" ]; then
	  spec="$1/csma.q"
	  tchecker_label="error,transm"
else
    echo "Unknown benchmark"
    exit 1
fi
if [ $mc == "symrob" ]; then
    CALL_MC="symrob --silent -c"
elif [ $mc == "symrob-ic3" ]; then
    CALL_MC="./symb-ic3 --silent -s --sym-alg-ic3"
elif [ $mc == "uppaal" ]; then
    CALL_MC="verifyta"
elif [ $mc == "pat" ]; then
	CALL_MC="wine $PAT_DIR/PAT3.Console.exe -ta -engine 7"
elif [ $mc == "tchecker" ]; then
	echo "TChecker"
else
    echo "Unknown model checker"
    exit 1
fi


ulimit -m ${MEMORY_LIMIT} -v ${MEMORY_LIMIT} -t ${TIME_LIMIT}
RES_TXT_FILE="${DIR}output/${benchmark}_${mc}.txt"
RES_CSV_FILE="${DIR}output/${benchmark}_${mc}.csv"
echo "" > ${RES_TXT_FILE}
echo "" > ${RES_CSV_FILE}
DIR="$BM_DIR/$1/"
GNU_TIME="time"

for filename in $DIR*.xml; do
	if [ $mc == "uppaal" ] || [ $mc == "symrob" ] || [ $mc == "symrob-ic3" ]; then
     echo "Checking file ${filename}..."
     echo "-BEGIN-" 1>> $RES_TXT_FILE
     echo "=====================  $filename =====================" 1>> $RES_TXT_FILE
	   echo "${GNU_TIME} --output=${RES_TXT_FILE} -a -f \"Time: %e sec (Real time) / %U sec (User CPU time)\" ${CALL_MC} $filename $spec >> ${RES_TXT_FILE}"
	   ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ${CALL_MC} $filename $spec >> ${RES_TXT_FILE}
     exit_code=$?
     if [ $exit_code != 0 ]; then
        echo "timeout or error" >> $RES_TXT_FILE
     fi
	fi
	python parse_log.py -p $mc ${RES_TXT_FILE} > ${RES_CSV_FILE}
done

if [ $mc == "pat" ]; then
	for filename in $DIR*.ta; do
       echo "Checking file ${filename}..."
       echo "-BEGIN-" 1>> $RES_TXT_FILE
       echo "=====================  $filename =====================" 1>> $RES_TXT_FILE
		 	 [ -d foo ] || mkdir foo
			 [ -d /tmp/`dirname $filename` ] || mkdir /tmp/`dirname $filename`
	     ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ${CALL_MC} $filename /tmp/$filename.out >> ${RES_TXT_FILE}
     	 exit_code=$?
       if [ $exit_code != 0 ]; then
         echo "timeout or error" >> $RES_TXT_FILE
       fi
   done
fi

if [ $mc == "tchecker" ]; then
  for filename in $DIR/*; do
	if [ -x $filename ] && [ ! -d $filename ] ; then
      echo "-BEGIN-" 1>> $RES_TXT_FILE
			echo "=====================  $filename =====================" 1>> $RES_TXT_FILE
	    ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ./$filename empty -a Shigh -l "${tchecker_label}" >> ${RES_TXT_FILE}
	    exit_code=$?
	    if [ $exit_code != 0 ]; then
		     echo "timeout or error" >> $RES_TXT_FILE
	    fi
	fi
    done
	python parse_log.py -p $mc ${RES_TXT_FILE} > ${RES_CSV_FILE}
fi
