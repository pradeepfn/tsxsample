#!/bin/bash
cd vacation;make clean;make;cd ..
#./bin/vacation -t1 -n4 -q60 -u90 -r1048576 -T4194304
perf stat -o log1 -T ./bin/vacation -t1 -n4 -q60 -u90 -r1048576 -T4194304
perf stat -o log2 -e tx_exec.misc1,tx_exec.misc2,tx_mem.abort_capacity,tx_mem.abort_conflict ./bin/vacation -t1 -n4 -q60 -u90 -r1048576 -T4194304
