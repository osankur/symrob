#!/bin/bash

# This is a benchmark framework that may be useful for evaluating
# synthesis tools developed for SyntComp.
#
# Version: 1.0.1
# Created by Robert Koenighofer, robert.koenighofer@iaik.tugraz.at
# Comments/edits by Swen Jacobs, swen.jacobs@iaik.tugraz.at

# This directory:
DIR=`dirname $0`/

# Time limit in seconds:
TIME_LIMIT=5
# Memory limit in kB:
MEMORY_LIMIT=4000000

# Maybe change the following line to point to GNU time:
GNU_TIME="time"

# The directory where the benchmarks are located:
BM_DIR="."

# The benchmarks to be used.
# The files have to be located in ${BM_DIR}.
FILES=(
load_5c_comp_comp7_REAL   $REAL
)

CALL_MC="symrob --silent -c "
TIMESTAMP=`date +%s`
RES_TXT_FILE="${DIR}tests/results_${TIMESTAMP}.txt"
RES_DIR="${DIR}tests/results_${TIMESTAMP}/"
mkdir -p "${DIR}tests/"
mkdir -p ${RES_DIR}

benchmark=$1
factor=$2
mc=$3
spec="mono.q"
if [ "$benchmark" == "multiprocess" ]; then
    spec="multi.q"
elif [ "$benchmark" == "monoprocess" ]; then
    spec="mono.q"
else
    echo "Unknown parameter"
    exit 1
fi
if [ $mc == "symrob" ]; then
    CALL_MC="symrob --silent -c"
elif [ $mc == "uppaal" ]; then
    CALL_MC="verifytga"
else
    echo "Unknown model checker"
    exit 1
fi



ulimit -m ${MEMORY_LIMIT} -v ${MEMORY_LIMIT} -t ${TIME_LIMIT}
DIR="$BM_DIR/$1$factor/"
#echo $DIR*.xml
#set -x
for filename in $DIR*.xml; do
     echo "Checking file ${filename}..."
     echo "=====================  $filename =====================" 1>> $RES_TXT_FILE
     #------------------------------------------------------------------------------
     # BEGIN execution of synthesis tool
     echo " Running model checker ... "
     echo "${GNU_TIME} --output=${RES_TXT_FILE} -a -f \"Time: %e sec (Real time) / %U sec (User CPU time)\" ${CALL_MC} $filename $spec >> ${RES_TXT_FILE}"
     ${GNU_TIME} --output=${RES_TXT_FILE} -a -f "Time: %e sec (Real time) / %U sec (User CPU time)" ${CALL_MC} $filename $spec >> ${RES_TXT_FILE}
     exit_code=$?
     if [ $exit_code != 0 ]; then
        echo "timeout or error" >> $RES_TXT_FILE
     fi
     echo " Done running the synthesizer. "
     # END execution of synthesis tool
done
