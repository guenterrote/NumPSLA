\documentclass[baseclass=article%
%,structure=flat
]{cweb-hy}
\usepackage[a4paper,margin=2cm]{geometry}
\usepackage{hyperref}
\usepackage{graphicx}
\pagestyle{myheadings}
\renewcommand{\sectionmark}[1]{ \markboth{}{#1} }
\usepackage{amsmath}
\hypersetup{colorlinks=true,linkcolor=blue,citecolor=darkgreen,
  filecolor=BrickRed,urlcolor=blue}
  
\let\CwebAssign=\gets     % assignment \let\K=\gets
\def\CwebRankNoEject{1}
%\secpagedepth=-2

\begin{document}
\let\K=\gets
%  \datethis
%  \pageheight=26cm
%  \voffset=-1cm
%\input epsf
%\def\dts{\mathinner{\ldotp\ldotp}}
\newcommand{\dts}{\mathinner{\ldotp\ldotp}}
%\let\from=\gets
%\def\bit#1{\\{bit}[#1]}
%\def\losub#1{^{\vphantom\prime}_{#1}} % for contexts like $x'_n+x\losub n$

\def\today{\ifcase\month\or
  January\or February\or March\or April\or May\or June\or
  July\or August\or September\or October\or November\or December\fi
  \space\number\day, \number\year}
\newcount\twodigits
\def\hours{\twodigits=\time \divide\twodigits by 60 \printtwodigits
  \multiply\twodigits by-60 \advance\twodigits by\time :\printtwodigits}
\def\gobbleone1{}
\def\printtwodigits{\advance\twodigits100
  \expandafter\gobbleone\number\twodigits
  \advance\twodigits-100 }

\newcommand{\jplus}{j^+}
\newcommand{\jprime}{j'}
\newcommand{\iprime}{i'}
\newcommand{\jplusold}{j^+_{\mathrm{old}}}
\newcommand{\kxright}{k_{\mathrm{right}}}
\newcommand{\kxleft}{k_{\mathrm{left}}}
\newcommand{\invP}{\bar P}

\noindent{\small\today\ at \hours}

\iffalse % PYTHON!
AOT = [1, 2, 3, 16, 135, 3315, 158830, 14320182, 2343203071,691470685682]
"http://oeis.org/A006247 (bis n=11)"
rAOT= [1, 2, 3, 16, 135, 3315, 158817, 14309547, 2334512907, None]
sAOT= [1, 2, 3, 12, 28 , 225 , 825 , 13103, 76188]

#/*A006245, Number of primitive sorting networks on $n$ elements; also number of rhombic tilings of $2n$-gon.
#Also the number of oriented matroids of rank 3 on $n$(?) elements. */
PSLA=[1, 1, 2, 8, 62, 908, 24698, 1232944, 112018190, 18410581880,
5449192389984,2894710651370536, 2752596959306389652,
 4675651520558571537540, 14163808995580022218786390]
# until $n=15$. */

def numfmt(num):
    if num is None: return ""
    return split3(str(num))

def split3(s):
    if len(s)<=3: return s
    return split3(s[:-3])+"."+s[-3:]



for n,(x,y) in enumerate(zip(AOT,rAOT)):
  print (n+3,"&",numfmt(x),"&",(numfmt(y) if y else ""),"&",
  (numfmt(x-y) if y else ""),"&",
   "0" if x==y else "%2.2f"%(100*(x-y)/x)+r"\,\%" if y else "" ,
         "&", "" if n>=len(sAOT) else numfmt(sAOT[n]), "&",
         numfmt(PSLA[n+2]) if n+2<len(PSLA) else "", r"\cr")
	 
\fi

@*%*%\section*
{NumPSLA, a program for enumerating pseudoline arrangements and
abstract order types}.

@q* Introduction.@>
The purpose of this program is to enumerate
%ORIENTED
abstract order types.
(sometimes also called
generalized configuration or a pseudoconfiguration)

The program enumerates the objects without
repetition and with negligible storage.

We consider nondegenerate cases only: no three points on a line.

We abbreviate
\emph{abstract order type} by AOT and
 \emph{oriented
   abstract order type} by OAOT.
(An \emph{oriented} abstract order type can be distinguished from its
mirror image by OAOT.

%For each OAOT for $n$ points has a unique parent with $n-1$ points.
%This defines a tree structure on the OAOTs.
%The principle of the enumeration is a depth-first traversal of this tree.

%(For statistics, can still report only one orientation of two mirror types)

@*1 Pseudoline arrangements and abstract order types.

We consider everything \emph{oriented}, i.e., the mirror object can be
isomorphic or not. Also, only \emph{simple}: No three curves through a point.

A \emph{projective} pseudoline arrangement (PSLA) is a family of
centrally symmetric closed Jordan curves on the sphere such that any two curves
intersect in two points, and they intersect transversally at these
points.

An \emph{affine} PSLA is a family of Jordan curves in the plane that go
to infinity at both ends and that intersect pairwise exactly once, and
they intersect transversally at these points.

An \emph{$x$-monotone} PSLA (\emph{wiring diagram}, primitive sorting network) is an affine PSLA
with $x$-monotone curves.

We consider two objects as equivalent under deformation by
orientation-preserving isotopies of the sphere, or the plane,
respectively.
(An {$x$-monotone} PSLA must remain {$x$-monotone} throughout
the deformation.)
% and in the last case,
%homeomorphisms that map vertical lines to vertical lines.

A \emph{marked} OAOT is an OAOT with a marked point on the convex hull.

\begin{figure}[hb]
  \centering
  \includegraphics{PSLA}
  \caption{Relations between different concepts. There are different
    paths from the top left to the bottom right,
    which apply specialization or geometric reinterpretation in different order.}
  \label{fig:PSLA}
\end{figure}

See Aichholzer and Krasser,
%Oswin Aichholzer and Hannes Krasser.
Abstract order type extension and new results on the
rectilinear crossing number. Comput. Geom. 36 (2007), 2--15,
%Special Issue on the 21st European Workshop on Computational Geometry. 
Table 1.

\halign{\strut\hfil$#$ &\ \hfil$#$ &\ \hfil$#$ &\ \hfil$#$ &\quad$#$\hfil
  &\ \hfil$#$&\ \ \hfil$#$\cr
&\hbox{[\href{https://oeis.org/A006247}{A006247}]}
&\hbox{[\href{https://oeis.org/A063666}{A063666}]}
&&&&\hbox{[\href{https://oeis.org/A006245}{A006245}]}
 \cr 
n & \hbox{\#AOT} & \hbox{\#realizable AOT} &\Delta&$relative $\Delta
 & \hbox{ \ \#mirror-symmetric AOT}
  & \hbox{\#$x$-monotonePSLA}
\cr
\noalign{\hrule}
3 & 1 & 1 & 0 & 0 & 1 & 2 \cr
4 & 2 & 2 & 0 & 0 & 2 & 8 \cr
5 & 3 & 3 & 0 & 0 & 3 & 62 \cr
6 & 16 & 16 & 0 & 0 & 12 & 908 \cr
7 & 135 & 135 & 0 & 0 & 28 & 24{,}698 \cr
8 & 3{,}315 & 3{,}315 & 0 & 0 & 225 & 1{,}232{,}944 \cr
9 & 158{,}830 & 158{,}817 & 13 & 0{,}01\,\% & 825 & 112{,}018{,}190 \cr
10 & 14{,}320{,}182 & 14{,}309{,}547 & 10{,}635 & 0{,}07\,\% & 13{,}103 & 18{,}410{,}581{,}880 \cr
11 & 2{,}343{,}203{,}071 & 2{,}334{,}512{,}907 & 8{,}690{,}164 & 0{,}37\,\% & 76{,}188 & 5{,}449{,}192{,}389{,}984 \cr
12 & 691{,}470{,}685{,}682 &  &  &  &  & 2{,}894{,}710{,}651{,}370{,}536 \cr
}
\smallskip

The last column counts the objects that the program actually
enumerates
one by one  (almost, because we try to apply shortcuts). These numbers are known up to $n=15$.
For example, to get the 158,830 AOTs with 9 points, we go through all
1{,}232{,}944 xPSLAs with 8 pseudolines.

%``m-symmetric'' stands for mirror-symmetric.
$$
\text{\#OAOT} = 2\times\text{\#AOT} - \text{\#mirror-symmetric AOT}
\eqno\hbox{[\href{https://oeis.org/A006246}{A006246}]}
$$
%According to OEIS, 
%http://oeis.org/A006247,
\#AOT equals the number of
%``simple pseudoline arrangements with a marked cell''.
%Indeed it is the number of
simple {projective} pseudoline arrangements with a marked cell.

According to OEIS, three different sequences give ``the number of
primitive sorting networks on $n$ elements'': A006245, A006246, A006248.

@* The main program.

@d MAXN 15 /* The maximum number of pseudolines for which the program will work. */


@p


@<Include standard libaries@>@;
@<Types and data structures@>@;
@<Global variables@>@;
@<Subroutines@>@;
@<Core subroutine for recursive generation@>@;
int main (int argc,char* argv[])
{
  @qLocal variables@>
  @<Parse the command line@>;
#if readdatabase /*  reading from the database
*/
 @<Read all point sets...@>@;
 return 0;
#endif
#if enumAOT
  @<Initialize statistics and open reporting file@>;
  @<Start the generation@>;
  @<Report statistics@>;
#endif
  return 0;
}

@*1 Preprocessor switches.

The program has the enumeration procedure at its core, but it can be
configured to
perfom different tasks, by setting  preprocessor switches at
compile-time.

We assume that the program will anyway be modified and extended for specific
counting or enumeration tasks, and it makes sense to
set these options at compile-time.

(Other options, which are less permanent, can be set by
command-line switches.)

@d enumAOT 1 /* purpose is enumeration of AOTs */
/* Other purposes might be enumeration of PSLAs */
@d readdatabase 0 // version for reading point sets of the order-type database
@d generatelist 0  /* List all PSLAs plus their IDs, as preparation for generating
exclude-files of nonrealizable AOTs, requires |enumAOT==1|. */
@d profile 1 // gather statistics and profiling information


@ Type definitions.


@<Types and data...@>=

typedef enum {@+@!false,@+@!true @+ } boolean;
@#


@ Standard libraries
@<Include standard libaries@>=
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


@*1 Auxiliary macros for \textbf{for}-loops.
@q for_t_from_to(type,x,first,last)  for(type x=first; x<= last; x++)@>
@d for_int_from_to(x,first,last)  for(int x=first; x<= last; x++)

@q type double@>
@s for_t_from_to for
@f for_int_from_to for

@d print_array(a,length,begin,separator,end) { // for reporting and debugging
    printf(begin);
    for_int_from_to(j, 0,length-1) {
    if (j>0) printf(separator);
    printf("%d",a[j]);
    }
    printf(end);
    } /* for \texttt{gcc}, compile with \texttt{-Wno-format-zero-length} to suppress warnings */

@*1 Command-line arguments.
@d PRINT_INSTRUCTIONS     printf(
"Usage: %s n [-exclude excludefile] [splitlevel parts part] [fileprefix]\n", argv[0]);

 @<Global ...@>=
small_int n_max,split_level;
unsigned int parts=1000,part=0;
char* fileprefix = "reportPSLA"; // default name
char* exclude_file_name = 0;
char fname[200] = "";
FILE *reportfile = 0;

@
@<Parse...@>=

if (argc<2)
n_max = 7;
else {
  if (argv[1][0]=='-') { /* first argument ``\texttt{--help}'' gives
    help message. */
    PRINT_INSTRUCTIONS;
    exit(0);
}
 n_max = atoi(argv[1]);
}
printf("Enumeration up to n = %d pseudolines, %d points.\n", n_max, n_max+1);
if (n_max>MAXN)
{ 
printf("The largest allowed value is %d. Aborting.\n", MAXN);
exit(1);
}

int argshift = 0;
if (argc>=3)
{
  if(strcmp(argv[2],"-exclude")==0) {
    if (argc>=4)
    {
      exclude_file_name = argv[3];
      argshift = 2;
      printf("Excluding entries from file %s.\n", exclude_file_name);
      @<Open the exclude-file and read first line@>
    }
    else {
      PRINT_INSTRUCTIONS;
      exit(1);
    }
  }
}
if (argc>=3+argshift) {
 
  split_level = atoi(argv[2+argshift]);
  if (split_level==0)
  { if (argv[2+argshift][0]!='-') fileprefix = argv[2+argshift];
snprintf(fname, sizeof(fname)-1, "%s-%d.txt", fileprefix,n_max);
parts = 1;
 }
else
{   
  if (argc>=4+argshift) parts = atoi(argv[3+argshift]);
  if (argc>=5+argshift) part = atoi(argv[4+argshift]);
  part = part % parts;
  if (argc>=6+argshift) fileprefix = argv[5+argshift];
  snprintf(fname, sizeof(fname)-1, "%s-%d-S%d-part_%d_of_%d.txt", fileprefix,n_max,
  split_level, part,parts);
  printf("Partial enumeration: split at level n = %d. Part %d of %d.\n",
  split_level, part,parts);
}
  printf("Results will be reported to file %s.\n", fname);
  fflush(stdout);
}


@* Representations of pseudoline arrangements.

Here is an $x$-monotone
pseudoline arrangement with $n=5$ pseudolines,
together with a primitive graphic representation
as produced
by the program |print_wiring_diagram|:
% \begin{verbatim}

\medskip
\noindent\hfill
\includegraphics{psa5}
\hfill
\raise 1ex
\vbox{
  \catcode`\>=\active
\offinterlineskip\obeylines\openup1.2\jot\obeyspaces%
\def>   #1^^M{\hbox{\texttt{#1}}}%
>   1-1-1-1 4-4 5-5
>          X   X   
>   2 3-3 4 1 5 4-4
>    X   X   X     
>   3 2 4 3 5 1 3-3
>      X   X   X   
>   4-4 2 5 3-3 1 2
>        X       X 
>   5-5-5 2-2-2-2 1
}
\hfill\null
\medskip

% \end{verbatim}
Pseudoline 1 starts topmost and ends bottommost. On the right end, the
order of all pseudolines is reversed.
There is an imaginary pseudoline $0$ of very negative slope that
intersects all other pseudolines from top to bottom at the very left
and again intersects all pseudolines from bottom to top at the very
right.

@*1 The local sequences matrix and its inverse.
Here is a representation as a two-dimensional array, indicating for
each pseudoline $i$ the sequence $P_i$ of crossings with the other
lines.

local sequences matrix

{
\def\minus{{\setbox0=\hbox{0}\hbox to \wd0{\hss-\hss}}}
\catcode`-=\active\let-=\minus
\begin{tabbing}
  \qquad\=\+
  $P_0=[1,2,3,4,5]$\qquad\qquad\=$\bar P_0=[-,0,1,2,3,4]$
  \qquad\qquad\=%$B_0=[0,0,0,0,0]$ 
  \\$P_1=[0,4,5,3,2]$\> $\bar P_1=[0,-,4,3,1,2]$ \>$B_1=[0,0,0,0,0]$ 
  \\$P_2=[0,3,4,5,1]$\> $\bar P_2=[0,4,-,1,2,3]$ \>$B_2=[0,0,0,0,1]$  
  \\$P_3=[0,2,4,5,1]$ \> $\bar P_3=[0,4,1,-,2,3]$ \>$B_3=[0,1,0,0,1]$ 
  \\$P_4=[0,2,3,1,5]$\> $\bar P_4=[0,3,1,2,-,4]$ \>$B_4=[0,1,1,1,0]$ 
  \\$P_5=[0,2,3,1,4]$\> $\bar P_5=[0,3,1,2,4,-]$ \>$B_5=[0,1,1,1,1]$  
\end{tabbing}
}
The first row and the first column are determined.
Each row has $n$ elements. 
We also use the data structure for an
inverse array $\bar P$, which is essentially the inverse permutation
of the rows.
The $j$-th element of $\bar P_i$ gives the position in $P_i$ where the
crossing with $j$ occurs. The diagonal entries are irrelevant.
 The column indices in $\bar P$ range from $0$ to $n$;
therefore we define the rows to have maximum length |MAXN+1|.


@<Types...@>=
typedef int PSLA[MAXN+1][MAXN+1];

@*1 Linked representation.

For modifying and extending PSLAs, it is best to work with a linked
representation.

Point $(j,k)$ describes the crossing with line $k$ along the line $j$.
|SUCC(j,k)| and |PRED(j,k)| point to the next and previous crossing on line $j$.
For $(k,j)$ we get the corresponding information for the line $k$.
In the example, we have |SUCC(2,3)|${}=5$
and accordingly |PRED(2,5)@t${}=3$@>|.

The infinite rays on line $j$ are represented by the additional line 0:
|SUCC(j,0)| is the first (leftmost) crossing on line $j$,
and
|PRED(j,0)| is the last crossing.
The intersections on line 0 are cyclically ordered $1,\dts,n$.
Thus, |SUCC(0,i)=i+1| and |SUCC(0,n)@t${}=1$@>|.

The program works with a single linked-list representation, which is
stored in the global arrays 
|succ| and |pred|. A single pair of these arrays is sufficient for the
whole program.

@d SUCC(i,j) succ[i][j] // access macros
@d PRED(i,j) pred[i][j]

@d LINK(j,  k1,k2) { // make crossing with $k_1$ and $k_2$ adjacent on line $j$
    SUCC(j,k1) = k2;
    PRED(j,k2) = k1;
  }


@s jplus TeX
@s jprime TeX
@s iprime TeX
@s jplusold TeX
@s k_right TeX
@s k_left TeX
  
@<Global...@>=
int succ[MAXN+1][MAXN+1];
int pred[MAXN+1][MAXN+1];


@* Recursive Enumeration.

We extend an $x$-monotone pseudoline arrangement
 of $n-1$ lines $1,\dts, n-1$, 
 by threading an additional line $n$ through it
from the bottom face to the top face. The new line gets the largest
slope of all lines.

Line 0 crosses the other lines
in the order $1,2,\dts,n$.

\begin{figure}[htb]
  \centering
  \includegraphics{cross-one-face}
  \caption{Threading line $n$ through a face}
  \label{fig:threading}
\end{figure}

@
@<Core subroutine for recursive generation@>=

void recursive_generate_PSLA_start(int n);

void recursive_generate_PSLA(int entering_edge, int k_right, int n)
{ /*
The new line enters a face $F$ from the bottom.
The edge through which it crosses is part of line |entering_edge|, and
its endpoint is the crossing with |k_right|.
*/


  int j = entering_edge;
  int jplus = k_right;
@q  printf("enter through %d right %d n %d\n",j,jplus,n);@>
  while(jplus>j)
    { // find right vertex of the current cell $F$
      int jplusold = jplus;
      jplus = SUCC(jplus,j);
      j = jplusold;
@q      printf("succ j %d j+ %d n %d\n",j,jplus,n);@>
}
// the right vertex is the intersection of |j| and |jplus|
  if (jplus==0) { // $F$ is unbounded
    if (j==n-1 )
      { // $F$ is the top face.
	LINK(n,@,@,entering_edge,0);    /* complete the insertion of line $n$ */
	@<Update counters@>@;
        @<Indicate Progress@>;
	@<Check for exclusion...@>@;
        if (is_excluded) return;
        @<Gather statistics about the AOT, collect output@>@;
@<Further processing of the AOT@>@;
	if (n<n_max)
          if (n!=split_level || countPSLA[n]%parts == part) {
#if enumAOT // screening one level below
        boolean hopeful = true;
        if(n==n_max-1) {
          @<Screen one level below level |n_max|@>@;
}
	if(hopeful)
#endif
{     localCountPSLA[n+1]=0; // reset child counter
	    recursive_generate_PSLA_start( n+1);
            /* thread the next pseudoline */
@q            if (localCountPSLA[n+1]>max_children[n])@>
@q            max_children[n]= localCountPSLA[n+1];@>
}            
}
	return;
      }
      else
      { /* jump to the upper bounding ray of $F$ */
        jplus=j+1; j = 0;
        }
  }
  /* Now the crossing |      j|$\times$|jplus| is the rightmost vertex
  of the face $F$. The edge
 |jplus| is on the upper side. If $F$ is bounded,
  $j$ is on the lower side; otherwise, $j=0$.
  */
  do
    { // scan the upper edges of $F$ from right to left and try them out.
      k_right = j;
      j = jplus;
      int k_left = jplus = PRED(j,k_right);
@q      printf("MID on line j %d between %d and %d (n=%d)\n",j,k_left,k_right,n);@>

// $j$ is the exiting edge

LINK(j,@,@,k_left,n); /* insert the crossing to prepare for the
recursive call */
      LINK(j,@,@,n,k_right);

      LINK(n,@,@,entering_edge,j);
@#
      recursive_generate_PSLA(j, k_right, n);
      /* enter the recursion */
@#
LINK(j,@,@,k_left,k_right); // undo the changes
@q printf("UNDO n=%d ",n); PSLA Ps;  convert_to_PS_array(&Ps,n);  print_pseudolines_short(&Ps,n);@>
    }
  while (jplus > j); /* terminate at left endpoint of the face $F$ or
  at unbounded ray (|jplus|=0) */
  return;
}

  void recursive_generate_PSLA_start(int n)
  { LINK(0,@,@,n-1,n); /* insert line $n$ on line 0 */
    LINK(0,@,@,n,1);
      recursive_generate_PSLA(0, 0, n);
      /* enter the recursion. */
      /* There us a little trick: With these parameters $0,0$,
      the procedure
|recursive_generate_PSLA| will skip the first loop and
will then correctly scan the edges of the bottom face $F$ from right to left.
 */
  LINK(0,@,@,n-1,1); // undo the insertion of line $n$
}
    
@ Start with 2 pseudolines.

  @<Start the generation@>=

  LINK(1,@,@,0,2);
  LINK(1,@,@,2,0);
  LINK(2,@,@,0,1);
  LINK(2,@,@,1,0);
@qSUCC(0,0)=1; // artificial, makes it easier for |convert_to_PS_array|@>
LINK(0,@,@,1,2); /* |LINK(0,@,@,2,3)| and |LINK(0,@,@,3,1)| will be established
shortly in the first recursive call. */

  recursive_generate_PSLA_start(3); 



@
@<Indicate Progress@>=
if (n==n_max && countPSLA[n] % 50000000000==0) { // $5\times 10^{10}$

printf("..%Ld.. ", countPSLA[n]);
  PSLA P;
  convert_to_PS_array(&P,n);
  print_pseudolines_short(&P,n);
@q  print_small(S, n_points);@>
  fflush(stdout);
}

@
@<Update counters@>=
    countPSLA[n]++; // update accession number counter
    localCountPSLA[n]++; // update local counter
@qif(n==n_max)  printf("%d\n",PRED(1,0));@>

@* Handling the exclude-file.

The array |excluded_code[3@t\ldots@>excluded_length]| contains the decimal code
of the next PSLA that should be excluded from the enumeration.
During the enumeration, the decimal code of the currently visited tree node
(as stored in |localCountPSLA|) agrees with
|excluded_code| up to position |matched_length|.

It is assumed that the codes in the exclude-file are sorted in
strictly increasing lexicographic order, and no code is a prefix of
another code.

To give an example,
here are a few lines from the middle of the file \texttt{exclude10.txt}:
\begin{verbatim}
1.3.7.12.9.17.45
1.3.7.12.9.18.35
1.3.7.12.9.18.37
1.3.7.12.9.19
1.3.7.12.9.20
1.3.7.12.9.21.36
1.3.7.12.9.21.37
\end{verbatim}

NOTE: As currently implemented, the handling of the
exclude-file does not work together with
the parallelization through the
\emph{splitlevel} option. This is not checked.

 @<Global variables@>+=
 unsigned excluded_code[MAXN+3];
 int excluded_length = 0;
 int matched_length = 0; /* These initial values will never lead to
 any match. */
 FILE *exclude_file;
char exclude_file_line[100];

@
@<Check for exclusion and set the flag |is_excluded| @>=
boolean is_excluded = false;
if (n==matched_length+1 &&
localCountPSLA[n]==excluded_code[n])
{
  matched_length = n; // one more matching entry was found.
  if (matched_length == excluded_length) {
    // skip this PSLA and the whole subtree
    is_excluded = true;
    @<Get the next excluded decimal code...@>@;
    @<Determine the matched length |matched_length|@>
}
}


@
@<Open the exclude-file and read first line@>=
 exclude_file = fopen(exclude_file_name, "r");@;
 @<Get the next excluded decimal code...@>@;
 matched_length = 2;


 @ I don't know why the following program piece is so badly formatted
 by \texttt{cweave}.
 @<Get the next excluded decimal code from the exclude-file@>=
 do {
if (fscanf(exclude_file, "%s\n", exclude_file_line)!=EOF)
  { 
    char *str1 = exclude_file_line;
    char *token, *saveptr;
    excluded_length = 2;  @/
    while (true)
    {
      token = strtok_r(str1, ".", &saveptr);
      if (token == NULL)
         break;
@q      printf("%d: %s<<\n", excluded_length, token); @>
      assert (excluded_length<MAXN+3-1);
      excluded_code[++excluded_length] = atoi(token);
      str1 = NULL;
    }
    }
    else
    {
  excluded_length = 0; // end of file reached.
  fclose(exclude_file);
}
} while (excluded_length>n_max); // patterns longer than |n_max| are filtered.

  @ (The following program piece could be accelerated if the exclude-file
  would not store every decimal code completely but
  indicate only the deviation from the previous code.)
@<Determine the matched length |matched_length|@> =
      matched_length = 2;
      while(excluded_code[matched_length+1] ==
      localCountPSLA[matched_length+1] &&
      matched_length < excluded_length &&
      matched_length < n)@/
@q      {print_id(n);  printf(" ++%Ld\n",countPSLA[n]); @>
      matched_length ++;
@q        printf(" ++%d\n",matched_length); } @>

    
@* Conversion between different representations.
@
Convert from linked list to array.

Input: PSLA with $n$ lines $1\dts n$, stored in |succ|. % and |pred|.
Output: PSLA-Array |P| of size $(n+1)\times(n-1)$ for pseudoline arrangement on $n$ pseudolines.
@<Subr...@>=

void convert_to_PS_array(PSLA *P, int n)
{
  int j = 1;
  for_int_from_to(i,0,n)
  { 
    for_int_from_to(p,0,n-1 )
    {
      (*P)[i][p]=j;
      j = SUCC(i,j);
    }
    j = 0; // j starts at 0 except for the very first line.
  }
}
@

The inverse PSLA matrix %$\bar P=I=$
|invP| gives the following information:
$\bar P_{jk}=p$ if
the intersection between line $j$ and line $k$ is
the $p$-th intersection on line $j$ ($p=0,\dts,n-1$).
This is used to answer orientation queries about the pseudoline
arrangement, and about the dual point set,
see Section~\ref{sec:orientation}.

\iffalse
void compute_inverse_PSLA(PSLA *P,PSLA *invP,int n)
{
  for_int_from_to(i, 0, n) 
    for_int_from_to(p, 0, n-1) 
    (*invP)[i][(*P)[i][p]] = p;
}
\fi

@s invP TeX

@<Subr...@>=

void convert_to_inverse_PS_array(PSLA *invP, int n)
{
  int j = 1;
  for_int_from_to(i,0,n)
  { 
    for_int_from_to(p,0,n-1 )
    {
      (*invP)[i][j]=p;
      j = SUCC(i,j);
    }
    j = 0; // j starts at 0 except for the very first line.
  }
}


@* The orientation predicate.
\label{sec:orientation}

%Instead of storing $O(n^3)$ values, we formulate a macro that
We compute the orientation predicate in constant time from the inverse permutation array |invP|.
It is a |boolean| predicate that returns |true| if the points $i,j,k$
are in counterclockwise order. It works only when the three indices are distinct.

It is computed by comparing the intersections on line $j$.



If $i<j<k$, this predicate is |true| if the intersection of lines $i$
and $k$ lies above line $j$.
%sides of the triangle formed by lines $i,j,k$ are from the lines $i,j,k$ in
% counter-clockwise order.
When $i,j,k$ are permuted, the predicate must change according to the
sign of the permutation.
For documentation purposes, we specify an expression
|getOrientation_explicit|
 that
distinguishes
all 3! possibilities in which the indices $i,j,k$ can be ordered.
|getOrientation| is a simpler, equivalent, expression.

\begin{figure}[htb]
  \centering
\includegraphics{orientation}
\end{figure}


@d getOrientation_explicit(invP, i, j, k) (
i<j && j<k ? invP[i][j]>invP[i][k] : 
i<k && k<j ? invP[i][j]>invP[i][k] : 
j<i && i<k ? invP[i][j]<invP[i][k] : @|@t\hskip -2em\phantom(@>
j<k && k<i ? invP[i][j]>invP[i][k] : 
k<j && j<i ? invP[i][j]>invP[i][k] : 
k<i && i<j ? invP[i][j]<invP[i][k] : 
0)

@d getOrientation(invP, i, j, k) ((i<j) ^ (j<k) ^ (invP[j][i]>invP[j][k]))



@ extreme points from the PSLA.

This is easy; we just scan the top face.  We
know that 0, 1, and $n$ belong to the convex hull.  0 represents the line at $\infty$).

The input is taken from the global variable |succ|. (|pred| is not used.)

\iffalse
small_int getHulledges_PSLA(int n,
      small_int* hulledges)
      {
        hulledges[0] = 0;
  small_int hullsize = 1;
  int k=0, k_left, k_right=1;
  do
  { /* scan the edges of the top bottom face $F$ from left to right, and
    then the edges of the bottom face $F$ from left to right      */
      k_left = k;
      k = k_right;
      k_right = SUCC(k,k_left);
      if (k!=k_right) hulledges[hullsize++] = k; // adjusted
    }
    while (k != 0);

  return hullsize; // Result is the number of  extreme points.

}
\fi
@<Subrout...@>=

small_int upper_hull_PSLA(int n,
      small_int* hulledges)
      {
        hulledges[0] = 0;
  small_int hullsize = 1;
  int k=0, k_left, k_right=1;
  do
  { /* scan the edges of the top face $F$ from left to right */
      k_left = k;
      k = k_right;
      k_right = SUCC(k,k_left);
      
      hulledges[hullsize++] = k;
    }
    while (k_right != 0);

  return hullsize; // Result is the number of  extreme points.

}

@* Unique identifiers, accession numbers, Dewey decimal notation.

The recursive enumeration algorithm imposes an  implicit tree structure on PSLAs: the
parents of a PSLA with $n$ lines is the unique PSLA on $n-1$ lines from
which it is generated.  We number the children of each node in the
order in which they are generated, starting from 1.
The sequence of labels on the path
from the root to a node gives a unique identifier to each node in the
tree. (This is, however, specific to details of the enumeration
algorithm: in which order edges are considered for crossing in the
insertion, the choice of lexicographic criterion.)


The purpose of this scheme is that it allows to identify a PSLA even if
we parallelize the computation, and one thread of the program only
visits certain branches of the tree.

 @<Global variables@>+=
 unsigned localCountPSLA[MAXN+3];


@ @<Subr...@>=

void print_id(int n)
{
  printf("%d",localCountPSLA[3]);
  for_int_from_to(i,4,n)
     printf(".%d",localCountPSLA[i]);
}

@* Output.

@ Prettyprinting of a wiring diagram. Fill a buffer of lines
columnwise from left to right.

@d TO_CHAR(i) ((char) (
		       (i<10? (int)'0' : ((int)'A' - 10))
		       + i))

@<Subr...@>=


void print_wiring_diagram(int n)
{ // ASCII, horizontal, column-wise
  int next_crossing[MAXN+1]; // current crossing on each line
  int line_at[MAXN+1]; // which line is on the $i$-th track
  boolean crossing[MAXN]; /* is there a crossing between track $i$ and
  $i+1$ */

  char buffer[2*MAXN][MAXN*MAXN];
  
  for_int_from_to(j,0,n-1) {
    next_crossing[j+1]=SUCC(j+1,0);
    /* crossing $\#0$ with line 0 ``at $\infty$'' is not considered. */
    line_at[j]=j+1;
  }
  crossing[n-1] = false;
  int n_crossings = 0;
  int column = 0;
  
  for_int_from_to(p,0,2*n-1) buffer[p][column]=' ';
   @+   column++;//empty column
  while(true)
    {
    /* find where crossings occur, set boolean array |crossing|$[0\dts
    n-2]$ accordingly. */
    boolean something_done = false;
    for_int_from_to(p, 0,n-2)
      {
	int i = line_at[p];
	int j = line_at[p+1];
	crossing[p] =next_crossing[i]==j && next_crossing[j]==i;
	if (crossing[p])
	  {
	    something_done = true;
	    n_crossings++;
	  }
        }
    for_int_from_to(p,0,n-1) {
    buffer[2*p][column]=TO_CHAR(line_at[p]);
    buffer[2*p+1][column]=' ';
    }
        
    column++;
    if (!something_done) break;
    for_int_from_to(p,0,n-1){
      buffer[2*p][column]='-';
      buffer[2*p+1][column]=' ';
    }
    for_int_from_to(p,0,n-2)
      {
	if (crossing[p])
	  {       // print the crossing as an |'X'|
	    buffer[2*p][column]=
	    buffer[2*p+2][column]=' '; // erase the adjacent lines
	    buffer[2*p+1][column]='X';
	  }
      }
    column++;
    for_int_from_to(p, 0,n-2)
      {       // carry out the crossings
	if(crossing[p])
	  {
	    int i = line_at[p];
	    int j = line_at[p+1];
	    next_crossing[i] = SUCC(i,next_crossing[i]);
	    next_crossing[j] = SUCC(j,next_crossing[j]);
	    line_at[p] = j;
	    line_at[p+1] = i;
	  }
      }
    }
  for_int_from_to(p,0,2*n-2) {
    buffer[p][column]=0; // finish the lines
    printf("%s\n",buffer[p]); // and print them
  }
  assert(n_crossings*2 == n*(n-1));
}

@*1 Fingerprints.

@<Subr...@>=

void print_pseudolines_short(PSLA *P,int n)
{
  printf("P");
  for_int_from_to(i, 0,n)
  {
    printf("!");
    for_int_from_to(j, 0,n-1)
       printf("%c",TO_CHAR((*P)[i][j]));
  }
  printf("\n");
}

void print_pseudolines_compact(PSLA *P,int n)
{ // line 0 is always 1234$\dts$
  for_int_from_to(i, 1,n)
  { // line $P_i$ starts with 0 and is a permutation that misses $i$.
    if (i>1) printf("!");
    for_int_from_to(j, 1,n-2)
       printf("%c",TO_CHAR((*P)[i][j]));
  }
}

@*2 A more compact fingerprint.

Sufficient to know


$B_i[j]=1$ if $P_i[j]<i$,
see Felsner,
Chapter 6.

binary arrays $B_1,\ldots,B_n$.
The first column is fixed.
The first row $B_1$ and the last row $B_n$ is fixed, and they need not
be coded.
Also, since row $B_i$ contains $i-1$ ones, we can omit the last entry
per row, since it can be reconstructed from the remaining entries.
Thus we encode the $(n-2)\times(n-2)$ array obtained
removing the bordere from the original $n\times n$ array.

We code 6 bits into an ASCII symbol, using the small and capital
letters, the digits, and the symbols \texttt{+} and \texttt{-}.

Since we use this encoding for the case when $n$ is known,
we need not worry about terminating the code.
%(Otherwise, we could terminate it with two 0-bits, because t

(Replace matrices would offer even more savings.)

@d FINGERPRINT_LENGTH 30
//enough for $13\times13$ bits plus terminating null

@<Global...@>+=
char fingerprint[FINGERPRINT_LENGTH];

@
@<Subr...@>=

char encode_bits(int acc)
{
      if (acc<26)
    return  (char) (acc + (int) 'A');
    else  if (acc<52)
    return  (char) (acc - 26 + (int) 'a');
    else  if (acc<62)
    return  (char) (acc - 52 + (int) '0');
    else  if (acc==62)
    return  '+';
    else
    return  '-';
}

void compute_fingerprint(PSLA *P,int n) {

int charpos = 0;
int bit_num = 0;
int acc = 0;
for_int_from_to(i,1,n-1)
for_int_from_to(j,1,n-1)
{acc <<= 1;
  if ((*P)[i][j]<i) acc |= 1;
  bit_num += 1;
  if (bit_num == 6) {
    fingerprint[charpos++] =  encode_bits(acc);
    assert(charpos < FINGERPRINT_LENGTH-1);
    bit_num = acc = 0;
  }
  }
  if (bit_num) 
    fingerprint[charpos++] =  encode_bits(acc<<(6-bit_num));
    assert(charpos < FINGERPRINT_LENGTH-1);
    fingerprint[charpos++] =  '\0';
  }

@  
  @<Print PSLA-fingerprint@>+=
  {
PSLA P;
convert_to_PS_array(&P,n);
compute_fingerprint(&P,n);
 printf("%s:",fingerprint);
 }

@q  printf("Info: small matrix %u bytes.\n", (int) sizeof (small_matrix));@>



@* Abstract order types.

@*1 Lexmin for PSLA representation.

In order to generate every AOT only once, we check whether the
representation is smallest among all PSLAs that produce
AOTs, that are \emph{equivalent} by rotation and reflection.

Lexicographically smallest.
We have to try all ``boundary points''(?) as pivot points.
The average number of extreme vertices is slightly less than 4.
It does not pay off to shorten the loop considerably.
(The average \emph{squared} face size matters!)

To determine !!!!  whether a PSLA is the lex-smallest among all PSLAs
representing an AOT, we scan the PSLA
matrix row-wise \emph{from right to left}. In comparison with the
more natural left-to-right order, this gives, experimentally, a
quicker way to eliminate tentative PSLA than the 
left-to-right order.

@<Global...@>=


int Sequence[MAXN+1][MAXN+1]; /*
|Sequence[r][p]| gives the $p$-th crossing on the $r$-th hull edge. */
int new_label[MAXN+1][MAXN+1]; /*
When the $r$-th hull edge is used in the role of line 0,
|new_label[r][j]| gives index that is use for the (original) line
$j$. */
int candidate[2*(MAXN+1)]; // list of candidates, gives index |r| into |hulledges|
@qint current_line[2*(MAXN+1)]; // indexed by candidate number @>
int current_crossing[2*(MAXN+1)]; // indexed by candidate number


int P_1_n_forward[MAXN+1];
int P_1_n_reverse[MAXN+1];


@
@<Subr...@>=

void prepare_label_arrays(small_int n,
small_int *hulledges, small_int hullsize)
{
  for_int_from_to(r,0,hullsize-1)
  if(P_1_n_reverse[r] ==P_1_n_forward[0] ||
  (r>0 && P_1_n_forward[r] ==P_1_n_forward[0]))
   { // otherwise not needed.
      int line0=hulledges[r];
@q      current_crossing[r+hullsize] =  current_crossing[r] = line0; @>
@q      current_line[r] = (r<hullsize-1)? hulledges[r+1]: 0; // |0==hulledges[0]| @>
@q      current_line[r+hullsize] = (r>0)? hulledges[r-1]: n; /* |n==extrempoints[last]| */ @>
      new_label[r][line0]=0;
      int i = (r<hullsize-1)? hulledges[r+1]: 0; // |0==hulledges[0]|
      for_int_from_to(p,1,n)
      {
        new_label[r][i]=p;
        Sequence[r][p]=i;
        i = SUCC(line0,i);
      }
    }
}

@*1 Compute the lex-smallest representation.

The input is taken from the global |succ| and |pred| arrays.
The function assumes that |hulledges| and |hullsize| have been computed.l)

@<Subr...@>=
void compute_lex_smallest_PSLA(PSLA *P, small_int n,
small_int *hulledges, small_int hullsize)
{

  for_int_from_to(q,0,n-1 ) (*P)[0][q]= q+1; // row 0

  for_int_from_to(r,0,hullsize-1)
    P_1_n_forward[r] = P_1_n_reverse[r] = 0;
/* no screening. dummy values ensure that
 |prepare_label_arrays| will prepare \emph{all} label arrays */

  prepare_label_arrays(n,hulledges,hullsize);

  int numcandidates=0;
  for_int_from_to(r,0,hullsize-1)
@q    if(P_1_n_forward[r] ==P_1_n_forward[0])@>
      candidate[numcandidates++] = r; 
  int numcandidates_forward=numcandidates;
  for_int_from_to(r,0,hullsize-1)
@q    if(P_1_n_reverse[r] ==P_1_n_forward[0]) @>
      candidate[numcandidates++] = r; 
@#@#
  for_int_from_to(p,1,n)
   { // compute row $P_p$ of the PSLA array $P$
     (*P)[p][0]= 0;
     for_int_from_to(c,0,numcandidates-1)
     { 
       int r = candidate[c];
       current_crossing[c]=hulledges[r]; /* plays the role of line 0 */
     }
     
     for_int_from_to(q,1,n-1 )
     { /* Compute $P_{p,n-q}$ by taking the minimum over all candidate choices of line 0. */
       int c;
       int new_candidates, new_candidates_forward;
       int current_min = n+1; // essentially $\infty$
       boolean reversed = false;
       int pos = p; /* position of line 0; the line we are currently
       searching in |Sequence| */
       for(c=0;c<numcandidates_forward;c++)
       {
         @<Process candidate |c|, keep in list and advance |new_candidates|
         if equal; reset |new_candidates| if better value than |current_min|@>@;
       }
       new_candidates_forward = new_candidates; 
          /* can be reset in the next loop */
       @#
       reversed = true;
       pos = n+1-p;
       for(;c<numcandidates;c++)
       {
         @<Process candidate |c|, keep in list and advance |new_candidates|
         if equal; reset |new_candidates| if better value than |current_min|@>@;
       }
       numcandidates_forward = new_candidates_forward;
       numcandidates = new_candidates;
       (*P)[p][n-q]= current_min;
       /* could enter a shortcut as soon as |numcandidates==1| */
     }
   }
 }
@ The list of candidates is scanned and simultaneously overwritten
with new values.

@<Process candidate |c|, keep in list and advance |new_candidates|
         if equal...@>=
         int r = candidate[c];
         int i=Sequence[r][pos]; // We are proceeding on line i
         int j=current_crossing[c];
         j = reversed ? SUCC(i,j): PRED(i,j);
         int a = new_label[r][j];
         if(reversed && a!=0)
           a=n+1-a;
         if(a<current_min) // new record:
         {
           new_candidates = new_candidates_forward = 0;
           current_min = a;
         }
         if (a==current_min)
         { // candidate survives.
           candidate[new_candidates]=r;
           current_crossing[new_candidates] = j;
           new_candidates++;
         } // Otherwise the candidate is skipped.




@
The output parameters have only a meaning if the test returns |true|.
|has_fixpoint| is only set if the PSLA is mirror-symmetric.

We scan the entries of $P$ row-wise from right to left.
We maintain a list of solutions, which are still
\emph{candidates} to be lex-smallest.
Initially we have $2\times{}$|hullsize| candidates,
|hullsize| ``forward'' candidates and the same number of
mirror-symmetric, reversed candidates.

Candidates $0\dts |numcandidates_forward|-1$ are forward candidates.
The remaining candidates up to |numcandidates-1| are reverse (mirror)
candidates.

If information about mirror symmetry is not necessary, then the mirror
candidates
can be omitted.

@*1 Streamlined version. Fast screening of candidates

Let $i$ and $j$ be two consecutive edges on the upper envelope.
The quantity $Q(i,j)$ is defined as follows, see Figure~\ref{fig:def-Q}a.

\begin{figure}[htb]
  \centering
  \includegraphics{def-Q}
  \caption{(a) An example with $Q(i,j)=4$ and $\bar Q(i,j)=5$;
  (b) an example with $Q(0,1)=\bar Q(0,1)=4$}
  \label{fig:def-Q}
\end{figure}


Let
$i'={}$|PRED|$(i,j)$. Walk on line $i$ to the right (by |SUCC|)  from the
intersection between $i$ and $j$ until meeting the intersection with
$i'$.
Then $Q(i,j)$ is the number of visited points on $i$, including the
endpoints.
This convention ensures that $Q(i,j)$ is the value $P_{1n}$ when line
$i$ is chosen to play the role of line $0$, (and $j$ will become line~1).
In the walk along $i$, we may cross line $0$ and wrap around to the
left end.



The quantity $\bar Q(i,j)$
is defined with switched roles of $i$ and $j$
and with left and right exchanged, and it gives
the value $P_{1n}$ in the mirror situation
(the \emph{backward} direction)
when line
$j$ is chosen to play the role of line $0$:
Let
$j'={}$|SUCC|$(i,j)$. Walk on line $j$ to the left (by |PRED|)
% from the intersection between $i$ and $j$
until meeting line~% the intersection with
$j'$.

We apply this definition two all pairs $(i,j)$ of
consecutive edges on the upper envelope, starting with $(0,1)$ and
ending with $(n,0)$. (The last pair is the only pair with $i>j$.)

The numbers
$Q(i,j)$ and
 $\bar Q(i,j)$
are between 2 and $n$,
and $Q(i,j)=2 \iff\bar Q(i,j)=2$.

For $(i,j)=(0,1)$,
the wedge between lines $i$ and $j$ appears actually at the
bottom right of the wiring diagram,
 see Figure~\ref{fig:def-Q}b. Here we have
 $Q(0,1)={}$|PRED|$(1,0)=P_{1n}$, since this is the original situation
 where line 0 is where it should be.
Similarly, for $(i,j)=(n,0)$, we have to look at the bottom left corner.

...

Our primary criterion in comparing candidates is $P_{1n}$ which is
given by $Q(i,j)$ and $\bar Q(i,j)$ for the pairs $(i,j)$ of
consecutive edges on the upper envelope. This has to be compared against.
$Q(0,1)$.


@ Screen candidates by comparing the leading entry $P_{1n}$,
 
Compute the leading entry $P_{1n}$ for all candidates directly,
without first computing the |label_arrays|.  The |label_arrays| are
computed afterwards (if at all), and only those that are still
necessary.  This saves about 20\,\% of the runtime for enumerating
AOTs.  If $P_{1n}=2$ for line 0, the screening has no effect, but
otherwise there is a high chance for finding a smaller value $P_{1n}$
for some of the other candidates.

[ Observation. The relative frequence of $P_{1n}$ over all PSLAs is
about 26\,\% for 2 and $n$, about 11\,\% for 3 and $n-1$ and decreases
towards the middle values. The symmetry can be explained as follows.
An xPSLA is essentially a projective oriented PSLA with a marked angle. Going to
an adjacent angle and mirroring the PSLA exchanges $a$ with $n+2-a$. ]

The following program treats each forward candidate $i$ together with
the corresponding mirror candidate~$j$.
it uses the condition $Q(i,j)=2 \iff\bar Q(i,j)=2$ to shortcut the
computation.
(not sure if it brings any advantage.)

 For example
 there are
 18,410,581,880 PSLAs 
 with $n=10$ lines.
 Of these, only
 5,910,452,118 pass the screening test.
 Eventually, only
 2,343,203,071 PSLA are really lex-min, and this is the number of
 AOTs that we really want.


@<Subr...@>=

boolean screen(small_int n,
small_int *hulledges, small_int hullsize)
{
@q  // |  if(P_1_n_forward[0]==2) return true;| @>
@q  /* shortcut is possible for the remaining entries */ @>
  
P_1_n_forward[0]= PRED(1,0); /* because |hulledges[1]==1| */
  for_int_from_to(r,1,hullsize-1)
  {
    int r_next = (r+1) % hullsize;
    int i=hulledges[r];
    int j =hulledges[r_next]; /* $i$ or $j$ plays the role of line 0 */
    int iprime = PRED(j,i);

    int a = 2;@+
    int j2 = SUCC(i,j);
    while (j2!=iprime)
      { // compute $a$ by running along |i|
        j2 = SUCC(i,j2); a++;
        if (a>P_1_n_forward[0]) break; // shortcut
      }
      if (a<P_1_n_forward[0]) return false;
      P_1_n_forward[r] = a;
    /* This may not be the precise value if |a>P_1_n_forward[0]| */
    }
@#
  for_int_from_to(r,0,hullsize-1)
  {
    int r_next = (r+1) % hullsize;
    if (P_1_n_forward[r] ==2)
    {
      P_1_n_reverse[r_next] = 2;
      /* The wedge between $i$ and $i$ is a triangle;
$Q(i,j)$ and $\bar Q(i,j)$ are both 2.
      */
      continue;
    }
    int i=hulledges[r];
    int j =hulledges[r_next]; /* $i$ or $j$ plays the role of line 0 */
    int jprime = SUCC(i,j);
    int a = 2;@+
    int i2 = PRED(j,i);
      do { // compute $a$ by running along |j|
        i2 = PRED(j,i2); a++;
        if (a>P_1_n_forward[0]) break;
      }
      while (i2!=jprime);
      if (a<P_1_n_forward[0]) return false;
    P_1_n_reverse[r_next] = a;
    }

  return true;
}


@ More effective screening at the previous level.

Rather than generating many PSLAs with $n$ lines and
 eliminating them by screening,
 it is better not to generate them at all, or to generate only those
 that
 have a change of surviving the screening test.

To do this, we apply a test at the previous level.

When adding a new line $n$, the quantities $Q(i,j)$ can change in a
few ways.

\begin{enumerate}
\item We cut off some hull vertices. In particular, $(n-1,0)$ will
  always disappear.
\item We generate two new hull vertices: $(i,n)$ with $1\le i \le
  n-1$, and $(n,0)$.
  
\item In the definition of $Q(i,j)$, line $n$ could take the role of
  $i'$.
  (or $j'$ in the case of $\bar Q(i,j)$).
\item In the definition of $Q(i,j)$, line $n$ could intervene between
  the intersections with $j$ and $i'$ on line $i$, thus increasing
 $Q(i,j)$ by 1.
  (or a similar situation for $\bar Q(i,j)$).
\end{enumerate}


A very rudimentary pre-screening test has been implemented, namely for
the comparison between $Q(0,1)$ and $\bar Q(1,0)$:

 \emph{If $\bar Q(0,1)< Q(1,0)-1$ in the arrangement with $n-1$ lines,
   then there is no chance to augment this to a lex-min PSLA.}

 Proof:
 See Figure~\ref{fig:def-Q}b.
 There are two cases.
 If line $n$ does not intersect the segment
 between
 $1\times 0$ and
 $1\times{}$|PRED|$(1,0)$, then
 $Q(0,1)=P_{1n}$ is unchanged.
 $\bar Q(1,0)$ can increase by at most 1. Thus
 $\bar Q(1,0)$ will beat $Q(1,0)$.

If line $n$ intersects line 1
 between
 $1\times 0$ and
 $1\times{}$|PRED|$(1,0)$, then
 $n$ becomes the new $i'={}$|PRED|$(1,0)=
 Q(0,1)=P_{1n}$, and thus
 $P_{1n}$ has the maximum possible value, $n$, and is certainly larger
 than before.
$\bar Q(1,0)$ can still increase by at most 1. Thus
 $\bar Q(1,0)$ will beat $Q(1,0)$.

 For example, with $n=9$ lines
 there are  112,018,190 PSLAs, and they generate as children
 18,410,581,880 PSLAs 
 with $n=10$ lines, as mentioned above. 
 The screening test at level $n=9$ eliminates
 22,023,041 out of the 112,018,190 PSLAs (19.66\%) because they are
 not able to produce a lex-min AOT in the next generation.
 The remaining  89,995,149 PSLAs produce 
 15,409,623,219 offspring PSLAs
 with $n=10$ lines.
 as opposed to 18,410,581,880 without this pruning procedure.
 These remaining PSLAs are subject to the screening as before.

 @
@<Screen one level below...@>=
int P_1_n = PRED(1,0);
/* insertion of last line $n$ can only make this larger. */
if(P_1_n>3)
{
  int a = 2;
  int i2 = P_1_n; // |==iprime|
  while (i2!=2)
  { // compute $a$ by running along |j==1|
    i2 = PRED(1,i2); a++;
  }
  /* Now |P_1_n_reverse == a| but insertion of line $n$
  could increase this by 1. */
  if (a+1<P_1_n) hopeful=false;
}
if(hopeful) cpass++; @+ else csaved++;

@ We maintain statistics about the effectiveness of this test:
 @<Global...@>=

long long unsigned cpass, csaved;

@
@<Subr...@>=

boolean is_lex_smallest_PSLA(small_int n,
small_int *hulledges, small_int hullsize, small_int*
rotation_period, boolean *is_symmetric, boolean *has_fixpoint)
{
  if (!screen(n, hulledges, hullsize))
    return false;

#if profile
    numTests ++;
#endif


  prepare_label_arrays(n,hulledges,hullsize);

  int numcandidates=0;
  for_int_from_to(r,1,hullsize-1)
    if(P_1_n_forward[r] ==P_1_n_forward[0])
      candidate[numcandidates++] = r; 
  int numcandidates_forward=numcandidates;
  for_int_from_to(r,0,hullsize-1)
    if(P_1_n_reverse[r] ==P_1_n_forward[0])
      candidate[numcandidates++] = r; 
@#@#
  for_int_from_to(p,1,n)
   { // explore row $P_p$ of the PSLA array $P$
     int current_crossing_0 = 0; // candidate $c=0$ is treated specially.
     for_int_from_to(c,0,numcandidates-1)
     { 
       int r = candidate[c];
@q       int line1 = current_line[c];@>
@q       current_line[c]=Sequence[r][c<numcandidates_forward?p:n+1-p];@>
/* plays the role of line 1 */
@qint line0 = @>
current_crossing[c]=hulledges[r]; /* plays the role of line
       0 */
@q       current_line[c] = c<numcandidates_forward? SUCC(line0,line1):PRED(line0,line1) ;@>
     }
     
     for_int_from_to(q,1,n-2 )
     { /*
Compute $P_{p,n-q}$ for all choices of line 0.
The last entry $q=n-1$ can be omitted, because every row is a permutation. */
       int target_value = current_crossing_0 =
       PRED(p,current_crossing_0); /* special treatment of candidate
       0:
       current line |i| is line |p|; no relabeling necessary. */
       int c;
       int new_candidates = 0;
@q       int (*next)[MAXN+1][MAXN+1] = &succ; /* points either to |succ|  or to |prev| */@>
       boolean reversed = false;
       int pos = p; // position of line 0
       for(c=0;c<numcandidates_forward;c++)
       {
         @<Process candidate |c|, keep in list and advance |new_candidates|
         if successful; return |false| if better value than |target_value|
 is found@>@;
       }
       numcandidates_forward = new_candidates;
       @#
       @qnext = &pred;@>
       reversed = true;
       pos = n+1-p;
       for(;c<numcandidates;c++) 
       {// continue the previous loop
         @<Process candidate |c|, keep in list and advance |new_candidates|
         if successful...@>@;
       }
       numcandidates = new_candidates;
       @#
       if(numcandidates==0)
       { // early return
         *rotation_period =  hullsize;
         *is_symmetric = false;
         return true;
       }
     }
   }
   @<Determine the result parameters, depending on the remaining candidates.@>@;
   
   return true;
}

@

@<Process candidate |c|, keep in list and advance |new_candidates|
         if successful...@>=

#if profile
    numComparisons ++;
#endif
         int r = candidate[c];
         int i=Sequence[r][pos];
@qcurrent_line[c];@>
         int j=current_crossing[c];
@q         j = (*next)[i][j];/* | j = PRED(i,j)| or |SUCC(i,j);| */@>
         j = reversed ? SUCC(i,j): PRED(i,j);
         int a = new_label[r][j];
         if(reversed && a!=0)
           a=n+1-a;
@q           if(c==0)@>
@q {printf("(p,q)=(%d,%d), (i,j)=(%d,%d), targ %d = %d a, r=%d\n", p,q,i,j,target_value,a,r); @>
@q  target_value=a;  else {@>
           if(a<target_value)
@q   {printf("r=%d, rev=%d, (p,q)=(%d,%d), %d<%d F.\n",r,reversed[c], p,q,a,target_value);@>
             return false;
         
         if (a==target_value)
         {
@q           if (new_candidates!=c)   {@>
             candidate[new_candidates]=r;
@q             current_line[new_candidates]=i;@>
           current_crossing[new_candidates] = j;
           new_candidates++;
         }
@qelse printf("r=%d, rev=%d, (p,q)=(%d,%d), %d>%d ELIM.\n",r,reversed[c], p,q,a,target_value);@>



@ 
@<Determine the result...@>=
{
  if(numcandidates_forward>0)
    *rotation_period = candidate[0];
  else
    *rotation_period =  hullsize;
  *is_symmetric = (numcandidates>numcandidates_forward);
   if (*is_symmetric) {
     int symmetric_shift = candidate[numcandidates_forward];
     /* There is a mirror symmetry that maps 0 to this hull vertex. */
      *has_fixpoint = ((*rotation_period)%2==1) || (symmetric_shift%2==0);
    }
  }



@* Statistics.
Characteristics:
\begin{itemize}
\item number $h$ of hull points.
\item period $p$ of rotational symmetry on the hull. (The order of the
  rotation group is $h/p$.)
\item mirror symmetry, with or without fixpoint on the hull (3 possibilities).
\end{itemize}

|PSLAcount| gives OAOT of point sets with a marked point on the convex hull.
http://oeis.org/A006245 (see below) is the same sequence with $n$ shifted by 0.

@d NO_MIRROR 0
@d MIRROR_WITH_FIXPOINT 1
@d MIRROR_WITHOUT_FIXPOINT 2

@<Global variables@>+=

  long long unsigned countPSLA[MAXN+2], countO[MAXN+2], countU[MAXN+2];
  
long long unsigned PSLAcount[MAXN+2];
/*A006245, Number of primitive sorting networks on $n$ elements; also number of rhombic tilings of $2n$-gon.
Also the number of oriented matroids of rank 3 on $n$(?) elements. */
/* 1, 1, 2, 8, 62, 908, 24698, 1232944, 112018190, 18410581880, 5449192389984
$\ldots$ until $n=15$. */
long long unsigned xPSLAcount[MAXN+2];
long long unsigned classcount[MAXN+2][MAXN+2][MAXN+2][3];



long long unsigned
numComparisons=0, numTests=0; // profiling

@
\iffalse
    for(small_int n=0; n<=n_max; n++)
    for(small_int k=0; k<=n_max; k++)
    for(small_int p=0; p<=n_max; p++)
    for(small_int t=0; t<3; t++)
assert (classcount[n][k][p][t]==0);
\fi

@<Initialize statistics...@>=

  countPSLA[1]=
  countPSLA[2]=1;
countO[3]=
countU[3]=
PSLAcount[2]=
xPSLAcount[2]=
1;
// All other counters are automatically initialized to 0.
  if (strlen(fname)) {
    reportfile = fopen(fname,"w");
  }


@ @<Gather statistics...@>=

@//* Determine the extreme points: */
   small_int hulledges[MAXN+1];
   small_int hullsize = upper_hull_PSLA(n, hulledges);

   small_int rotation_period;
   boolean has_fixpoint;
   boolean is_symmetric;


   int n_points = n+1; // number of points of the AOT

boolean lex_smallest =
is_lex_smallest_PSLA(n,
hulledges, hullsize,
&rotation_period, &is_symmetric, &has_fixpoint);

if(lex_smallest)
{
  countU[n_points]++;
  if (is_symmetric)
  {
    countO[n_points]++;
    PSLAcount[n]+=rotation_period;
     if(has_fixpoint)
        xPSLAcount[n]+=rotation_period/2+1;
	// works for even and odd |rotation_period|
   else
      xPSLAcount[n]+=rotation_period/2;
  }
  else
  {
    countO[n_points]+=2;
    PSLAcount[n]+=2*rotation_period;
    xPSLAcount[n]+=rotation_period;
  }

  classcount[n_points][hullsize][rotation_period][
  !is_symmetric? NO_MIRROR : has_fixpoint ? MIRROR_WITH_FIXPOINT :
  MIRROR_WITHOUT_FIXPOINT] ++;
}

#if 0 // debugging
printf("found n=%d. %Ld ",n_points,countO[n_points]);
print_small(S,n_points);
#endif

@

written to a file so that a subsequent program
can conveniently read and process it.


@<Report statistics...@>=
  printf("%34s%69s\n","#PSLA visited by the program", "#PSLA computed from AOT");
for_int_from_to(n,3,n_max+1) {
  long long symmetric =  2*countU[n] - countO[n];
  printf("n=%2d", n);
  if (split_level!=0 && n>split_level)  printf("*,"); @+
  else  printf(", ");
  printf("#PSLA=%11Ld", countPSLA[n]);
#if 1
  printf(", #AOT=%10Ld, #OAOT=%10Ld, #symm. AOT=%7Ld, ",
  countU[n], 
countO[n], symmetric
  );
  printf("#PSLA=%11Ld, #xPSLA=%10Ld", PSLAcount[n], xPSLAcount[n]);
#endif
  printf("\n");

}

if (split_level!=0) printf("* Lines with \"*\" give results from partial enumeration.\n");
#if profile
printf("Total tests is_lex_min (after screening) = %Ld, total comparisons = %Ld, average =%6.3f\n",
numTests, numComparisons, numComparisons/(double)numTests);
#endif

printf("passed %Ld, saved %Ld out of %Ld = %.2f%%\n", cpass, csaved,
               cpass+csaved, 100*csaved/(double)(cpass+csaved));

 if (strlen(fname)) {
  fprintf(reportfile,"# N_max=%d/%d", n_max, n_max+1);
  if (parts!=1)
  fprintf(reportfile,", split-level=%d, part %d of %d",
     split_level, part,parts);	
  fprintf(reportfile,"\n#x N hull period mirror-type  NUM\n");
    for_int_from_to( n,0, n_max+1)
    { 
    char c = 'T'; /* total count */
      if (parts!=1 && n>split_level+1)
      c = 'P'; /* partial count */
    for_int_from_to( k,0, n_max+1)
    for_int_from_to( p,0, n_max+1)
    for(small_int t=0; t<3; t++)
      if (classcount[n][k][p][t])
  fprintf(reportfile,
     "%c %d %d %d %d  %Ld\n", c,n,k,p,t,  classcount[n][k][p][t]);
}
  if (parts==1)
  fprintf(reportfile,"EOF\n");
  else
  fprintf(reportfile,"EOF %d, part %d of %d\n",
     split_level, part,parts);	

fclose(reportfile);
    printf("Results have been written to file %s.\n", fname);
  }


@ Problem-specific processing can be added here.

After computing the inverse PSLA matrix, one can perform a few tests on the
order type, using orientation queries.

The following test program compares the orientation queries against an
explicitly computed ``large $\Lambda$-matrix''.

@<Further processing...@>=

#if generatelist /* List all PSLAs plus their IDs, as preparation for generating
exclude-files of nonrealizable AOTs */
if(n==n_max && lex_smallest) {
   @<Print PSLA-fingerprint@>
print_id(n);printf("\n"); }
#endif
@qprint_id(n); printf(" .. %d",matched_length); printf(" --%Ld\n",countPSLA[n]);@>
#if 0
if(n==n_max && countPSLA[n]==50) { // print ``some'' example
  PSLA PP,invPP;
  convert_to_PS_array(&PP,n);
  convert_to_inverse_PS_array(&invPP,n);
  print_pseudolines_short(&PP,n);
  printf("inverse ");  print_pseudolines_short(&invPP,n+1);
  print_wiring_diagram(n);
  }
#endif

#if 0  // estimate size of possibly subproblems for d\&c Ansatz
#define MID 5
if(n==2*MID-2)
{
  PSLA P;
  convert_to_PS_array(&P,n);
@q  print_pseudolines_short(&P, n);@>
  for_int_from_to(i, 2,MID-1)
  {
    boolean show = true;
    for_int_from_to(j, 1,n-1)
    {
      int x = P[i][j];
      if(x==MID||x==1) break;
      printf("%c",TO_CHAR(x));

    }
    printf("!");
  }
  for_int_from_to(i, MID+1,n)
  {
    boolean show = false;
    for_int_from_to(j, 1,n-1)
    {
      int x = P[i][j];
     @q if (!show) printf(".");@>
      if (show)
        printf("%c",TO_CHAR(x));
      if(x==MID) show = true;
      if(x==1) break;
    }
    printf(i<n?"!":" ");
  }
  for_int_from_to(j, 1,n-1) {
      int x = P[1][j];
      if (x==MID) break;
      printf("%c",TO_CHAR(x));}
  printf("!");

  for_int_from_to(j, 1,n-1){
      int x = P[MID][j];
      if (x==1) break;
      printf("%c",TO_CHAR(x));}
  printf("\n");
}

#endif


#if 0
PSLA invP; // the orientation test is computed from this array.
convert_to_inverse_PS_array(&invP,n);
@#
small_matrix S;
convert_to_small_lambda_matrix(&S, n_points);
large_matrix L;
convert_small_to_large(&S, &L, n_points);
@<Compare orientation tests@>@;
#endif

@
@<Compare orientation tests@>=

{int n=n_points;
  for_int_from_to(i,0,n-1)
  for_int_from_to(j,0,n-1)
  if (i!=j)
  for_int_from_to(k,0,n-1)
  if (k!=j && k!=i)
  if(getOrientation(invP,i,j,k) != L[i][j][k]) {
    @qprint_small(S, n_points);@>
  printf ("[%d,%d,%d]=%d!=%d\n", i,j,k,
  getOrientation(invP,i,j,k), L[i][j][k]);
  exit(1);
  }
  ;

}  

@* Data structures for abstract order types.

@  $\lambda$-matrices.

In this program, entries $\Lambda_{ijk}$ of the large matrix are only
ever accessed for $i<j<k$.
For more general access, we provide the macro
|get_entry_large|.
It would be possible to save space by a more elaborate indexing function into a one-dimensional array.

 natural labeling around the |pivot| point, which is assumed to lie
on the convex hull.


%d entry_small(A,i,j) (A).entry[(i)*MAXN+(j)]
%d entry_large_ordered(A,i,j,k) (A).entry[(i)*MAXN*MAXN+(j)*MAXN+(k)]  // assumes $i<j<k$
@d entry_small(A,i,j) (A)[i][j]


@ More type definitions.


@s small_int int
@s  small_matrix_entry int
@s  large_matrix_entry int
% ought to be done automatically

@<Types and data...@>=


typedef uint_fast8_t XXsmall_matrix_entry; /* suffices up to $n=255+1$ */
@qtypedef int_fast8_t XXlarge_matrix_entry;@>
typedef int_fast8_t XXsmall_int; // suffices for $n$
typedef boolean large_matrix_entry;
typedef unsigned small_matrix_entry;
typedef int small_int; // simpler and maybe even faster?


typedef small_matrix_entry small_matrix[MAXN+1][MAXN+1];
typedef large_matrix_entry large_matrix[MAXN+1][MAXN+1][MAXN+1];



@ Generating the $\Lambda$-matrix. Only for testing purposes.
Assumes natural ordering. Assumes general position. Works by plucking
points from the convex hull one by one.

@<Subrout...@>=

void copy_small(small_matrix *A,small_matrix *B, small_int n)
{
  for(small_int i=0;i<n;i++)
     for(small_int j=0;j<n;j++)
        entry_small(*B,i,j) = entry_small(*A,i,j);
}

void convert_small_to_large(small_matrix *A, large_matrix *B,
small_int n)
{
    small_matrix Temp;
    copy_small(A,&Temp,n); //  the small matrix |Temp| will be destroyed
    for(small_int k=0;k<n;k++)
        for(small_int i=k+1;i<n;i++)
            for(small_int j=i+1;j<n;j++) // $k<i<j$
            {
              if (entry_small(Temp,i,k)<entry_small(Temp,j,k))
              {
                entry_small(Temp,i,j)--;
                (*B)[k][i][j]=(*B)[i][j][k]=(*B)[j][k][i]= true;
                (*B)[k][j][i]=(*B)[i][k][j]=(*B)[j][i][k]= false;
              }
              else
              {
                entry_small(Temp,j,i)--;
                (*B)[k][i][j]=(*B)[i][j][k]=(*B)[j][k][i]= false;
                (*B)[k][j][i]=(*B)[i][k][j]=(*B)[j][i][k]= true;
              }
            }
}


@* Auxiliary routines and conversion to other formats.

@ Input: PSLA with $n$ lines $1\dts n$ plus line $0$ ``at $\infty$''.
Output: small $\lambda$-matrix $B$ for AOT on $n+1$ points.
Line at $\infty$ corresponds to point 0 on the convex hull.
@<Subr...@>=


void convert_to_small_lambda_matrix(small_matrix *B, int n)
{
  for_int_from_to(i,0,n)
    {
      (*B)[i][i] = 0;
    }
  for_int_from_to(i,1,n)
    {
      int level = i-1; // number of lines above the crossing
      (*B)[0][i] = level;
      (*B)[i][0] = n-1-level;
      int j = SUCC(i,0);
      while (j!= 0)
	{
	  if (i<j)
	    {  
              (*B)[i][j] = level;
          level++;              }
	  else {level--;
          (*B)[i][j] = n-1-
          level;

	  }
          j = SUCC(i,j);
	}
    }
}

@q Insert extra extensions here --- @>

@i readDataBase


@* Things to consider.

\begin{enumerate}
\item 
The \texttt{-exclude} option does not work with
the parallelization through
\emph{splitlevel}. (This is not currently checked.)
%Streamline the \texttt{screening} program.
\item 
Using inverse-PSLA makes
\emph{screening} slower!
It is only good if combined with screening one level before!
Computing |inverse_PSLA| one level before |max_n| costs almost nothing.
% (Whatever that means!)
\item
The |succ| and |pred| arrays could be implemented as one-dimensional
  arrays. Need to check which is faster.
\end{enumerate}

@d SUCC_ALTERNATE(i,j) succ[i<<4 | j]
// A shift of 4 is sufficient for |MAXN+1==16|
@q assert(1<<SHIFT >= MAXN+1); # if @>

@
\markboth{}{Table of contents}
\tableofcontents
\eject\markboth{}{Index}
\iftrue % to offset a dangling \fi from somewhere
\end{document}
%%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Local Variables:
%%% mode: LaTeX
%%% compile-command: "ctangle NumPSLA.w && pdflatex NumPSLA"
%%% End:
