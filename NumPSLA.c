#define SUCC(i,j) succ[i][j]
#define PRED(i,j) pred[i][j] \

#define LINK(j,k1,k2) { \
SUCC(j,k1) = k2; \
PRED(j,k2) = k1; \
} \
 \

#define MAXN 15 \
 \

#define enumAOT 1 \

#define readdatabase 0
#define generatelist 0 \

#define profile 1 \
 \

#define for_int_from_to(x,first,last) for(int x= first;x<=last;x++)  \
 \

#define PRINT_INSTRUCTIONS printf( \
"Usage: %s n [-exclude excludefile] [splitlevel parts part] [fileprefix]\n",argv[0]) ; \

#define getOrientation_explicit(PaInverse,i,j,k) ( \
i<j&&j<k?PaInverse[i][j]> PaInverse[i][k]: \
i<k&&k<j?PaInverse[i][j]> PaInverse[i][k]: \
j<i&&i<k?PaInverse[i][j]<PaInverse[i][k]: \
j<k&&k<i?PaInverse[i][j]> PaInverse[i][k]: \
k<j&&j<i?PaInverse[i][j]> PaInverse[i][k]: \
k<i&&i<j?PaInverse[i][j]<PaInverse[i][k]: \
0)  \

#define getOrientation(PaInverse,i,j,k) ((i<j) ^(j<k) ^(PaInverse[j][i]> PaInverse[j][k]) )  \
 \
 \

#define TO_CHAR(i) ((char) ( \
(i<10?(int) '0':((int) 'A'-10) )  \
+i) )  \

#define FINGERPRINT_LENGTH 30 \
 \

#define NO_MIRROR 0
#define MIRROR_WITH_FIXED_VERTEX 1
#define MIRROR_WITHOUT_FIXED_VERTEX 2 \

#define entry_small(A,i,j) (A) [i][j] \
 \

/*6:*/
#line 355 "NumPSLA.w"



/*10:*/
#line 426 "NumPSLA.w"

#include <stdio.h> 
#include <stdint.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 


/*:10*//*75:*/
#line 128 "readDataBase.w"

#include <fcntl.h> 
#include <unistd.h> 

/*:75*/
#line 358 "NumPSLA.w"

/*4:*/
#line 296 "NumPSLA.w"

typedef int P_matrix[MAXN+1][MAXN+1];

/*:4*//*9:*/
#line 419 "NumPSLA.w"


typedef enum{false,true}boolean;



/*:9*//*67:*/
#line 2345 "NumPSLA.w"






typedef boolean large_matrix_entry;
typedef unsigned small_matrix_entry;



typedef small_matrix_entry small_lambda_matrix[MAXN+1][MAXN+1];
typedef large_matrix_entry large_Lambda_matrix[MAXN+1][MAXN+1][MAXN+1];



/*:67*//*73:*/
#line 36 "readDataBase.w"

typedef int_least64_t large_int;



/*:73*/
#line 359 "NumPSLA.w"

/*5:*/
#line 340 "NumPSLA.w"

int succ[MAXN+1][MAXN+1];
int pred[MAXN+1][MAXN+1];


/*:5*//*12:*/
#line 459 "NumPSLA.w"

int n_max,split_level= 0;
unsigned int parts= 1000,part= 0;
char*fileprefix= "reportPSLA";
char*exclude_file_name= 0;
char fname[200]= "";
FILE*reportfile= 0;

/*:12*//*20:*/
#line 726 "NumPSLA.w"

unsigned excluded_code[MAXN+3];
int excluded_length= 0;
int matched_length= 0;

FILE*exclude_file;
char exclude_file_line[100];

/*:20*//*39:*/
#line 1322 "NumPSLA.w"



int Sequence[MAXN+1][MAXN+1];

int new_label[MAXN+1][MAXN+1];



int candidate[2*(MAXN+1)];

int current_crossing[2*(MAXN+1)];


int P_1_n_forward[MAXN+1];
int P_1_n_reverse[MAXN+1];


/*:39*//*50:*/
#line 1948 "NumPSLA.w"


long long unsigned cpass,csaved;




/*:50*//*51:*/
#line 1982 "NumPSLA.w"


long long unsigned countPSLA[MAXN+2],countO[MAXN+2],countU[MAXN+2];

long long unsigned PSLAcount[MAXN+2];





long long unsigned U_PSLAcount[MAXN+2];
long long unsigned classcount[MAXN+2][MAXN+2][MAXN+2][3];



long long unsigned
numComparisons= 0,numTests= 0;

/*:51*//*71:*/
#line 7 "readDataBase.w"

struct{
uint16_t x,y;}points[MAXN+1];
struct{
uint8_t x,y;}pointsmall[MAXN+1];


/*:71*/
#line 360 "NumPSLA.w"

