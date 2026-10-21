#define SUCC(i,j) succ[i][j]
#define PRED(i,j) pred[i][j] \

#define LINK(j,k1,k2) { \
SUCC(j,k1) = k2; \
PRED(j,k2) = k1; \
} \
 \

#define MAXN 15 \
 \

#define for_int_from_to(x,first,last) for(int x= first;x<=last;x++)  \
 \

#define PRINT_INSTRUCTIONS fprintf(stderr, \
"Usage: %s n [fileprefix]\n" \
"or     %s n splitlevel parts part [fileprefix]\n" \
"or     %s n -exclude excludefile [fileprefix]\n", \
program_name,program_name,program_name) ; \

#define getOrientation_explicit(PaInverse,i,j,k) ( \
i<j&&j<k?PaInverse[i][j]<PaInverse[i][k]: \
i<k&&k<j?PaInverse[i][j]<PaInverse[i][k]: \
j<i&&i<k?PaInverse[i][j]> PaInverse[i][k]: \
j<k&&k<i?PaInverse[i][j]<PaInverse[i][k]: \
k<j&&j<i?PaInverse[i][j]<PaInverse[i][k]: \
k<i&&i<j?PaInverse[i][j]> PaInverse[i][k]: \
0)  \

#define getOrientation(PaInverse,i,j,k) ((i<j) ^(j<k) ^(PaInverse[j][i]<PaInverse[j][k]) )  \
 \
 \

#define TO_CHAR(i) ((char) ( \
(i<10?(int) '0':((int) 'A'-10) )  \
+i) )  \

#define FINGERPRINT_LENGTH (((MAXN-1) *(MAXN-1) +5) /6+1)  \
 \

#define NO_MIRROR 0
#define MIRROR_WITH_FIXED_VERTEX 1
#define MIRROR_WITHOUT_FIXED_VERTEX 2 \

#define entry_small(A,i,j) (A) [i][j] \
 \

/*6:*/
#line 366 "NumPSLA.w"


/*7:*/
#line 409 "NumPSLA.w"

#ifndef enumAOT
#define enumAOT 1





#endif
#line 418 "NumPSLA.w"
#ifndef readdatabase
#define readdatabase 0 
#endif
#line 421 "NumPSLA.w"
#ifndef generatelist
#define generatelist 0 



#endif
#line 427 "NumPSLA.w"
#ifndef profile
#define profile 1 

#endif
#line 431 "NumPSLA.w"


/*:7*/
#line 368 "NumPSLA.w"

/*10:*/
#line 457 "NumPSLA.w"

#include <stdio.h> 
#include <stdint.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 


/*:10*//*79:*/
#line 128 "pred"

#include <fcntl.h> 
#include <unistd.h> 

/*:79*/
#line 369 "NumPSLA.w"

/*4:*/
#line 306 "NumPSLA.w"

typedef int P_matrix[MAXN+1][MAXN+1];

/*:4*//*9:*/
#line 450 "NumPSLA.w"


typedef enum{false,true}boolean;



/*:9*//*69:*/
#line 2563 "NumPSLA.w"






typedef boolean large_matrix_entry;
typedef unsigned small_matrix_entry;



typedef small_matrix_entry small_lambda_matrix[MAXN+1][MAXN+1];
typedef large_matrix_entry large_Lambda_matrix[MAXN+1][MAXN+1][MAXN+1];



/*:69*//*77:*/
#line 36 "pred"

typedef int_least64_t large_int;



/*:77*/
#line 370 "NumPSLA.w"

/*5:*/
#line 351 "NumPSLA.w"

int succ[MAXN+1][MAXN+1];
int pred[MAXN+1][MAXN+1];


/*:5*//*13:*/
#line 549 "NumPSLA.w"

int n_max,split_level= 0;
unsigned int parts= 1,part= 0;
char*fileprefix= "reportPSLA";
char*exclude_file_name= 0;
char fname[200]= "";
FILE*reportfile= 0;
char*program_name= "NumPSLA";

/*:13*//*22:*/
#line 858 "NumPSLA.w"

unsigned excluded_code[MAXN+3];
int excluded_length= 0;
int matched_length= 0;

FILE*exclude_file= 0;
int exclude_line_number= 1;
unsigned previous_code[MAXN+3];
int previous_length= 0;

/*:22*//*43:*/
#line 1562 "NumPSLA.w"



int Sequence[MAXN+1][MAXN+1];

int new_label[MAXN+1][MAXN+1];



int candidate[2*(MAXN+1)];

int current_crossing[2*(MAXN+1)];


int P_1_n_forward[MAXN+1];
int P_1_n_reverse[MAXN+1];


/*:43*//*54:*/
#line 2197 "NumPSLA.w"


long long unsigned cpass,csaved;




/*:54*//*55:*/
#line 2231 "NumPSLA.w"


long long unsigned countPSLA[MAXN+2],countO[MAXN+2],countU[MAXN+2];

long long unsigned PSLAcount[MAXN+2];





long long unsigned U_PSLAcount[MAXN+2];
long long unsigned classcount[MAXN+2][MAXN+2][MAXN+2][3];



long long unsigned
numComparisons= 0,numTests= 0;

/*:55*//*75:*/
#line 7 "pred"

struct{
uint16_t x,y;}points[MAXN+1];
struct{
uint8_t x,y;}pointsmall[MAXN+1];


/*:75*/
#line 371 "NumPSLA.w"

/*14:*/
#line 559 "NumPSLA.w"

void usage_error(const char*format,const char*argument)
{
fprintf(stderr,"Error: ");
fprintf(stderr,format,argument);
fprintf(stderr," Aborting.\n");
PRINT_INSTRUCTIONS;
exit(1);
}

boolean is_number(const char*s)
{
char*end;
if(*s==0)return false;
strtol(s,&end,10);
return*end==0;
}

long parse_int(const char*s,const char*name,long low,long high)
{
char message[200];
if(!is_number(s)){
snprintf(message,sizeof(message),"The parameter %s must be an integer, but it is \"%%s\".",name);
usage_error(message,s);
}
long value= strtol(s,NULL,10);
if(value<low||value> high){
snprintf(message,sizeof(message),
"The parameter %s must be between %ld and %ld, but it is %%s.",name,low,high);
usage_error(message,s);
}
return value;
}

/*:14*//*27:*/
#line 928 "NumPSLA.w"

void print_excluded_code(FILE*f)
{
fprintf(f,"%u",excluded_code[3]);
for_int_from_to(q,4,excluded_length)fprintf(f,".%u",excluded_code[q]);
}

void exclude_file_error(const char*message)
{
fprintf(stderr,"Error in exclude-file %s, line %d: %s Aborting.\n",
exclude_file_name,exclude_line_number,message);
exit(1);
}

int read_excluded_code(void)
{
if(exclude_file==NULL)return 0;
int c= getc(exclude_file);
while(c==' '||c=='\t'||c=='\r'||c=='\n'){
if(c=='\n')exclude_line_number++;
c= getc(exclude_file);
}
if(c==EOF){
if(ferror(exclude_file))exclude_file_error("Read error.");
fclose(exclude_file);
exclude_file= NULL;
return 0;
}
int length= 2;
while(true){
if(c<'0'||c> '9')exclude_file_error("Illegal character; a number was expected.");
unsigned long value= 0;
while(c>='0'&&c<='9'){
value= 10*value+(c-'0');
if(value> 1000000000)exclude_file_error("Number too large.");
c= getc(exclude_file);
}
if(value==0)exclude_file_error("Components of the code must be positive.");
if(length>=MAXN)exclude_file_error("Code is too long.");
excluded_code[++length]= value;
if(c!='.')break;
c= getc(exclude_file);
}
if(c!=EOF&&c!=' '&&c!='\t'&&c!='\r'&&c!='\n')
exclude_file_error("Illegal character in code.");
if(c!=EOF)ungetc(c,exclude_file);
/*28:*/
#line 979 "NumPSLA.w"

if(previous_length> 0){
int common= previous_length<length?previous_length:length;
int q= 3;
while(q<=common&&previous_code[q]==excluded_code[q])q++;
if(q> common)
exclude_file_error(previous_length==length?"Duplicate code.":
previous_length<length?"The previous code is a prefix of this code.":
"This code is a prefix of the previous code.");
if(previous_code[q]> excluded_code[q])
exclude_file_error("The codes are not sorted.");
}
for_int_from_to(q,3,length)previous_code[q]= excluded_code[q];
previous_length= length;

/*:28*/
#line 975 "NumPSLA.w"

return length;
}

/*:27*//*31:*/
#line 1014 "NumPSLA.w"


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

/*:31*//*32:*/
#line 1052 "NumPSLA.w"


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


/*:32*//*34:*/
#line 1147 "NumPSLA.w"


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

/*:34*//*35:*/
#line 1195 "NumPSLA.w"

unsigned localCountPSLA[MAXN+3];

void print_id(int n)
{
printf("%d",localCountPSLA[3]);
for_int_from_to(i,4,n)
printf(".%d",localCountPSLA[i]);
}

/*:35*//*37:*/
#line 1216 "NumPSLA.w"



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

/*:37*//*38:*/
#line 1300 "NumPSLA.w"


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

/*:38*//*39:*/
#line 1382 "NumPSLA.w"

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
bit_num= acc= 0;
}
}
if(bit_num)
fingerprint[charpos++]= encode_bits(acc<<(6-bit_num));
assert(charpos<FINGERPRINT_LENGTH);
fingerprint[charpos]= '\0';
}

/*:39*//*42:*/
#line 1471 "NumPSLA.w"


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


/*:42*//*44:*/
#line 1583 "NumPSLA.w"


void prepare_label_arrays(int n,
int hulledges[],int hullsize,boolean compute_all)
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



/*:44*//*45:*/
#line 1643 "NumPSLA.w"

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
int new_candidates= 0,new_candidates_forward= 0;
int current_min= n+1;
boolean reversed= false;
int pos= p;

for(c= 0;c<numcandidates_forward;c++)
{
/*46:*/
#line 1704 "NumPSLA.w"

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



/*:46*/
#line 1680 "NumPSLA.w"

}
new_candidates_forward= new_candidates;


reversed= true;
pos= n+1-p;
for(;c<numcandidates;c++)
{
/*46:*/
#line 1704 "NumPSLA.w"

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



/*:46*/
#line 1690 "NumPSLA.w"

}
numcandidates_forward= new_candidates_forward;
numcandidates= new_candidates;
(*P)[p][n-q]= current_min;

}
}
}
/*:45*//*47:*/
#line 1740 "NumPSLA.w"


/*51:*/
#line 2039 "NumPSLA.w"

boolean screen_lex_smallest(int n,
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


/*:51*/
#line 1742 "NumPSLA.w"


boolean has_lex_smallest_P_matrix(int n,
int*hulledges,int hullsize,int*
rotation_period,boolean*has_mirror_symmetry,boolean*has_fixed_vertex)
{
if(!screen_lex_smallest(n,hulledges,hullsize))
return false;

#if profile
numTests++;

#endif
#line 1755 "NumPSLA.w"


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
/*48:*/
#line 1838 "NumPSLA.w"


#if profile
numComparisons++;
#endif
#line 1843 "NumPSLA.w"
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




/*:48*/
#line 1803 "NumPSLA.w"

}
numcandidates_forward= new_candidates;


reversed= true;
pos= n+1-p;
for(;c<numcandidates;c++)
{
/*48:*/
#line 1838 "NumPSLA.w"


#if profile
numComparisons++;
#endif
#line 1843 "NumPSLA.w"
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




/*:48*/
#line 1813 "NumPSLA.w"

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
/*49:*/
#line 1874 "NumPSLA.w"

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


/*:49*/
#line 1825 "NumPSLA.w"


return true;
}

/*:47*//*70:*/
#line 2588 "NumPSLA.w"



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

/*:70*//*72:*/
#line 2643 "NumPSLA.w"


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
(*B)[k][i][j]= (*B)[i][j][k]= (*B)[j][k][i]= !plus;
(*B)[k][j][i]= (*B)[i][k][j]= (*B)[j][i][k]= plus;

if(plus)
entry_small(Temp,i,j)--;
else
entry_small(Temp,j,i)--;
}
}

/*:72*//*76:*/
#line 19 "pred"

large_int orientation_test(int i,int j,int k)
{
large_int a= points[j].x-(large_int)points[i].x;
large_int b= points[j].y-(large_int)points[i].y;
large_int c= points[k].x-(large_int)points[i].x;
large_int d= points[k].y-(large_int)points[i].y;
return a*d-b*c;
}
/*:76*//*78:*/
#line 56 "pred"

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

/*:78*//*80:*/
#line 133 "pred"


void swap_all_bytes(int n)
{
for_int_from_to(i,0,n-1)
{
points[i].x= (points[i].x>>8)|(points[i].x<<8);
points[i].y= (points[i].y>>8)|(points[i].y<<8);

}
}

/*:80*//*82:*/
#line 178 "pred"

long long unsigned read_count= 0;

void read_database_file(char*inputfile,int bits,int record_size,
int n_points,boolean is_big_endian
){
printf("Reading from file %s\n",inputfile);
int databasefile= open(inputfile,O_RDONLY);
if(databasefile==-1)
{
fprintf(stderr,"Error: File %s could not be opened. Aborting.\n",inputfile);
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
if(bytes_read!=record_size){
fprintf(stderr,"Error: %s while reading file %s. Aborting.\n",
bytes_read<0?"Read error":"Incomplete record",inputfile);
exit(1);
}
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


#line 2711 "NumPSLA.w"


/*:82*/
#line 372 "NumPSLA.w"

/*17:*/
#line 678 "NumPSLA.w"


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
/*19:*/
#line 786 "NumPSLA.w"

countPSLA[n]++;
localCountPSLA[n]++;


/*:19*/
#line 705 "NumPSLA.w"

/*20:*/
#line 793 "NumPSLA.w"

/*21:*/
#line 803 "NumPSLA.w"

if(n==n_max&&countPSLA[n]%50000000000==0){

printf("..%Ld.. ",countPSLA[n]);
P_matrix P;
convert_to_P_matrix(&P,n);
print_pseudolines_short(&P,n);

fflush(stdout);
}


/*:21*/
#line 794 "NumPSLA.w"
;
boolean is_excluded= false;
/*23:*/
#line 869 "NumPSLA.w"

if(excluded_length> 0&&n<=excluded_length&&
(n<=matched_length
||
(n==matched_length+1&&localCountPSLA[n]> excluded_code[n])))

{fprintf(stderr,"Error: Exclude-file entry ");
print_excluded_code(stderr);
fprintf(stderr," (line %d) was skipped (not in tree). Aborting.\n",
exclude_line_number);
exit(1);
}
if(n==matched_length+1&&
localCountPSLA[n]==excluded_code[n])
{
matched_length= n;
if(matched_length==excluded_length){

is_excluded= true;
/*26:*/
#line 917 "NumPSLA.w"

do
excluded_length= read_excluded_code();
while(excluded_length> n_max);

/*:26*/
#line 888 "NumPSLA.w"

/*29:*/
#line 998 "NumPSLA.w"

matched_length= 2;
while(matched_length<excluded_length&&
matched_length<n&&
excluded_code[matched_length+1]==
localCountPSLA[matched_length+1])
matched_length++;


/*:29*/
#line 889 "NumPSLA.w"

}
}

/*:23*//*62:*/
#line 2457 "NumPSLA.w"



/*:62*/
#line 796 "NumPSLA.w"

if(is_excluded)return;
/*57:*/
#line 2270 "NumPSLA.w"


int hulledges[MAXN+1];
int hullsize= upper_hull_PSLA(n,hulledges);

int rotation_period;
boolean has_fixed_vertex;
boolean has_mirror_symmetry;


int n_points= n+1;

boolean lex_smallest= 
has_lex_smallest_P_matrix(n,
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
#line 2321 "NumPSLA.w"

/*:57*/
#line 798 "NumPSLA.w"

/*63:*/
#line 2462 "NumPSLA.w"



/*:63*//*64:*/
#line 2470 "NumPSLA.w"


#if generatelist
if(n==n_max&&lex_smallest){
/*40:*/
#line 1421 "NumPSLA.w"

{
P_matrix P;
convert_to_P_matrix(&P,n);
compute_fingerprint(&P,n);
printf("%s:",fingerprint);
}





/*:40*/
#line 2474 "NumPSLA.w"

print_id(n);printf("\n");}
#endif
#line 2477 "NumPSLA.w"


/*:64*//*66:*/
#line 2482 "NumPSLA.w"

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
#line 2493 "NumPSLA.w"


/*:66*//*67:*/
#line 2496 "NumPSLA.w"

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
#line 2544 "NumPSLA.w"


/*:67*//*73:*/
#line 2681 "NumPSLA.w"


#if 0
P_matrix PaInverse;
convert_to_inverse_P_matrix(&PaInverse,n);

small_lambda_matrix S;
convert_to_small_lambda_matrix(&S,n_points);
large_Lambda_matrix L;
convert_small_to_large(&S,&L,n_points);
/*74:*/
#line 2695 "NumPSLA.w"


for_int_from_to(i,0,n_points-1)
for_int_from_to(j,0,n_points-1)
for_int_from_to(k,0,n_points-1)
if(i!=j&&k!=j&&k!=i)
if(getOrientation(PaInverse,i,j,k)!=L[i][j][k]){

printf("[%d,%d,%d]=%d!=%d\n",i,j,k,
getOrientation(PaInverse,i,j,k),L[i][j][k]);
exit(1);
}



#line 1 "pred"
/*:74*/
#line 2691 "NumPSLA.w"

#endif
#line 2693 "NumPSLA.w"

/*:73*/
#line 799 "NumPSLA.w"


/*:20*/
#line 706 "NumPSLA.w"

if(n<n_max)
if(n!=split_level||countPSLA[n]%parts==part){
#if enumAOT 
boolean hopeful= true;
if(n==n_max-1){
/*53:*/
#line 2179 "NumPSLA.w"

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

/*:53*/
#line 712 "NumPSLA.w"

}
if(hopeful)
#endif
#line 716 "NumPSLA.w"
 recursive_generate_PSLA_start(n+1);

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
{localCountPSLA[n]= 0;
LINK(0,n-1,n);
LINK(0,n,1);
recursive_generate_PSLA(0,0,n);






LINK(0,n-1,1);
}

/*:17*/
#line 373 "NumPSLA.w"

int main(int argc,char*argv[])
{

/*15:*/
#line 594 "NumPSLA.w"

program_name= argv[0];
int arg= 1;
if(argc<2)
n_max= 7;
else{
if(argv[1][0]=='-'){

PRINT_INSTRUCTIONS;
exit(0);
}
n_max= parse_int(argv[1],"n",3,MAXN);
arg= 2;
}
printf("Enumeration up to n = %d pseudolines, %d points.\n",n_max,n_max+1);

if(arg<argc&&strcmp(argv[arg],"-exclude")==0){
if(arg+1>=argc)
usage_error("The option %s must be followed by the name of the exclude-file.",argv[arg]);
exclude_file_name= argv[arg+1];
arg+= 2;
if(arg<argc&&is_number(argv[arg]))
usage_error("Unexpected numeric parameter %s after the exclude-file."
" (The -exclude option cannot be combined with a splitlevel,"
" and the former extra parameter 0 is no longer used.)",argv[arg]);
printf("Excluding entries from file %s.\n",exclude_file_name);
/*25:*/
#line 905 "NumPSLA.w"

exclude_file= fopen(exclude_file_name,"r");
if(exclude_file==NULL){
fprintf(stderr,"Error: The exclude-file %s cannot be opened. Aborting.\n",
exclude_file_name);
exit(1);
}
/*26:*/
#line 917 "NumPSLA.w"

do
excluded_length= read_excluded_code();
while(excluded_length> n_max);

/*:26*/
#line 912 "NumPSLA.w"

matched_length= 2;


/*:25*/
#line 620 "NumPSLA.w"

}
else if(arg<argc&&is_number(argv[arg])){
if(n_max<4)
usage_error("Splitting is not possible for n = %s.",argv[1]);
split_level= parse_int(argv[arg],"splitlevel",3,n_max-1);
if(arg+2>=argc)
usage_error("The splitlevel %s must be followed by the two parameters parts and part.",argv[arg]);
parts= parse_int(argv[arg+1],"parts",1,1000000000);
part= parse_int(argv[arg+2],"part",0,parts);
part= part%parts;
arg+= 3;
}
if(arg<argc){
if(argv[arg][0]=='-'||is_number(argv[arg]))
usage_error("Unexpected parameter %s.",argv[arg]);
fileprefix= argv[arg++];
if(split_level==0)
if(snprintf(fname,sizeof(fname),"%s-%d.txt",fileprefix,n_max)>=(int)sizeof(fname))
usage_error("The fileprefix %s is too long.",fileprefix);
}
if(arg<argc)
usage_error("Too many parameters, starting with %s.",argv[arg]);
if(split_level> 0){
if(snprintf(fname,sizeof(fname),"%s-%d-S%d-part_%d_of_%d.txt",fileprefix,n_max,
split_level,part,parts)>=(int)sizeof(fname))
usage_error("The fileprefix %s is too long.",fileprefix);
printf("Partial enumeration: split at level n = %d. Part %d of %d.\n",
split_level,part,parts);
}
if(strlen(fname)){
printf("Results will be reported to file %s.\n",fname);
}
fflush(stdout);



/*:15*/
#line 377 "NumPSLA.w"
;
#if readdatabase 

/*81:*/
#line 146 "pred"

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


/*:81*/
#line 380 "NumPSLA.w"

return 0;
#endif
#line 383 "NumPSLA.w"
#if enumAOT
/*56:*/
#line 2251 "NumPSLA.w"


countPSLA[1]= 
countPSLA[2]= 1;
countO[3]= 
countU[3]= 
PSLAcount[2]= 
U_PSLAcount[2]= 
1;

if(strlen(fname)){
reportfile= fopen(fname,"w");
if(reportfile==NULL){
fprintf(stderr,"Error: The report-file %s cannot be opened for writing. Aborting.\n",fname);
exit(1);
}
}


/*:56*/
#line 384 "NumPSLA.w"
;
/*18:*/
#line 773 "NumPSLA.w"


LINK(1,0,2);
LINK(1,2,0);
LINK(2,0,1);
LINK(2,1,0);

LINK(0,1,2);


recursive_generate_PSLA_start(3);

/*:18*/
#line 385 "NumPSLA.w"
;
/*24:*/
#line 895 "NumPSLA.w"

if(excluded_length> 0){
fprintf(stderr,"Error: Exclude-file entry ");
print_excluded_code(stderr);
fprintf(stderr," (line %d) was never reached (not in tree). Aborting.\n",
exclude_line_number);
exit(1);
}

/*:24*/
#line 386 "NumPSLA.w"
;
/*58:*/
#line 2326 "NumPSLA.w"

printf("%34s%76s\n","#PSLA visited by the program","#PSLA computed from AOT");
for_int_from_to(n,3,n_max+1){
long long mirror_symmetric= 2*countU[n]-countO[n];
printf("n=%2d",n);
if(split_level!=0&&n> split_level)printf("*,");
else printf(", ");
printf("#PSLA=%11Ld",countPSLA[n]);
#if enumAOT
printf(", #AOT=%10Ld, #OAOT=%10Ld, #mirror-symm. AOT=%7Ld, ",
countU[n],
countO[n],mirror_symmetric
);
printf("#PSLA=%11Ld, #uPSLA=%10Ld",PSLAcount[n],U_PSLAcount[n]);
#endif
#line 2341 "NumPSLA.w"
 printf("\n");

}

if(split_level!=0)printf("* Lines with \"*\" give results from partial enumeration.\n");
#if profile
printf("Total tests is_lex_min (after screening) = %Ld, total comparisons = %Ld, average =%6.3f\n",
numTests,numComparisons,numComparisons/(double)numTests);
#endif
#line 2350 "NumPSLA.w"

#if enumAOT
printf("Prescreening: passed %Ld, saved %Ld out of %Ld = %.2f%%\n",cpass,csaved,
cpass+csaved,100*csaved/(double)(cpass+csaved));
#endif
#line 2355 "NumPSLA.w"
/*:58*//*59:*/
#line 2362 "NumPSLA.w"



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

/*:59*/
#line 387 "NumPSLA.w"
;
#endif
#line 389 "NumPSLA.w"
 return 0;
}

/*:6*/
