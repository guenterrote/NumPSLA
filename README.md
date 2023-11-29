# NumPSLA
An experimental research tool for pseudoline arrangements and order types

## Workflow for generating exclude-files for non-realizable AOTs of 9, 10, and 11 points

1. Compile the program with the switch generatelist=1 (and readdatabase=0)
2. Run the resulting program as follows (assuming it is called "generate")
   ```
   ./generate 8 > A9
   ```
   This will write a list of all 9-point AOTs. (The parameter 8 is correct!)

3. Compile the program with the switch readdatabase=1
4. Run the resulting program as follows
   ```
   ./readDB 8 > DB9
   ```
   This will write a list of all 9-point AOTs

4. Sort both files, using the sort command.
5. Use the python prepare-non-realizable.py script to process the two sorted files:
   ```
   python3 prepare-non-realizable.py A9-sorted DB9-sorted non-r9.txt
   ```
   The resulting file contains the Dewey decimal notations of the non-realizable AOTs.

6. Sort non-r9.txt lexicographically, taking care to sort the indidivual entries numerically:
   ```
   sort -t . -n -k1,1 -k2,2 -k3,3 -k4,4 -k5,5 -k6,6 -k7,7 -k8,8 -k9,9 -k10,10 non-r9.txt -o exclude9-raw.txt
   ```
7. Repeat the above steps, for 10 and 11 points. Beware, the file A11 has 85.3 GBytes. The computer
   needs to have enough disk space for temporary files.
8. Finally, merge the these files into the final exclude-files:
   ```
   cp exclude9-raw.txt  exclude9.txt
   python3 merge-non-realizable.py exclude09.txt exclude10-raw.txt exclude10.txt
   python3 merge-non-realizable.py exclude10.txt exclude11-raw.txt exclude11.txt
   ```
   This merges the files and removes 10-point AOTs whose code hat a prefix appearing
   in exclude09.txt etc.

The file exclude11.txt can be used for excluding the nonrealizable AOTs for up to 11 points.