/*27:*/
#line 803 "NumPSLA.w"


void convert_to_P_matrix(P_matrix*P,int n)
{
int j= 1;
for_int_from_to(i,0,n)
{
for_int_from_to(p,0,n-1)
{
(*P)[i][p]= j;
j= SUCC(i,j);
}
j= 0;
}
}

/*:27*//*28:*/
#line 841 "NumPSLA.w"


void convert_to_inverse_P_matrix(P_matrix*PaInverse,int n)
{
int j= 1;
for_int_from_to(i,0,n)
{
for_int_from_to(p,0,n-1)
{
(*PaInverse)[i][j]= p;
j= SUCC(i,j);
}
j= 0;
}
}


/*:28*//*30:*/
#line 932 "NumPSLA.w"


int upper_hull_PSLA(int n,
int*hulledges)
{
hulledges[0]= 0;
int hullsize= 1;
int k= 0,k_left,k_right= 1;
do
{
k_left= k;
k= k_right;
k_right= SUCC(k,k_left);

hulledges[hullsize++]= k;
}
while(k_right!=0);

return hullsize;

}

/*:30*//*31:*/
#line 979 "NumPSLA.w"

unsigned localCountPSLA[MAXN+3];

void print_id(int n)
{
printf("%d",localCountPSLA[3]);
for_int_from_to(i,4,n)
printf(".%d",localCountPSLA[i]);
}

/*:31*//*33:*/
#line 1000 "NumPSLA.w"



void print_wiring_diagram(int n)
{
int next_crossing[MAXN+1];
int line_at[MAXN];
boolean crossing[MAXN-1];


char buffer_line[2*MAXN-1][MAXN*MAXN];


for_int_from_to(j,0,n-1){
line_at[j]= j+1;
next_crossing[j+1]= SUCC(j+1,0);

}
int num_crossings= 0;
int column= 0;

for_int_from_to(p,0,2*n-2)buffer_line[p][column]= ' ';
for(column= 1;;column++)
{
for_int_from_to(p,0,n-1)
buffer_line[2*p][column]= TO_CHAR(line_at[p]);
for_int_from_to(p,0,n-2)
buffer_line[2*p+1][column]= ' ';


column++;



boolean something_to_do= false;
for_int_from_to(p,0,n-2)
{
int i= line_at[p];
int j= line_at[p+1];
crossing[p]= next_crossing[i]==j&&next_crossing[j]==i;
if(crossing[p])
something_to_do= true;
}
if(!something_to_do)break;
for_int_from_to(p,0,n-1)
buffer_line[2*p][column]= '-';


for_int_from_to(p,0,n-2)
if(crossing[p]){
num_crossings++;
buffer_line[2*p+1][column]= 'X';
buffer_line[2*p][column]= 
buffer_line[2*p+2][column]= ' ';




int i= line_at[p];
int j= line_at[p+1];
next_crossing[i]= SUCC(i,next_crossing[i]);
next_crossing[j]= SUCC(j,next_crossing[j]);
line_at[p]= j;
line_at[p+1]= i;
}
else buffer_line[2*p+1][column]= ' ';
}
for_int_from_to(p,0,2*n-2){
buffer_line[p][column]= 0;
printf("%s\n",buffer_line[p]);
}
assert(num_crossings==n*(n-1)/2);
}

/*:33*//*34:*/
#line 1084 "NumPSLA.w"


void print_pseudolines_short(P_matrix*P,int n)
{
printf("P");
for_int_from_to(i,0,n)
{
printf("!");
for_int_from_to(j,0,n-1)
printf("%c",TO_CHAR((*P)[i][j]));
}
printf("\n");
}

void print_pseudolines_compact(P_matrix*P,int n)
{
for_int_from_to(i,1,n)
{
if(i> 1)printf("!");
for_int_from_to(j,1,n-2)
printf("%c",TO_CHAR((*P)[i][j]));
}
}

/*:34*//*35:*/
#line 1163 "NumPSLA.w"

char fingerprint[FINGERPRINT_LENGTH];

char encode_bits(int acc)
{
if(acc<26)
return(char)(acc+(int)'A');
else if(acc<52)
return(char)(acc-26+(int)'a');
else if(acc<62)
return(char)(acc-52+(int)'0');
else if(acc==62)
return'+';
else
return'-';
}

void compute_fingerprint(P_matrix*P,int n){

int charpos= 0;
int bit_num= 0;
int acc= 0;
for_int_from_to(i,1,n-1)
for_int_from_to(j,1,n-1)
{acc<<= 1;
if((*P)[i][j]<i)acc|= 1;
bit_num+= 1;
if(bit_num==6){
fingerprint[charpos++]= encode_bits(acc);
assert(charpos<FINGERPRINT_LENGTH-1);
bit_num= acc= 0;
}
}
if(bit_num)
fingerprint[charpos++]= encode_bits(acc<<(6-bit_num));
assert(charpos<FINGERPRINT_LENGTH-1);
fingerprint[charpos]= '\0';
}

