#!/bin/bash

SCRIPTPATH=$( dirname ${BASH_SOURCE[0]} )
cd ${SCRIPTPATH}
cd ../tests
qmake
make 
./sca_tests
