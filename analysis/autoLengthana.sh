#!/bin/sh

for length in $(seq  $1 30 $2); do

    echo "Analysing fast length = ${length} "

    result=$(./G4dataAnalysis ~/g4data/PoGOLite+Cu0.5mmPbSn100um/fastlength/polyDefault/CrabAtm4g/G4dataCrabFast${length}mm.root | grep 'MF')
    #result=$(./G4dataAnalysis ~/g4data/PoGOLite+Cu0.5mmPbSn100um/fastlength/polyDefault/gammas/G4dataGammaBgFast${length}mm.root | grep 'MF')
    #result=$(./G4dataAnalysis ~/g4data/PoGOLite+Cu0.5mmPbSn100um/fastlength/polyDefault/neutrons/G4dataNeutronBgFast${length}mm.root | grep 'MF')
    echo ${length} ${result} >> ${1}to${2}mm.txt

done
exit 0