/*:35*//*38:*/
#line 1251 "NumPSLA.w"


void compute_new_P_matrix(P_matrix*P,int n,int line0,
int right_vertex,boolean reversed)
{
int Sequence[MAXN+1];


int new_label[MAXN+1];





new_label[line0]= 0;
int i= right_vertex;
for_int_from_to(p,1,n)
{
new_label[i]= p;
Sequence[p]= i;
i= SUCC(line0,i);
}


for_int_from_to(q,0,n-1)(*P)[0][q]= q+1;
for_int_from_to(p,1,n)
{
int pos= reversed?n+1-p:p;
(*P)[p][0]= 0;
int i= Sequence[pos];

int j= line0;



for_int_from_to(q,1,n-1)
{
j= reversed?SUCC(i,j):PRED(i,j);
(*P)[p][n-q]= new_label[j];
}
}
}


/*:38*//*40:*/
#line 1343 "NumPSLA.w"


void prepare_label_arrays(int n,
int*hulledges,int hullsize,boolean compute_all)
{
for_int_from_to(r,0,hullsize-1)
if(compute_all||P_1_n_reverse[r]==P_1_n_forward[0]||
(r> 0&&P_1_n_forward[r]==P_1_n_forward[0]))
{
int line0= hulledges[r];



new_label[r][line0]= 0;
int i= (r<hullsize-1)?hulledges[r+1]:0;
for_int_from_to(p,1,n)
{
new_label[r][i]= p;
Sequence[r][p]= i;
i= SUCC(line0,i);
}
}
}



/*:40*//*41:*/
#line 1403 "NumPSLA.w"

void compute_lex_smallest_P_matrix(P_matrix*P,int n,
int*hulledges,int hullsize)
{

for_int_from_to(q,0,n-1)(*P)[0][q]= q+1;

prepare_label_arrays(n,hulledges,hullsize,true);

int numcandidates= 0;
for_int_from_to(r,0,hullsize-1)

candidate[numcandidates++]= r;
int numcandidates_forward= numcandidates;
for_int_from_to(r,0,hullsize-1)

candidate[numcandidates++]= r;

for_int_from_to(p,1,n)
{
(*P)[p][0]= 0;
for_int_from_to(c,0,numcandidates-1)
{
int r= candidate[c];
current_crossing[c]= hulledges[r];
}

for_int_from_to(q,1,n-1){
int c;
int new_candidates,new_candidates_forward;
int current_min= n+1;
boolean reversed= false;
int pos= p;

for(c= 0;c<numcandidates_forward;c++)
{
/*42:*/
#line 1464 "NumPSLA.w"

int r= candidate[c];
int i= Sequence[r][pos];
int j= current_crossing[c];
j= reversed?SUCC(i,j):PRED(i,j);
int a= new_label[r][j];
if(reversed&&a!=0)
a= n+1-a;
if(a<current_min)
{
new_candidates= new_candidates_forward= 0;
current_min= a;
}
if(a==current_min)
{
candidate[new_candidates]= r;
current_crossing[new_candidates]= j;
new_candidates++;
}



/*:42*/
#line 1440 "NumPSLA.w"

}
new_candidates_forward= new_candidates;


reversed= true;
pos= n+1-p;
for(;c<numcandidates;c++)
{
/*42:*/
#line 1464 "NumPSLA.w"

int r= candidate[c];
int i= Sequence[r][pos];
int j= current_crossing[c];
j= reversed?SUCC(i,j):PRED(i,j);
int a= new_label[r][j];
if(reversed&&a!=0)
a= n+1-a;
if(a<current_min)
{
new_candidates= new_candidates_forward= 0;
current_min= a;
}
if(a==current_min)
{
candidate[new_candidates]= r;
current_crossing[new_candidates]= j;
new_candidates++;
}



/*:42*/
#line 1450 "NumPSLA.w"

}
numcandidates_forward= new_candidates_forward;
numcandidates= new_candidates;
(*P)[p][n-q]= current_min;

}
}
}
/*:41*//*43:*/
#line 1500 "NumPSLA.w"


/*47:*/
#line 1790 "NumPSLA.w"

