#define MAXN 15 \
 \

#define enumAOT 1 \

#define readdatabase 0
#define generatelist 0 \

#define profile 1 \
 \

#define for_int_from_to(x,first,last) for(int x= first;x<=last;x++)  \
 \

#define print_array(a,length,begin,separator,end) { \
printf(begin) ; \
for_int_from_to(j,0,length-1) { \
if(j> 0) printf(separator) ; \
printf("%d",a[j]) ; \
} \
printf(end) ; \
} \

#define PRINT_INSTRUCTIONS printf( \
"Usage: %s n [-exclude excludefile] [splitlevel parts part] [fileprefix]\n",argv[0]) ; \

#define SUCC(i,j) succ[i][j]
#define PRED(i,j) pred[i][j] \

#define LINK(j,k1,k2) { \
SUCC(j,k1) = k2; \
PRED(j,k2) = k1; \
} \
 \

#define getOrientation_explicit(invP,i,j,k) ( \
i<j&&j<k?invP[i][j]> invP[i][k]: \
i<k&&k<j?invP[i][j]> invP[i][k]: \
j<i&&i<k?invP[i][j]<invP[i][k]: \
j<k&&k<i?invP[i][j]> invP[i][k]: \
k<j&&j<i?invP[i][j]> invP[i][k]: \
k<i&&i<j?invP[i][j]<invP[i][k]: \
0)  \

#define getOrientation(invP,i,j,k) ((i<j) ^(j<k) ^(invP[j][i]> invP[j][k]) )  \
 \
 \

#define TO_CHAR(i) ((char) ( \
(i<10?(int) '0':((int) 'A'-10) )  \
+i) )  \

#define FINGERPRINT_LENGTH 30 \
 \

#define NO_MIRROR 0
#define MIRROR_WITH_FIXPOINT 1
#define MIRROR_WITHOUT_FIXPOINT 2 \

#define entry_small(A,i,j) (A) [i][j] \
 \

#define SUCC_ALTERNATE(i,j) succ[i<<4|j] \
 \
 \

/*2:*/
#line 198 "NumPSLA.w"



/*5:*/
#line 255 "NumPSLA.w"

#include <stdio.h> 
#include <stdint.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 


/*:5*//*65:*/
#line 126 "readDataBase.w"

#include <fcntl.h> 
#include <unistd.h> 

/*:65*/
#line 201 "NumPSLA.w"

/*4:*/
#line 248 "NumPSLA.w"


typedef enum{false,true}boolean;



/*:4*//*10:*/
#line 424 "NumPSLA.w"

typedef int PSLA[MAXN+1][MAXN+1];

/*:10*//*57:*/
#line 1975 "NumPSLA.w"



typedef uint_fast8_t XXsmall_matrix_entry;

typedef int_fast8_t XXsmall_int;
typedef boolean large_matrix_entry;
typedef unsigned small_matrix_entry;
typedef int small_int;


typedef small_matrix_entry small_matrix[MAXN+1][MAXN+1];
typedef large_matrix_entry large_matrix[MAXN+1][MAXN+1][MAXN+1];



/*:57*//*63:*/
#line 36 "readDataBase.w"

typedef int_least64_t large_int;



/*:63*/
#line 202 "NumPSLA.w"

/*7:*/
#line 284 "NumPSLA.w"

small_int n_max,split_level;
unsigned int parts= 1000,part= 0;
char*fileprefix= "reportPSLA";
char*exclude_file_name= 0;
char fname[200]= "";
FILE*reportfile= 0;

/*:7*//*11:*/
#line 466 "NumPSLA.w"

int succ[MAXN+1][MAXN+1];
int pred[MAXN+1][MAXN+1];


/*:11*//*17:*/
#line 653 "NumPSLA.w"

unsigned excluded_code[MAXN+3];
int excluded_length= 0;
int matched_length= 0;

FILE*exclude_file;
char exclude_file_line[100];

/*:17*//*27:*/
#line 896 "NumPSLA.w"

unsigned localCountPSLA[MAXN+3];


/*:27*//*32:*/
#line 1054 "NumPSLA.w"

char fingerprint[FINGERPRINT_LENGTH];

/*:32*//*36:*/
#line 1130 "NumPSLA.w"



int Sequence[MAXN+1][MAXN+1];

