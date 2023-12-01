benchmark:
Read all point sets from the order-type database, and
compute the number of hull points.

@x
@d readdatabase 0 // version for reading point sets of the order-type database
@y
@d readdatabase 1 // version for reading point sets of the order-type database
@z


@x
@*3 Orientation test for points.
@y
long long unsigned nums[MAXN+1];

@*3 Orientation test for points.
@z

@x
@<Subro...@>=  
long long unsigned read_count = 0;@/
@y

@<Subr...@>=  
int stack[MAXN+1]; @/

int hull_size(int n_points)
{
  stack[0]=0;
  stack[1]=1;
  stack[2]=2;
  int top=2;
  for (int i=3; i<n_points; i++)
    {
      while (orientation_test(stack[top-1],stack[top], i)>0)
        top--;
      stack[++top] = i;
    }
  return top+1;
}

long long unsigned read_count = 0;@/
@z

@x
      int n= n_points-1;
      PSLA_from_points(n_points);
      small_int hulledges[MAXN+1];
      small_int hullsize = upper_hull_PSLA(n, hulledges);
      PSLA P;
      compute_lex_smallest_PSLA(&P, n, hulledges, hullsize);
      compute_fingerprint(&P,n);
      printf("%s:\n",fingerprint);
    }
  close(databasefile);
@y
      int h = hull_size(n_points);
      nums[h]++;
    }
  close(databasefile);
 @q printf("%Ld point sets.\n",counter); @>
  for(int i=0; i<=n_points; i++)
    if(nums[i]) printf("%2d: %10Ld\n",i,nums[i]);
@z