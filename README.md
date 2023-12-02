# NumPSLA
An experimental research tool for pseudoline arrangements and order types

# The main enumeration program
`NumPSLA.w` is written in CWEB (the CWEB system of structured documentation of Donald E. Knuth and Silvio Levy,
http://tug.ctan.org/info/knuth/cwebman.pdf).
It contains simultaneously the program (in C) and the documentation (in LaTeX). The command
```
ctangle NumPSLA.w
```
generates the C-program `NumPSLA.c`. The command
```
cweave NumPSLA.w
```
generates the LaTeX-file `NumPSLA.tex`.
For convenience, the pdf-Version of this file is available as `NumPSLA-pdf.pdf`. `NumPSLA.w` needs another CWEB file, `readDataBase.w`, for inclusion.

The program is called with the parameters
```
./NumPSLA n [-exclude excludefile] [splitlevel parts part] [fileprefix]
```
The pseudoline arrangments will be enumerated up to n pseudolines.
This corresponds to AOTs with up to n+1 points.
If a `fileprefix` is given, statistics about the enumerated AOTs are
written to the text file fileprefix-*n*.txt, where *n* is the given parameter.
A python script like "  .py" can be used to analyze this output and
aggregate into interesting tables.

The excludefile can be used to enumerate only _realizable_ AOTs with up to
11 points. For this purpose the three files
`exclude11.txt`, `exclude10.txt` (for up to 10 points), and `exclude09.txt` (for 9 points) are provided.
`exclude11.txt` is provided in gzipped-format because its uncompressed size is 184.6 MBytes.

The parameters "`splitlevel parts part`" are used separating the enumeration task
into independent tasks for parallel. If the _splitlevel_ is 8, then all
PSLAs with 8 lines are visited, and we can imagine them as nodes on level 8 of
the tree, which are numbered consecutively.
Then the program will expand only those nodes whose number if congruent to _part_ modulo _parts_.

For example, starting the program with `NumPSLA 11 8 100 0 out`, `NumPSLA 11 8 100 1 out`, ..., `NumPSLA 11 8 100 99 out`, 
will lead to 100 independent runs that collectively go to all nodes at level 11.
The outputs in the files starting with `out` can then be aggregated into a single file
with the python program `aggregate-reportfiles.py`.

# Utility programs in Python

+ `NumPSLA-basic.py`
  
  This is

+ `wiring_diagram.py`

  a function to draw a wiring diagram of a PSLA that is stored in the `SUCC` array.
  By default, it draws an ASCII-art representation. With the option `ipe=True`,
  it will generate an IPE-file. For this, the module `ipestart.py` is required.

+ `NumPSLA-show.py`

  produce the wiring diagram of either a single PSLA, based on the Dewey decimal code,
  or of several PSLAs read from a file, optionally as an IPE file.

# Determining the crossing number and counting halving lines
`crossing-number-plus-halving-lines.ch` is a change-file for the CWEB system. It modifies the program
to count the halving-lines of each AOT.
```
ctangle NumPSLA.w crossing-number-plus-halving-lines.ch -o count-crossing.c
cweave NumPSLA.w crossing-number-plus-halving-lines.ch -o NumPSLA-crossing.tex
```
For convenience, the pdf-Version of this file is available as `NumPSLA-crossing.pdf`.
The results for up to 12 points are in the file `crossing+halving-results-12.txt`.
For each combination of the 6 parameters
n, hull, period, mirror-type, halving-lines, crossing-number,
with n<=12, for which a PSLA with those characteristics exists,
there is a line in the file which gives the number of PSLAs with those characteristics.
The script
```
python3 makereport.py crossing+halving-results-12.txt
```
will read these data and produce some tables of data

# Benchmark
As a benchmark, we read point sets from the order-type database and compute their convex hull.
This is done by compiling the program with the change-file `benchmark.ch`:
```
ctangle NumPSLA.w benchmark.ch
```

# Workflow for generating exclude-files for non-realizable AOTs of 9, 10, and 11 points

0. Obtain the order-type database files. Up to 10 points, they can be downloaded from
   http://www.ist.tugraz.at/aichholzer/research/rp/triangulations/ordertypes/.
   The database for 11 points can be obtained from Oswin Aichholzer directly.
   It consists of 94 files with a total of 102,718,567,908 bytes (102.7 GBytes),
   44 bytes per order type.
   We assume that the order types with up to 10 points are stored in the
   current directory in with the original file names
   `otypes10.b16`, `otypes09.b16`, `otypes08.b08`, etc.,
   and the order types with 11 points are stored 
   in a subdirectory `Ordertypes` with names
   `Ordertypes/ord11_00.b16` ... `Ordertypes/ord11_93.b16`.
2. Compile the program with the switch `generatelist=1` (and `readdatabase=0`)
3. Run the resulting program as follows (assuming it is called "`generate`")
   ```
   ./generate 8 > A9
   ```
   This will write a list of all 9-point AOTs. (The parameter 8 is correct!)

4. Compile the program with the switch `readdatabase=1`
5. Run the resulting program as follows
   ```
   ./readDB 8 > DB9
   ```
   This will write the list of all 9-point OTs. (This file may be useful as a
   crossreference from the fingerprint codes into the database, which
   contains the coordinates of a realizing point set.)

4. Sort both files, using the `sort` command.
   ```
   LANG=C sort A9 -o A9-sorted 
   LANG=C sort DB9 -o DB9-sorted 
   ```
   The `LANG=C` prefix is important; otherwise lowercase and uppercase letters may be folded together in the sort.
6. Use the python script `prepare-non-realizable.py` to process the two sorted files:
   ```
   python3 prepare-non-realizable.py A9-sorted DB9-sorted non-r9.txt
   ```
   The resulting file contains the Dewey decimal notations of the non-realizable AOTs.

7. Sort `non-r9.txt` lexicographically, taking care to sort the indidivual entries numerically:
   ```
   sort -t . -n -k1,1 -k2,2 -k3,3 -k4,4 -k5,5 -k6,6 -k7,7 -k8,8 -k9,9 -k10,10 non-r9.txt -o exclude9-raw.txt
   ```
8. Repeat the above steps for 10 and 11 points. Beware, the file `A11` has 85.3 GBytes. For sorting, the computer
   needs to have enough disk space for temporary files.
9. Finally, merge the these files into the final exclude-files:
   ```
   cp exclude9-raw.txt  exclude09.txt
   python3 merge-non-realizable.py exclude09.txt exclude10-raw.txt exclude10.txt
   python3 merge-non-realizable.py exclude10.txt exclude11-raw.txt exclude11.txt
   ```
   This merges the files and removes 10-point AOTs whose code hat a prefix appearing
   in `exclude09.txt` etc.

The file `exclude11.txt` can be used for excluding the nonrealizable AOTs for up to 11 points.
For excluding the nonrealizable AOTs for up to 10 points, the file `exclude10.txt` is sufficient.