int new_label[MAXN+1][MAXN+1];



int candidate[2*(MAXN+1)];

int current_crossing[2*(MAXN+1)];


int P_1_n_forward[MAXN+1];
int P_1_n_reverse[MAXN+1];


/*:36*//*45:*/
#line 1531 "NumPSLA.w"


long long unsigned cpass,csaved;

/*:45*//*49:*/
#line 1689 "NumPSLA.w"


long long unsigned countPSLA[MAXN+2],countO[MAXN+2],countU[MAXN+2];

long long unsigned PSLAcount[MAXN+2];




long long unsigned xPSLAcount[MAXN+2];
long long unsigned classcount[MAXN+2][MAXN+2][MAXN+2][3];



long long unsigned
numComparisons= 0,numTests= 0;

/*:49*//*61:*/
#line 7 "readDataBase.w"

struct{
uint16_t x,y;}points[MAXN+1];
struct{
uint8_t x,y;}pointsmall[MAXN+1];


/*:61*/
#line 203 "NumPSLA.w"

/*23:*/
#line 731 "NumPSLA.w"


void convert_to_PS_array(PSLA*P,int n)
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
/*:23*//*24:*/
#line 768 "NumPSLA.w"


void convert_to_inverse_PS_array(PSLA*invP,int n)
{
int j= 1;
for_int_from_to(i,0,n)
{
for_int_from_to(p,0,n-1)
{
(*invP)[i][j]= p;
j= SUCC(i,j);
}
j= 0;
}
}


/*:24*//*26:*/
#line 857 "NumPSLA.w"


