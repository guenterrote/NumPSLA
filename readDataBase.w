@* Reading from the Order-Type Database.

For simplicity,
we work only with numbers in the 16-bit format.
Inputs in 8-bit formats are converted.

@<Global...@>=
struct { /* 16-bit unsigned coordinates: */
uint16_t x,y; } points[MAXN+1];
struct { /* 8-bit unsigned coordinates: */
uint8_t x,y; } pointsmall[MAXN+1];


@*1 Orientation test for points.

The return value of |orientation_test| is positive for counterclockwise orientation
of the points $i,j,k$.

@<Subr...@>=
large_int orientation_test(int i,int j,int k)
{
  large_int a=points[j].x-(large_int)points[i].x; /* range $-65535\dts 65535$ */
  large_int b=points[j].y-(large_int)points[i].y;
  large_int c=points[k].x-(large_int)points[i].x;
  large_int d=points[k].y-(large_int)points[i].y;
  return a*d-b*c;
}
@ Intermediate results can be almost $2^{32}$ in absolute value,
     and they have signs.
The final value is the signed area of the parallelogram spanned by 3 points.
Thus it can also be almost $2^{32}$ in absolute value.
32 bits are not enough to be safe. We use 64 bits.

@s  large_int int

@<Type...@>=
typedef int_least64_t large_int; /* for intermediate calculations */



@*1 Turn point set with coordinates into PSLA.

We insert the lines one by one into the arrangement.  This is similar
to the insertion of line $n$ in the recursive enumeration procedure
|recursive_generate_PSLA| of Section~\ref{recursive-enumeration}.
The difference is that we don't try all possibilities for the edge
through which line $n$ exits, but we choose the correct edge the
by orientation test.
By the zone theorem, the insertion of line $n$ takes $O(n)$ time.

We have $n$ points. The first point (point $0$) is on the convex hull and the
other points are sorted around this point.
We get a PSLA with $n-1$ pseudolines, which correspond to points $1,\ldots,n-1$ in the order in which they are given.


@<Subr...@>=
void insert_line(int n);


  void PSLA_from_points(int n)
{
  LINK(1,@,@,0,2);
  LINK(1,@,@,2,0);
  LINK(2,@,@,0,1);
  LINK(2,@,@,1,0);
LINK(0,@,@,1,2); /* |LINK(0,@,@,2,3)| and |LINK(0,@,@,3,1)| will be established
shortly in the first recursive call. */
 for_int_from_to(i,3,n-1)
   insert_line(i);
}


void insert_line(int n)
{ LINK(0,@,@,n-1,n);
  LINK(0,@,@,n,1);
  int entering_edge = 0, j=0, jplus = 0;
  int k_left,  k_right;
  while(1)
    {
      while(jplus>j)
	{ // find right vertex of the cell
	  int jplusold = jplus;
	  jplus = SUCC(jplus,j);
	  j = jplusold;
	}
      if (jplus==0) { // $F$ is unbounded
	if (j==n-1 )
	  { // $F$ is the top face.
	    LINK(n,@,@,entering_edge,0);    /* complete the insertion of line $n$ */
	    return;
	  }
	jplus=j+1; /* jump to the upper ray of $F$ */
	j = 0;
      }
	/* Now the crossing |j|$\times$|jplus| is the rightmost vertex
	   of the face $F$.
	   |jplus| is on the upper side, and if $F$ is bounded,
	   $j$ is on the lower side,  */
      do
	{ /* scan the upper edges of $F$ from right
	     to left and find the correct one to cross. */
	  k_right = j;
	  j = jplus;
	  k_left = jplus = PRED(j,k_right);
	}
      while (jplus>j && orientation_test(j,k_left,n)>0);
	  
      LINK(j,@,@,k_left,n); // insert crossing with $n$ on line $j$
      LINK(j,@,@,n,k_right);

      LINK(n,@,@,entering_edge,j);
@#
      entering_edge = j;
      jplus = k_right;
    }
}

@*1 Select the order-type files to be read.

We have to figure out the filenames and the format of the stored numbers.
We assume that the order types with up to 10 points are stored in the
current directory in with the original file names
\texttt{otypes10.b16}, \texttt{otypes09.b16}, \texttt{otypes08.b08},
etc., and the order types with 11 points are stored in a subdirectory
\texttt{Ordertypes} with names \texttt{Ordertypes/ord11\_00.b16} \ldots
\texttt{Ordertypes/ord11\_93.b16}.

@<Include standard libaries@>+=
#include <fcntl.h>
#include <unistd.h>

@
@<Subr...@>=

void swap_all_bytes(int n)
{ // convert numbers from little-endian to big-endian format.
  for_int_from_to(i,0,n-1)
    {
      points[i].x = (points[i].x>>8) | (points[i].x<<8);
      points[i].y = (points[i].y>>8) | (points[i].y<<8);
      /* Assumes 16 bits. It is important that coordinates are \emph{unsigned}. */
    }
}
  
@
@<Read all point sets of size |n_max+1| from the database and process them@>=
int  n_points = n_max+1;
  int bits = n_points >=9 ? 16 : 8;

  char inputfile [60];
  int record_size = (bits/8)*2*n_points;
  printf("Reading order types of %d points\n", n_points);
  printf(".\n");
  printf("One record is %d bytes long.\n", record_size); @/
  boolean is_big_endian = (*(uint16_t *)"\0\xff" < 0x100);
  if (bits>8) {
  if (is_big_endian)
      printf("This computer is big-endian.\n");
  else
      printf("This computer is little-endian. No byte swaps are necessary.\n");
  }     

  if (n_points<11) {
    snprintf(inputfile, 60, "otypes%02d.b%02d",n_points,bits);
     read_database_file(inputfile, bits, record_size, n_points,  is_big_endian);
    }
  else
    for_int_from_to(num_db, 0, 93) {
      snprintf(inputfile, 60, "Ordertypes/ord%02d_%02d.b16",
        n_points, num_db);
     read_database_file(inputfile, bits, record_size, n_points,  is_big_endian);
}
  printf("%Ld point sets were read from the file(s).\n",read_count);


@*1 Do the actual reading.
 Open and read database file and process the input points.
@<Subro...@>=
long long unsigned read_count = 0;@/

void read_database_file(char *inputfile, int bits, int record_size,
 int n_points, boolean is_big_endian
) {
    printf("Reading from file %s\n", inputfile);
    int databasefile = open(inputfile,O_RDONLY);
  if(databasefile == -1)
    {
      printf("File could not be opened.\n");
      exit(1);
    }

  while (1)
    {
      ssize_t bytes_read;
      if (bits==16)
	bytes_read = read(databasefile, &points, record_size);
      else
	bytes_read = read(databasefile, &pointsmall, record_size);
     
      if(bytes_read==0) break;
      if(bytes_read!=record_size) { printf("Incomplete file.\n"); exit(1); }
      read_count++;
      if (bits==16 && is_big_endian) swap_all_bytes(n_points);
      if (bits==8)
	for_int_from_to(i,0,n_points-1)
	  {
	    points[i].x = pointsmall[i].x;
	    points[i].y = pointsmall[i].y;
	  }
      int n= n_points-1;
      PSLA_from_points(n_points);
      int hulledges[MAXN+1];
      int hullsize = upper_hull_PSLA(n, hulledges);
      P_matrix P;
      compute_lex_smallest_P_matrix(&P, n, hulledges, hullsize);
      compute_fingerprint(&P,n);
      printf("%s:\n",fingerprint);
    }
  close(databasefile);
}

@q print_wiring_diagram(n);@>