boolean screen(int n,
int*hulledges,int hullsize)
{



P_1_n_forward[0]= PRED(1,0);
for_int_from_to(r,1,hullsize-1)
{
int r_next= (r+1)%hullsize;
int i= hulledges[r];
int j= hulledges[r_next];
int iprime= PRED(j,i);

int a= 2;
int j2= SUCC(i,j);
while(j2!=iprime)
{
j2= SUCC(i,j2);a++;
if(a> P_1_n_forward[0])break;
}
if(a<P_1_n_forward[0])return false;
P_1_n_forward[r]= a;



}

for_int_from_to(r,0,hullsize-1)
{
int r_next= (r+1)%hullsize;
if(P_1_n_forward[r]==2)
{
P_1_n_reverse[r_next]= 2;



continue;
}
int i= hulledges[r];
int j= hulledges[r_next];
int jprime= SUCC(i,j);
int a= 2;
int i2= PRED(j,i);
do{
i2= PRED(j,i2);a++;
if(a> P_1_n_forward[0])break;
}
while(i2!=jprime);
if(a<P_1_n_forward[0])return false;
P_1_n_reverse[r_next]= a;
}

return true;
}


/*:47*/
#line 1502 "NumPSLA.w"


boolean is_lex_smallest_P_matrix(int n,
int*hulledges,int hullsize,int*
rotation_period,boolean*has_mirror_symmetry,boolean*has_fixed_vertex)
{
if(!screen(n,hulledges,hullsize))
return false;

#if profile
numTests++;
#endif


prepare_label_arrays(n,hulledges,hullsize,false);

int numcandidates= 0;
for_int_from_to(r,1,hullsize-1)
if(P_1_n_forward[r]==P_1_n_forward[0])
candidate[numcandidates++]= r;
int numcandidates_forward= numcandidates;
for_int_from_to(r,0,hullsize-1)
if(P_1_n_reverse[r]==P_1_n_forward[0])
candidate[numcandidates++]= r;

for_int_from_to(p,1,n)
{
int current_crossing_0= 0;
for_int_from_to(c,0,numcandidates-1)
{
int r= candidate[c];




current_crossing[c]= hulledges[r];


}

for_int_from_to(q,1,n-2)
{





int target_value= current_crossing_0= 
PRED(p,current_crossing_0);


int c;
int new_candidates= 0;

boolean reversed= false;
int pos= p;
for(c= 0;c<numcandidates_forward;c++)
{
/*44:*/
#line 1597 "NumPSLA.w"


#if profile
numComparisons++;
#endif
int r= candidate[c];
int i= Sequence[r][pos];

int j= current_crossing[c];

j= reversed?SUCC(i,j):PRED(i,j);
int a= new_label[r][j];
if(reversed&&a!=0)
a= n+1-a;



if(a<target_value)

return false;

if(a==target_value)
{

candidate[new_candidates]= r;

current_crossing[new_candidates]= j;
new_candidates++;
}




/*:44*/
#line 1562 "NumPSLA.w"

}
numcandidates_forward= new_candidates;


reversed= true;
pos= n+1-p;
for(;c<numcandidates;c++)
{
/*44:*/
#line 1597 "NumPSLA.w"


#if profile
numComparisons++;
#endif
int r= candidate[c];
int i= Sequence[r][pos];

int j= current_crossing[c];

j= reversed?SUCC(i,j):PRED(i,j);
int a= new_label[r][j];
if(reversed&&a!=0)
a= n+1-a;



if(a<target_value)

return false;

if(a==target_value)
{

candidate[new_candidates]= r;

current_crossing[new_candidates]= j;
new_candidates++;
}




/*:44*/
#line 1572 "NumPSLA.w"

}
numcandidates= new_candidates;

if(numcandidates==0)
{
*rotation_period= hullsize;
*has_mirror_symmetry= false;
return true;
}
}
}
/*45:*/
#line 1633 "NumPSLA.w"

{
if(numcandidates_forward> 0)
*rotation_period= candidate[0];
else
*rotation_period= hullsize;
*has_mirror_symmetry= numcandidates> numcandidates_forward;
if(*has_mirror_symmetry){
int symmetric_shift= candidate[numcandidates_forward];

*has_fixed_vertex= ((*rotation_period)%2==1)||(symmetric_shift%2==0);
}
}


/*:45*/
#line 1584 "NumPSLA.w"


return true;
}

/*:43*//*68:*/
#line 2370 "NumPSLA.w"



void convert_to_small_lambda_matrix(small_lambda_matrix*B,int n)
{
for_int_from_to(i,0,n)
{
(*B)[i][i]= 0;
}
for_int_from_to(i,1,n)
{
int level= i-1;
(*B)[0][i]= level;
(*B)[i][0]= n-1-level;
int j= SUCC(i,0);
while(j!=0)
{
if(i<j)
{
(*B)[i][j]= level;
level++;}
else{level--;
(*B)[i][j]= n-1-
level;

}
j= SUCC(i,j);
}
}
}

/*:68*//*70:*/
#line 2425 "NumPSLA.w"


void copy_small(small_lambda_matrix*A,small_lambda_matrix*B,int n)
{
for_int_from_to(i,0,n-1)
for_int_from_to(j,0,n-1)
entry_small(*B,i,j)= entry_small(*A,i,j);
}

