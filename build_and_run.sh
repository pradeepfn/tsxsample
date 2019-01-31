#!/bin/bash
cd vacation;make clean;make;cd ..
./bin/vacation -t1 -n4 -q60 -u90 -r1048576 -T4194304
