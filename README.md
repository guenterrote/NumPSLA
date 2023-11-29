# NumPSLA
An experimental research tool for pseudoline arrangements and order types

## Workflow for generating exclude-files for non-realizable AOTs of 9, 10, and 11 points

1. Compile the program with the switch generatelist=1 (and readdatabase=0)
2. Run the program as follows
   ```
   ./generate 8 > A9
```
   This will write a list of all 9-point AOTs

3. 1. Compile the program with the switch readdatabase=1 generatelist=1
2. Run the program as follows
   ```
   ./generate 8 > A9
```
   This will write a list of all 9-point AOTs

3. 



compile the program with the switch readdatabase1
#define generatelist 0 \


run the program

order-type database

sort both files

python prepare-non-realizable.py f1 f2 f-diff

creates file f-diff
containing only the Dewey decimal notations

sort f-diff lexicographically (taking care to sort the indidivual
entries numerically)

sort -t . -n -k1,1 -k2,2 -k3,3 -k4,4 -k5,5 -k6,6 -k7,7 -k8,8 -k9,9 -k10,10

merge-non-realizable.py
python3 merge-non-realizable.py exclude09.txt exclude10-raw.txt exclude10.txt