void convert_small_to_large(small_lambda_matrix*A,large_Lambda_matrix*B,
int n)
{
small_lambda_matrix Temp;
copy_small(A,&Temp,n);
for_int_from_to(k,0,n-1)
for_int_from_to(i,k+1,n-1)
for_int_from_to(j,i+1,n-1)
{
boolean plus= entry_small(Temp,i,k)<entry_small(Temp,j,k);
(*B)[k][i][j]= (*B)[i][j][k]= (*B)[j][k][i]= plus;
(*B)[k][j][i]= (*B)[i][k][j]= (*B)[j][i][k]= !plus;
if(plus)
entry_small(Temp,i,j)--;
else
entry_small(Temp,j,i)--;
}
}



#line 1 "readDataBase.w"
/*:70*//*72:*/
#line 19 "readDataBase.w"

large_int orientation_test(int i,int j,int k)
{
large_int a= points[j].x-(large_int)points[i].x;
large_int b= points[j].y-(large_int)points[i].y;
large_int c= points[k].x-(large_int)points[i].x;
large_int d= points[k].y-(large_int)points[i].y;
return a*d-b*c;
}
/*:72*//*74:*/
#line 56 "readDataBase.w"

void insert_line(int n);


void PSLA_from_points(int n)
{
LINK(1,0,2);
LINK(1,2,0);
LINK(2,0,1);
LINK(2,1,0);
LINK(0,1,2);

for_int_from_to(i,3,n-1)
insert_line(i);
}


void insert_line(int n)
{LINK(0,n-1,n);
LINK(0,n,1);
int entering_edge= 0,j= 0,jplus= 0;
int k_left,k_right;
while(1)
{
while(jplus> j)
{
int jplusold= jplus;
jplus= SUCC(jplus,j);
j= jplusold;
}
if(jplus==0){
if(j==n-1)
{
LINK(n,entering_edge,0);
return;
}
jplus= j+1;
j= 0;
}




do
{

k_right= j;
j= jplus;
k_left= jplus= PRED(j,k_right);
}
while(jplus> j&&orientation_test(j,k_left,n)> 0);

LINK(j,k_left,n);
LINK(j,n,k_right);

LINK(n,entering_edge,j);

entering_edge= j;
jplus= k_right;
}
}

/*:74*//*76:*/
#line 133 "readDataBase.w"


void swap_all_bytes(int n)
{
for_int_from_to(i,0,n-1)
{
points[i].x= (points[i].x>>8)|(points[i].x<<8);
points[i].y= (points[i].y>>8)|(points[i].y<<8);

}
}

/*:76*//*78:*/
#line 178 "readDataBase.w"

long long unsigned read_count= 0;

void read_database_file(char*inputfile,int bits,int record_size,
int n_points,boolean is_big_endian
){
printf("Reading from file %s\n",inputfile);
int databasefile= open(inputfile,O_RDONLY);
if(databasefile==-1)
{
printf("File could not be opened.\n");
exit(1);
}

while(1)
{
ssize_t bytes_read;
if(bits==16)
bytes_read= read(databasefile,&points,record_size);
else
bytes_read= read(databasefile,&pointsmall,record_size);

if(bytes_read==0)break;
if(bytes_read!=record_size){printf("Incomplete file.\n");exit(1);}
read_count++;
if(bits==16&&is_big_endian)swap_all_bytes(n_points);
if(bits==8)
for_int_from_to(i,0,n_points-1)
{
points[i].x= pointsmall[i].x;
points[i].y= pointsmall[i].y;
}
int n= n_points-1;
PSLA_from_points(n_points);
int hulledges[MAXN+1];
int hullsize= upper_hull_PSLA(n,hulledges);
P_matrix P;
compute_lex_smallest_P_matrix(&P,n,hulledges,hullsize);
compute_fingerprint(&P,n);
printf("%s:\n",fingerprint);
}
close(databasefile);
}


#line 2456 "NumPSLA.w"


/*:78*/
#line 361 "NumPSLA.w"

/*15:*/
#line 554 "NumPSLA.w"


void recursive_generate_PSLA_start(int n);

