Change file for counting halving-lines


@x statistics array:
long long unsigned classcount[MAXN+2][MAXN+2][MAXN+2][3];
@y
long long unsigned classcount[MAXN+2][MAXN+2][MAXN+2][3][MAX_HALVING_LINES+1];
@z

@x updating the statistics
  classcount[n_points][hullsize][rotation_period][
  !is_symmetric? NO_MIRROR : has_fixpoint ? MIRROR_WITH_FIXPOINT :
  MIRROR_WITHOUT_FIXPOINT] ++;
@y
  int num_halving = count_halving_lines(n);
  assert (num_halving <= MAX_HALVING_LINES);
  classcount[n_points][hullsize][rotation_period][
  !is_symmetric? NO_MIRROR : has_fixpoint ? MIRROR_WITH_FIXPOINT :
  MIRROR_WITHOUT_FIXPOINT][num_halving] ++;
@z

@x
  fprintf(reportfile,"\n#x N hull period mirror-type  NUM\n");
@y  
  fprintf(reportfile,"\n#x N hull period mirror-type halving-lines  NUM\n");
@z  

@x statistics reporting:
    for(small_int t=0; t<3; t++)
      if (classcount[n][k][p][t])
  fprintf(reportfile,
     "%c %d %d %d %d  %Ld\n", c,n,k,p,t,  classcount[n][k][p][t]);
}
@y     
    for_int_from_to(t,0,2)
    for_int_from_to(h,0,MAX_HALVING_LINES)
      if (classcount[n][k][p][t][h])
  fprintf(reportfile,
     "%c %d %d %d %d %d  %Ld\n", c,n,k,p,t,h,  classcount[n][k][p][t][h]);
}
@z

========= Here comes the computation of halving-lines
not sure where this is supposed to go

@<Global...@>+= .......

@x Here comes the computation of halving-lines
@i readDataBase
@y

@* Count halving-lines.
@*1 Extension. Count halving-lines for each AOT.

$n=16$ has at most 27 halving-lines.

odd ones are nearly $70\,\%$ higher than even ones.

... on the safe side ...

@d MAX_HALVING_LINES 50

@ How to check for a crossing.

... some text ...

consecutive tracks  |p| and $p+1$. */

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
int count_halving_lines(int n)
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
num_crossings_on_level[p]=0;@;

/* maintain a stack |crossings| of available crossings.
 $p\in$ crossings means that tracks $p$ and $p+1$ are ready to cross */
 
 for_int_from_to(p, 0,n-2) 
	CHECK_CROSSING(p)


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
	CHECK_CROSSING(p-1)
if(p<=n-2)
	CHECK_CROSSING(p+1)

}

/* compute result */

@q print_wiring_diagram(n); @>
@q for_int_from_to(p, 0,n-2) printf("%d ",num_crossings_on_level[p]); printf("\n"); @>

if (n%2) 
/* |n| odd, number of points even: */
   return 1+num_crossings_on_level[(n-1)/2];
else
/* |n| even, number of points odd: */
   return 2+num_crossings_on_level[n/2]
   +num_crossings_on_level[n/2-1];
}

@i readDataBase
@z
