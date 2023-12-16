Change file for determining crossing numbers

@x
\documentclass[baseclass=article%
@y
\documentclass[baseclass=article,suppress=unchanged,
suppress=reflist,suppress=index%
@z

@x
\noindent{\small\today\ at \hours}
@y
\noindent{\small\today\ at \hours}

\noindent Changed sections for computing the crossing number.

@z

@x
@d MAXN 15 /* The maximum number of pseudolines for which the program will work. */
@y

\emph{Change:}
We are keeping statistics for several independent characteristics,
one of which (the |crossing_number|) can rise to high values
(see |MAX_CROSSINGS| in Section~\ref{crossing-number}).
Therefore, we reduce the maximum number |MAXN| of pseudolines from 15 to what we really need.

@d MAXN 12 /* The maximum number of pseudolines for which the program will work. */
@z

@x
\item mirror symmetry, with or without fixed vertex on the hull (3 possibilities).
\end{itemize}
@y
\item mirror symmetry, with or without fixed vertex on the hull (3 possibilities).
\end{itemize}
In addition, we keep
\begin{itemize}
\item the number of halving-lines,
|num_halving_lines|.
\item the crossing number, 
|crossing_number|.
\end{itemize}
@z


@x statistics array:
long long unsigned classcount[MAXN+2][MAXN+2][MAXN+2][3];
@y
long long unsigned classcount[MAXN+2][MAXN+2][MAXN+2][3]
[MAX_HALVING_LINES+1]
[MAX_CROSSINGS+1];
/* This is a huge array: If it were full it would take
about 2 GBytes of main memory.
But it is very sparsely filled. With the \texttt{gcc} compiler,
the system reports less than
30 MBytes of used storage, and often only 2 or 3 MBytes.
This might just depend on the available memory for swapping.
 With \texttt{clang} compiler, the observed memory usage was
 also less than
3 MBytes.
Only in |@<Report stat...@>| is the full array scanned once.
*/
int num_halving_lines; // global variable; (This is not the cleanest way to do it.)

@z

@x updating the statistics
  classcount[n_points][hullsize][rotation_period]
  @|[  !has_mirror_symmetry? NO_MIRROR : has_fixed_vertex ? MIRROR_WITH_FIXED_VERTEX :
  MIRROR_WITHOUT_FIXED_VERTEX] ++;
@y
  int crossing_number = count_crossings(n);
  assert (num_halving_lines <= MAX_HALVING_LINES);
  classcount[n_points][hullsize][rotation_period][
  !has_mirror_symmetry? NO_MIRROR : has_fixed_vertex ? MIRROR_WITH_FIXED_VERTEX :
  MIRROR_WITHOUT_FIXED_VERTEX][num_halving_lines][crossing_number] ++;
@z

@x statistics reporting:
  fprintf(reportfile,"\n#x N hull period mirror-type  NUM\n");
@y  
  fprintf(reportfile,"\n#x N hull period mirror-type halving-lines crossing-number NUM\n");
@z  

@x statistics reporting:
    for_int_from_to(t,0, 2)
      if (classcount[n][k][p][t])
  fprintf(reportfile,
     "%c %d %d %d %d  %Ld\n", c,n,k,p,t,  classcount[n][k][p][t]);
}
@y     
    for_int_from_to(t,0,2)
    for_int_from_to(h,0,MAX_HALVING_LINES)
    for_int_from_to(cr,0,MAX_CROSSINGS)
      if (classcount[n][k][p][t][h][cr])
  fprintf(reportfile,
     "%c %d %d %d %d %d %d  %Ld\n", c,n,k,p,t,h,cr,  classcount[n][k][p][t][h][cr]);
}
@z

========= Here comes the computation of halving-lines
not sure where this is supposed to go

@<Global...@>+= .......

@x Here comes the computation of halving-lines
@*1 Further processing of AOTs.
Problem-specific processing can be added here.
@<Further processing of the AOT@>=
// Currently no further processing of the AOT.

@y
@* {Extension: Compute crossing-number for each AOT}.
\label{crossing-number}

@q# A076523 (b-file synthesized from sequence entry)@>
@q 2:3, 3:6, 4:9, 5:13, 6:18, 7:22, 8:27, 9:33, 10:38, 11:44, 12:51, 13:57@>

