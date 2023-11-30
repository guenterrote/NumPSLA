# NumPSLA
An experimental research tool for pseudoline arrangements and order types

## Workflow for generating exclude-files for non-realizable AOTs of 9, 10, and 11 points

0. Obtain the order-type database files. Up to 10 points, they can be downloaded from
   http://www.ist.tugraz.at/aichholzer/research/rp/triangulations/ordertypes/.
   The database for 11 points can be obtained from Oswin Aichholzer directly.
   It consists of 94 files with a total of 102,718,567,908 bytes (102.7 GBytes),
   44 bytes per order type.
   We assume that the order types with up to 10 points are stored in the
   current directory in with the original file names
   otypes10.b16, otypes09.b16, otypes08.b08, etc.,
   and the order types with 11 points are stored 
   in a subdirectory Ordertypes with names
   Ordertypes/ord11_00.b16 ... Ordertypes/ord11_93.b16
2. Compile the program with the switch generatelist=1 (and readdatabase=0)
3. Run the resulting program as follows (assuming it is called "generate")
   ```
   ./generate 8 > A9
   ```
   This will write a list of all 9-point AOTs. (The parameter 8 is correct!)

4. Compile the program with the switch readdatabase=1
5. Run the resulting program as follows
   ```
   ./readDB 8 > DB9
   ```
   This will write the list of all 9-point OTs. (This file may be useful as a
   crossreference from the fingerprint codes into the database, which
   contains the coordinates of a realizing point set.)

4. Sort both files, using the sort command.
   ```
   LANG=C sort A9 -o A9-sorted 
   LANG=C sort DB9 -o DB9-sorted 
   ```
   The LANG=C prefix is important; otherwise lowercase and uppercase letters may be folded together in the sort.
6. Use the python prepare-non-realizable.py script to process the two sorted files:
   ```
   python3 prepare-non-realizable.py A9-sorted DB9-sorted non-r9.txt
   ```
   The resulting file contains the Dewey decimal notations of the non-realizable AOTs.

7. Sort non-r9.txt lexicographically, taking care to sort the indidivual entries numerically:
   ```
   sort -t . -n -k1,1 -k2,2 -k3,3 -k4,4 -k5,5 -k6,6 -k7,7 -k8,8 -k9,9 -k10,10 non-r9.txt -o exclude9-raw.txt
   ```
8. Repeat the above steps for 10 and 11 points. Beware, the file A11 has 85.3 GBytes. For sorting, the computer
   needs to have enough disk space for temporary files.
9. Finally, merge the these files into the final exclude-files:
   ```
   cp exclude9-raw.txt  exclude9.txt
   python3 merge-non-realizable.py exclude09.txt exclude10-raw.txt exclude10.txt
   python3 merge-non-realizable.py exclude10.txt exclude11-raw.txt exclude11.txt
   ```
   This merges the files and removes 10-point AOTs whose code hat a prefix appearing
   in exclude09.txt etc.

The file exclude11.txt can be used for excluding the nonrealizable AOTs for up to 11 points.