small_int upper_hull_PSLA(int n,
small_int*hulledges)
{
hulledges[0]= 0;
small_int hullsize= 1;
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

/*:26*//*28:*/
#line 900 "NumPSLA.w"


void print_id(int n)
{
printf("%d",localCountPSLA[3]);
for_int_from_to(i,4,n)
printf(".%d",localCountPSLA[i]);
}

/*:28*//*30:*/
#line 918 "NumPSLA.w"



void print_wiring_diagram(int n)
{
int next_crossing[MAXN+1];
int line_at[MAXN+1];
boolean crossing[MAXN];


char buffer[2*MAXN][MAXN*MAXN];

for_int_from_to(j,0,n-1){
next_crossing[j+1]= SUCC(j+1,0);

line_at[j]= j+1;
}
crossing[n-1]= false;
int n_crossings= 0;
int column= 0;

for_int_from_to(p,0,2*n-1)buffer[p][column]= ' ';
column++;
while(true)
{


boolean something_done= false;
for_int_from_to(p,0,n-2)
{
int i= line_at[p];
int j= line_at[p+1];
crossing[p]= next_crossing[i]==j&&next_crossing[j]==i;
if(crossing[p])
{
something_done= true;
n_crossings++;
}
}
for_int_from_to(p,0,n-1){
buffer[2*p][column]= TO_CHAR(line_at[p]);
buffer[2*p+1][column]= ' ';
}

column++;
if(!something_done)break;
for_int_from_to(p,0,n-1){
buffer[2*p][column]= '-';
buffer[2*p+1][column]= ' ';
}
for_int_from_to(p,0,n-2)
{
if(crossing[p])
{
buffer[2*p][column]= 
buffer[2*p+2][column]= ' ';
buffer[2*p+1][column]= 'X';
}
}
column++;
for_int_from_to(p,0,n-2)
{
if(crossing[p])
{
int i= line_at[p];
int j= line_at[p+1];
next_crossing[i]= SUCC(i,next_crossing[i]);
next_crossing[j]= SUCC(j,next_crossing[j]);
line_at[p]= j;
line_at[p+1]= i;
}
}
}
for_int_from_to(p,0,2*n-2){
buffer[p][column]= 0;
printf("%s\n",buffer[p]);
}
assert(n_crossings*2==n*(n-1));
}

/*:30*//*31:*/
#line 1000 "NumPSLA.w"


void print_pseudolines_short(PSLA*P,int n)
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

void print_pseudolines_compact(PSLA*P,int n)
{
for_int_from_to(i,1,n)
{
if(i> 1)printf("!");
for_int_from_to(j,1,n-2)
printf("%c",TO_CHAR((*P)[i][j]));
}
}

/*:31*//*33:*/
#line 1058 "NumPSLA.w"


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

void compute_fingerprint(PSLA*P,int n){

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
fingerprint[charpos++]= '\0';
}

/*:33*//*37:*/
#line 1149 "NumPSLA.w"


void prepare_label_arrays(small_int n,
small_int*hulledges,small_int hullsize)
{
for_int_from_to(r,0,hullsize-1)
if(P_1_n_reverse[r]==P_1_n_forward[0]||
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

/*:37*//*38:*/
#line 1178 "NumPSLA.w"

void compute_lex_smallest_PSLA(PSLA*P,small_int n,
small_int*hulledges,small_int hullsize)
{

for_int_from_to(q,0,n-1)(*P)[0][q]= q+1;

for_int_from_to(r,0,hullsize-1)
P_1_n_forward[r]= P_1_n_reverse[r]= 0;



prepare_label_arrays(n,hulledges,hullsize);

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

for_int_from_to(q,1,n-1)
{
int c;
int new_candidates,new_candidates_forward;
int current_min= n+1;
boolean reversed= false;
int pos= p;

for(c= 0;c<numcandidates_forward;c++)
{
/*39:*/
#line 1244 "NumPSLA.w"

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




/*:39*/
#line 1221 "NumPSLA.w"

}
new_candidates_forward= new_candidates;


reversed= true;
pos= n+1-p;
for(;c<numcandidates;c++)
{
/*39:*/
#line 1244 "NumPSLA.w"

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




/*:39*/
#line 1231 "NumPSLA.w"

}
numcandidates_forward= new_candidates_forward;
numcandidates= new_candidates;
(*P)[p][n-q]= current_min;

}
}
}
/*:38*//*42:*/
#line 1385 "NumPSLA.w"


boolean screen(small_int n,
small_int*hulledges,small_int hullsize)
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


/*:42*//*46:*/
#line 1536 "NumPSLA.w"


boolean is_lex_smallest_PSLA(small_int n,
small_int*hulledges,small_int hullsize,small_int*
rotation_period,boolean*is_symmetric,boolean*has_fixpoint)
{
if(!screen(n,hulledges,hullsize))
return false;

#if profile
numTests++;
#endif


prepare_label_arrays(n,hulledges,hullsize);

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
/*47:*/
#line 1623 "NumPSLA.w"


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




/*:47*/
#line 1593 "NumPSLA.w"

}
numcandidates_forward= new_candidates;


reversed= true;
pos= n+1-p;
for(;c<numcandidates;c++)
{
/*47:*/
#line 1623 "NumPSLA.w"


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




/*:47*/
#line 1603 "NumPSLA.w"

}
numcandidates= new_candidates;

if(numcandidates==0)
{
*rotation_period= hullsize;
*is_symmetric= false;
return true;
}
}
}
/*48:*/
#line 1657 "NumPSLA.w"

{
if(numcandidates_forward> 0)
*rotation_period= candidate[0];
else
*rotation_period= hullsize;
*is_symmetric= (numcandidates> numcandidates_forward);
if(*is_symmetric){
int symmetric_shift= candidate[numcandidates_forward];

*has_fixpoint= ((*rotation_period)%2==1)||(symmetric_shift%2==0);
}
}



/*:48*/
#line 1615 "NumPSLA.w"


return true;
}

/*:46*//*58:*/
#line 1995 "NumPSLA.w"


void copy_small(small_matrix*A,small_matrix*B,small_int n)
{
for(small_int i= 0;i<n;i++)
for(small_int j= 0;j<n;j++)
entry_small(*B,i,j)= entry_small(*A,i,j);
}

void convert_small_to_large(small_matrix*A,large_matrix*B,
small_int n)
{
small_matrix Temp;
copy_small(A,&Temp,n);
for(small_int k= 0;k<n;k++)
for(small_int i= k+1;i<n;i++)
for(small_int j= i+1;j<n;j++)
{
if(entry_small(Temp,i,k)<entry_small(Temp,j,k))
{
entry_small(Temp,i,j)--;
(*B)[k][i][j]= (*B)[i][j][k]= (*B)[j][k][i]= true;
(*B)[k][j][i]= (*B)[i][k][j]= (*B)[j][i][k]= false;
}
else
{
entry_small(Temp,j,i)--;
(*B)[k][i][j]= (*B)[i][j][k]= (*B)[j][k][i]= false;
(*B)[k][j][i]= (*B)[i][k][j]= (*B)[j][i][k]= true;
}
}
}


