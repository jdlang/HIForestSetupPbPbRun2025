#!/bin/bash

FILELIST=${1}
OUTPUT=${2}
MAXCORES=10

rm ExecOnForest
g++ CheckHLTRates.cpp -o ExecOnForest `root-config --cflags --glibs`

rm -r $OUTPUT/*.root  > /dev/null
mkdir -p $OUTPUT

wait_for_slot() {
    while (( $(jobs -r | wc -l) >= MAXCORES )); do
        # Wait a bit before checking again
        sleep 1
    done
}

COUNTER=0
while read -r FILE; do
    echo "Processing $(basename $FILE)..."
    ./ExecOnForest "$FILE" "$OUTPUT/output_${COUNTER}.root" &
    ((COUNTER++))
    wait_for_slot
done < $FILELIST
wait
echo "Finished processing! Merging files..."

rm $OUTPUT.root > /dev/null
hadd $OUTPUT.root $OUTPUT/output*.root
wait
echo "Merge done: $OUTPUT.root"