void recursive_generate_PSLA(int entering_edge,int k_right,int n)
{






int j= entering_edge;
int jplus= k_right;

while(jplus> j)
{
int jplusold= jplus;
jplus= SUCC(jplus,j);
j= jplusold;

}

if(jplus==0){
if(j==n-1)
{
LINK(n,entering_edge,0);
/*17:*/
#line 665 "NumPSLA.w"

countPSLA[n]++;
localCountPSLA[n]++;


/*:17*/
#line 581 "NumPSLA.w"

/*18:*/
#line 672 "NumPSLA.w"

/*19:*/
#line 682 "NumPSLA.w"

if(n==n_max&&countPSLA[n]%50000000000==0){

printf("..%Ld.. ",countPSLA[n]);
P_matrix P;
convert_to_P_matrix(&P,n);
print_pseudolines_short(&P,n);

fflush(stdout);
}


/*:19*/
#line 673 "NumPSLA.w"
;
boolean is_excluded= false;
/*21:*/
#line 735 "NumPSLA.w"

if(n==matched_length+1&&
localCountPSLA[n]==excluded_code[n])
{
matched_length= n;
if(matched_length==excluded_length){

is_excluded= true;
/*23:*/
#line 757 "NumPSLA.w"

do{
if(fscanf(exclude_file,"%s\n",exclude_file_line)!=EOF)
{
char*str1= exclude_file_line;
char*token,*saveptr;
excluded_length= 2;
while(true)
{
token= strtok_r(str1,".",&saveptr);
if(token==NULL)
break;

assert(excluded_length<MAXN+3-1);
excluded_code[++excluded_length]= atoi(token);
str1= NULL;
}
}
else
{
excluded_length= 0;
fclose(exclude_file);
}
}while(excluded_length> n_max);

/*:23*/
#line 743 "NumPSLA.w"

/*24:*/
#line 785 "NumPSLA.w"

matched_length= 2;
while(excluded_code[matched_length+1]==
localCountPSLA[matched_length+1]&&
matched_length<excluded_length&&
matched_length<n)

matched_length++;



/*:24*/
#line 744 "NumPSLA.w"

}
}


/*:21*//*58:*/
#line 2199 "NumPSLA.w"



/*:58*/
#line 675 "NumPSLA.w"

if(is_excluded)return;
/*53:*/
#line 2017 "NumPSLA.w"


int hulledges[MAXN+1];
int hullsize= upper_hull_PSLA(n,hulledges);

int rotation_period;
boolean has_fixed_vertex;
boolean has_mirror_symmetry;


int n_points= n+1;

boolean lex_smallest= 
is_lex_smallest_P_matrix(n,
hulledges,hullsize,
&rotation_period,&has_mirror_symmetry,&has_fixed_vertex);

if(lex_smallest)
{
countU[n_points]++;





if(has_mirror_symmetry)
{
countO[n_points]++;
PSLAcount[n]+= rotation_period;
if(has_fixed_vertex)
U_PSLAcount[n]+= rotation_period/2+1;

else
U_PSLAcount[n]+= rotation_period/2;
}
else
{
countO[n_points]+= 2;
PSLAcount[n]+= 2*rotation_period;
U_PSLAcount[n]+= rotation_period;
}

classcount[n_points][hullsize][rotation_period]
[!has_mirror_symmetry?NO_MIRROR:has_fixed_vertex?MIRROR_WITH_FIXED_VERTEX:
MIRROR_WITHOUT_FIXED_VERTEX]++;
}

#if 0 
printf("found n=%d. %Ld ",n_points,countO[n_points]);
print_small(S,n_points);
#endif

/*:53*/
#line 677 "NumPSLA.w"

/*59:*/
#line 2204 "NumPSLA.w"



/*:59*//*60:*/
#line 2212 "NumPSLA.w"


#if generatelist
if(n==n_max&&lex_smallest){
/*36:*/
#line 1203 "NumPSLA.w"

{
P_matrix P;
convert_to_P_matrix(&P,n);
compute_fingerprint(&P,n);
printf("%s:",fingerprint);
}





/*:36*/
#line 2216 "NumPSLA.w"

print_id(n);printf("\n");}
#endif


/*:60*//*61:*/
#line 2230 "NumPSLA.w"


#if 0
P_matrix PaInverse;
convert_to_inverse_P_matrix(&PaInverse,n);

small_lambda_matrix S;
convert_to_small_lambda_matrix(&S,n_points);
large_Lambda_matrix L;
convert_small_to_large(&S,&L,n_points);
/*62:*/
#line 2244 "NumPSLA.w"


{int n= n_points;
for_int_from_to(i,0,n-1)
for_int_from_to(j,0,n-1)
if(i!=j)
for_int_from_to(k,0,n-1)
if(k!=j&&k!=i)
if(getOrientation(PaInverse,i,j,k)!=L[i][j][k]){

printf("[%d,%d,%d]=%d!=%d\n",i,j,k,
getOrientation(PaInverse,i,j,k),L[i][j][k]);
exit(1);
}
;

}
/*:62*/
#line 2240 "NumPSLA.w"

#endif

/*:61*//*64:*/
#line 2264 "NumPSLA.w"

#if 0
if(n==n_max&&countPSLA[n]==50){
P_matrix P,PaInverse;
convert_to_P_matrix(&P,n);
convert_to_inverse_P_matrix(&PaInverse,n);
print_pseudolines_short(&P,n);
printf("inverse ");print_pseudolines_short(&PaInverse,n+1);
print_wiring_diagram(n);
}
#endif


/*:64*//*65:*/
#line 2278 "NumPSLA.w"

#if 0  
#define MID 5
if(n==2*MID-2)
{
P_matrix P;
convert_to_P_matrix(&P,n);

for_int_from_to(i,2,MID-1)
{
boolean show= true;
for_int_from_to(j,1,n-1)
{
int x= P[i][j];
if(x==MID||x==1)break;
printf("%c",TO_CHAR(x));

}
printf("!");
}
for_int_from_to(i,MID+1,n)
{
boolean show= false;
for_int_from_to(j,1,n-1)
{
int x= P[i][j];

if(show)
printf("%c",TO_CHAR(x));
if(x==MID)show= true;
if(x==1)break;
}
printf(i<n?"!":" ");
}
for_int_from_to(j,1,n-1){
int x= P[1][j];
if(x==MID)break;
printf("%c",TO_CHAR(x));}
printf("!");

for_int_from_to(j,1,n-1){
int x= P[MID][j];
if(x==1)break;
printf("%c",TO_CHAR(x));}
printf("\n");
}

#endif


/*:65*/
#line 678 "NumPSLA.w"


/*:18*/
#line 582 "NumPSLA.w"

if(n<n_max)
if(n!=split_level||countPSLA[n]%parts==part){
#if enumAOT 
boolean hopeful= true;
if(n==n_max-1){
/*49:*/
#line 1930 "NumPSLA.w"

int P_1_n= PRED(1,0);

if(P_1_n> 3)
{
int a= 2;
int i2= P_1_n;
while(i2!=2)
{
i2= PRED(1,i2);a++;
}


if(a+1<P_1_n)hopeful= false;
}
if(hopeful)cpass++;else csaved++;

/*:49*/
#line 588 "NumPSLA.w"

}
if(hopeful)
#endif
{localCountPSLA[n+1]= 0;
recursive_generate_PSLA_start(n+1);



}
}
return;
}
else
{
jplus= j+1;j= 0;
}
}





do
{
k_right= j;
j= jplus;
int k_left= jplus= PRED(j,k_right);




LINK(j,k_left,n);

LINK(j,n,k_right);

LINK(n,entering_edge,j);

recursive_generate_PSLA(j,k_right,n);


LINK(j,k_left,k_right);

}
while(jplus> j);

return;
}