/*:58*//*60:*/
#line 2034 "NumPSLA.w"



void convert_to_small_lambda_matrix(small_matrix*B,int n)
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


#line 1 "readDataBase.w"
/*:60*//*62:*/
#line 19 "readDataBase.w"

large_int orientation_test(int i,int j,int k)
{
large_int a= points[j].x-(large_int)points[i].x;
large_int b= points[j].y-(large_int)points[i].y;
large_int c= points[k].x-(large_int)points[i].x;
large_int d= points[k].y-(large_int)points[i].y;
return a*d-b*c;
}
/*:62*//*64:*/
#line 54 "readDataBase.w"

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

/*:64*//*66:*/
#line 131 "readDataBase.w"


void swap_all_bytes(int n)
{
for_int_from_to(i,0,n-1)
{
points[i].x= (points[i].x>>8)|(points[i].x<<8);
points[i].y= (points[i].y>>8)|(points[i].y<<8);

}
}

/*:66*//*68:*/
#line 175 "readDataBase.w"

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
small_int hulledges[MAXN+1];
small_int hullsize= upper_hull_PSLA(n,hulledges);
PSLA P;
compute_lex_smallest_PSLA(&P,n,hulledges,hullsize);
compute_fingerprint(&P,n);
printf("%s:\n",fingerprint);
}
close(databasefile);
}


#line 2067 "NumPSLA.w"


/*:68*/
#line 204 "NumPSLA.w"

/*13:*/
#line 490 "NumPSLA.w"


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
/*16:*/
#line 619 "NumPSLA.w"

countPSLA[n]++;
localCountPSLA[n]++;


/*:16*/
#line 517 "NumPSLA.w"

/*15:*/
#line 607 "NumPSLA.w"

if(n==n_max&&countPSLA[n]%50000000000==0){

printf("..%Ld.. ",countPSLA[n]);
PSLA P;
convert_to_PS_array(&P,n);
print_pseudolines_short(&P,n);

fflush(stdout);
}

/*:15*/
#line 518 "NumPSLA.w"
;
/*18:*/
#line 662 "NumPSLA.w"

boolean is_excluded= false;
if(n==matched_length+1&&
localCountPSLA[n]==excluded_code[n])
{
matched_length= n;
if(matched_length==excluded_length){

is_excluded= true;
/*20:*/
#line 686 "NumPSLA.w"

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

/*:20*/
#line 671 "NumPSLA.w"

/*21:*/
#line 714 "NumPSLA.w"

matched_length= 2;
while(excluded_code[matched_length+1]==
localCountPSLA[matched_length+1]&&
matched_length<excluded_length&&
matched_length<n)

matched_length++;



/*:21*/
#line 672 "NumPSLA.w"

}
}


/*:18*/
#line 519 "NumPSLA.w"

if(is_excluded)return;
/*51:*/
#line 1730 "NumPSLA.w"



small_int hulledges[MAXN+1];
small_int hullsize= upper_hull_PSLA(n,hulledges);

small_int rotation_period;
boolean has_fixpoint;
boolean is_symmetric;


int n_points= n+1;

boolean lex_smallest= 
is_lex_smallest_PSLA(n,
hulledges,hullsize,
&rotation_period,&is_symmetric,&has_fixpoint);

if(lex_smallest)
{
countU[n_points]++;
if(is_symmetric)
{
countO[n_points]++;
PSLAcount[n]+= rotation_period;
if(has_fixpoint)
xPSLAcount[n]+= rotation_period/2+1;

else
xPSLAcount[n]+= rotation_period/2;
}
else
{
countO[n_points]+= 2;
PSLAcount[n]+= 2*rotation_period;
xPSLAcount[n]+= rotation_period;
}

classcount[n_points][hullsize][rotation_period][
!is_symmetric?NO_MIRROR:has_fixpoint?MIRROR_WITH_FIXPOINT:
MIRROR_WITHOUT_FIXPOINT]++;
}

#if 0 
printf("found n=%d. %Ld ",n_points,countO[n_points]);
print_small(S,n_points);
#endif