What range of values should we anticipate for the number of halving-lines?
By \url{https://oeis.org/A076523}, a set with
$n=12$ points %, (the maximum that the program is set up to deal with),
has at most 18 halving-lines.
According to  S. Bereg and M. Haghpanah,
New algorithms and bounds for halving pseudolines,
Discrete Applied Mathematics 319 (2022) 194--206, \url{https://doi.org/10.1016/j.dam.2021.05.029},
Table 1 on p.~196,
the number of halving lines-with for odd numbers $n$ of points
are nearly $70\,\%$ higher than for the adjacent even values.
I could not find the bounds for small odd $n$ in the literature
or on the internet.
%With a bound of 50 we should be on the safe side.
After running the program once with a larger safety margin,
it was found that
a set with $n=11$ points has at most 24 halving-lines.
(The program checks if the bound is not violated.)
With $n=13$ points and a bound 40 on the halving-lines we should be on the safe side.
@d MAX_HALVING_LINES 40 // For $n=12$ point, |MAX_HALVING_LINES=24| would be sufficient.


@d MAX_CROSSINGS (MAXN+1)*MAXN*(MAXN-1)*(MAXN-2)/24
 /* crossing-number goes up to $\binom n4$ for $n$ points */

@ Find the number of crossings on each level of the wiring diagram.

This algorithm is like the program for drawing the wiring diagram,
except that it does not draw anything.

The wires run on $n$ \emph{tracks}, which are labeled from 1 to $n$
from top to bottom.

The program computes the number of crossings
|num_crossings_on_level[p]|
at
each level |p| including the crossings with line 0.
A crossing at level |p| is a crossing between
consecutive tracks  |p| and $p+1$, $1\le p \le n-1$.

From this information,
the crossing number
of the complete graph $K_n$ when it is drawn on this point set
can be computed by easy explicit formula,
see Lov\'{a}sz, Vesztergombi, Wagner, and Welzl, \emph{Convex quadrilaterals and
  $k$-sets}, 
DOI:\href{http://doi.org/10.1090/conm/342/06138}{10.1090/conm/342/06138}.

In addition, the program stores the number of halving-lines
in the global variable |num_halving_lines|. % (This is not the cleanest way to do it.)

@<Subr...@>+=
int count_crossings(int n)
{
	int line_at[MAXN+1];
	int next_crossing[MAXN+1];
	int num_crossings_on_level[MAXN+1];
 for_int_from_to(i, 0,n) { /* Initialize: */
   line_at[i] = i;
    /* which line is on the $i$-th track, $1\le i\le n$.
 Tracks are numbered $p=1\ldots n$ from top to bottom. */
   next_crossing[i] = SUCC(i,0);
    /* current crossing on each line; the first crossing with line 0 ``at $\infty$'' is counted separately: */
   num_crossings_on_level[i]=1; // The initial value counts the crossing with line 0
}

next_crossing[0] = 1; /* sentinel values to ensure that the loop breaks at $p=0$ */

int p = n;
while(true) { /* Main loop */
/* Invariant throughout: The lines at levels $p+1,\ldots,n$ want to cross \emph{upwards} (or are finished.) */

while ( next_crossing[p]<line_at[p]) p--; // |while p| wants to cross upwards
if(p==0) break;
do {
 /* The line |i == line_at[p]| on track |p| wants to cross down and the line |j == line_at[p+1]|
 on track |p+1| wants to cross up. 
 (In this case, we must actually have |next_crossing[i]==j| and
|next_crossing[j]==i|.) */
@/
num_crossings_on_level[p]++;
@#@t\hskip-2em @>//    update the data structures to CARRY OUT the crossing $p\leftrightarrow p+1$:
        int i = line_at[p];
        int j = line_at[p+1];
	int temp = SUCC(i,next_crossing[p]);
	next_crossing[p] = SUCC(j,next_crossing[p+1]);
        next_crossing[p+1] = temp;
        line_at[p] = j;
        line_at[p+1] = i;
	@#
	p++;
}
while( next_crossing[p]>line_at[p]);  // |while p| wants to cross downwards
p-=2; // We need not check $p-1$, because this would be an immediate back-crossing at the same level.
}

   @#@t\hskip-3em @>
   // Number of halving-lines is stored in the global variable |num_halving_lines|:

if (n%2) 
/* |n| odd, number of points even: */
   num_halving_lines = num_crossings_on_level[(n+1)/2];
else
/* |n| even, number of points odd: */
   num_halving_lines = num_crossings_on_level[n/2]
   +num_crossings_on_level[n/2+1];

   @#@t\hskip-3em @>
   /* compute crossing number according to the formula: */
int crossing_formula = -(n+1)*n*(n-1)/2;

for_int_from_to(p,1,n)
   crossing_formula += num_crossings_on_level[p]*(n+1-2*p)*(n+1-2*p);




@qprint_wiring_diagram(n); @>
@qfor_int_from_to(p, 0,n-1) printf("%d ",num_crossings_on_level[p]);@>
@qprintf("%d\n", crossing_formula);@>
@qprintf("n=%d, %d %d\n", n, crossing_formula, num_halving_lines);@>

return crossing_formula/4;

}

@z

@x
\tableofcontents
@y
@z
