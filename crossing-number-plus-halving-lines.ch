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

@d MAXN 11 /* The maximum number of pseudolines for which the program will work. */
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
int num_halving_lines; // global variable; this is not clean

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
$n=12$ points (the maximum that the program is set up
to deal with), has at most 18 halving-lines.
According to  S. Bereg and M. Haghpanah,
New algorithms and bounds for halving pseudolines,
Discrete Applied Mathematics 319 (2022) 194--206, \url{https://doi.org/10.1016/j.dam.2021.05.029},
Table 1 on p.~196,
the number of halving lines-with for odd numbers $n$ of points
are nearly $70\,\%$ higher than for the adjacent even values.
I could not find the bounds for small odd $n$ in the literature.
%With a bound of 50 we should be on the safe side.
After running the program once with a larger safety margin,
it was found that
a set with $n=11$ points has at most 24 halving-lines.
(The program checks if the bound is not violated.)
@d MAX_HALVING_LINES 24


@d MAX_CROSSINGS (MAXN+1)*MAXN*(MAXN-1)*(MAXN-2)/24
 /* crossing-number goes up to $\binom n4$ for $n$ points */

@ How to check for a crossing.

This algorithm is like the program for drawing the wiring diagram,
except that it does not draw anything.


The program computes the number of crossings
|num_crossings_on_level[p]|
at
each level |p| including the crossings with line 0.
A crossing at level |p| is a crossings between
consecutive tracks  |p| and $p+1$, $0\le p \le n-1$.

From this information, there is an easy formula to compute the crossing number
of the complete graph $K_n$ when it is drawn on this point set,
see Lov\'{a}sz, Vesztergombi, Wagner, and Welzl, \emph{Convex quadrilaterals and
  $k$-sets}, 
DOI:\href{http://doi.org/10.1090/conm/342/06138}{10.1090/conm/342/06138}.

@d CHECK_CROSSING(p) {{
        int i = line_at[p];
        int j = line_at[p+1];
 if (i<j && next_crossing[i]>i && next_crossing[j]<j
 && next_crossing[j]!=0) 
    /* Line i wants to cross down and line j wants to cross up. */
/*     (In this case, we must actually have |next_crossing[i]==j| and |next_crossing[j]==i|.) */
         crossings[num_crossings++] = p;
	 /* The value |p| indicates a crossing between tracks |p| and $p+1$. */
}}

@<Subr...@>+=
int count_crossings(int n)
{
	int next_crossing[MAXN+1];
	int line_at[MAXN+1];
	int num_crossings_on_level[MAXN-1];
	int crossings[MAXN]; /* stack */
	int num_crossings=0;

/* Initialize */
 for_int_from_to(i, 1,n) {
    next_crossing[i] = SUCC(i,0);
    /* current crossing on each line;
The first crossing with line 0 ``at $\infty$'' is not considered. */
    line_at[i-1] = i;
    /* which line is on the $p$-th track, $0\le p<n$.
 tracks are numbered $p=0\ldots n-1$ from top to bottom. */
}

 for_int_from_to(p, 0,n-1)
num_crossings_on_level[p]=1; // counting the crossing with line 0
@/

/* maintain a stack |crossings| of available crossings.
 $p\in$ crossings means that tracks $p$ and $p+1$ are ready to cross */
 
 for_int_from_to(p, 0,n-2) 
	CHECK_CROSSING(p)@;@/


while(num_crossings) { /* Main loop */

     int    p = crossings[--num_crossings];
num_crossings_on_level[p]++;

//    update the data structures to CARRY OUT the crossing
        int i = line_at[p];
        int j = line_at[p+1];
        next_crossing[i] = SUCC(i,next_crossing[i]);
        next_crossing[j] = SUCC(j,next_crossing[j]);
        line_at[p] = j;
        line_at[p+1] = i;

// Look for new crossings:
if(p>0)
	CHECK_CROSSING(p-1)@;
if(p<n-1)
	CHECK_CROSSING(p+1)@;

}
@/
/* compute result */


int crossing_formula = -(n+1)*n*(n-1)/2;
for_int_from_to(p,0,n-1)
   crossing_formula += num_crossings_on_level[p]*(n-1-2*p)*(n-1-2*p);


// global variable |num_halving_lines| is set.

if (n%2) 
/* |n| odd, number of points even: */
   num_halving_lines = num_crossings_on_level[(n-1)/2];
else
/* |n| even, number of points odd: */
   num_halving_lines = num_crossings_on_level[n/2]
   +num_crossings_on_level[n/2-1];



@qprint_wiring_diagram(n); @>
@qfor_int_from_to(p, 0,n-1) printf("%d ",num_crossings_on_level[p]);@>
@qprintf("%d\n", crossing_formula);@>

return crossing_formula/4;

}

@z

@x
\tableofcontents
@y
@z