/*:51*/
#line 521 "NumPSLA.w"

/*53:*/
#line 1849 "NumPSLA.w"


#if generatelist 

if(n==n_max&&lex_smallest){
/*34:*/
#line 1097 "NumPSLA.w"

{
PSLA P;
convert_to_PS_array(&P,n);
compute_fingerprint(&P,n);
printf("%s:",fingerprint);
}





/*:34*/
#line 1854 "NumPSLA.w"

print_id(n);printf("\n");}
#endif

#if 0
if(n==n_max&&countPSLA[n]==50){
PSLA PP,invPP;
convert_to_PS_array(&PP,n);
convert_to_inverse_PS_array(&invPP,n);
print_pseudolines_short(&PP,n);
printf("inverse ");print_pseudolines_short(&invPP,n+1);
print_wiring_diagram(n);
}
#endif

#if 0  
#define MID 5
if(n==2*MID-2)
{
PSLA P;
convert_to_PS_array(&P,n);

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


#if 0
PSLA invP;
convert_to_inverse_PS_array(&invP,n);

small_matrix S;
convert_to_small_lambda_matrix(&S,n_points);
large_matrix L;
convert_small_to_large(&S,&L,n_points);
/*54:*/
#line 1930 "NumPSLA.w"


{int n= n_points;
for_int_from_to(i,0,n-1)
for_int_from_to(j,0,n-1)
if(i!=j)
for_int_from_to(k,0,n-1)
if(k!=j&&k!=i)
if(getOrientation(invP,i,j,k)!=L[i][j][k]){

printf("[%d,%d,%d]=%d!=%d\n",i,j,k,
getOrientation(invP,i,j,k),L[i][j][k]);
exit(1);
}
;

}

/*:54*/
#line 1926 "NumPSLA.w"

#endif

/*:53*/
#line 522 "NumPSLA.w"

if(n<n_max)
if(n!=split_level||countPSLA[n]%parts==part){
#if enumAOT 
boolean hopeful= true;
if(n==n_max-1){
/*44:*/
#line 1513 "NumPSLA.w"

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

/*:44*/
#line 528 "NumPSLA.w"

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

/*:13*/
#line 205 "NumPSLA.w"

int main(int argc,char*argv[])
{

/*8:*/
#line 293 "NumPSLA.w"


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
/*19:*/
#line 678 "NumPSLA.w"

exclude_file= fopen(exclude_file_name,"r");
/*20:*/
#line 686 "NumPSLA.w"

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

/*:20*/
#line 680 "NumPSLA.w"

matched_length= 2;


/*:19*/
#line 321 "NumPSLA.w"

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
{if(argv[2+argshift][0]!='-')fileprefix= argv[2+argshift];
snprintf(fname,sizeof(fname)-1,"%s-%d.txt",fileprefix,n_max);
parts= 1;
}
else
{
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


/*:8*/
#line 209 "NumPSLA.w"
;
#if readdatabase 

/*67:*/
#line 144 "readDataBase.w"

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
printf("This computer is big endian.\n");
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


/*:67*/
#line 212 "NumPSLA.w"

return 0;
#endif
#if enumAOT
/*50:*/
#line 1715 "NumPSLA.w"


countPSLA[1]= 
countPSLA[2]= 1;
countO[3]= 
countU[3]= 
PSLAcount[2]= 
xPSLAcount[2]= 
1;

if(strlen(fname)){
reportfile= fopen(fname,"w");
}


/*:50*/
#line 216 "NumPSLA.w"
;
/*14:*/
#line 592 "NumPSLA.w"


LINK(1,0,2);
LINK(1,2,0);
LINK(2,0,1);
LINK(2,1,0);

LINK(0,1,2);


recursive_generate_PSLA_start(3);



/*:14*/
#line 217 "NumPSLA.w"
;
/*52:*/
#line 1784 "NumPSLA.w"

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
printf("#PSLA=%11Ld, #xPSLA=%10Ld",PSLAcount[n],xPSLAcount[n]);
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
for_int_from_to(k,0,n_max+1)
for_int_from_to(p,0,n_max+1)
for(small_int t= 0;t<3;t++)
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


/*:52*/
#line 218 "NumPSLA.w"
;
#endif
return 0;
}

/*:2*/
