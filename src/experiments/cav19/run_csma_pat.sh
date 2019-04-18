TIME_LIMIT=1800
MEMORY_LIMIT=8000000
ulimit -m ${MEMORY_LIMIT} -v ${MEMORY_LIMIT} -t ${TIME_LIMIT}
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma3.ta output
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma4.ta output
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma5.ta output
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma6.ta output
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma7.ta output
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma8.ta output
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma9.ta output
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma10.ta output
time wine /home/osankur/tools/PAT/PAT3.Console.exe -ta -engine 7 ./csma/csma11.ta output