void recursive_generate_PSLA_start(int n)
{LINK(0,n-1,n);
LINK(0,n,1);
recursive_generate_PSLA(0,0,n);






LINK(0,n-1,1);
}

/*:15*/
#line 362 "NumPSLA.w"

int main(int argc,char*argv[])
{

/*13:*/
#line 468 "NumPSLA.w"


if(argc<2)
n_max= 7;
else{
if(argv[1][0]=='-'){

PRINT_INSTRUCTIONS;
exit(0);
}
n_max= atoi(argv[1]);
}
printf("Enumeration up to n = %d pseudolines, %d points.\n",n_max,n_max+1);
if(n_max> MAXN)
{
printf("The largest allowed value is %d. Aborting.\n",MAXN);
exit(1);
}

int argshift= 0;
if(argc>=3)
{
if(strcmp(argv[2],"-exclude")==0){
if(argc>=4)
{
exclude_file_name= argv[3];
argshift= 2;
printf("Excluding entries from file %s.\n",exclude_file_name);
/*22:*/
#line 750 "NumPSLA.w"

exclude_file= fopen(exclude_file_name,"r");
/*23:*/
#line 757 "NumPSLA.w"

do{
if(fscanf(exclude_file,"%s\n",exclude_file_line)!=EOF)
{
char*str1= exclude_file_line;
char*token,*saveptr;
excluded_length= 2;
while(true)
{
token= strtok_r(str1,".",&saveptr);
if(token==NULL)
break;

assert(excluded_length<MAXN+3-1);
excluded_code[++excluded_length]= atoi(token);
str1= NULL;
}
}
else
{
excluded_length= 0;
fclose(exclude_file);
}
}while(excluded_length> n_max);

/*:23*/
#line 752 "NumPSLA.w"

matched_length= 2;


/*:22*/
#line 496 "NumPSLA.w"

}
else{
PRINT_INSTRUCTIONS;
exit(1);
}
}
}
if(argc>=3+argshift){

split_level= atoi(argv[2+argshift]);
if(split_level==0)
{if(argv[3+argshift][0]!='-')fileprefix= argv[3+argshift];
snprintf(fname,sizeof(fname)-1,"%s-%d.txt",fileprefix,n_max);
parts= 1;
}
else
{
if(exclude_file_name!=0)
{printf("The -exclude option with a positive splitlevel %d is not implemented. Aborting.\n",split_level);
exit(1);
}

if(argc>=4+argshift)parts= atoi(argv[3+argshift]);
if(argc>=5+argshift)part= atoi(argv[4+argshift]);
part= part%parts;
if(argc>=6+argshift)fileprefix= argv[5+argshift];
snprintf(fname,sizeof(fname)-1,"%s-%d-S%d-part_%d_of_%d.txt",fileprefix,n_max,
split_level,part,parts);
printf("Partial enumeration: split at level n = %d. Part %d of %d.\n",
split_level,part,parts);
}
printf("Results will be reported to file %s.\n",fname);
fflush(stdout);
}



/*:13*/
#line 366 "NumPSLA.w"
;
#if readdatabase 

/*77:*/
#line 146 "readDataBase.w"

int n_points= n_max+1;
int bits= n_points>=9?16:8;

char inputfile[60];
int record_size= (bits/8)*2*n_points;
printf("Reading order types of %d points\n",n_points);
printf(".\n");
printf("One record is %d bytes long.\n",record_size);
boolean is_big_endian= (*(uint16_t*)"\0\xff"<0x100);
if(bits> 8){
if(is_big_endian)
printf("This computer is big-endian.\n");
else
printf("This computer is little-endian. No byte swaps are necessary.\n");
}

if(n_points<11){
snprintf(inputfile,60,"otypes%02d.b%02d",n_points,bits);
read_database_file(inputfile,bits,record_size,n_points,is_big_endian);
}
else
for_int_from_to(num_db,0,93){
snprintf(inputfile,60,"Ordertypes/ord%02d_%02d.b16",
n_points,num_db);
read_database_file(inputfile,bits,record_size,n_points,is_big_endian);
}
printf("%Ld point sets were read from the file(s).\n",read_count);


/*:77*/
#line 369 "NumPSLA.w"

return 0;
#endif
#if enumAOT
/*52:*/
#line 2002 "NumPSLA.w"


countPSLA[1]= 
countPSLA[2]= 1;
countO[3]= 
countU[3]= 
PSLAcount[2]= 
U_PSLAcount[2]= 
1;

if(strlen(fname)){
reportfile= fopen(fname,"w");
}


/*:52*/
#line 373 "NumPSLA.w"
;
/*16:*/
#line 652 "NumPSLA.w"


LINK(1,0,2);
LINK(1,2,0);
LINK(2,0,1);
LINK(2,1,0);

LINK(0,1,2);


recursive_generate_PSLA_start(3);

/*:16*/
#line 374 "NumPSLA.w"
;
/*54:*/
#line 2073 "NumPSLA.w"

printf("%34s%69s\n","#PSLA visited by the program","#PSLA computed from AOT");
for_int_from_to(n,3,n_max+1){
long long symmetric= 2*countU[n]-countO[n];
printf("n=%2d",n);
if(split_level!=0&&n> split_level)printf("*,");
else printf(", ");
printf("#PSLA=%11Ld",countPSLA[n]);
#if 1
printf(", #AOT=%10Ld, #OAOT=%10Ld, #symm. AOT=%7Ld, ",
countU[n],
countO[n],symmetric
);
printf("#PSLA=%11Ld, #uPSLA=%10Ld",PSLAcount[n],U_PSLAcount[n]);
#endif
printf("\n");

}

if(split_level!=0)printf("* Lines with \"*\" give results from partial enumeration.\n");
#if profile
printf("Total tests is_lex_min (after screening) = %Ld, total comparisons = %Ld, average =%6.3f\n",
numTests,numComparisons,numComparisons/(double)numTests);
#endif

printf("passed %Ld, saved %Ld out of %Ld = %.2f%%\n",cpass,csaved,
cpass+csaved,100*csaved/(double)(cpass+csaved));

/*:54*//*55:*/
#line 2108 "NumPSLA.w"



if(strlen(fname)){
fprintf(reportfile,"# N_max=%d/%d",n_max,n_max+1);
if(parts!=1)
fprintf(reportfile,", split-level=%d, part %d of %d",
split_level,part,parts);
fprintf(reportfile,"\n#x N hull period mirror-type  NUM\n");
for_int_from_to(n,0,n_max+1)
{
char c= 'T';
if(parts!=1&&n> split_level+1)
c= 'P';
for_int_from_to(k,0,n)
for_int_from_to(p,0,n)
for_int_from_to(t,0,2)
if(classcount[n][k][p][t])
fprintf(reportfile,
"%c %d %d %d %d  %Ld\n",c,n,k,p,t,classcount[n][k][p][t]);
}
if(parts==1)
fprintf(reportfile,"EOF\n");
else
fprintf(reportfile,"EOF %d, part %d of %d\n",
split_level,part,parts);

fclose(reportfile);
printf("Results have been written to file %s.\n",fname);
}

/*:55*/
#line 375 "NumPSLA.w"
;
#endif
return 0;
}

/*:6*/
