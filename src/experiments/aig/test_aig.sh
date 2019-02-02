#!/bin/bash

# This is a benchmark framework that may be useful for evaluating
# synthesis tools developed for SyntComp.
#
# Version: 1.0.1
# Created by Robert Koenighofer, robert.koenighofer@iaik.tugraz.at
# Comments/edits by Swen Jacobs, swen.jacobs@iaik.tugraz.at

# This directory:
DIR=`dirname $0`/

PAT_DIR=~/tools/PAT

# Time limit in seconds:
#TIME_LIMIT=1800
TIME_LIMIT=1800
# Memory limit in kB:
MEMORY_LIMIT=2000000

# Maybe change the following line to point to GNU time:
GNU_TIME="time"

# The directory where the benchmarks are located:
BM_DIR="."

CALL_MC="symrob --silent -c "
TIMESTAMP=`date +%d_%m_%R%s`
#RES_DIR="${DIR}tests/results_${TIMESTAMP}/"
#mkdir -p "${DIR}tests/"
#mkdir -p ${RES_DIR}

benchmark=$1
mc=$2
suffix=$3
spec="mono.q"
if [ "$benchmark" == "multiprocess" ]; then
    spec="multi.q"
elif [ "$benchmark" == "monoprocess" ]; then
    spec="mono.q"
elif [ "$benchmark" == "wave" ]; then
		spec="wave.q"
		suffix=""
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
	echo "TChecker"
else
    echo "Unknown model checker"
    exit 1
fi

RES_TXT_FILE="${DIR}tests/${benchmark}${suffix}_${mc}_${TIMESTAMP}.txt"


ulimit -m ${MEMORY_LIMIT} -v ${MEMORY_LIMIT} -t ${TIME_LIMIT}
DIR="$BM_DIR/$1$suffix/"
#echo $DIR*.xml
#set -x
for filename in $DIR*.xml; do
	if [ $mc == "uppaal" ] || [ $mc == "symrob" ]; then
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
     # END execution of synthesis tool
done

for filename in $DIR*.ta; do
		 if [ $mc == "pat" ]; then
       echo "Checking file ${filename}..."
       echo "-BEGIN-" 1>> $RES_TXT_FILE
       echo "=====================  $filename =====================" 1>> $RES_TXT_FILE
     #------------------------------------------------------------------------------
     # BEGIN execution of synthesis tool
		 	 [ -d foo ] || mkdir foo
			 [ -d /tmp/`dirname $filename` ] || mkdir /tmp/`dirname $filename`
	     ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ${CALL_MC} $filename /tmp/$filename.out >> ${RES_TXT_FILE}
		 fi
     exit_code=$?
     if [ $exit_code != 0 ]; then
        echo "timeout or error" >> $RES_TXT_FILE
     fi
     # END execution of synthesis tool
done

RES_TXT_FILE=/tmp/output
if [ $mc == "tchecker" ]; then
    for filename in $DIR/*; do
        echo $filename
	if [ -x $filename ] && [ ! -d $filename ] ; then
            echo "=====================  $filename =====================" 1>> $RES_TXT_FILE
	    ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ./$filename empty -a -Lhigh -l "err" >> ${RES_TXT_FILE}
	    exit_code=$?
	    if [ $exit_code != 0 ]; then
		echo "timeout or error" >> $RES_TXT_FILE
	    fi
	fi
    done
fi
