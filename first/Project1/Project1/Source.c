#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#define WORD_SIZE 32
int NUM_WAYS;
FILE *stuff;
FILE *check;
FILE *stream;


struct block{
	int tag;
	int index;
	int block_offset[50];
	int number_node; // number of node
	int valid; // valid = 1 gia non valid = 0
	int lru_number; //used for the lru
	int way ;//se periptosi n-way cache na apothikeute o arithmos tu node se pio way aniki
	int address;
	int dirty_bit; // 0 is ok 1 for dirty
	struct block *next;
};

int check_for_max(int q1,int q2){
	if(q1==q2)
		return 0;   //equals
	else if(q1>q2)
		return 1;   //true for q1
	else if(q1<q2)
		return -1; //false for q1
}


int logarithmos_dio(int number){
	int result;
	result = log(number)/log(2);
	return result;
}
int decimal = 0;
double z;

int binaryToDec(long int *n, int i,int limit){
int l=0;
decimal=0;
l = i-limit;
for (i;i>=limit;i--){
	
	z=pow(2.0,l);
	l--;
	//printf(" %d ",(int)z);
	//printf(" %d ",n[i]);
	decimal = decimal  + (n[i] * z);

}
return decimal;

}

void checkAction(char action,long int num,int len,int indexNo,int offset,int choice,int *numberInd,int *numberBlockOff,int *numberTag){
	double z;
	int copyI;
	int decBin=0;
	errno_t err;
	int i=0;
	int tag;
	int g;
	long int ipolipo[50];
	int location = num;
	int length = len;
	long int numRan;
	memset(ipolipo,0,sizeof(ipolipo));
	tag = len - indexNo - offset;
    err  = fopen_s( &stream, "exodos.txt", "a" );
	//printf("the tag is %d\n",tag);

	if(action == 'r'){
	//printf("He wants to read   to  cache : ");
	fprintf(stream,"He wants to read   to  cache : ");
	}
	else if(action == 'w'){
	//printf("He wants to write  to  cache : ");
	fprintf(stream,"He wants to write  to  cache : ");
	}
	else if(action == 'm'){
	//printf("He wants to modify to  cache : ");
	fprintf(stream,"He wants to modify to  cache : ");
	}
	else if(action == 'f'){
	//printf("He wants to flush  the cache : ");
	fprintf(stream,"------------------------>He wants to flush  the cache<------------------------");
	}
	else {
	//printf("Something went wrong!!!\n");
	fprintf(stream,"Something went wrong!!!\n");
	}

	while(num>0)
    {
		ipolipo[i]=num%2;
		num=num/2;
	    i++;
	}
//decBin = binaryToDec(ipolipo,i);
/*
	decimal=0;
for (i;i>=0;i--){
	
	z=pow(2.0,i);
	printf(" %d ",(int)z);
	printf(" %d ",ipolipo[i]);
	decimal = decimal+ (ipolipo[i] * z);
}
*/
//printf("\n***************** %d *****************\n",decBin);
//printing

 if(choice==1 && action != 'f'){
	if(offset>0){
		  for(i=length-1;i>=0;i--) {
	   // printf("%ld",ipolipo[i]);
		fprintf(stream,"%ld",ipolipo[i]);
		  }
	// printf(" Tag Bits: ");
	 fprintf(stream," Tag Bits: ");
	 for(i=length-1;i>=(indexNo+offset);i--) {
		// printf("%d",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	   }
	 	
	*numberTag = binaryToDec(ipolipo,length-1,indexNo+offset);
	 fprintf(stream," %d",binaryToDec(ipolipo,length-1,indexNo+offset));
	 // printf(" Index Bits: ");
	 if(indexNo>0){
		fprintf(stream," Index Bits: ");
		copyI=i;
		for(i;i>=offset;i--) {
			// printf("%ld",ipolipo[i]);
			 fprintf(stream,"%ld",ipolipo[i]);
		}
		*numberInd = binaryToDec(ipolipo,copyI,offset);
		fprintf(stream," %d",binaryToDec(ipolipo,copyI,offset));
	 }
	 // printf(" Block Bits: ");
	  fprintf_s(stream," Block Bits: ");
	  copyI=i;
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	   }
	 *numberBlockOff = binaryToDec(ipolipo,copyI,0);
	 fprintf(stream," %d",binaryToDec(ipolipo,copyI,0));
	}
	else {
	  for(i=length-1;i>=0;i--) {
	  //printf("%ld",ipolipo[i]);
	    fprintf(stream,"%ld",ipolipo[i]);
	  }
	 fprintf(stream," Tag Bits: ");
	 for(i=length-1;i>=indexNo;i--) {
		// printf("%d",ipolipo[i]);
		 fprintf(stream,"%d",ipolipo[i]);
	   }
	  *numberTag = binaryToDec(ipolipo,length-1,indexNo);
	  fprintf(stream," %d",*numberTag);
	//  printf(" Index Bits: ");
	  fprintf(stream," Index Bits: ");
	  copyI=i;
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%d",ipolipo[i]);
	 }
	 *numberInd = binaryToDec(ipolipo,copyI,0);
	 fprintf(stream," %d",*numberInd);
	 *numberBlockOff = -1;

	}
 }//end of choice1

 else if(choice==2 && action != 'f'){
	 	
	 if(offset>0){
		  for(i=length-1;i>=0;i--) {
	   // printf("%ld",ipolipo[i]);
	    fprintf(stream,"%d",ipolipo[i]);
		  }
	// printf(" Tag Bits: ");
	 fprintf(stream," Tag Bits: ");
	 for(i=length-1;i>=(indexNo+offset);i--) {
		 //printf("%d",ipolipo[i]);
		 fprintf(stream,"%d",ipolipo[i]);
	   }
	 *numberTag = binaryToDec(ipolipo,length-1,(indexNo+offset));
	 fprintf(stream," %d",*numberTag);
	  //printf(" Index Bits: ");
	  if(indexNo>0){
		fprintf(stream," Index Bits: ");
		copyI=i;
		for(i;i>=offset;i--) {
			// printf("%ld",ipolipo[i]);
			fprintf(stream,"%ld",ipolipo[i]);
		  }
		*numberInd = binaryToDec(ipolipo,copyI,offset);
		fprintf(stream," %d",*numberInd);
	  }
	   else{
		 *numberInd=0;
	 }
	//  printf(" Block Bits: ");
	  fprintf(stream," Block Bits: ");
	  copyI=i;
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	   }
	     *numberBlockOff = binaryToDec(ipolipo,copyI,0);
	     fprintf(stream," %d",*numberBlockOff);
	}
	else {
	  for(i=length-1;i>=0;i--){
	  //  printf("%ld",ipolipo[i]);
	    fprintf(stream,"%ld",ipolipo[i]);
	    }
	// printf(" Tag Bits: ");
	 fprintf(stream," Tag Bits: ");
	 for(i=length-1;i>=indexNo;i--) {
		// printf("%d",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	    }
		*numberTag = binaryToDec(ipolipo,length-1,indexNo);
		fprintf(stream," %d",*numberTag);
	 if(indexNo>0){
	 // printf(" Index Bits: ");
     fprintf(stream," Index Bits: ");
	 copyI=i;
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	    }
	 *numberInd = binaryToDec(ipolipo,copyI,0);
	 fprintf(stream," %d",*numberInd);
	 }
	 else{
		 *numberInd=0;
	 }
	 *numberBlockOff=-1;
  }//end of else
numRan = rand() % (NUM_WAYS) ;
//printf(" way:%d",numRan);
//fprintf(stream," way:%d",numRan);

 }
  else if(choice==3 && action != 'f'){
	  for(i=length-1;i>=0;i--) {
	  //  printf("%ld",ipolipo[i]);
		fprintf(stream,"%ld",ipolipo[i]);
	   }
	// printf(" Tag Bits: ");
	 fprintf(stream," Tag Bits: ");
	 for(i=length-1;i>=offset;i--) {
		// printf("%d",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
		  
	   }
		*numberTag = binaryToDec(ipolipo,length-1,offset);
		   fprintf(stream," %d",*numberTag);
	 // printf(" Block Bits: ");
	  fprintf(stream," Block Bits: ");
	 copyI=i;
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	 }
	 if(offset==0)
		 *numberBlockOff = -1;
	 else{
		 *numberBlockOff = binaryToDec(ipolipo,copyI,0);
		 fprintf(stream," %d",*numberBlockOff);
	     }
}

	//printf("\n");

	//fprintf(stream,"\n");
	if( stream )
   {
      err = fclose( stream );
   }

}//end of function checkAction

///////////////// checkaction2

void checkAction2(char action,long int num,int len2,int indexNo2,int offset2,int choice,int *numberInd2,int *numberBlockOff2,int *numberTag2){
	int tag2;
	double z;
	int copyI;
	int decBin=0;
	//errno_t err;
	int i=0;
	int g;
	long int ipolipo2[50];
	int location = num;
	int length2 = len2;
	long int numRan;
	memset(ipolipo2,0,sizeof(ipolipo2));

	tag2 = len2 - indexNo2 - offset2;
 
	while(num>0)
    {
		ipolipo2[i]=num%2;
		num=num/2;
	    i++;
	}

 if(choice==1 && action != 'f'){
		if(offset2>0){
		  for(i=length2-1;i>=0;i--) {
		  }

	// fprintf(stream," Tag Bits: ");
	 for(i=length2-1;i>=(indexNo2+offset2);i--) {
		// fprintf(stream,"%ld",ipolipo2[i]);
	   }
	*numberTag2 = binaryToDec(ipolipo2,length2-1,indexNo2+offset2);
	 //fprintf(stream," %d",binaryToDec(ipolipo2,length2-1,indexNo2+offset2));
	
	 if(indexNo2>0){
		//fprintf(stream," Index Bits: ");
		copyI=i;
		for(i;i>=offset2;i--) {
			 //fprintf(stream,"%ld",ipolipo2[i]);
		}
		*numberInd2 = binaryToDec(ipolipo2,copyI,offset2);
		//fprintf(stream," %d",binaryToDec(ipolipo2,copyI,offset2));
	 }
	 // fprintf_s(stream," Block Bits: ");
	  copyI=i;
	 for(i;i>=0;i--) {
		// fprintf(stream,"%ld",ipolipo2[i]);
	   }
	 *numberBlockOff2 = binaryToDec(ipolipo2,copyI,0);
	// fprintf(stream," %d",binaryToDec(ipolipo2,copyI,0));
	}
	else {
	  for(i=length2-1;i>=0;i--) {
	   // fprintf(stream,"%ld",ipolipo2[i]);
	  }
	 fprintf(stream," Tag Bits: ");
	 for(i=length2-1;i>=indexNo2;i--) {
		// fprintf(stream,"%d",ipolipo2[i]);
	   }
	  *numberTag2 = binaryToDec(ipolipo2,length2-1,indexNo2);
	  //fprintf(stream," %d",*numberTag2);
	  //fprintf(stream," Index Bits: ");
	  copyI=i;
	 for(i;i>=0;i--) {
		// fprintf(stream,"%d",ipolipo2[i]);
	 }
	 *numberInd2 = binaryToDec(ipolipo2,copyI,0);
	 //fprintf(stream," %d",*numberInd2);
	 *numberBlockOff2 = -1;
	}
 }//end of choice1

// else if(choice==2 && action != 'f'){
//	 	
//	 if(offset>0){
//		  for(i=length-1;i>=0;i--) {
//	   // printf("%ld",ipolipo[i]);
//	    fprintf(stream,"%d",ipolipo[i]);
//		  }
//	// printf(" Tag Bits: ");
//	 fprintf(stream," Tag Bits: ");
//	 for(i=length-1;i>=(indexNo+offset);i--) {
//		 //printf("%d",ipolipo[i]);
//		 fprintf(stream,"%d",ipolipo[i]);
//	   }
//	 *numberTag = binaryToDec(ipolipo,length-1,(indexNo+offset));
//	 fprintf(stream," %d",*numberTag);
//	  //printf(" Index Bits: ");
//	  if(indexNo>0){
//		fprintf(stream," Index Bits: ");
//		copyI=i;
//		for(i;i>=offset;i--) {
//			// printf("%ld",ipolipo[i]);
//			fprintf(stream,"%ld",ipolipo[i]);
//		  }
//		*numberInd = binaryToDec(ipolipo,copyI,offset);
//		fprintf(stream," %d",*numberInd);
//	  }
//	   else{
//		 *numberInd=0;
//	 }
//	//  printf(" Block Bits: ");
//	  fprintf(stream," Block Bits: ");
//	  copyI=i;
//	 for(i;i>=0;i--) {
//		// printf("%ld",ipolipo[i]);
//		 fprintf(stream,"%ld",ipolipo[i]);
//	   }
//	     *numberBlockOff = binaryToDec(ipolipo,copyI,0);
//	     fprintf(stream," %d",*numberBlockOff);
//	}
//	else {
//	  for(i=length-1;i>=0;i--){
//	  //  printf("%ld",ipolipo[i]);
//	    fprintf(stream,"%ld",ipolipo[i]);
//	    }
//	// printf(" Tag Bits: ");
//	 fprintf(stream," Tag Bits: ");
//	 for(i=length-1;i>=indexNo;i--) {
//		// printf("%d",ipolipo[i]);
//		 fprintf(stream,"%ld",ipolipo[i]);
//	    }
//		*numberTag = binaryToDec(ipolipo,length-1,indexNo);
//		fprintf(stream," %d",*numberTag);
//	 if(indexNo>0){
//	 // printf(" Index Bits: ");
//     fprintf(stream," Index Bits: ");
//	 copyI=i;
//	 for(i;i>=0;i--) {
//		// printf("%ld",ipolipo[i]);
//		 fprintf(stream,"%ld",ipolipo[i]);
//	    }
//	 *numberInd = binaryToDec(ipolipo,copyI,0);
//	 fprintf(stream," %d",*numberInd);
//	 }
//	 else{
//		 *numberInd=0;
//	 }
//	 *numberBlockOff=-1;
//  }//end of else
//numRan = rand() % (NUM_WAYS) ;
////printf(" way:%d",numRan);
////fprintf(stream," way:%d",numRan);
//
// }
  else if(choice==3 && action != 'f'){
	  for(i=length2-1;i>=0;i--) {
	  //  printf("%ld",ipolipo[i]);
		//fprintf(stream,"%ld",ipolipo2[i]);
	   }
	// printf(" Tag Bits: ");
	// fprintf(stream," Tag Bits: ");
	 for(i=length2-1;i>=offset2;i--) {
		// printf("%d",ipolipo[i]);
		 //fprintf(stream,"%ld",ipolipo2[i]);
		  
	   }
		*numberTag2 = binaryToDec(ipolipo2,length2-1,offset2);
		   //fprintf(stream," %d",*numberTag2);
	 // printf(" Block Bits: ");
	  //fprintf(stream," Block Bits: ");
	 copyI=i;
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 //fprintf(stream,"%ld",ipolipo2[i]);
	 }
	 if(offset2==0)
		 *numberBlockOff2 = -1;
	 else{
		 *numberBlockOff2 = binaryToDec(ipolipo2,copyI,0);
		 //fprintf(stream," %d",*numberBlockOff2);
	     }
}

	//printf("\n");/

	//fprintf(stream,"\n");
	//if( stream )
 //  {
 //     err = fclose( stream );
 //  }

}//end of function checkAction2
////////////////////////////////////////////

int main()
{
	
	int fifo_number2=0;
	int count_full2=0;
	int check_word;
	int j;
	double percentage_overall=0;
	int hit_overall=0;
	int hit2=0;
	int hit3=0;
	int read_cache2,read_victim,write_cache2,write_victim;
	int lastL2;
	int index2=0;
	int checkV=0;
	int vNo=0;
	struct block *iterator5;
	int victimSize; //APOTHIKEVI TO MEGETHOS TIS CACHE
	int victim; //PERNI TIMI O EAN DEN THELUME VICTIM CACHE, KE PERNI 1 EAN THELUME VICTIM CACHE
	struct block *iterator4,*root3;
	struct block *iterator3;
	int numberInd2,numberBlockOff2,numberTag2;
	struct block *iterator2;
	struct block *root2;
	int tag2;
	int bo2 = 0; // metavlites pu tha apothikevun ton arithmo twn index bits gia ti level 2 cache, kai ta block offset bits antistixa  
	int bits_ltwo; // arithmos twn bits pu tha xriasti i level 2 krifi mnimi
	int ltwo; // SIZE OF LEVEL 2 CACHE
	int ltwo_inclusive; // LEVEL 2 CACHE TO SET TO NUMBER 1 = EXCLUSIVE AND NUMBER 0 = INCLUSIVE
	int ltwo_enable; // LEVEL 2 CACHE TO SET TO ENABLE = 1, DISABLE = 0
	int static miss;
	errno_t err;
	double percentage;
	int static total_cycles=0;
	int read_cache,read_ram,write_cache,write_ram;
	int lru_way;
	int flag2;
	int numWays[32];
	int way_fifo_number[32];
	int cpNum; // copy tis metavlitis NUM_WAYS
	int way_zero2;
	int way_node_number=0;
	int way_zero;
	int base;
	int max,max_node,indicate,rn;
	int flag=0;
	int count_full=0;
	int fifo_number=0;
	char dat;
	int numberInd,numberBlockOff,numberTag;
	struct block *root;      
	struct block *iterator;
	int bo = 0;     //xrisi metavlitis gia to block offset 
	int flush = 0;  //xrisi metavlitis gia ton arithmo twn flush
	int words = 0;  //xrisi metavlitis posa words 8a exei ena block sto data
	int ch;			//xrisi metavlitis gia na diavazi apo to arxeio dedwmenwn 
	int address;    //xrisi metavlitis gia na perna ton arithmo dieuthinsis(ton dekadiko) apo to arxio dedwmenwn
	int times;	    //xrisi metavlitis gia to poses fores na kani reference(entries) 
	int krifi;	    //xrisi metavlitis gia na apothikeusi to megethos tis cache memory
	int bitsRam;	//xrisi metavlitis gia ta bits pou tha exi i Ram
	int bitsCache;  //xrisi metavlitis gia na kratai ta bits tis cache memory
	long int size;    //size pu dinume gia ti cache
	int min = 0;  //xrisi tou ston ipologismo tis rand() 
	int yo = 0; //xrisi toy sto for loop gia dimiurgia tu file dedwmenwn
	int r, i;  // ypologizun tixea arithmo mexri to max pu tu dinume
	char work[4] = { 'r','w' ,'m','f' } ; //r:read, w:write, m:modify, f:flush
	int index;	// xrisi tu sto sto na exi posa bit 8a exi to index 
	int choice; // apothikeui tin epilogi toy xristi
	int bytesWord =  WORD_SIZE / 8; // exi tin timi twn bytesWord
	int tag; // exi tin timi twn tag bits 
	int blu = 0; // metavliti gia tin voithia wste na emfanizete akomi ena minima se periptosi lawthwvn isodwn pu dini o xristis 
	int s; // xrisi tis gia ton elegxo sto an ine se dinami tu 2 i timi pu dinete ,xrisi tis se periptosis pio katw gia to megethos
	int counter = 0; // counter for the flush
	int flusho; //ena guarantee rate poses fores 8a emfanizete to flush,ypologizete pio kato i timi 
	char b;
	int type; // tipos tou algorithmu antikatastasis
	int write_type;
	int allocate;
	int wayNum;
	int v;
	int p;
	int static hit = 0;
	//int miss = 0;
	allocate=-1;
	//remove("exodos.txt");
fopen_s(&check,"eisodos.txt","r");
if(check != NULL){
		printf("The file opened ok!\n");
	}	
	else{
		printf("failed to create the file \n");
	}
	//the reading process begins here!!!!
	fscanf_s(check,"%c",&b,1); 
	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&size); 

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&krifi);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&ltwo);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&ltwo_inclusive); 

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&ltwo_enable); 

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&victim); 

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&victimSize); 

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&times); 

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&flush);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&words);
	
	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&choice);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&wayNum);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&type);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&write_type);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&allocate);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&read_cache);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&read_ram);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&write_cache);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&write_ram);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&read_cache2);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&read_victim);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&write_cache2);

	while((char)b!=','){
	fscanf_s(check,"%c",&b,1);
	}
	fscanf_s(check,"%c",&b,1); 
	fscanf_s(check,"%d",&write_victim);
	//the reading process ends here!!!!
	
	// just for checking
	//printf("victim is %d\n",victim);
	//printf("victim size is %d\n",victimSize);
	//printf("the level 2 cache size is %d and it is enabled? %d and is exlusive? %d \n",ltwo,ltwo_enable,ltwo_inclusive); 
	/*printf("read cache2: %d\n",read_cache2);
	printf("read victim: %d\n",read_victim);
	printf("write cache2: %d\n",write_cache2);
	printf("write victim: %d\n",write_victim);*/
	//printf("the type of algorith is: %d\n",type);
	//printf("the type of the write is: %d\n",write_type);
	
	
		// elegxos an o arithmos pio pano sto #define NUM_WAYS, ine se dinami tu 2, alios termatizi to programa
	s = wayNum && !(wayNum & (wayNum - 1));
		if(s==0){
			printf("Please give a number for the NUM_WAYS in power 2,excluding zero! and rerun the program\n");
			system("pause");
			exit(0);
		}
	NUM_WAYS = wayNum;
	
	
	//s = size && !(size & (size - 1));
	//if(s==0){
	//		printf("Please give a number for the size in power 2,excluding zero! and rerun the program\n");
	//		system("pause");
	//		exit(0);
	//	}
	
	s = krifi && !(krifi & (krifi - 1));
		if(s==0 || size<krifi){
			printf("Please give a number for the cache in power 2,excluding zero! and rerun the program\n");
			printf("The cache must be smaller in size from main memory\n");
			system("pause");
			exit(0);
		}
	
	if(times<=0){
		printf("Please references to the cache memory,must be a positive number! (excluding zero) and rerun the program\n");
		system("pause");
		exit(0);
	}
	if(flush<0){
		printf("The times you want the flush to operate,must be a positive number!, and rerun the program\n");
		system("pause");
		exit(0);
	}

	s = words && !(words & (words - 1));
	if(s==0){
		printf("The words must be in power of 2!,and rerun the program\n");
		system("pause");
		exit(0);
	}
	
	s = ltwo && !(ltwo & (ltwo - 1));
	if(s==0){
		printf("The size of level 2 cache must be in power of 2!, please rerun the program\n");
		system("pause");
		exit(0);
	}

	if(( (ltwo_enable<=-1) || (ltwo_enable>=2) )){
		printf("The number for variable enable/disable for Level 2 cache must be 1 or 0, please rerun the program\n");
		system("pause");
		exit(0);
	}

	if(( (ltwo_inclusive<=-1) || (ltwo_inclusive>=2) )){
		printf("The number for variable exclusive/inclusive for Level 2 cache must be 1 or 0, please rerun the program\n");
		system("pause");
		exit(0);
	}

		if(( (victim<=-1) || (victim>=2) )){
		printf("The number for variable victim for victim cache must be 1 or 0, please rerun the program\n");
		system("pause");
		exit(0);
	}

		if(victimSize<=0){
		printf("The size for victim cache must be in words and bigger than 0!, please rerun the program\n");
		system("pause");
		exit(0);
	}

		if(ltwo<krifi || ltwo>size){
			printf("The level 2 cache must be smaller in size from main memory and bigger in size from level 1 cache\n");
			system("pause");
			exit(0);
		}

	ltwo = ltwo / bytesWord;   //ipologismos twn 8esewn(arithmos twn blocks tis level 2 krifis mnimis)
	size = size / bytesWord;   //ipologismos twn 8esewn(arithmos twn blocks tis kirias mnimis)
	krifi = krifi / bytesWord; //ipologismos twn 8esewn(arithmos twn blocks tis krifis mnimis)
	
	if(ltwo_enable==1){
		bits_ltwo = logarithmos_dio(ltwo);
		printf("Bits for the level 2 cache memory %d\n",bits_ltwo);

	}
	bitsRam = logarithmos_dio(size);
	printf("Bits for the main memory %d\n",bitsRam);
	bitsCache = logarithmos_dio(krifi);
	printf("Bits for the cache memory %d\n",bitsCache);
		
	if(( (choice<=0) || (choice>3) )){
		printf("Please give me a choice between 1-3 only!, and rerun the program");
		system("pause");
		exit(0);
	}
	if(read_cache<0){
		printf("Please read cache must be a positive number! and rerun the program\n");
		system("pause");
		exit(0);
	}
	if(read_ram<0){
		printf("Please read ram must be a positive number! and rerun the program\n");
		system("pause");
		exit(0);
	}
	if(write_cache<0){
		printf("Please write cache must be a positive number! and rerun the program\n");
		system("pause");
		exit(0);
	}
	if(write_ram<0){
		printf("Please write ram must be a positive number! and rerun the program\n");
		system("pause");
		exit(0);
	}
	if(( (write_type<0) || (write_type>1) )){
		printf("Please give me a write type between 0 or 1 only!, and rerun the program");
		system("pause");
		exit(0);
	}
	if(( (allocate<0) || (allocate>1) )){
		printf("Please give me a allocate between 0 or 1 only!, and rerun the program");
		system("pause");
		exit(0);
	}
// ginete diadikasia ipologismu twn pediwn dieuthintodotisis vasi twn pliroforiwn pio panw
	if(choice==1){
		if(words>1){
			bo = logarithmos_dio(words);
			index = logarithmos_dio(krifi/words);
			if(ltwo_enable==1){
				bo2 = logarithmos_dio(words);
				index2 = logarithmos_dio(ltwo/words);
			     }
		  } else {
	    if(ltwo_enable==1){
			index2 = bits_ltwo;
				}
		index = bitsCache;
			}
	  } else if(choice==2){
			if(words>1){
				bo = logarithmos_dio(words);
				index = logarithmos_dio((krifi/(NUM_WAYS))) - logarithmos_dio(words);
				if(ltwo_enable==1){
					bo2 = logarithmos_dio(words);
					index2 = logarithmos_dio((ltwo/(NUM_WAYS))) - logarithmos_dio(words);
					}
			  } else {
					index = logarithmos_dio(krifi/NUM_WAYS);
					if(ltwo_enable==1){
						index2 = logarithmos_dio(ltwo/NUM_WAYS);
						}
		        }
	   } else if(choice==3){
		   printf("There are no index-set bits here!\n");
		   index = 0;
		   if(words>1){
				bo = logarithmos_dio(words);
		   if(ltwo_enable==1)
			    bo2 = logarithmos_dio(words);
		   }
	   } else{
		printf("you did not choose something!!!\n");
		exit(0);
	}

tag = bitsRam - index - bo;

printf("the tag is %d bits \n",tag);
printf("the index is %d bits \n",index);

if(ltwo_enable==1){
tag2 = bitsRam - index2 - bo2;

printf("the tag of level 2 cache is %d bits \n",tag2);
printf("the index of level 2 cache is %d bits \n",index2);
}
if(flush!=0)
	flusho = ((times*size) / flush); //ypologismos gia to kathe poses fores iparxi periptosi na epilegi to flush
else 
	flusho = flush;

if(words>1){
	printf("the block offset %d bits \n",bo);
	if(ltwo_enable==1)
		printf("the block offset for level 2 cache is %d bits \n",bo2);
}

//  Anigma arxiu gia na gini i eggrafi,elegxos an ginete 
	fopen_s(&stuff,"dedwmena.txt","w");
	if(stuff != NULL){
		printf("The file opened ok!\n");
	}	
	else{
		printf("failed to create the file \n");
	}

	srand((int)time(NULL));
		for(yo;yo<(size*times);yo++) {
			if(flush>0 && counter>=flusho){
				r = (rand() % (size-min))+min;
				i = (rand() % (3+1-min))+min;
				if(i==3) {
					flush--;
					counter=0;
				  }
				//printf("%c %d\n",work[i],r);
				fprintf_s(stuff,"%c %d\n",work[i],r);
			}
			else{
				r = (rand() % (size-min))+min;
				i = (rand() % (3-min))+min;
				//printf("%c %d\n",work[i],r);
				fprintf_s(stuff,"%c %d\n",work[i],r);
			}
		counter++; //auxisi tou counter gia ipologismo twn forwn pu den egine to flush
		}//end of for loop
	
	fclose(stuff); //klisimo arxiou dedwmenwn 
	fopen_s(&stuff,"dedwmena.txt","r"); //anigma xana tou arxiou dedwmenwn gia diavasma
	//printf("NUM_WAYS %d\n",NUM_WAYS);
	//printf(" %d \n",(krifi/words));
	if(victim==1){
		 root3 = (struct block *) malloc( sizeof(struct block) ); 
		 root3->next = 0;
		 root3->index = 0;
		 root3->valid = 0;
		 root3->number_node = 0;
		 iterator4 = root3;

		 for(v=1;v<=(victimSize);v++){
		iterator4->next =(struct block *) malloc( sizeof(struct block) ); 
		iterator4 = iterator4->next;
		iterator4->index=v;
		iterator4->valid=0;
		iterator4->number_node=v;
	}
	iterator4->next = 0;
	iterator4 = root3;
	while(iterator4->next!=0)
	{
		//printf(" [%d]-> ",iterator4->number_node);
		iterator4 = iterator4->next;
	}
	iterator4 = root3;
	
}//end of creation of victim cache
	if(choice==1){

    root = (struct block *) malloc( sizeof(struct block) ); 
	root->next = 0;
	root->index = 0;
	root->valid = 0;
	iterator = root;

	for(v=1;v<=(krifi/words);v++){
		
		iterator->next =(struct block *) malloc( sizeof(struct block) ); 
		iterator = iterator->next;
		iterator->index=v;
		iterator->valid=0;
	}
	iterator->next = 0;
	iterator = root;
	while(iterator->next!=0)
	{
		printf(" [%d]-> ",iterator->index);
		iterator = iterator->next;
	}
	iterator = root;

	if(ltwo_enable==1){
		
	root2 = (struct block *) malloc( sizeof(struct block) ); 
	root2->next = 0;
	root2->index = 0;
	root2->valid = 0;
	iterator2 = root2;

	for(v=1;v<=(ltwo/words);v++){
		iterator2->next =(struct block *) malloc( sizeof(struct block) ); 
		iterator2 = iterator2->next;
		iterator2->index=v;
		iterator2->valid=0;
	}
	iterator2->next = 0;
	iterator2 = root2;

	while(iterator2->next!=0)
	{
		//printf(" [%d]-> ",iterator2->index);
		iterator2 = iterator2->next;
	}
	iterator2 = root2;
	
	 }//creation for level 2 cache
	}
	else if(choice==3){
	root = (struct block *) malloc( sizeof(struct block) ); 
	root->next = 0;
	root->valid = 0;
	root->number_node = 0;
	root->lru_number=0;
	iterator = root;
	

	for(v=1;v<=(krifi/words);v++){
		iterator->next =(struct block *) malloc( sizeof(struct block) ); 
		iterator = iterator->next;
		iterator->number_node=v;
		iterator->valid=0;
		iterator->lru_number=0;
	}
	iterator->next = 0;
	iterator = root;
	//while(iterator->next!=0)
	//{
	////	printf(" [%d]-> ",iterator->number_node);
	//	iterator = iterator->next;
	//}
	//iterator = root;
		if(ltwo_enable==1){
		
	root2 = (struct block *) malloc( sizeof(struct block) ); 
	root2->next = 0;
	root2->number_node = 0;
	root2->lru_number=0;
	root2->valid = 0;
	iterator2 = root2;

	for(v=1;v<=(ltwo/words);v++){
		iterator2->next =(struct block *) malloc( sizeof(struct block) ); 
		iterator2 = iterator2->next;
		iterator2->lru_number=0;
		iterator2->number_node=v;
		iterator2->valid=0;
	}
	iterator2->next = 0;
	iterator2 = root2;

	while(iterator2->next!=0)
	{
		//printf(" [%d]-> ",iterator2->number_node);
		iterator2 = iterator2->next;
	}
	iterator2 = root2;
	
	 }//creation for level 2 cache
	}//end of choice 3

	else if(choice==2){

	root = (struct block *) malloc( sizeof(struct block) ); 
	root->next = 0;
	root->valid = 0;
	root->index = 0;
	root->number_node = way_node_number;
	root->lru_number=0;
	root->way = 0;
	iterator = root;
	way_node_number++;


	for(way_zero=0;way_zero<(NUM_WAYS-1);way_zero++){
			iterator->next =(struct block *) malloc( sizeof(struct block) ); 
			iterator = iterator->next;
			iterator->number_node=way_node_number;
			iterator->index = 0;
			iterator->valid=0;
			iterator->way = way_zero + 1 ;
			iterator->lru_number=0;
			way_node_number++;
	}
	v=1;

	while(v<((krifi/words)/NUM_WAYS)){
			for(way_zero2=0;way_zero2<NUM_WAYS;way_zero2++){
				iterator->next =(struct block *) malloc( sizeof(struct block) ); 
				iterator = iterator->next;
				iterator->number_node=way_node_number;
				iterator->valid=0;
				iterator->index = v;
				iterator->lru_number=0;
				iterator->way = way_zero2;
				way_node_number++;
				
			 }
			v++;
	  }
	iterator->next =(struct block *) malloc( sizeof(struct block) ); 
				iterator = iterator->next;
				iterator->number_node=way_node_number;
				iterator->valid=0;
				iterator->index = v;
				iterator->way=way_zero2;
				iterator->lru_number=0;

	iterator->next = 0;
	iterator = root;
		while(iterator->next!=0)
	{
		printf(" [%d]-> ",iterator->number_node);
		printf(" %d",iterator->index);
		printf(" way %d\n",iterator->way);
		iterator = iterator->next;
	}
	iterator = root;
	memset(numWays,0,sizeof(numWays));
	memset(way_fifo_number,0,sizeof(way_fifo_number));
	}//end of choice 2 

	for(i=0;i<(size*times);i++){
	fscanf_s(stuff,"%c",&ch,1);
	fscanf_s(stuff,"%d\n",&address,4);
	checkAction((char)ch,(long int)address,bitsRam,index,bo,choice,&numberInd,&numberBlockOff,&numberTag);
	err  = fopen_s(&stream, "exodos.txt","a");
	
	dat=(char)ch;

	if(choice==1){
	if(numberBlockOff==-1){
		if(dat=='r'){
	iterator=root;
		while(iterator->next!=0){
			if(iterator->index==numberInd){
				if(iterator->tag==numberTag && iterator->valid==1){
		
						printf("hit at read %d\n",address);
						fprintf(stream," Hit at read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
						hit++;
					  }
					
				else{
					if(iterator->valid!=1){
						miss++;
						printf("miss at read %d\n",address);
						fprintf(stream," miss at read %d ",address);
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}

					}else{
						printf("miss at L1 read %d\n",address);
						fprintf(stream," miss at L1 read %d ",address);
						if(ltwo_enable==1){
						checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);

					iterator2=root2;
				    while(iterator2->next!=0){
						if(iterator2->index==numberInd2){
							if(iterator2->tag==numberTag2 && iterator2->valid==1){
								checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
										printf(" hit at L2 read %d\n",address);
										fprintf(stream," Hit at L2 read %d ",address);

											if(write_type==0 && allocate==1){
												total_cycles =  total_cycles + write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
												total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
												total_cycles =  total_cycles + write_cache + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache));
											}
										hit2++;
										iterator3=root2;
									while(iterator3->next!=0){
									if(iterator3->index==numberInd2){
										 iterator3->tag=numberTag2;
										 iterator3->valid=1;
										 iterator3->address=iterator->address;
										}
									iterator3=iterator3->next;
									  }
										iterator->tag=numberTag;
										iterator->valid=1;
										iterator->address=address;
							  }
							else{
										printf(" Miss at L2 read %d\n",address);
										fprintf(stream," Miss at L2 read %d ",address);
										if(ltwo_inclusive==1){
										printf("iterator->address %d\n",iterator->address);
									    checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
										printf("numberTag2 %d\n",numberTag2);
										printf("numberInd2 %d\n",numberInd2);
										if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at victim cache read  %d\n",address);
												fprintf(stream," Hit at victim cache read %d ",address);
												checkV=1;

												
											if(write_type==0 && allocate==1){
												total_cycles =  total_cycles + write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
												total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
												total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}
											hit3++;

												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at victim cache read  %d\n",address);
												fprintf(stream," Miss at victim cache read %d ",address);

														
											if(write_type==0 && allocate==1){
												total_cycles =  total_cycles + write_cache + read_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
												total_cycles = total_cycles +  write_cache + read_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
												total_cycles =  total_cycles + write_cache + read_ram;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_ram;
											fprintf(stream," cycles: %d ",(write_cache));
											}

										  }
										}//end of victim enable

										if(write_type==0 && allocate==1){
												total_cycles =  total_cycles + write_cache + read_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
												total_cycles = total_cycles +  write_cache + read_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
												total_cycles =  total_cycles + write_cache + read_ram;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_ram;
											fprintf(stream," cycles: %d ",(write_cache));
											}

										iterator3=root2;
										while(iterator3->next!=0){
											if(iterator3->index==numberInd2){

												if(checkV==0 && victim==1){
													iterator4=root3;
													while(iterator4->next!=0){
														if(iterator4->number_node==vNo){
															iterator4->address=iterator3->address;
															vNo++;
															break;
														}
													iterator4=iterator4->next;
												    }//end of inner while loop
											    } 
												if(checkV==0){
												iterator3->tag=numberTag2;
												iterator3->valid=1;
												iterator3->address=iterator->address;
												}
												}
												iterator3=iterator3->next;
									         }
										if(checkV==0){
										iterator->tag=numberTag;
										iterator->valid=1;
										iterator->address=address;
										 
										}
										if(vNo>=victimSize){
											vNo=0;
										  }
										}
										else if(ltwo_inclusive==0){
											if(victim==0){
											iterator2->tag=numberTag2;
											iterator2->valid=1;
											iterator2->address=address;
											iterator->tag=numberTag;
											iterator->valid=1;
											iterator->address=address;
											}
											else if(victim==1){
												iterator4=root3;
												checkV=0;
													while(iterator4->next!=0){
														if(iterator4->address==address){
														printf(" Hit at victim cache read  %d\n",address);
														fprintf(stream," Hit at victim cache read %d ",address);
														checkV=1;
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}
															hit3++;
														break;
															}
													iterator4=iterator4->next;
													}
												   if(checkV==0){
														printf(" Miss at victim cache read  %d\n",address);
														fprintf(stream," Miss at victim cache read %d ",address);
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}
													 }
												   if(checkV==0){
												iterator4=root3;
												while(iterator4->next!=0){
													if(iterator4->number_node==vNo){
														iterator4->address=iterator2->address;
														vNo++;
														break;
													  }
												iterator4=iterator4->next;
												}
												iterator2->tag=numberTag2;
												iterator2->valid=1;
												iterator2->address=address;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												 }
												if(vNo>=victimSize){
													vNo=0;
												 }
											}
										} //end of ltwo inclusive
							  }
						    }
						iterator2=iterator2->next;
					    } // end of while iterator2
					 }//end of enable 
					 else{
						 	if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at victim cache read  %d\n",address);
												fprintf(stream," Hit at victim cache read %d ",address);
												checkV=1;
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}
															hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at victim cache read  %d\n",address);
												fprintf(stream," Miss at victim cache read %d ",address);
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}
										  }
										}//end of victim enable
						 if(victim==1 && checkV==0){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
									iterator4->address=iterator->address;
									vNo++;
									break;
								}
								iterator4=iterator4->next;
							}
						 }
						 if(checkV==0){
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						 }
						if(vNo>=victimSize){
							vNo=0;
						  }
					  }//end of else enable
				    }

				  } //end of else(miss)
				 }
			iterator = iterator->next;
			}

  }//end of read
  if(dat=='w'){
		iterator=root;
		while(iterator->next!=0){
			if(iterator->index==numberInd){
				if(iterator->tag==numberTag && iterator->valid==1){
		
						printf("hit at write %d\n",address);
						fprintf(stream," Hit at write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
						hit++;
					  }
				else{
					if(iterator->valid!=1){
						miss++;
						printf("Compulsory miss at write %d\n",address);
						fprintf(stream," Compulsory miss at write %d ",address);

						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}

						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
					}else{
						printf("Conflict miss at L1 write %d\n",address);
						fprintf(stream," Conflict miss at L1 write %d ",address);
						if(ltwo_enable==1){
						checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);

						iterator2=root2;

				    while(iterator2->next!=0){
						if(iterator2->index==numberInd2){
							if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf(" hit at L2 write  %d\n",address);
										fprintf(stream," Hit at L2 write %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache));
											}
											hit2++;
											iterator3=root2;
									while(iterator3->next!=0){
									if(iterator3->index==numberInd2){
										 iterator3->tag=numberTag2;
										 iterator3->valid=1;
										 iterator3->address=iterator->address;
										}
									iterator3=iterator3->next;
									  }
										iterator->tag=numberTag;
										iterator->valid=1;
										iterator->address=address;
							  }
							else{
										printf(" Miss at L2 write  %d\n",address);
										fprintf(stream," Miss at L2 write %d ",address);
										if(ltwo_inclusive==1){
										printf("iterator->address %d\n",iterator->address);
									    checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
										printf("numberTag2 %d\n",numberTag2);
										printf("numberInd2 %d\n",numberInd2);
										if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at victim cache write  %d\n",address);
												fprintf(stream," Hit at victim cache write %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}
											hit3++;
												checkV=1;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at victim cache write  %d\n",address);
												fprintf(stream," Miss at victim cache write %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}

										  }
										}//end of victim enable
										iterator3=root2;
										while(iterator3->next!=0){
											if(iterator3->index==numberInd2){

												if(checkV==0 && victim==1){
													iterator4=root3;
													while(iterator4->next!=0){
														if(iterator4->number_node==vNo){
															iterator4->address=iterator3->address;
															vNo++;
															break;
														}
													iterator4=iterator4->next;
												    }//end of inner while loop
											    } 
												if(checkV==0){
												iterator3->tag=numberTag2;
												iterator3->valid=1;
												iterator3->address=iterator->address;
												}
												}
												iterator3=iterator3->next;
									         }
										if(checkV==0){
										iterator->tag=numberTag;
										iterator->valid=1;
										iterator->address=address;
										 
										}
										if(vNo>=victimSize){
											vNo=0;
										  }
										}
										else if(ltwo_inclusive==0){
											if(victim==0){
											iterator2->tag=numberTag2;
											iterator2->valid=1;
											iterator2->address=address;
											iterator->tag=numberTag;
											iterator->valid=1;
											iterator->address=address;
											}
											else if(victim==1){
												iterator4=root3;
												checkV=0;
													while(iterator4->next!=0){
														if(iterator4->address==address){
														printf(" Hit at victim cache write  %d\n",address);
														fprintf(stream," Hit at victim cache write %d ",address);
														checkV=1;
														break;

																if(write_type==0 && allocate==1){
																total_cycles =  total_cycles + write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==0 && allocate==0){
																total_cycles = total_cycles +  write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==1 && allocate==0){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}if(write_type==1 && allocate==1){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}
																hit3++;
														}
													iterator4=iterator4->next;
													}
												   if(checkV==0){
														printf(" Miss at victim cache write  %d\n",address);
														fprintf(stream," Miss at victim cache write %d ",address);

															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}

													 }
												   if(checkV==0){
												iterator4=root3;
												while(iterator4->next!=0){
													if(iterator4->number_node==vNo){
														iterator4->address=iterator2->address;
														vNo++;
														break;
													  }
												iterator4=iterator4->next;
												}
												iterator2->tag=numberTag2;
												iterator2->valid=1;
												iterator2->address=address;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												 }
												if(vNo>=victimSize){
													vNo=0;
												 }
											}
										} // end of level two inclusive
							  }
						    }
						iterator2=iterator2->next;
					    } // end of while iterator2
					 }//end of enable 
					 else{
								if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at victim cache write  %d\n",address);
												fprintf(stream," Hit at victim write read %d ",address);
												checkV=1;

													if(write_type==0 && allocate==1){
																total_cycles =  total_cycles + write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==0 && allocate==0){
																total_cycles = total_cycles +  write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==1 && allocate==0){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}if(write_type==1 && allocate==1){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}
																hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at victim cache write  %d\n",address);
												fprintf(stream," Miss at victim cache write %d ",address);

												if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}
										  }
										}//end of victim enable
						 if(victim==1 && checkV==0){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
									iterator4->address=iterator->address;
									vNo++;
									break;
								}
								iterator4=iterator4->next;
							}
						 }
						if(checkV==0){
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						}
						if(vNo>=victimSize){
							vNo=0;
						  }
					  }//end of else enable
				    }

				  } //end of else(miss)
				 }
			iterator = iterator->next;
			}
	 } //end of write
   if(dat=='m'){
		 iterator=root;
		 	while(iterator->next!=0){
			if(iterator->index==numberInd){
				if(iterator->tag==numberTag && iterator->valid==1){
				
						printf("hit to modify the word at level 1 cache at %d\n",address);
						fprintf(stream," hit to modify the word at level 1 cache at %d ",address);
						hit++;
						total_cycles = total_cycles + read_cache ;
						fprintf(stream," cycles: %d ",(read_cache));
					   }
			    else{
					    printf("miss to modify at level 1 cache at %d\n",address);
						miss++;
						fprintf(stream," miss to modify the word at level 1 cache at %d ",address);
						total_cycles = total_cycles + read_cache + read_ram;
						fprintf(stream," cycles: %d ",(read_cache + read_ram));
						if(ltwo_enable==1){
							checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2=root2;
							while(iterator2->next!=0){
								if(iterator2->index==numberInd2){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("hit to modify the word at level 2 cache at %d\n",address);
										fprintf(stream," hit to modify the word at level 2 cache at %d ",address);
										hit2++;
										total_cycles = total_cycles + read_cache2 + read_cache ;
										fprintf(stream," cycles: %d ",(read_cache + read_cache2 ));
										break;
									  }
									else{
										printf("miss to modify the word at level 2 cache at %d\n",address);
										fprintf(stream," miss to modify the word at level 2 cache at %d ",address);

										total_cycles = total_cycles + read_cache + read_ram + read_cache2;
										fprintf(stream," cycles: %d ",(read_cache + read_ram + read_cache2));

										if(victim==1){
											iterator4=root3;
											checkV=0;
											while(iterator4->next!=0){
												if(iterator4->address==address){
													printf(" hit to modify the word at victim cache at %d\n",address);
													fprintf(stream," hit to modify the word at victim cache at %d ",address);
													hit3++;
													total_cycles = total_cycles + read_cache2 + read_cache + read_victim;
													fprintf(stream," cycles: %d ",(read_cache + read_cache2 + read_victim));
													checkV=1;
													break;
												}
											iterator4=iterator4->next;
											}
											if(checkV==0){
												printf(" miss to modify the word at victim cache at %d\n",address);
												fprintf(stream," miss to modify the word at victim cache at %d ",address);
												total_cycles = total_cycles + read_cache + read_ram + read_cache2 + read_victim;
												fprintf(stream," cycles: %d ",(read_cache + read_ram + read_cache2 + read_victim));
											}	
										} //end of victim
									break;
									}
								 }
								iterator2=iterator2->next;
							 }
				       }
						else if(ltwo_enable=0){
							if(victim==1){
											iterator4=root3;
											checkV=0;
											while(iterator4->next!=0){
												if(iterator4->address==address){
													printf(" hit to modify the word at victim cache at %d\n",address);
													fprintf(stream," hit to modify the word at victim cache at %d ",address);
													checkV=1;
													hit3++;
													total_cycles = total_cycles + read_cache + read_victim;
													fprintf(stream," cycles: %d ",(read_cache + read_cache + read_victim));
													break;
												}
											iterator4=iterator4->next;
											}
											if(checkV==0){
												printf(" miss to modify the word at victim cache at %d\n",address);
												fprintf(stream," miss to modify the word at victim cache at %d ",address);
												total_cycles = total_cycles + read_cache + read_victim + read_ram;
												fprintf(stream," cycles: %d ",(read_cache + read_cache + read_victim + read_ram));
											}	
								} //end of victim
						}

	
				 }//end of else
			}
						iterator = iterator->next;
		} //end of while
    }
   if(dat=='f'){
		 iterator=root;
			while(iterator->next!=0){
				iterator->valid=0;
				iterator = iterator->next;
			  }
		if(ltwo_enable==1){
			iterator2=root2;
			while(iterator2->next!=0){
				iterator2->valid=0;
				iterator2 = iterator2->next;
			  }
		}
		if(victim==1){
			iterator4=root3;
			while(iterator4->next!=0){
				iterator4->valid=0;
				iterator4 = iterator4->next;
			  }
		}
	 }
	  
 }//ean numberBlockoff=-1 end of if statement
	else{

if(dat=='r'){
		
		iterator=root;
		while(iterator->next!=0){
			if(iterator->index==numberInd){
				
				if(iterator->tag==numberTag && iterator->valid==1){
					
					if(iterator->block_offset[numberBlockOff]==address){
						printf("hit at read %d\n",address);
						fprintf(stream," Hit at read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
						hit++;
					  }else{
					printf("miss at read %d\n",address);
					fprintf(stream," Miss at read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
						iterator->block_offset[numberBlockOff]=address;
					  }
					 }
				else{
					if(iterator->valid!=1){
						miss++;
						printf("miss at read %d\n",address);
						fprintf(stream," miss at read %d ",address);

						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}

						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						iterator->block_offset[numberBlockOff]=address;
					}else{
						printf("miss at L1 read %d\n",address);
						fprintf(stream," miss at L1 read %d ",address);
						if(ltwo_enable==1){
						checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						//printf("\nnumber block off is %d",numberBlockOff2);
						iterator2=root2;

				    while(iterator2->next!=0){
						if(iterator2->index==numberInd2){
							if(iterator2->tag==numberTag2 && iterator2->valid==1){
								if(iterator2->block_offset[numberBlockOff2]==address){
										printf(" hit at L2 read  %d\n",address);
										fprintf(stream," Hit at L2 read %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache));
											}
											hit2++;

								}
							  }
							else{
										printf(" Miss at L2 read  %d\n",address);
										fprintf(stream," Miss at L2 read %d ",address);
										if(ltwo_inclusive==1){
										//	printf("iterator->address %d\n",iterator->block_offset[numberBlockOff]);
										checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
									//	if(iterator->block_offset[numberBlockOff]<0)

									//	printf("numberTag2 %d\n",numberTag2);
										//printf("numberInd2 %d\n",numberInd2);

										if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at victim cache read %d\n",address);
												fprintf(stream," Hit at victim cache read %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}
											hit3++;
												checkV=1;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at victim cache read %d\n",address);
												fprintf(stream," Miss at victim cache read %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}

										  }
										}//end of victim enable

										iterator3=root2;
										while(iterator3->next!=0){
											if(iterator3->index==numberInd2){

												if(checkV==0 && victim==1){
													iterator4=root3;
													while(iterator4->next!=0){
														if(iterator4->number_node==vNo){
															for(j=0;j<words;j++){
																if(iterator3->block_offset[j]>=0){
																	iterator4->address=iterator3->block_offset[j];
																	vNo++;
																}
															}
														break;
														}
													iterator4=iterator4->next;
												    }//end of inner while loop
											    } 
												//miss at l2 level and i dont have a victim cache
												if(checkV==0){
												iterator3->tag=numberTag2;
												iterator3->valid=1;
												iterator3->address=iterator->address;
												iterator3->block_offset[numberBlockOff2]=iterator->address;
												}
												}
												iterator3=iterator3->next;
									         }
										if(checkV==0){
										iterator->tag=numberTag;
										iterator->valid=1;
										iterator->address=address;
										iterator->block_offset[numberBlockOff]=address;
										 
										}
										if(vNo>=victimSize){
											vNo=0;
										  }
										}
										else if(ltwo_inclusive==0){
											if(victim==0){
											iterator2->tag=numberTag2;
											iterator2->valid=1;
											iterator2->address=address;
											iterator2->block_offset[numberBlockOff2]=address;
											iterator->tag=numberTag;
											iterator->valid=1;
											iterator->address=address;
											iterator->block_offset[numberBlockOff]=address;
											}
											else if(victim==1){
												iterator4=root3;
												checkV=0;
													while(iterator4->next!=0){
														if(iterator4->address==address){
														printf(" Hit at victim cache read  %d\n",address);
														fprintf(stream," Hit at victim cache read %d ",address);
														

																if(write_type==0 && allocate==1){
																total_cycles =  total_cycles + write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==0 && allocate==0){
																total_cycles = total_cycles +  write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==1 && allocate==0){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}if(write_type==1 && allocate==1){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}
																hit3++;
														checkV=1;
														break;
														}
													iterator4=iterator4->next;
													}
												   if(checkV==0){
														printf(" Miss at victim cache read  %d\n",address);
														fprintf(stream," Miss at victim cache read %d ",address);

															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}

													 }
												   if(checkV==0){
												iterator4=root3;
												while(iterator4->next!=0){
													if(iterator4->number_node==vNo){
														for(j=0;j<words;j++){
																if(iterator2->block_offset[j]>=0){
																	iterator4->address=iterator2->block_offset[j];
																	vNo++;
																}
															}
														break;
													  }
												iterator4=iterator4->next;
												}
												iterator2->tag=numberTag2;
												iterator2->valid=1;
												iterator2->address=address;
												iterator2->block_offset[numberBlockOff2]=address;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												iterator->block_offset[numberBlockOff]=address;
												 }
												if(vNo>=victimSize){
													vNo=0;
												 }
											}
										} // end of level two inclusive
							  } //end of else at miss at level two
							 
						    }
						iterator2=iterator2->next;
					    } // end of while iterator2
					 }//end of enable 
					 else{
								if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at victim cache read %d\n",address);
												fprintf(stream," Hit at victim read %d ",address);
												checkV=1;

													if(write_type==0 && allocate==1){
																total_cycles =  total_cycles + write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==0 && allocate==0){
																total_cycles = total_cycles +  write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==1 && allocate==0){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}if(write_type==1 && allocate==1){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}
																hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at victim cache read %d\n",address);
												fprintf(stream," Miss at victim cache read %d ",address);

												if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}
										  }
										}//end of victim enable
						 if(victim==1 && checkV==0){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
										for(j=0;j<words;j++){
												if(iterator->block_offset[j]>=0){
														iterator4->address=iterator->block_offset[j];
														vNo++;
												 }
										}
									break;
								}
								iterator4=iterator4->next;
							}
						 }
						if(checkV==0){
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						iterator->block_offset[numberBlockOff]=address;
						}
						if(vNo>=victimSize){
							vNo=0;
						  }
					  }//end of else enable
				    }

				  } //end of else(miss)
				 }
			iterator = iterator->next;
			}
	 } //end of read


if(dat=='w'){
		
		iterator=root;
		while(iterator->next!=0){
			if(iterator->index==numberInd){
				
				if(iterator->tag==numberTag && iterator->valid==1){
					
					if(iterator->block_offset[numberBlockOff]==address){
						printf("hit at write %d\n",address);
						fprintf(stream," Hit at write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
						hit++;
					  }
					else{
					printf("miss at write %d\n",address);
					fprintf(stream," Miss at write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
						iterator->block_offset[numberBlockOff]=address;
					  }
					 }
				else{
					if(iterator->valid!=1){
						miss++;
						printf("Compulsory miss at write %d\n",address);
						fprintf(stream," Compulsory miss at write %d ",address);

						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}

						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						iterator->block_offset[numberBlockOff]=address;
					}else{
						printf("Conflict miss at L1 write %d\n",address);
						fprintf(stream," Conflict miss at L1 write %d ",address);
						if(ltwo_enable==1){
						checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						//printf("\nnumber block off is %d",numberBlockOff2);
						iterator2=root2;

				    while(iterator2->next!=0){
						if(iterator2->index==numberInd2){
							if(iterator2->tag==numberTag2 && iterator2->valid==1){
								if(iterator2->block_offset[numberBlockOff2]==address){
										printf(" hit at L2 write %d\n",address);
										fprintf(stream," Hit at L2 write %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_cache2;
											fprintf(stream," cycles: %d ",(write_cache));
											}
											hit2++;
								}
							  }
							else{
										printf(" Miss at L2 write %d\n",address);
										fprintf(stream," Miss at L2 write %d ",address);
										if(ltwo_inclusive==1){
										//	printf("iterator->address %d\n",iterator->block_offset[numberBlockOff]);
										checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
									//	if(iterator->block_offset[numberBlockOff]<0)

									//	printf("numberTag2 %d\n",numberTag2);
										//printf("numberInd2 %d\n",numberInd2);

										if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at victim cache write %d\n",address);
												fprintf(stream," Hit at victim cache write %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}
											hit3++;
												checkV=1;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at victim cache write %d\n",address);
												fprintf(stream," Miss at victim cache write %d ",address);

											if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==0 && allocate==0){
											total_cycles = total_cycles + write_ram + read_victim;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
											}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache + read_victim;
											fprintf(stream," cycles: %d ",(write_cache));
											}

										  }
										}//end of victim enable

										iterator3=root2;
										while(iterator3->next!=0){
											if(iterator3->index==numberInd2){

												if(checkV==0 && victim==1){
													iterator4=root3;
													while(iterator4->next!=0){
														if(iterator4->number_node==vNo){
															for(j=0;j<words;j++){
																if(iterator3->block_offset[j]>=0){
																	iterator4->address=iterator3->block_offset[j];
																	vNo++;
																}
															}
														break;
														}
													iterator4=iterator4->next;
												    }//end of inner while loop
											    } 
												//miss at l2 level and i dont have a victim cache
												if(checkV==0){
												iterator3->tag=numberTag2;
												iterator3->valid=1;
												iterator3->address=iterator->address;
												iterator3->block_offset[numberBlockOff2]=iterator->address;
												}
												}
												iterator3=iterator3->next;
									         }
										if(checkV==0){
										iterator->tag=numberTag;
										iterator->valid=1;
										iterator->address=address;
										iterator->block_offset[numberBlockOff]=address;
										 
										}
										if(vNo>=victimSize){
											vNo=0;
										  }
										}
										else if(ltwo_inclusive==0){
											if(victim==0){
											iterator2->tag=numberTag2;
											iterator2->valid=1;
											iterator2->address=address;
											iterator2->block_offset[numberBlockOff2]=address;
											iterator->tag=numberTag;
											iterator->valid=1;
											iterator->address=address;
											iterator->block_offset[numberBlockOff]=address;
											}
											else if(victim==1){
												iterator4=root3;
												checkV=0;
													while(iterator4->next!=0){
														if(iterator4->address==address){
														printf(" Hit at victim cache write %d\n",address);
														fprintf(stream," Hit at victim cache write %d ",address);
														

																if(write_type==0 && allocate==1){
																total_cycles =  total_cycles + write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==0 && allocate==0){
																total_cycles = total_cycles +  write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==1 && allocate==0){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}if(write_type==1 && allocate==1){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}
																hit3++;
														checkV=1;
														break;
														}
													iterator4=iterator4->next;
													}
												   if(checkV==0){
														printf(" Miss at victim cache write %d\n",address);
														fprintf(stream," Miss at victim cache write %d ",address);

															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}

													 }
												   if(checkV==0){
												iterator4=root3;
												while(iterator4->next!=0){
													if(iterator4->number_node==vNo){
														for(j=0;j<words;j++){
																if(iterator2->block_offset[j]>=0){
																	iterator4->address=iterator2->block_offset[j];
																	vNo++;
																}
															}
														break;
													  }
												iterator4=iterator4->next;
												}
												iterator2->tag=numberTag2;
												iterator2->valid=1;
												iterator2->address=address;
												iterator2->block_offset[numberBlockOff2]=address;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												iterator->block_offset[numberBlockOff]=address;
												 }
												if(vNo>=victimSize){
													vNo=0;
												 }
											}
										} // end of level two inclusive
							  } //end of else at miss at level two
							 
						    }
						iterator2=iterator2->next;
					    } // end of while iterator2
					 }//end of enable 
					 else{
								if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at victim cache write %d\n",address);
												fprintf(stream," Hit at victim write %d ",address);
												checkV=1;

													if(write_type==0 && allocate==1){
																total_cycles =  total_cycles + write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==0 && allocate==0){
																total_cycles = total_cycles +  write_cache + write_ram + read_victim;
																fprintf(stream," cycles: %d ",(write_cache + write_ram));
																}if(write_type==1 && allocate==0){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}if(write_type==1 && allocate==1){
																total_cycles =  total_cycles + write_cache + read_victim;
																fprintf(stream," cycles: %d ",(write_cache));
																}
																hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at victim cache write %d\n",address);
												fprintf(stream," Miss at victim cache write %d ",address);

												if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}
										  }
										}//end of victim enable
						 if(victim==1 && checkV==0){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
										for(j=0;j<words;j++){
												if(iterator->block_offset[j]>=0){
														iterator4->address=iterator->block_offset[j];
														vNo++;
												 }
										}
									break;
								}
								iterator4=iterator4->next;
							}
						 }
						if(checkV==0){
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						iterator->block_offset[numberBlockOff]=address;
						}
						if(vNo>=victimSize){
							vNo=0;
						  }
					  }//end of else enable
				    }

				  } //end of else(miss)
				 }
			iterator = iterator->next;
			}
	 } //end of write

   if(dat=='m'){
		 iterator=root;
		 	while(iterator->next!=0){
			if(iterator->index==numberInd){
				if(iterator->tag==numberTag && iterator->valid==1 && iterator->block_offset[numberBlockOff]==address ){
				
						printf("hit to modify the word at level 1 cache at %d\n",address);
						fprintf(stream," hit to modify the word at level 1 cache at %d ",address);
						hit++;
						total_cycles = total_cycles + read_cache ;
						fprintf(stream," cycles: %d ",(read_cache));
					   }
					 
			    else{
					    printf("miss to modify at level 1 cache at %d\n",address);
						fprintf(stream," miss to modify the word at level 1 cache at %d ",address);
						total_cycles = total_cycles + read_cache + read_ram;
						fprintf(stream," cycles: %d ",(read_cache + read_ram));
						if(ltwo_enable==1){
							checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2=root2;
							while(iterator2->next!=0){
								if(iterator2->index==numberInd2){
									if(iterator2->tag==numberTag2 && iterator2->valid==1 && iterator2->block_offset[numberBlockOff2]==address){
										printf("hit to modify the word at level 2 cache at %d\n",address);
										fprintf(stream," hit to modify the word at level 2 cache at %d ",address);
										hit2++;
										total_cycles = total_cycles + read_cache2 + read_cache ;
										fprintf(stream," cycles: %d ",(read_cache + read_cache2 ));
										break;
									  }
									else{
										printf("miss to modify the word at level 2 cache at %d\n",address);
										fprintf(stream," miss to modify the word at level 2 cache at %d ",address);

										total_cycles = total_cycles + read_cache + read_ram + read_cache2;
										fprintf(stream," cycles: %d ",(read_cache + read_ram + read_cache2));

										if(victim==1){
											iterator4=root3;
											checkV=0;
											while(iterator4->next!=0){
												if(iterator4->address==address){
													printf(" hit to modify the word at victim cache at %d\n",address);
													fprintf(stream," hit to modify the word at victim cache at %d ",address);
													hit3++;
													total_cycles = total_cycles + read_cache2 + read_cache + read_victim;
													fprintf(stream," cycles: %d ",(read_cache + read_cache2 + read_victim));
													checkV=1;
													break;
												}
											iterator4=iterator4->next;
											}
											if(checkV==0){
												printf(" miss to modify the word at victim cache at %d\n",address);
												fprintf(stream," miss to modify the word at victim cache at %d ",address);
												total_cycles = total_cycles + read_cache + read_ram + read_cache2 + read_victim;
												fprintf(stream," cycles: %d ",(read_cache + read_ram + read_cache2 + read_victim));
											}	
										} //end of victim
									break;
									}
								 }
								iterator2=iterator2->next;
							 }
				       }
						else if(ltwo_enable=0){
							if(victim==1){
											iterator4=root3;
											checkV=0;
											while(iterator4->next!=0){
												if(iterator4->address==address){
													printf(" hit to modify the word at victim cache at %d\n",address);
													fprintf(stream," hit to modify the word at victim cache at %d ",address);
													checkV=1;
													hit3++;
													total_cycles = total_cycles + read_cache + read_victim;
													fprintf(stream," cycles: %d ",(read_cache + read_cache + read_victim));
													break;
												}
											iterator4=iterator4->next;
											}
											if(checkV==0){
												printf(" miss to modify the word at victim cache at %d\n",address);
												fprintf(stream," miss to modify the word at victim cache at %d ",address);
												total_cycles = total_cycles + read_cache + read_victim + read_ram;
												fprintf(stream," cycles: %d ",(read_cache + read_cache + read_victim + read_ram));
											}	
								} //end of victim
						}

	
				 }//end of else
			}
						iterator = iterator->next;
		} //end of while
    }


if(dat=='f'){
		 iterator=root;
			while(iterator->next!=0){
				iterator->valid=0;
				iterator = iterator->next;
				for(j=0;j<words;j++)
				iterator->block_offset[j]=-1;
			  }
		if(ltwo_enable==1){
			iterator2=root2;
			while(iterator2->next!=0){
				iterator2->valid=0;
				iterator2 = iterator2->next;
				for(j=0;j<words;j++)
				iterator2->block_offset[j]=-1;
			  }
		}
		if(victim==1){
			iterator4=root3;
			while(iterator4->next!=0){
				iterator4->valid=0;
				iterator4 = iterator4->next;
				for(j=0;j<words;j++)
				iterator4->block_offset[j]=-1;
			  }
		}
	 }
	  

	 }//end of else
	}//choice 1 closed

	else if(choice==3){
		//printf("the blockoff is %d\n",numberBlockOff);
		if(numberBlockOff==-1){
			iterator=root;
			while(iterator->next!=0 && iterator->valid==1){
				iterator->lru_number++;
				iterator=iterator->next;
			}
			if(ltwo_enable==1){
				iterator2=root2;
			while(iterator2->next!=0 && iterator2->valid==1){
				iterator2->lru_number++;
				iterator2=iterator2->next;
			    }
			}

if(dat=='r'){
			j=0;
			flag=0;
			iterator=root;
			if(count_full<(krifi/words)){
				while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
				    
						printf("hit at read %d\n",address);
						fprintf(stream," Hit at read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;
				   } 
				iterator=iterator->next;
				}
				if(flag==0){
					printf(" miss at read %d\n",address);
					fprintf(stream," Miss at read %d ",address);
					
						if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}


					iterator=root;
					while(iterator->next!=0){
					if(iterator->number_node==count_full){
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						count_full++;
						break;
					}
					iterator=iterator->next;
				   }
			  }
			}
			else {
				flag=0;
				iterator=root;
					while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
				 
						printf("hit at read %d\n",address);
						fprintf(stream," Hit at read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;

				   } 
				iterator=iterator->next;
				}
				if(flag==0){

				if(type==1){
					//iterator=root;
					printf("miss at read %d\n",address);
					fprintf(stream," Miss at read %d ",address);
					miss++;
							if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					if(ltwo_enable==1){
						j=0;
						flag=0;
						checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						if(ltwo_inclusive==1){
							if(count_full2<(ltwo/words)){
								iterator2=root2;
								while(iterator2->next!=0){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("hit at L2 Cache Read %d\n",address);
										fprintf(stream," Hit at L2 Cache Read %d ",address);
										if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + read_cache2 + write_ram;
											fprintf(stream," cycles: %d ",(read_cache2 + write_ram));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  read_cache2 + write_ram;
											fprintf(stream," cycles: %d ",(read_cache2 + write_ram));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}
										hit2++;
										iterator2->lru_number=0;
										flag=1;
										j=1;
										break;
									}
									iterator2=iterator2->next;
								}
									
										if(flag==0){
										printf("Miss at L2 cache Read %d\n",address);
										fprintf(stream," Miss at L2 cache Read %d ",address);

												if(write_type==0 && allocate==1){
												total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
												fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
											}else if(write_type==0 && allocate==0){
												total_cycles =  total_cycles + write_cache2 + write_ram;
												fprintf(stream," cycles: %d ",( write_cache2 + write_ram));
											}else if(write_type==1 && allocate==0){
												if(iterator->valid==1){
												total_cycles =  total_cycles + write_cache2 + write_ram;
												fprintf(stream," cycles: %d ",( write_cache2 + write_ram ));
												}else{
												total_cycles = total_cycles + write_cache2;
												fprintf(stream," cycles: %d ",(write_cache2));
												}
											}else if(write_type==1 && allocate==1){
												total_cycles = total_cycles + write_cache2 + read_ram ;
												fprintf(stream," cycles: %d ",( write_cache2 + read_ram));
											}
											iterator=root;
											while(iterator->next!=0){
												if(iterator->number_node==fifo_number){
													break;
												  }
												iterator=iterator->next;
											}
											iterator2=root2;
											while(iterator2->next!=0){
											if(iterator2->number_node==count_full2){
												checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												printf("the tag is %d",numberTag2);
												printf("the address is %d",iterator->address);
												iterator2->tag=numberTag2;
												iterator2->valid=1;
												iterator2->address=iterator->address;
												count_full2++;
												break;
											}
											iterator2=iterator2->next;
										   }
									
								}
							  
							}//end of check for countfull2
							else{
									
									printf("Miss at L2 Cache Read %d\n",address);
									fprintf(stream," Miss at L2 Cache Read %d ",address);
					
											if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache2 + write_ram + read_ram;
										fprintf(stream," cycles: %d ",( write_cache2 + write_ram + read_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache2 + write_ram;
										fprintf(stream," cycles: %d ",( write_cache2 + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache2 + write_ram;
										fprintf(stream," cycles: %d ",( write_cache2 + write_ram));
										}else{
										total_cycles = total_cycles + write_cache2;
										fprintf(stream," cycles: %d ",( write_cache2));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache2 + read_ram;
										fprintf(stream," cycles: %d ",( write_cache2 + read_ram));
									}

											iterator=root;
											while(iterator->next!=0){
												if(iterator->number_node==fifo_number){
													break;
												  }
												iterator=iterator->next;
											}
									iterator2=root2;
									while(iterator2->next!=0){
										if(iterator2->number_node==fifo_number2){
											fprintf(stream," %d got replaced by %d beccause of fifo in place %d ",iterator2->tag,iterator->address,fifo_number2);
											checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
											iterator2->tag=numberTag2;
											iterator2->valid=1;
											iterator2->address=iterator->address;
											fifo_number2++;
											break;
										  }
										iterator2=iterator2->next;
									}
									if(fifo_number2>=(ltwo/words))
										fifo_number2=0;
							}//end of else for countfull2>ltwo size
						}//end of exlusive l2 type cache
						else{
							flag=0;
							checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2=root2;
								while(iterator2->next!=0){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("Hit at L2 Cache Read %d\n",address);
										fprintf(stream," Hit at L2 Cache Read %d ",address);
										if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache2 + write_ram;
											fprintf(stream," cycles: %d ",(write_cache2 + write_ram));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache2 + write_ram;
											fprintf(stream," cycles: %d ",(write_cache2 + write_ram));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache2;
											fprintf(stream," cycles: %d ",(write_cache2));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache2;
											fprintf(stream," cycles: %d ",(write_cache2));
										}
										hit2++;
										iterator2->lru_number=0;
										flag=1;
										j=1;
										break;
									}
									iterator2=iterator2->next;
								}
							if(flag==0){
										printf("Miss at L2 Cache Read %d\n",address);
										fprintf(stream," Miss at L2 Cache Read %d ",address);
									
											if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache2 + write_ram + read_ram;
										fprintf(stream," cycles: %d ",( write_cache2 + write_ram + read_ram ));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache2 + write_ram;
										fprintf(stream," cycles: %d ",( write_cache2 + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache2 + write_ram;
										fprintf(stream," cycles: %d ",( write_cache2 + write_ram));
										}else{
										total_cycles = total_cycles + write_cache2;
										fprintf(stream," cycles: %d ",( write_cache2));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache2 + read_ram;
										fprintf(stream," cycles: %d ",( write_cache2 + read_ram));
									}
							iterator2=root2;
							while(iterator2->next!=0){
										if(iterator2->number_node==fifo_number2){
											fprintf(stream," %d got replaced by %d beccause of fifo in place %d ",iterator2->tag,address,fifo_number2);
											checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
											iterator2->tag=numberTag2;
											iterator2->valid=1;
											iterator2->address=address;
											fifo_number2++;

											break;
										  }
										iterator2=iterator2->next;
									}
									if(fifo_number2>=(ltwo/words))
										fifo_number2=0;
							}
						}
					}//end of ltwo_enable

					if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at Victim Cache Read  %d\n",address);
												fprintf(stream," Hit at Victim Cache Read %d ",address);
												checkV=1;
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_ram + read_victim));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(read_victim + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + read_victim;
															fprintf(stream," cycles: %d ",(read_victim));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + read_victim;
															fprintf(stream," cycles: %d ",(read_victim));
															}
															hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at Victim Cache Read  %d\n",address);
												fprintf(stream," Miss at Victim Cache Read %d ",address);
															if(write_type==0 && allocate==1){
																total_cycles =  total_cycles + write_cache + read_ram + write_ram;
																fprintf(stream," cycles: %d ",(write_cache + read_ram + write_ram));
															}if(write_type==0 && allocate==0){
																total_cycles = total_cycles +  write_cache + read_ram + write_ram;
																fprintf(stream," cycles: %d ",(write_cache + read_ram + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}
										  }
										}//end of victim enable

					if(j==0){
					while(iterator->next!=0){
						if(iterator->number_node==fifo_number){
							fprintf(stream," %d got replaced by %d beccause of fifo in place %d ",iterator->tag,address,fifo_number);
							if(victim==1){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
									iterator4->address=iterator->address;
									vNo++;
									break;
								}
								iterator4=iterator4->next;
							}
							}
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->address=address;
							fifo_number++;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						if(fifo_number>=(krifi/words))
							fifo_number=0;
						if(vNo>=victimSize){
							vNo=0;
						}
					}
				}
				else if(type==2){
					iterator=root;
					flag=0;
					printf("Capacity Miss at Read %d\n",address);
					fprintf(stream," Capacity Miss at Read %d ",address);
					miss++;

							if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at Victim Cache Read  %d\n",address);
												fprintf(stream," Hit at Victim Cache Read %d ",address);
												checkV=1;
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + write_ram + read_cache2;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + read_victim;
															fprintf(stream," cycles: %d ",(read_victim));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + read_victim;
															fprintf(stream," cycles: %d ",(read_victim));
															}
															hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at Victim Cache Read  %d\n",address);
												fprintf(stream," Miss at Victim Cache Read %d ",address);
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + read_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(read_ram + write_cache ));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(read_ram + write_cache ));
															}
										  }
										}//end of victim enable
						if(ltwo_enable==1){
						j=0;
						flag=0;
						checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						if(ltwo_inclusive==1){
							if(count_full2<(ltwo/words)){
								iterator2=root2;
								while(iterator2->next!=0){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("hit at L2 cache Read %d\n",address);
										fprintf(stream," hit at L2 cache Read %d ",address);
										if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(write_ram + read_cache2));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles + write_ram + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2 + write_ram));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache2;
											fprintf(stream," cycles: %d ",(write_cache2));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache2;
											fprintf(stream," cycles: %d ",(write_cache2));
										}
										hit2++;
										iterator2->lru_number=0;
										flag=1;
										j=1;
										break;
									}
									iterator2=iterator2->next;
								}
									
										if(flag==0){
										printf("Cumpolsory Miss at L2 Cache Read %d\n",address);
										fprintf(stream," Cumpolsory Miss at L2 Cache Read",address);

												if(write_type==0 && allocate==1){
												total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
												fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
											}else if(write_type==0 && allocate==0){
												total_cycles =  total_cycles + write_cache + write_ram;
												fprintf(stream," cycles: %d ",( write_cache + write_ram));
											}else if(write_type==1 && allocate==0){
												if(iterator->valid==1){
												total_cycles =  total_cycles + write_cache + write_ram + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
												}else{
												total_cycles = total_cycles + write_cache + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + write_cache));
												}
											}else if(write_type==1 && allocate==1){
												total_cycles = total_cycles + write_cache + read_ram + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
											}
							iterator=root;
							while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
												}
										  }
									flag++;
									iterator=iterator->next;
			  
										  }
								iterator=root;
								while(iterator->next!=0){
									if(iterator->number_node==max_node){
										break;
									}
									iterator=iterator->next;
								}

						iterator2=root2;
						while(iterator2->next!=0){
							if(iterator2->number_node==count_full2){
							checkAction2((char)ch,(long int)(iterator->tag),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2->tag=numberTag2;
							iterator2->valid=1;
							iterator2->lru_number=0;
							count_full2++;
							break;
						  }
					
					     iterator2=iterator2->next;
					    }
								
								}
							}//end of check for countfull2
							else{
									iterator2=root2;
									printf("Capacity Miss at L2 cache Read %d\n",address);
									fprintf(stream," Capacity Miss at L2 cache Read %d ",address);
					
											if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache + write_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
										}else{
										total_cycles = total_cycles + write_cache + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_cache));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache + read_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
									}
								iterator=root;
							while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
												}
										  }
									flag++;
									iterator=iterator->next;
			  
										  }
								iterator=root;
								while(iterator->next!=0){
									if(iterator->number_node==max_node){
										break;
									}
									iterator=iterator->next;
								}
								
									iterator2=root2;
							while(iterator2->next!=0){
							if(flag==0){
								max=iterator2->lru_number;
								max_node=iterator2->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator2->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator2->lru_number;
										max_node=iterator2->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator2->lru_number;
									max_node=iterator2->number_node;
												}
										  }
									flag++;
									iterator2=iterator2->next;
			  
										  }
								iterator2=root;
								while(iterator2->next!=0){
									if(iterator2->number_node==max_node){
										checkAction2((char)ch,(long int)(iterator->tag),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
										iterator2->tag=numberTag2;
										iterator2->valid=1;
										iterator2->lru_number=0;
										iterator2->address=iterator->tag;
										break;
									}
									iterator2=iterator2->next;
								}
									
							}//end of else for countfull2>ltwo size
						}//end of exlusive l2 type cache
						else{
							flag=0;
							checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2=root2;
								while(iterator2->next!=0){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("Hit at L2 Cache Read %d\n",address);
										fprintf(stream," Hit at L2 Cache Read %d ",address);
										if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + read_cache2 + write_ram;
											fprintf(stream," cycles: %d ",(read_cache2 + write_ram));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  read_cache2 + write_ram;
											fprintf(stream," cycles: %d ",(read_cache2 + write_ram));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}
										hit2++;
										iterator2->lru_number=0;
										flag=1;
										j=1;
										break;
									}
									iterator2=iterator2->next;
								}
							if(flag==0){

										printf("Miss at L2 Cache Read %d\n",address);
										fprintf(stream," Miss at L2 Cache Read %d ",address);
									
											if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache + write_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
										}else{
										total_cycles = total_cycles + write_cache + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_cache));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache + read_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
									}

							iterator=root;
							while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
												}
										  }
									flag++;
									iterator=iterator->next;
			  
										  }
								iterator=root;
								while(iterator->next!=0){
									if(iterator->number_node==max_node){
										iterator->valid=1;
										iterator->lru_number=0;
										iterator->address=address;
										iterator->tag=numberTag;
										break;
									}
									iterator=iterator->next;
								}

						iterator2=root2;
							while(iterator2->next!=0){
							if(flag==0){
								max=iterator2->lru_number;
								max_node=iterator2->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator2->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator2->lru_number;
										max_node=iterator2->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator2->lru_number;
									max_node=iterator2->number_node;
												}
										  }
									flag++;
									iterator2=iterator2->next;
			  
										  }
						iterator2=root2;
						while(iterator2->next!=0){
							if(iterator2->number_node==max_node){
							checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2->tag=numberTag2;
							iterator2->valid=1;
							iterator2->lru_number=0;
							iterator2->address=address;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator2=iterator2->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }

							}
						}
					}//end of ltwo_enable
						while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
								}
						  }
					flag++;
					iterator=iterator->next;
					
						  
				  }
						iterator=root;
						while(iterator->next!=0){
						if(iterator->number_node==max_node){
							fprintf(stream," %d got replaced by %d beccause of lru with lru number to be %d in place with the max node %d ",iterator->tag,address,iterator->lru_number,max_node);
							if(victim==1){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
									iterator4->address=iterator->address;
									vNo++;
									break;
								}
								iterator4=iterator4->next;
							}
							}
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->lru_number=0;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						if(vNo>=victimSize){
							vNo=0;
						}
				} // end of type 2
				if(type==3){
					if(ltwo_enable==1){
						checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						iterator2=root2;
						if(ltwo_inclusive==1){
							if(count_full2<ltwo){
							while(iterator2->next!=0){
								if(iterator2->tag==numberTag2 && iterator2->valid==1){
									printf("Hit at Read L2 Cache at %d",address);
									fprintf(stream," Hit at Read L2 Cache at %d",address);
									if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}
									flag=1;
									hit2++;
									break;
								}
								iterator2=iterator2->next;
							}
						  if(flag==0){
							  printf("Miss at Read L2 Cache at %d",address);
								fprintf(stream," Miss at Read L2 Cache at %d",address);
								rn = rand() % ((krifi/words));
								iterator=root;
								iterator2=root2;
								while(iterator->next!=0){
									if(iterator->number_node==rn){
										fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->tag,address,rn);
										while(iterator2->next!=0){
											if(iterator2->number_node==count_full2){
												checkAction2((char)ch,(long int)(iterator->tag),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->address=iterator->address;
												iterator2->valid=1;
												count_full2++;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												break;
											}
										iterator2=iterator2->next;
									 }
									break;
									}
									iterator=iterator->next;
					}//end of while
						   }//end of miss flag=0
						  }
							else{
								iterator2=root2;
								while(iterator2->next!=0){
								if(iterator2->tag==numberTag2 && iterator2->valid==1){
									printf("Hit at Read L2 Cache at %d",address);
									fprintf(stream," Hit at Read L2 Cache at %d",address);
									flag=1;
									hit2++;
									break;
								}
								iterator2=iterator2->next;
							}
						  if(flag==0){
							  printf("Miss at Read L2 Cache at %d",address);
								fprintf(stream," Miss at Read L2 Cache at %d",address);
										if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache + write_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
										}else{
										total_cycles = total_cycles + write_cache + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_cache));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache + read_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
									}
								rn = rand() % ((krifi/words));
								j = rand() % ltwo;
								iterator=root;
								iterator2=root2;
								while(iterator->next!=0){
									if(iterator->number_node==rn){
										fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator2->tag,iterator->address,j);
										while(iterator2->next!=0){
											if(iterator2->number_node==j){
												checkAction2((char)ch,(long int)(iterator->tag),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->address=iterator->address;
												iterator2->valid=1;
												count_full2++;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												break;
											}
										iterator2=iterator2->next;
									 }
									break;
									}
									iterator=iterator->next;
					}//end of while
						   }//end of miss flag=0
							}
						} // end of ltwo to be exlusive
						else{
							if(count_full2<ltwo){
								iterator2=root2;
								while(iterator2->next!=0){
								if(iterator2->tag==numberTag2 && iterator2->valid==1){
									printf("Hit at Read L2 Cache at %d",address);
									fprintf(stream," Hit at Read L2 Cache at %d",address);
									if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}
									flag=1;
									hit2++;
									break;
								}
								iterator2=iterator2->next;
							}
						  if(flag==0){
							  printf("Miss at Read L2 Cache at %d",address);
								fprintf(stream," Miss at Read L2 Cache at %d",address);
								rn = rand() % ((krifi/words));
								j = rand() % ltwo;
								iterator=root;
								iterator2=root2;
								while(iterator->next!=0){
									if(iterator->number_node==rn){
										fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->tag,address,rn);
										while(iterator2->next!=0){
											if(iterator2->number_node==count_full2){
												checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->address=address;
												iterator2->valid=1;
												count_full2++;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												break;
											}
										iterator2=iterator2->next;
									 }
									break;
									}
									iterator=iterator->next;
					}//end of while
						   }//end of miss flag=0
						}
							else{
								iterator2=root2;
								while(iterator2->next!=0){
								if(iterator2->tag==numberTag2 && iterator2->valid==1){
									printf("Hit at Read L2 Cache at %d",address);
									fprintf(stream," Hit at Read L2 Cache at %d",address);
									if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + read_cache2;
											fprintf(stream," cycles: %d ",(read_cache2));
										}
									flag=1;
									hit2++;
									break;
								}
								iterator2=iterator2->next;
							}
						  if(flag==0){
							  printf("Miss at Read L2 Cache at %d",address);
								fprintf(stream," Miss at Read L2 Cache at %d",address);
									if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache + write_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
										}else{
										total_cycles = total_cycles + write_cache + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_cache));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache + read_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
									}
								rn = rand() % ((krifi/words));
								j = rand() % ltwo;
								iterator=root;
								iterator2=root2;
								while(iterator->next!=0){
									if(iterator->number_node==rn){
										fprintf(stream," at L1 %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->tag,address,rn);
										fprintf(stream," at L2 %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator2->tag,address,j);
										while(iterator2->next!=0){
											if(iterator2->number_node==j){
												checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->address=address;
												iterator2->valid=1;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												break;
											}
										iterator2=iterator2->next;
									 }
									break;
									}
									iterator=iterator->next;
								}//end of while
						   }//end of miss flag=0

							}
					  }
					}//end of ltwo enabled
					if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at Victim cache Read  %d\n",address);
												fprintf(stream," Hit at Victim cache Read %d ",address);
												checkV=1;
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + read_victim;
															fprintf(stream," cycles: %d ",(read_victim));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles + read_victim;
															fprintf(stream," cycles: %d ",(read_victim));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + read_victim;
															fprintf(stream," cycles: %d ",(read_victim));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + read_victim;
															fprintf(stream," cycles: %d ",(read_victim));
															}
															hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at Victim cache Read  %d\n",address);
												fprintf(stream," Miss at Victim cache Read %d ",address);
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram + read_victim));
															}if(write_type==0 && allocate==0){
																total_cycles = total_cycles +  write_cache + read_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram + read_victim));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + read_victim));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + read_victim));
															}
										}
									
										}//end of victim enable
					iterator=root;
					flag=0;
					miss++;
					printf("Capacity Miss at Read %d\n",address);
					fprintf(stream," Capacity Miss at Read %d ",address);
							if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

	
					rn = rand() % ((krifi/words));
					printf("rn : %d \n",rn);
					while(iterator->next!=0){
						if(iterator->number_node==rn){
							fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->tag,address,rn);
							
										if(victim==1){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
									iterator4->address=iterator->tag;
									vNo++;
									break;
								}
							iterator4=iterator4->next;
							}
							}
							iterator->tag=numberTag;
							iterator->valid=1;
							break;
						  }
						iterator=iterator->next;
					}//end of while
					if(vNo==victimSize){
						vNo=0;
					}
				}//end of type 3 if statment
			 }//end of flag
			}//endo of else
		}//end of read

		if(dat=='w'){
			j=0;
			flag=0;
			iterator=root;
			if(count_full<(krifi/words)){
				while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
				    
						printf("Hit at Write %d\n",address);
						fprintf(stream," Hit at Write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;
				   } 
				iterator=iterator->next;
				}
				if(flag==0){
					printf("Compulsory Miss at Write %d\n",address);
					fprintf(stream," Compulsory Miss at Write %d ",address);
					
						if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}


					iterator=root;
					while(iterator->next!=0){
					if(iterator->number_node==count_full){
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->address=address;
						count_full++;
						break;
					}
					iterator=iterator->next;
				   }
			  }
			}
			else {
				flag=0;
				iterator=root;
					while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
				 
						printf("Hit at Write %d\n",address);
						fprintf(stream," Hit at Write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;

				   } 
				iterator=iterator->next;
				}
				if(flag==0){

				if(type==1){
					iterator=root;
					printf("Capacity Miss at Write %d\n",address);
					fprintf(stream," Capacity Miss at Write %d ",address);
					
							if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					if(ltwo_enable==1){
						j=0;
						flag=0;
						checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						if(ltwo_inclusive==1){
							if(count_full2<(ltwo/words)){
								iterator2=root2;
								while(iterator2->next!=0){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("Hit at L2 cache Write %d\n",address);
										fprintf(stream," Hit at L2 cache Write %d ",address);
										if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache;
											fprintf(stream," cycles: %d ",(write_cache));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache;
											fprintf(stream," cycles: %d ",(write_cache));
										}
										hit2++;
										iterator2->lru_number=0;
										flag=1;
										j=1;
										break;
									}
									iterator2=iterator2->next;
								}
									
										if(flag==0){
										printf("Cumpolsory Miss at L2 cache Write %d\n",address);
										fprintf(stream," Cumpolsory Miss at L2 cache Write %d ",address);

												if(write_type==0 && allocate==1){
												total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
												fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
											}else if(write_type==0 && allocate==0){
												total_cycles =  total_cycles + write_cache + write_ram;
												fprintf(stream," cycles: %d ",( write_cache + write_ram));
											}else if(write_type==1 && allocate==0){
												if(iterator->valid==1){
												total_cycles =  total_cycles + write_cache + write_ram + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
												}else{
												total_cycles = total_cycles + write_cache + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + write_cache));
												}
											}else if(write_type==1 && allocate==1){
												total_cycles = total_cycles + write_cache + read_ram + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
											}
											iterator=root;
											while(iterator->next!=0){
												if(iterator->number_node==fifo_number){
													break;
												  }
												iterator=iterator->next;
											}
											iterator2=root2;
											while(iterator2->next!=0){
											if(iterator2->number_node==count_full2){
												checkAction2((char)ch,(long int)(iterator->tag),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->valid=1;
												iterator2->address=iterator->address;
												count_full2++;
												break;
											}
											iterator2=iterator2->next;
										   }
									
								}
							  
							}//end of check for countfull2
							else{
									iterator2=root2;
									printf("Capacity Miss at L2 Cache Write %d\n",address);
									fprintf(stream," Capacity Miss at L2 Cache Write %d ",address);
					
											if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache + write_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
										}else{
										total_cycles = total_cycles + write_cache + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_cache));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache + read_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
									}

											iterator=root;
											while(iterator->next!=0){
												if(iterator->number_node==fifo_number){
													break;
												  }
												iterator=iterator->next;
											}
									while(iterator2->next!=0){
										if(iterator2->number_node==fifo_number2){
											fprintf(stream," %d got replaced by %d beccause of fifo in place %d ",iterator2->tag,iterator->address,fifo_number2);
											checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
											iterator2->tag=numberTag2;
											iterator2->valid=1;
											iterator2->address=iterator->address;
											fifo_number2++;
											break;
										  }
										iterator2=iterator2->next;
									}
									if(fifo_number2>=(ltwo/words))
										fifo_number2=0;
							}//end of else for countfull2>ltwo size
						}//end of exlusive l2 type cache
						else{
							flag=0;
							checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2=root2;
								while(iterator2->next!=0){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("Hit at L2 Cache Write %d\n",address);
										fprintf(stream," Hit at L2 Cache Write %d ",address);
										if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache;
											fprintf(stream," cycles: %d ",(write_cache));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache;
											fprintf(stream," cycles: %d ",(write_cache));
										}
										hit2++;
										iterator2->lru_number=0;
										flag=1;
										j=1;
										break;
									}
									iterator2=iterator2->next;
								}
							if(flag==0){

										printf("Miss at L2 Cache Write %d\n",address);
										fprintf(stream," Miss at L2 Cache Write %d ",address);
									
											if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache + write_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
										}else{
										total_cycles = total_cycles + write_cache + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_cache));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache + read_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
									}
							iterator2=root2;
							while(iterator2->next!=0){
										if(iterator2->number_node==fifo_number2){
											fprintf(stream," %d got replaced by %d beccause of fifo in place %d ",iterator2->tag,address,fifo_number2);
											checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
											iterator2->tag=numberTag2;
											iterator2->valid=1;
											iterator2->address=address;
											fifo_number2++;

											break;
										  }
										iterator2=iterator2->next;
									}
									if(fifo_number2>=(ltwo/words))
										fifo_number2=0;
							}
						}
					}//end of ltwo_enable

					if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at Victim Cache Write  %d\n",address);
												fprintf(stream," Hit at Victim Cache Write %d ",address);
												checkV=1;
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}
															hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at Victim Cache Write  %d\n",address);
												fprintf(stream," Miss at Victim Cache Write %d ",address);
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}
										  }
										}//end of victim enable

					if(j==0){
					while(iterator->next!=0){
						if(iterator->number_node==fifo_number){
							fprintf(stream," %d got replaced by %d beccause of fifo in place %d ",iterator->tag,address,fifo_number);	
							if(victim==1){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
									iterator4->address=iterator->address;
									vNo++;
									break;
								}
								iterator4=iterator4->next;
							}
							}

							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->address=address;
							fifo_number++;
							break;
						  }
					
					iterator=iterator->next;
					
					     }
						if(fifo_number>=(krifi/words))
							fifo_number=0;
						if(vNo>=victimSize){
							vNo=0;
						}
					}
				}
				else if(type==2){
					iterator=root;
					flag=0;
					printf("Capacity Miss at Write %d\n",address);
					fprintf(stream," Capacity Miss at Write %d ",address);
					miss++;

							if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
						if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at Victim Cache Write  %d\n",address);
												fprintf(stream," Hit at Victim Cache Write %d ",address);
												checkV=1;
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}
															hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at Victim Cache Write %d\n",address);
												fprintf(stream," Miss at Victim Cache Write %d ",address);
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}
										  }
										}//end of victim enable
						if(ltwo_enable==1){
						j=0;
						flag=0;
						checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						if(ltwo_inclusive==1){
							if(count_full2<(ltwo/words)){
								iterator2=root2;
								while(iterator2->next!=0){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("hit at L2 Cache Write %d\n",address);
										fprintf(stream," Hit at L2 Cache Write %d ",address);
										if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache;
											fprintf(stream," cycles: %d ",(write_cache));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache;
											fprintf(stream," cycles: %d ",(write_cache));
										}
										hit2++;
										iterator2->lru_number=0;
										flag=1;
										j=1;
										break;
									}
									iterator2=iterator2->next;
								}
									
										if(flag==0){
										printf("Cumpolsory Miss at L2 cache Write %d\n",address);
										fprintf(stream," Cumpolsory Miss at L2 cache Write %d ",address);

												if(write_type==0 && allocate==1){
												total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
												fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
											}else if(write_type==0 && allocate==0){
												total_cycles =  total_cycles + write_cache + write_ram;
												fprintf(stream," cycles: %d ",( write_cache + write_ram));
											}else if(write_type==1 && allocate==0){
												if(iterator->valid==1){
												total_cycles =  total_cycles + write_cache + write_ram + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
												}else{
												total_cycles = total_cycles + write_cache + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + write_cache));
												}
											}else if(write_type==1 && allocate==1){
												total_cycles = total_cycles + write_cache + read_ram + write_cache;
												fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
											}
							iterator=root;
							while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
												}
										  }
									flag++;
									iterator=iterator->next;
			  
										  }
								iterator=root;
								while(iterator->next!=0){
									if(iterator->number_node==max_node){
										break;
									}
									iterator=iterator->next;
								}

						iterator2=root2;
						while(iterator2->next!=0){
							if(iterator2->number_node==count_full2){
							checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2->tag=numberTag2;
							iterator2->valid=1;
							iterator2->lru_number=0;
							count_full2++;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator2=iterator2->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
								
								}
							  
							}//end of check for countfull2
							else{
									iterator2=root2;
									printf("Capacity Miss at L2 Cache Write %d\n",address);
									fprintf(stream," Capacity Miss at L2 Cache Write %d ",address);
					
											if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache + write_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
										}else{
										total_cycles = total_cycles + write_cache + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_cache));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache + read_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
									}
								iterator=root;
							while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
												}
										  }
									flag++;
									iterator=iterator->next;
			  
										  }
								iterator=root;
								while(iterator->next!=0){
									if(iterator->number_node==max_node){
										break;
									}
									iterator=iterator->next;
								}
								
									iterator2=root2;
							while(iterator2->next!=0){
							if(flag==0){
								max=iterator2->lru_number;
								max_node=iterator2->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator2->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator2->lru_number;
										max_node=iterator2->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator2->lru_number;
									max_node=iterator2->number_node;
												}
										  }
									flag++;
									iterator2=iterator2->next;
			  
										  }
								iterator2=root;
								while(iterator2->next!=0){
									if(iterator2->number_node==max_node){
										checkAction2((char)ch,(long int)(iterator->address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
										iterator2->tag=numberTag2;
										iterator2->valid=1;
										iterator2->lru_number=0;
										break;
									}
									iterator2=iterator2->next;
								}
									
							}//end of else for countfull2>ltwo size
						}//end of exlusive l2 type cache
						else{
							flag=0;
							checkAction2((char)ch,(long int)address,bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2=root2;
								while(iterator2->next!=0){
									if(iterator2->tag==numberTag2 && iterator2->valid==1){
										printf("Hit at L2 cache Write %d\n",address);
										fprintf(stream," Hit at L2 cache Write %d ",address);
										if(write_type==0 && allocate==1){
											total_cycles =  total_cycles + write_cache + write_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
										}if(write_type==0 && allocate==0){
											total_cycles = total_cycles +  write_cache + write_ram;
											fprintf(stream," cycles: %d ",(write_cache + write_ram));
										}if(write_type==1 && allocate==0){
											total_cycles =  total_cycles + write_cache;
											fprintf(stream," cycles: %d ",(write_cache));
										}if(write_type==1 && allocate==1){
											total_cycles =  total_cycles + write_cache;
											fprintf(stream," cycles: %d ",(write_cache));
										}
										hit2++;
										iterator2->lru_number=0;
										flag=1;
										j=1;
										break;
									}
									iterator2=iterator2->next;
								}
							if(flag==0){

										printf("Miss at l2 Cache Write %d\n",address);
										fprintf(stream," Miss at l2 Cache Write %d ",address);
									
											if(write_type==0 && allocate==1){
										total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
									}else if(write_type==0 && allocate==0){
										total_cycles =  total_cycles + write_cache + write_ram;
										fprintf(stream," cycles: %d ",( write_cache + write_ram));
									}else if(write_type==1 && allocate==0){
										if(iterator->valid==1){
										total_cycles =  total_cycles + write_cache + write_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
										}else{
										total_cycles = total_cycles + write_cache + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + write_cache));
										}
									}else if(write_type==1 && allocate==1){
										total_cycles = total_cycles + write_cache + read_ram + write_cache;
										fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
									}

							iterator=root;
							while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
												}
										  }
									flag++;
									iterator=iterator->next;
			  
										  }
								iterator=root;
								while(iterator->next!=0){
									if(iterator->number_node==max_node){
										iterator->valid=1;
										iterator->lru_number=0;
										iterator->address=address;
										iterator->tag=numberTag;
										break;
									}
									iterator=iterator->next;
								}

						iterator2=root2;
							while(iterator2->next!=0){
							if(flag==0){
								max=iterator2->lru_number;
								max_node=iterator2->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator2->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator2->lru_number;
										max_node=iterator2->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator2->lru_number;
									max_node=iterator2->number_node;
												}
										  }
									flag++;
									iterator2=iterator2->next;
			  
										  }
						iterator2=root2;
						while(iterator2->next!=0){
							if(iterator2->number_node==max_node){
							checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
							iterator2->tag=numberTag2;
							iterator2->valid=1;
							iterator2->lru_number=0;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator2=iterator2->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }

							}
						}
					}//end of ltwo_enable


						while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
								}
						  }
					flag++;
					iterator=iterator->next;
					
						  
				  }
						iterator=root;
						while(iterator->next!=0){
						if(iterator->number_node==max_node){
							fprintf(stream," %d got replaced by %d beccause of lru with lru number to be %d in place with the max node %d ",iterator->tag,address,iterator->lru_number,max_node);
							if(victim==1){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
									iterator4->address=iterator->address;
									vNo++;
									break;
								}
								iterator4=iterator4->next;
							}
							}
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->lru_number=0;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						if(vNo>=victimSize){
							vNo=0;
						}
				} // end of type 2
				if(type==3){
					iterator=root;
					flag=0;
					miss++;
					printf("Capacity miss at Write %d\n",address);
					fprintf(stream," Capacity miss at Wwrite %d ",address);
							if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					if(ltwo_enable==1){
						checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						iterator2=root2;
						if(ltwo_inclusive==1){
							if(count_full2<ltwo){
							while(iterator2->next!=0){
								if(iterator2->tag==numberTag2 && iterator2->valid==1){
									printf("Hit at Write L2 Cache at %d",address);
									fprintf(stream," Hit at Write L2 Cache at %d",address);
									flag=1;
									hit2++;
									break;
								}
								iterator2=iterator2->next;
							}
						  if(flag==0){
							  printf("Miss at Write L2 Cache at %d",address);
								fprintf(stream," Miss at Write L2 Cache at %d",address);
								rn = rand() % ((krifi/words));
								iterator=root;
								iterator2=root2;
								while(iterator->next!=0){
									if(iterator->number_node==rn){
										fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->tag,address,rn);
										while(iterator2->next!=0){
											if(iterator2->number_node==count_full2){
												checkAction2((char)ch,(long int)(iterator->tag),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->address=iterator->address;
												iterator2->valid=1;
												count_full2++;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												break;
											}
										iterator2=iterator2->next;
									 }
									break;
									}
									iterator=iterator->next;
					}//end of while
						   }//end of miss flag=0
						  }
							else{
								iterator2=root2;
								while(iterator2->next!=0){
								if(iterator2->tag==numberTag2 && iterator2->valid==1){
									printf("Hit at Write L2 Cache at %d",address);
									fprintf(stream," Hit at Write L2 Cache at %d",address);
									flag=1;
									hit2++;
									break;
								}
								iterator2=iterator2->next;
							}
						  if(flag==0){
							  printf("Miss at Write L2 Cache at %d",address);
								fprintf(stream," Miss at Write L2 Cache at %d",address);
								rn = rand() % ((krifi/words));
								j = rand() % ltwo;
								iterator=root;
								iterator2=root2;
								while(iterator->next!=0){
									if(iterator->number_node==rn){
										fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator2->tag,iterator->address,j);
										while(iterator2->next!=0){
											if(iterator2->number_node==j){
												checkAction2((char)ch,(long int)(iterator->tag),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->address=iterator->address;
												iterator2->valid=1;
												count_full2++;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												break;
											}
										iterator2=iterator2->next;
									 }
									break;
									}
									iterator=iterator->next;
					}//end of while
						   }//end of miss flag=0
							}
						} // end of ltwo to be exlusive
						else{
							if(count_full2<ltwo){
								iterator2=root2;
								while(iterator2->next!=0){
								if(iterator2->tag==numberTag2 && iterator2->valid==1){
									printf("Hit at Write L2 Cache at %d",address);
									fprintf(stream," Hit at Write L2 Cache at %d",address);
									flag=1;
									hit2++;
									break;
								}
								iterator2=iterator2->next;
							}
						  if(flag==0){
							  printf("Miss at Write L2 Cache at %d",address);
								fprintf(stream," Miss at Write L2 Cache at %d",address);
								rn = rand() % ((krifi/words));
								j = rand() % ltwo;
								iterator=root;
								iterator2=root2;
								while(iterator->next!=0){
									if(iterator->number_node==rn){
										fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->tag,address,rn);
										while(iterator2->next!=0){
											if(iterator2->number_node==count_full2){
												checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->address=address;
												iterator2->valid=1;
												count_full2++;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												break;
											}
										iterator2=iterator2->next;
									 }
									break;
									}
									iterator=iterator->next;
					}//end of while
						   }//end of miss flag=0
						}
							else{
								iterator2=root2;
								while(iterator2->next!=0){
								if(iterator2->tag==numberTag2 && iterator2->valid==1){
									printf("Hit at Write L2 Cache at %d",address);
									fprintf(stream," Hit at Write L2 Cache at %d",address);
									flag=1;
									hit2++;
									break;
								}
								iterator2=iterator2->next;
							}
						  if(flag==0){
							  printf("Miss at write L2 Cache at %d",address);
								fprintf(stream," Miss at write L2 Cache at %d",address);
								rn = rand() % ((krifi/words));
								j = rand() % ltwo;
								iterator=root;
								iterator2=root2;
								while(iterator->next!=0){
									if(iterator->number_node==rn){
										fprintf(stream," at L1 %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->tag,address,rn);
										fprintf(stream," at L2 %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator2->tag,address,j);
										while(iterator2->next!=0){
											if(iterator2->number_node==j){
												checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
												iterator2->tag=numberTag2;
												iterator2->address=address;
												iterator2->valid=1;
												iterator->tag=numberTag;
												iterator->valid=1;
												iterator->address=address;
												break;
											}
										iterator2=iterator2->next;
									 }
									break;
									}
									iterator=iterator->next;
								}//end of while
						   }//end of miss flag=0

							}
					  }
					}//end of ltwo enabled
					if(victim==1){
										iterator4=root3;
										checkV=0;
										while(iterator4->next!=0){
											if(iterator4->address==address){
												printf(" Hit at Victim Cache Write  %d\n",address);
												fprintf(stream," Hit at Victim Cache Write %d ",address);
												checkV=1;
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + write_ram + read_victim;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + write_ram + read_cache2;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_victim;
															fprintf(stream," cycles: %d ",(write_cache));
															}
															hit3++;
												break;
											}
											iterator4=iterator4->next;
										}
										if(checkV==0){
												printf(" Miss at Victim Cache Write  %d\n",address);
												fprintf(stream," Miss at Victim Cache Write %d ",address);
															if(write_type==0 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==0 && allocate==0){
															total_cycles = total_cycles +  write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache + write_ram));
															}if(write_type==1 && allocate==0){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}if(write_type==1 && allocate==1){
															total_cycles =  total_cycles + write_cache + read_ram;
															fprintf(stream," cycles: %d ",(write_cache));
															}
										  }

										}//end of victim enable

					rn = rand() % ((krifi/words));
					//printf("rn : %d \n",rn);
					while(iterator->next!=0){
						if(iterator->number_node==rn){
							fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->tag,address,rn);
							if(victim==1){
							iterator4=root3;
							while(iterator4->next!=0){
								if(iterator4->number_node==vNo){
									iterator4->address=iterator->tag;
									vNo++;
									break;
								}
							iterator4=iterator4->next;
							}
							}
							iterator->tag=numberTag;
							iterator->valid=1;
							break;
						  }
						iterator=iterator->next;
					}//end of while
					if(vNo==victimSize){
						vNo=0;
					}
				}//end of type 3 if statment
			 }//end of flag
			}//endo of else
		}//end of write

		if(dat=='m'){
			flag=0;
			iterator=root;
			while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
				    printf("Hit at Modify %d\n",address);
					fprintf(stream," Hit at Modify at L1 Cache %d ",address);
					hit++;
					total_cycles = total_cycles + read_cache;
					fprintf(stream," cycles: %d ",read_cache);
					iterator->lru_number=0;
					flag++;
					break;
				   } 
				else{
						}
				 
			
			iterator = iterator->next;
	 
			}
			if(flag==0){
					printf("Miss at Modify %d\n",(int)address);
					fprintf(stream," Miss at Modify at L1 Cache %d ",address);
					total_cycles = total_cycles + read_cache + read_ram;
					fprintf(stream," cycles: %d ",read_cache + read_ram);
					if(ltwo_enable==1){
						checkAction2((char)ch,(long int)(address),bitsRam,index2,bo2,choice,&numberInd2,&numberBlockOff2,&numberTag2);
						flag=0;
						iterator2=root2;
						while(iterator2->next!=0){
							if(iterator2->tag==numberTag2 && iterator2->valid==1){
								printf("Hit at Modify L2 Cache at %d\n",address);
								fprintf(stream," Hit at Modify L2 Cache at %d ",address);
								hit2++;
								flag=1;
								break;
							}
						iterator2=iterator2->next;
						}
						if(flag==0){
							   printf("Miss at Modify L2 Cache at %d\n",address);
							   fprintf(stream," Miss at Modify L2 Cache at %d ",address);
						 }
					}
					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf("Hit at Modify Victim Cache at %d\n",address);
								fprintf(stream," Hit at Modify Victim Cache at %d ",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
					   if(flag==0){
								printf("Miss at Modify Victim Cache at %d\n",address);
								fprintf(stream," Miss at Modify Victim Cache at %d ",address);
					     }
				   }//end of victim is enabled 
			  }//end of flag==0 modify
          } // end of modify
		  if(dat=='f'){
		 iterator=root;
			while(iterator->next!=0){
				iterator->valid=0;
				iterator->lru_number=0;
				iterator = iterator->next;
			  }
			if(ltwo_enable==1){
				iterator2=root2;
			while(iterator2->next!=0){
				iterator2->valid=0;
				iterator2->lru_number=0;
				iterator2 = iterator2->next;
			  }
			count_full2=0;
			fifo_number2=0;
			}
			if(victim==1){
				iterator4=root3;
				while(iterator4->next!=0){
				iterator4->valid=0;
				iterator4->lru_number=0;
				iterator4->address=-1;
				iterator4 = iterator4->next;
			     }
				vNo=0;
			}
			count_full=0;
			fifo_number=0;
		} //end of flush

		//iterator=root;
	//	while(iterator->next!=0)
	//{
	//	//printf(" [%d]-> ",iterator->number_node);
	//	//printf(" %d ",iterator->tag);
	//	//printf(" lru %d",iterator->lru_number);
	//	//iterator = iterator->next;
	//}
	//printf("\n");

	}//end of numberOffblock=-1
	else {

		iterator=root;
			while(iterator->next!=0 && iterator->valid==1){
				iterator->lru_number++;
				iterator=iterator->next;
			}

  //if(dat=='r'){
		//	flag=0;
		//	iterator=root;
		//	while(iterator->next!=0){
		//		if(iterator->tag==numberTag  && iterator->valid==1){
		//			if(iterator->block_offset[numberBlockOff]==address){
		//						 printf("hit at read at %d\n",address);
		//						 fprintf(stream," hit at read at %d ",address);
		//						 hit++;
		//						 total_cycles = total_cycles + read_cache;
		//						 fprintf(stream," cycles: %d ",read_cache);
		//						 iterator->lru_number=0;
		//						 flag++;
		//						 break;
		//			  } else{
		//						
		//		       } 
		//		   
		//		   } 
		//		else{
		//				}
		//		 
		//	
		//	iterator = iterator->next;
	 //
		//	}
		//	if(flag==0){
		//			printf("miss at read at %d\n",(int)address);
		//			fprintf(stream," miss at read at %d ",address);
		//			total_cycles = total_cycles + read_cache + read_ram;
		//			fprintf(stream," cycles %d ",read_cache + read_ram);
		//			miss++;
		//	} // end of if flag==0 statement
  //        } // end of read
	if(dat=='r'){
		
			flag=0;
			iterator=root;
			if(count_full<(krifi/words)){
				while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
					if(iterator->block_offset[numberBlockOff]==address){
						//printf("yo");
						
						printf("hit at Read %d\n",address);
						fprintf(stream," Hit at Read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
						iterator->lru_number=0;
						flag=1;
						hit++;
					  }
					else{
						miss++;
						printf("miss at Read at %d\n",address);
						fprintf(stream," Miss at Read at %d ",address);
						if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						iterator->block_offset[numberBlockOff]=address;
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->lru_number=0;
						iterator->address=address;
						flag=1;
					    }
				}
				  
				iterator=iterator->next;

			}
				if(flag==0){
					miss++;
					printf("Compulsory miss at Read at %d\n",address);
					fprintf(stream," Compulsory miss at Read at %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					iterator=root;
					while(iterator->next!=0){
					if(iterator->number_node==count_full){
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->block_offset[numberBlockOff]=address;
						iterator->address=address;
						count_full++;
						break;
					}
					iterator=iterator->next;
				   }
			  }
			}
			else {
				flag=0;
				iterator=root;
					while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
					if(iterator->block_offset[numberBlockOff]==address){
				//printf("yo3");
				    
						printf("hit at Read %d\n",address);
						fprintf(stream," Hit at Read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;
					}
					else{
						miss++;
						printf("miss at Read at %d\n",address);
						fprintf(stream," Miss at Read %d ",address);
						if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						iterator->block_offset[numberBlockOff]=address;
						iterator->lru_number=0;
						iterator->address=address;
						flag=1;
					    }
				   } 
				iterator=iterator->next;
				}
				if(flag==0){

				if(type==1){
					flag=0;
					iterator=root;
					miss++;
					printf("Capacity miss at Read at %d\n",address);
					fprintf(stream," Capacity miss at Read at %d ",address);
				if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //emd of victim to be enabled
					
				if(flag==0){
					while(iterator->next!=0){
						if(iterator->number_node==fifo_number){
							fprintf(stream," %d got replaced by %d beccause of fifo in place %d ",iterator->address,address,fifo_number);
							if(victim==1 ){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							iterator->block_offset[numberBlockOff]=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							 iterator->address=address;
							fifo_number++;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
				}
						//printf("%krifi / words %d\n",(krifi/words));
						if(fifo_number>=(krifi/words))
							fifo_number=0;
			   }
				else if(type==2){
					iterator=root;
					flag=0;
					miss++;
					printf("Capacity miss at Read %d\n",address);
					fprintf(stream," Capacity miss at Read at %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

						while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
								}
						  }
					flag++;
					iterator=iterator->next;
					
						  
				  }
						//if(flag==0){
						iterator=root;
						while(iterator->next!=0){
						if(iterator->number_node==max_node){
							fprintf(stream," %d got replaced by %d beccause of lru with lru number to be %d in place with the max node %d ",iterator->address,address,iterator->lru_number,max_node);
							if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							for(base=0;base<words;base++)
								iterator->block_offset[base]=-1;

							iterator->block_offset[numberBlockOff]=address;
							
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->lru_number=0;
							iterator->address=address;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						//}
				} // end of type 2
				if(type==3){
					iterator=root;
					miss++;
					flag=0;
					printf("Capacity miss at read %d\n",address);
					fprintf(stream," Capacity miss at Read at %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

	
					rn = rand() % ((krifi/words));
					printf("rn : %d \n",rn);
					while(iterator->next!=0){
						if(iterator->number_node==rn){
							fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->address,address,rn);
							if(victim==1 ){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							for(base=0;base<words;base++)
								iterator->block_offset[base]=-1;
							iterator->block_offset[numberBlockOff]=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->address=address;
							break;
						  }
						iterator=iterator->next;
					}//end of while
				}//end of type 3 if statment
			 }//end of flag
			}//endo of else
		}//end of write

	if(dat=='w'){
		
			flag=0;
			iterator=root;
			if(count_full<(krifi/words)){
				while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
					if(iterator->block_offset[numberBlockOff]==address){
						//printf("yo");
						
						printf("hit at write %d\n",address);
						fprintf(stream," Hit at write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
						iterator->lru_number=0;
						flag=1;
						hit++;
					  }
					else{
						miss++;
						printf("miss at write2 at %d\n",address);
						fprintf(stream," Miss at write at %d ",address);
						if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						iterator->block_offset[numberBlockOff]=address;
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->lru_number=0;
						iterator->address=address;
						flag=1;
					    }
				}
				  
				iterator=iterator->next;

			}
				if(flag==0){
					miss++;
					printf("Compulsory miss at write at %d\n",address);
					fprintf(stream," Compulsory miss at write at %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					iterator=root;
					while(iterator->next!=0){
					if(iterator->number_node==count_full){
						iterator->tag=numberTag;
						iterator->valid=1;
						iterator->block_offset[numberBlockOff]=address;
						iterator->address=address;
						count_full++;
						break;
					}
					iterator=iterator->next;
				   }
			  }
			}
			else {
				flag=0;
				iterator=root;
					while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
					if(iterator->block_offset[numberBlockOff]==address){
				//printf("yo3");
				    
						printf("hit at write %d\n",address);
						fprintf(stream," Hit at write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;
					}
					else{
						miss++;
						printf("miss at write2 at %d\n",address);
						fprintf(stream," Miss at write %d ",address);
						if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						iterator->block_offset[numberBlockOff]=address;
						iterator->lru_number=0;
						iterator->address=address;
						flag=1;
					    }
				   } 
				iterator=iterator->next;
				}
				if(flag==0){

				if(type==1){
					flag=0;
					iterator=root;
					miss++;
					printf("Capacity miss at write at %d\n",address);
					fprintf(stream," Capacity miss at write at %d ",address);
				if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Write at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Write at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Write at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Write at Victim Cache at %d",address);
						}
					} //emd of victim to be enabled
					
				if(flag==0){
					while(iterator->next!=0){
						if(iterator->number_node==fifo_number){
							fprintf(stream," %d got replaced by %d beccause of fifo in place %d ",iterator->address,address,fifo_number);
							if(victim==1 ){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							iterator->block_offset[numberBlockOff]=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							 iterator->address=address;
							fifo_number++;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
				}
						//printf("%krifi / words %d\n",(krifi/words));
						if(fifo_number>=(krifi/words))
							fifo_number=0;
			   }
				else if(type==2){
					iterator=root;
					flag=0;
					miss++;
					printf("Capacity miss at write %d\n",address);
					fprintf(stream," Capacity miss at write at %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Write at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Write at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Write at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Write at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

						while(iterator->next!=0){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
								}
						  }
					flag++;
					iterator=iterator->next;
					
						  
				  }
						//if(flag==0){
						iterator=root;
						while(iterator->next!=0){
						if(iterator->number_node==max_node){
							fprintf(stream," %d got replaced by %d beccause of lru with lru number to be %d in place with the max node %d ",iterator->address,address,iterator->lru_number,max_node);
							if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							for(base=0;base<words;base++)
								iterator->block_offset[base]=-1;

							iterator->block_offset[numberBlockOff]=address;
							
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->lru_number=0;
							iterator->address=address;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						//}
				} // end of type 2
				if(type==3){
					iterator=root;
					miss++;
					flag=0;
					printf("Capacity miss at write %d\n",address);
					fprintf(stream," Capacity miss at write at %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Write at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Write at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Write at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Write at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

	
					rn = rand() % ((krifi/words));
					printf("rn : %d \n",rn);
					while(iterator->next!=0){
						if(iterator->number_node==rn){
							fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d ",iterator->address,address,rn);
							if(victim==1 ){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							for(base=0;base<words;base++)
								iterator->block_offset[base]=-1;
							iterator->block_offset[numberBlockOff]=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->address=address;
							break;
						  }
						iterator=iterator->next;
					}//end of while
				}//end of type 3 if statment
			 }//end of flag
			}//endo of else
		}//end of write
		
		if(dat=='m'){
			flag=0;
			iterator=root;
			while(iterator->next!=0){
				if(iterator->tag==numberTag  && iterator->valid==1){
					if(iterator->block_offset[numberBlockOff]==address){
								 printf("hit at modify at %d\n",address);
								 fprintf(stream," Hit at modify %d ",address);
								 hit++;
								 total_cycles = total_cycles + read_cache;
								 fprintf(stream,"cycles: %d ",read_cache);
								 iterator->lru_number=0;
								 flag++;
								 break;
					  } else{
								
				       } 
				   
				   } 
				else{
						}
				 
			
			iterator = iterator->next;
	 
			}
			if(flag==0){
					printf("miss at modify at %d\n",(int)address);
					fprintf(stream," Miss at modify %d ",address);
					total_cycles = total_cycles + read_cache + read_ram;
					fprintf(stream,"cycles: %d ",read_cache + read_ram);
								if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Write at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Write at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Write at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Write at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

			 } //end of if flag ==0 statement
          } // end of modify
		if(dat=='f'){
		 iterator=root;
			while(iterator->next!=0){
				for(base=0;base<words;base++)
					iterator->block_offset[base]=-1;
				iterator->valid=0;
				iterator->lru_number=0;
				iterator = iterator->next;
			  }
			count_full=0;
			fifo_number=0;
		} //end of flush

		
	
	
	
	}//end of final else
	//iterator=root;
	//	
	//	while(iterator->next!=0)
	//{
	//	
	//	printf(" [%d]-> ",iterator->number_node);
	//	printf(" %d ",iterator->block_offset[0]);
	//	printf(" %d ",iterator->block_offset[1]);

	//	//printf(" lru %d",iterator->lru_number);
	//	iterator = iterator->next;
	//}
	//printf("\n");
 }//end of choice==3
 else if(choice==2){
	 
	 if(numberBlockOff==-1){
		iterator=root;
			while(iterator->next!=0 && iterator->valid==1){
				iterator->lru_number++;
				iterator=iterator->next;
			}
			//if(dat=='r'){
			//flag=0;
			//iterator=root;
			//while(iterator->next!=0){
			//	if(iterator->index==numberInd){
			//	if(iterator->tag==numberTag  && iterator->valid==1){
			//	    printf("hit at read %d\n",address);
			//		fprintf(stream," hit at read %d ",address);
			//		hit++;
			//		total_cycles = total_cycles + read_cache;
			//		fprintf(stream," cycles: %d ",read_cache);
			//		iterator->lru_number=0;
			//		flag++;
			//		break;
			//	   } 
			//	else{
			//			}
			//	 
			//
	 
			//}
			//	
			//iterator = iterator->next;
		 //  }
			//if(flag==0){
			//		printf("miss at read %d\n",(int)address);
			//		fprintf(stream," miss at read %d ",address);
			//		total_cycles = total_cycles + read_cache + read_ram;
			//		fprintf(stream," cycles: %d ",read_cache + read_ram);
			//		miss++;
			// }// end of if statement flag==0 
   //       } // end of read
		  if(dat=='r'){
	
			flag=0;
			flag2=0;
			iterator=root;
				while(iterator->next!=0){
					if(iterator->index==numberInd){
						
				if(iterator->tag==numberTag  && iterator->valid==1){
			//	printf("yo2");
				   printf("hit at Read %d\n",address);
						fprintf(stream," Hit at Read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;
					flag2=1;
				   }
				
			     }
					iterator=iterator->next;
				}
				if(flag==0){
					if(iterator->valid==0 && numWays[numberInd]<NUM_WAYS){
					printf("miss at Read %d\n",address);
					fprintf(stream," miss at Read %d ",address);
					}
					miss++;
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}


					iterator=root;
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							//printf("yo yo yo");
							if(numWays[numberInd]<NUM_WAYS){
									
								if(iterator->way==numWays[numberInd]){
									iterator->address=address;
									iterator->tag=numberTag;
									iterator->valid=1;
									numWays[numberInd] = numWays[numberInd] + 1;
									flag2=1;
									break;
								}
							}
						}
						
					
					iterator=iterator->next;
				   }
			  }
			if(flag2==0){
		
				//flag=0;
		/*		iterator=root;*/
				//if(flag==0){

				if(type==1){
					iterator=root;
					miss++;
					printf(" miss at Read %d\n",address);
					fprintf(stream,"miss at Read %d ",address);
				if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

					
					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

				
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							if(iterator->way==way_fifo_number[numberInd]){
							fprintf(stream," %d got replaced by %d beccause of fifo in place %d in way %d ",iterator->address,address,way_fifo_number[numberInd],iterator->way);
								if(victim==1 && flag==0 ){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							iterator->address=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							way_fifo_number[numberInd]=way_fifo_number[numberInd] + 1;
							break;
						  }
						}
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						if(way_fifo_number[numberInd]>NUM_WAYS)
							way_fifo_number[numberInd]=0;
			   }
				else if(type==2){
					j=0;
					iterator=root;
					flag=0;
					miss++;
					printf("miss at Read %d\n",address);
					fprintf(stream," miss at Read %d ",address);

					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					if(victim==1){
						j=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at  Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								j=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(j==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

						while(iterator->next!=0){
							if(iterator->index==numberInd){
								for(lru_way=0;lru_way<NUM_WAYS;lru_way++){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								iterator=iterator->next;
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
								}
						  }
					 flag++;
					 }
					
					}
					
					iterator=iterator->next;
				  }
						if(j==0){
						iterator=root;
						while(iterator->next!=0){
						if(iterator->number_node==max_node){
								if(victim==1 && j==0){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of lru with lru number to be %d in place with the max node %d in way %d ",iterator->address,address,iterator->lru_number,max_node,iterator->way);
							iterator->address=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->lru_number=0;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						}
				} // end of type 2
				if(type==3){
					iterator=root;
					flag=0;
					printf("Read at write %d\n",address);
					fprintf(stream," Read at write %d ",address);
					miss++;
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
	                
					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

					rn = rand() % (NUM_WAYS);
					printf("rn : %d \n",rn);
					
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							if(iterator->way==rn){
							if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d in way %d ",iterator->address,address,rn,iterator->way);
							iterator->address=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							break;
						  }
						 }
						iterator=iterator->next;
					}//end of while
					
				}//end of type 3 if statment
			// }//end of flag
			}//endo of else
		}//end of read choice 2
		  if(dat=='w'){
	
			flag=0;
			flag2=0;
			iterator=root;
				while(iterator->next!=0){
					if(iterator->index==numberInd){
						
				if(iterator->tag==numberTag  && iterator->valid==1){
			//	printf("yo2");
				   printf("hit at write %d\n",address);
						fprintf(stream," Hit at write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;
					flag2=1;
				   }
				
			     }
					iterator=iterator->next;
				}
				if(flag==0){
					if(iterator->valid==0 && numWays[numberInd]<NUM_WAYS){
					printf("Compulsory miss at write %d\n",address);
					fprintf(stream," Compulsory miss at write %d ",address);
					}
					miss++;
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}


					iterator=root;
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							//printf("yo yo yo");
							if(numWays[numberInd]<NUM_WAYS){
									
								if(iterator->way==numWays[numberInd]){
									iterator->address=address;
									iterator->tag=numberTag;
									iterator->valid=1;
									numWays[numberInd] = numWays[numberInd] + 1;
									flag2=1;
									break;
								}
							}
						}
						
					
					iterator=iterator->next;
				   }
			  }
			if(flag2==0){
		
				//flag=0;
		/*		iterator=root;*/
				//if(flag==0){

				if(type==1){
					iterator=root;
					miss++;
					printf("Capacity miss at write %d\n",address);
					fprintf(stream," Capacity miss at write %d ",address);
				if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

					
					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Write at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Write at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Write at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Write at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

				
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							if(iterator->way==way_fifo_number[numberInd]){
							fprintf(stream," %d got replaced by %d beccause of fifo in place %d in way %d ",iterator->address,address,way_fifo_number[numberInd],iterator->way);
								if(victim==1 && flag==0 ){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							iterator->address=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							way_fifo_number[numberInd]=way_fifo_number[numberInd] + 1;
							break;
						  }
						}
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						if(way_fifo_number[numberInd]>NUM_WAYS)
							way_fifo_number[numberInd]=0;
			   }
				else if(type==2){
					j=0;
					iterator=root;
					flag=0;
					miss++;
					printf("Capacity miss at write %d\n",address);
					fprintf(stream," Capacity miss at write %d ",address);

					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					if(victim==1){
						j=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Write at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Write at Victim Cache at %d",address);
								hit3++;
								j=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(j==0){
							    printf(" Miss at Write at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Write at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

						while(iterator->next!=0){
							if(iterator->index==numberInd){
								for(lru_way=0;lru_way<NUM_WAYS;lru_way++){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								iterator=iterator->next;
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
								}
						  }
					 flag++;
					 }
					
					}
					
					iterator=iterator->next;
				  }
						if(j==0){
						iterator=root;
						while(iterator->next!=0){
						if(iterator->number_node==max_node){
								if(victim==1 && j==0){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of lru with lru number to be %d in place with the max node %d in way %d ",iterator->address,address,iterator->lru_number,max_node,iterator->way);
							iterator->address=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->lru_number=0;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						}
				} // end of type 2
				if(type==3){
					iterator=root;
					flag=0;
					printf("Capacity miss at write %d\n",address);
					fprintf(stream," Capacity miss at write %d ",address);
					miss++;
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
	                
					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Write at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Write at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Write at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Write at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

					rn = rand() % (NUM_WAYS);
					printf("rn : %d \n",rn);
					
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							if(iterator->way==rn){
							if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d in way %d ",iterator->address,address,rn,iterator->way);
							iterator->address=address;
							iterator->tag=numberTag;
							iterator->valid=1;
							break;
						  }
						 }
						iterator=iterator->next;
					}//end of while
					
				}//end of type 3 if statment
			// }//end of flag
			}//endo of else
		}//end of write choice 2
				if(dat=='m'){
			flag=0;
			iterator=root;
			while(iterator->next!=0){
				if(iterator->index==numberInd){
				if(iterator->tag==numberTag  && iterator->valid==1){
				    printf("hit at modify %d\n",address);
					fprintf(stream," hit at modify %d ",address);
					hit++;
					total_cycles = total_cycles + read_cache;
					fprintf(stream," cycles: %d ", read_cache);
					iterator->lru_number=0;
					flag++;
					break;
				   } 
				else{
						}
				 
			
	 
			}
				
			iterator = iterator->next;
		   }
			if(flag==0){
					miss++;
					printf("miss at modify %d\n",(int)address);
					fprintf(stream," miss at modify %d ",address);
					total_cycles = total_cycles + read_cache + read_ram;
					fprintf(stream," cycles: %d ",read_cache + read_ram);
					
					if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Modify at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Modify at Victim Cache at %d",address);
						}
					} //end of victim to be enabled
			  }//end of if statement flag==0
          } // end of modify choice 2
		  if(dat=='f'){
		 iterator=root;
			while(iterator->next!=0){
				iterator->valid=0;
				iterator->lru_number=0;
				iterator = iterator->next;
			  }
			memset(numWays,0,sizeof(numWays));
			memset(way_fifo_number,0,sizeof(way_fifo_number));
			if(victim==1){
			iterator4=root3;
			while(iterator4->next){
				iterator4->address=-1;
				iterator4->valid=0;
				iterator4=iterator4->next;
			}
			vNo=0;
		}
		} //end of flush choice 2


  }//end of numberBlockOff=-1
  else {

	  iterator=root;
			while(iterator->next!=0 && iterator->valid==1){
				iterator->lru_number++;
				iterator=iterator->next;
			}
			//if(dat=='r'){
			//flag=0;
			//iterator=root;
			//while(iterator->next!=0){
			//	if(iterator->index==numberInd){
			//	if(iterator->tag==numberTag  && iterator->valid==1){
			//		if(iterator->block_offset[numberBlockOff]==address){
			//	    printf("hit at read %d\n",address);
			//		fprintf(stream," hit at read %d ",address);
			//		hit++;
			//		total_cycles = total_cycles + read_cache;
			//		fprintf(stream," cycles: %d ",read_cache);
			//		iterator->lru_number=0;
			//		flag++;
			//		break;
			//	   } 
			//	else{
			//			}
			//	}
			//
	 
		   if(dat=='r'){
		//printf("yo");
		//printf(" %d\n",numberInd);
			
			flag=0;
			flag2=0;
			iterator=root;
				while(iterator->next!=0){
					if(iterator->index==numberInd){
				if(iterator->tag==numberTag  && iterator->valid==1){
					if(iterator->block_offset[numberBlockOff]==address){
						printf("hit at Read %d\n",address);
						fprintf(stream," Hit at Read %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;
					flag2=1;
				   } 
					else{
						miss++;
						printf("miss at Read at %d\n",address);
						fprintf(stream," miss at Read %d ",address);
						if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						iterator->address = address;
						iterator->block_offset[numberBlockOff]=address;
						iterator->lru_number=0;
						flag=1;
						flag2=1;
					    }

			     }
			    }
					iterator=iterator->next;
				}
				if(flag==0){
					miss++;
					if(iterator->valid==0 && numWays[numberInd]<NUM_WAYS){
					printf("Compulsory miss at Read %d\n",address);
					fprintf(stream," Compulsory miss at Read %d ",address);
					}
				if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					iterator=root;
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							//printf("yo yo yo");
							if(numWays[numberInd]<NUM_WAYS){
									
								if(iterator->way==numWays[numberInd]){
									//printf("numberBlockOff: %d and address %d\n",numberBlockOff,address);
									iterator->address = address;
									iterator->tag=numberTag;
									iterator->valid=1;
									numWays[numberInd] = numWays[numberInd] + 1;
									iterator->block_offset[numberBlockOff]=address;
									flag2=1;
									break;
								}
							}
						}
						
					
					iterator=iterator->next;
				   }
			  }
			if(flag2==0){
		
				//flag=0;
		/*		iterator=root;*/
				//if(flag==0){

				if(type==1){
					iterator=root;
					miss++;
					printf("miss at Read %d\n",address);
					fprintf(stream," Capacity miss at Read %d ",address);

				if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
							if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //end of victim to be enabled
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							if(iterator->way==way_fifo_number[numberInd]){
								
								if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of fifo in place %d in way %d ",iterator->address,address,way_fifo_number[numberInd],iterator->way);
							iterator->address = address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->block_offset[numberBlockOff]=address;
							way_fifo_number[numberInd]=way_fifo_number[numberInd] + 1;
							break;
						  }
						}
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						if(way_fifo_number[numberInd]>=NUM_WAYS)
							way_fifo_number[numberInd]=0;
			   }
				else if(type==2){
					miss++;
					iterator=root;
					flag=0;
					printf("miss at Read %d\n",address);
					fprintf(stream," Capacity miss at Read %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						if(victim==1){
						j=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								j=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(j==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

						while(iterator->next!=0){
							if(iterator->index==numberInd){
								for(lru_way=0;lru_way<NUM_WAYS;lru_way++){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								iterator=iterator->next;
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
								}
						  }
					 flag++;
					 }
					
					}
					
					iterator=iterator->next;
				  }
						iterator=root;
						while(iterator->next!=0){
						if(iterator->number_node==max_node){
								
							if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of lru with lru number to be %d in place with the max node %d in way %d ",iterator->address,address,iterator->lru_number,max_node,iterator->way);
							iterator->address = address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->lru_number=0;
							iterator->block_offset[numberBlockOff]=address;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
				} // end of type 2
				if(type==3){
					miss++;
					iterator=root;
					flag=0;
					printf("miss at Read %d\n",address);
					fprintf(stream," Capacity Read at write %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					
					if(victim==1){
						j=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Read at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Read at Victim Cache at %d",address);
								hit3++;
								j=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(j==0){
							    printf(" Miss at Read at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Read at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

					rn = rand() % (NUM_WAYS);
					printf("rn : %d \n",rn);
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							if(iterator->way==rn){

							  if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d in way %d ",iterator->address,address,rn,iterator->way);
							iterator->address = address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->block_offset[numberBlockOff]=address;
							break;
						  }
						 }
						iterator=iterator->next;
					}//end of while
				}//end of type 3 if statment
			// }//end of flag
			}//endo of else
		}//end of read choice 2

			//}
			//	
			//iterator = iterator->next;
		 //  }
			//if(flag==0){
			//		printf("miss at read %d\n",(int)address);
			//		fprintf(stream," miss at read %d ",address);
			//		total_cycles = total_cycles + read_cache + read_ram;
			//		fprintf(stream," cycles: %d ",read_cache + read_ram);
			//		miss++;
			//}//end of if statement flag==0
   //       } // end of read with blockoffset!=-1

		   if(dat=='w'){
		//printf("yo");
		//printf(" %d\n",numberInd);
			
			flag=0;
			flag2=0;
			iterator=root;
				while(iterator->next!=0){
					if(iterator->index==numberInd){
				if(iterator->tag==numberTag  && iterator->valid==1){
					if(iterator->block_offset[numberBlockOff]==address){
						printf("hit at write %d\n",address);
						fprintf(stream," Hit at write %d ",address);
						if(write_type==0 && allocate==1){
							total_cycles =  total_cycles + write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==0 && allocate==0){
							total_cycles = total_cycles +  write_cache + write_ram;
							fprintf(stream," cycles: %d ",(write_cache + write_ram));
						}if(write_type==1 && allocate==0){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}if(write_type==1 && allocate==1){
							total_cycles =  total_cycles + write_cache;
							fprintf(stream," cycles: %d ",(write_cache));
						}
					hit++;
					iterator->lru_number=0;
					flag=1;
					flag2=1;
				   } 
					else{
						miss++;
						printf("miss at write2 at %d\n",address);
						fprintf(stream," miss at write %d ",address);
						if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						iterator->address = address;
						iterator->block_offset[numberBlockOff]=address;
						iterator->lru_number=0;
						flag=1;
						flag2=1;
					    }

			     }
			    }
					iterator=iterator->next;
				}
				if(flag==0){
					miss++;
					if(iterator->valid==0 && numWays[numberInd]<NUM_WAYS){
					printf("Compulsory miss at write %d\n",address);
					fprintf(stream," Compulsory miss at write %d ",address);
					}
				if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					iterator=root;
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							//printf("yo yo yo");
							if(numWays[numberInd]<NUM_WAYS){
									
								if(iterator->way==numWays[numberInd]){
									//printf("numberBlockOff: %d and address %d\n",numberBlockOff,address);
									iterator->address = address;
									iterator->tag=numberTag;
									iterator->valid=1;
									numWays[numberInd] = numWays[numberInd] + 1;
									iterator->block_offset[numberBlockOff]=address;
									flag2=1;
									break;
								}
							}
						}
						
					
					iterator=iterator->next;
				   }
			  }
			if(flag2==0){
		
				//flag=0;
		/*		iterator=root;*/
				//if(flag==0){

				if(type==1){
					iterator=root;
					miss++;
					printf("miss at write %d\n",address);
					fprintf(stream," Capacity miss at write %d ",address);

				if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
							if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Modify at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Modify at Victim Cache at %d",address);
						}
					} //end of victim to be enabled
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							if(iterator->way==way_fifo_number[numberInd]){
								
								if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of fifo in place %d in way %d ",iterator->address,address,way_fifo_number[numberInd],iterator->way);
							iterator->address = address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->block_offset[numberBlockOff]=address;
							way_fifo_number[numberInd]=way_fifo_number[numberInd] + 1;
							break;
						  }
						}
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
						if(way_fifo_number[numberInd]>=NUM_WAYS)
							way_fifo_number[numberInd]=0;
			   }
				else if(type==2){
					miss++;
					iterator=root;
					flag=0;
					printf("miss at write %d\n",address);
					fprintf(stream," Capacity miss at write %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}

						if(victim==1){
						j=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Modify at Victim Cache at %d",address);
								hit3++;
								j=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(j==0){
							    printf(" Miss at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Modify at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

						while(iterator->next!=0){
							if(iterator->index==numberInd){
								for(lru_way=0;lru_way<NUM_WAYS;lru_way++){
							if(flag==0){
								max=iterator->lru_number;
								max_node=iterator->number_node;
							}
							if(flag!=0){
								iterator=iterator->next;
								indicate = check_for_max(max,iterator->lru_number);
								if(indicate==0){
									rn=rand() % 1;
									printf("rn is :%d\n",rn);
									if(rn==0){
										max=max;
										max_node=max_node;
									}
									else if(rn==1) {
										max=iterator->lru_number;
										max_node=iterator->number_node;										
									}
								}
								else if(indicate==-1){
									max=iterator->lru_number;
									max_node=iterator->number_node;
								}
						  }
					 flag++;
					 }
					
					}
					
					iterator=iterator->next;
				  }
						iterator=root;
						while(iterator->next!=0){
						if(iterator->number_node==max_node){
								
							if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of lru with lru number to be %d in place with the max node %d in way %d ",iterator->address,address,iterator->lru_number,max_node,iterator->way);
							iterator->address = address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->lru_number=0;
							iterator->block_offset[numberBlockOff]=address;
							break;
						  }
					//printf("fifo number: %d\n",fifo_number);
					iterator=iterator->next;
					//printf("fifo number: %d\n",fifo_number);
						  
					     }
				} // end of type 2
				if(type==3){
					miss++;
					iterator=root;
					flag=0;
					printf("miss at write %d\n",address);
					fprintf(stream," Capacity miss at write %d ",address);
					if(write_type==0 && allocate==1){
						total_cycles =  total_cycles + write_cache + write_ram + read_ram + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + read_ram + write_ram));
					}else if(write_type==0 && allocate==0){
						total_cycles =  total_cycles + write_cache + write_ram;
						fprintf(stream," cycles: %d ",( write_cache + write_ram));
					}else if(write_type==1 && allocate==0){
						if(iterator->valid==1){
						total_cycles =  total_cycles + write_cache + write_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_ram + write_cache));
						}else{
						total_cycles = total_cycles + write_cache + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + write_cache));
						}
					}else if(write_type==1 && allocate==1){
						total_cycles = total_cycles + write_cache + read_ram + write_cache;
						fprintf(stream," cycles: %d ",( write_cache + read_ram + write_cache));
					}
					
					if(victim==1){
						j=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Modify at Victim Cache at %d",address);
								hit3++;
								j=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(j==0){
							    printf(" Miss at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Modify at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

					rn = rand() % (NUM_WAYS);
					printf("rn : %d \n",rn);
					while(iterator->next!=0){
						if(iterator->index==numberInd){
							if(iterator->way==rn){

							  if(victim==1){
								iterator4=root3;
								while(iterator4->next!=0){
									if(iterator4->number_node==vNo){
										iterator4->address=iterator->address;
										vNo++;
										break;
									}
								iterator4=iterator4->next;
								}
								if(vNo>=victimSize){
								vNo=0;
								}
							}
							fprintf(stream," %d got replaced by %d beccause of Random algorith to random place to be %d in way %d ",iterator->address,address,rn,iterator->way);
							iterator->address = address;
							iterator->tag=numberTag;
							iterator->valid=1;
							iterator->block_offset[numberBlockOff]=address;
							break;
						  }
						 }
						iterator=iterator->next;
					}//end of while
				}//end of type 3 if statment
			// }//end of flag
			}//endo of else
		}//end of write choice 2
		if(dat=='m'){
			flag=0;
			iterator=root;
			while(iterator->next!=0){
				if(iterator->index==numberInd){
				if(iterator->tag==numberTag  && iterator->valid==1){
					if(iterator->block_offset[numberBlockOff]==address){
				    printf("hit at modify %d\n",address);
					fprintf(stream," hit at modify %d ",address);
					hit++;
					total_cycles = total_cycles + read_cache;
					fprintf(stream," cycles: %d ",read_cache);
					iterator->lru_number=0;
					flag++;
					break;
				   } 
				else{
						}
				}
			
	 
			}
				
			iterator = iterator->next;
		   }
			if(flag==0) {
					printf("miss at modify %d\n",(int)address);
					fprintf(stream," miss at modify %d ",(int)address);
					total_cycles = total_cycles + read_cache + read_ram;
					fprintf(stream," cycles: %d ",read_cache + read_ram);
					miss++;

						if(victim==1){
						flag=0;
						iterator4=root3;
						while(iterator4->next!=0){
							if(iterator4->address==address){
								printf(" Hit at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Hit at Modify at Victim Cache at %d",address);
								hit3++;
								flag=1;
								break;
							}
						iterator4=iterator4->next;
						}
						if(flag==0){
							    printf(" Miss at Modify at Victim Cache at %d\n",address);
								fprintf(stream," Miss at Modify at Victim Cache at %d",address);
						}
					} //end of victim to be enabled

			  }// end of if statement flag==0
          } // end of modify with blockoffset!=-1

		 if(dat=='f'){
		 iterator=root;
			while(iterator->next!=0){
				for(base=0;base<words;base++)
					iterator->block_offset[base]=-1;
				iterator->valid=0;
				iterator->lru_number=0;
				iterator = iterator->next;
			  }
			memset(numWays,0,sizeof(numWays));
			memset(way_fifo_number,0,sizeof(way_fifo_number));
		if(victim==1){
			iterator4=root3;
			while(iterator4->next){
				iterator4->address=-1;
				iterator4->valid=0;
				iterator4=iterator4->next;
			}
			vNo=0;
		}
		} //end of flush choice 2 with blockoffset!=-1

	  
  /*	iterator = root;
		while(iterator->next!=0)
	{
		printf(" [%d]-> ",iterator->number_node);
		printf(" index %d",iterator->index);
		printf(" %d",iterator->tag);
		printf(" way %d",iterator->way);
		iterator = iterator->next;
	}
	printf("\n");*/
  }//end of else 
 }//end of choice 2
 fprintf(stream,"\n");
 		if( stream )
   {
      err = fclose( stream );
   }
	
}//end of for
	 


	//ch = getc(stuff);  // read in the character at the current position in the inputfile
	//printf("am here!, %c %d\n",(char)ch,(int)address);
	
	fclose(stuff);
	fclose(check);
	err  = fopen_s(&stream, "exodos.txt","a");
	
	percentage = 100*((double)hit/((double)size * (double)times));
	printf("hit level 1 cache -> %d",hit);
	fprintf(stream,"\nhit level 1 cache -> %d",hit);
	hit_overall = hit_overall + hit;
	if(ltwo_enable==1){
	printf("hit level 2 cache -> %d",hit2);
	fprintf(stream,"\nhit level 2 cache -> %d",hit2);
	hit_overall = hit_overall + hit2;
	}
	if(victim==1){
	printf("\n hit victim cache -> %d",hit3);
	fprintf(stream,"\nhit victim cache -> %d",hit3);
	hit_overall = hit_overall + hit3;
	}
	
	if(victim==1 || ltwo_enable==1){
	printf("\n hit overal -> %d",hit_overall);
	fprintf(stream,"\n hit overal -> %d",hit_overall);
	percentage_overall = 100*((double)hit_overall/((double)size * (double)times));
	}

	printf(" and total cycles %d -> %.2f ",total_cycles,percentage);
	if(victim==0 && ltwo_enable==0)
	fprintf(stream," out of %d references -> %.2f\n ",(size*times),percentage);
	else
    fprintf(stream," out of %d references -> %.2f\n ",(size*times),percentage_overall);

	if(victim==0 && ltwo_enable==0){
	printf("\n Miss -> %d",(size*times) - hit);
	fprintf(stream,"\n Miss -> %d",(size*times) - hit);
	percentage = 100*((double)(size*times - hit)/((double)size * (double)times));
	printf(" -> %.2f ",percentage);
	fprintf(stream,"  out of %d references -> %.2f\n ",(size*times),percentage);
	fprintf(stream,"And Total Cycles: %d",total_cycles);
	}
	else{
	printf("\n Miss -> %d",(size*times) - hit_overall);
	fprintf(stream,"\n Miss -> %d",(size*times) - hit_overall);
	percentage_overall = 100*((double)(size*times - hit_overall)/((double)size * (double)times));
	printf(" -> %.2f ",percentage_overall);
	fprintf(stream,"  out of %d references -> %.2f\n ",(size*times),percentage_overall);
	fprintf(stream,"And Total Cycles: %d",total_cycles);
	}
		if(write_type==0 && allocate==1)
			fprintf(stream,"\n Write Through  and write allocate");
	if(write_type==0 && allocate==0)
			fprintf(stream,"\n Write Through  and non write allocate");
	if(write_type==1 && allocate==0)
			fprintf(stream,"\n Write Back  and non write allocate");				
	if(write_type==1 && allocate==1)
			fprintf(stream,"\n Write Back  and write allocate");
	fprintf(stream,"\n");
 		if( stream )
   {
      err = fclose( stream );
   }
	system("pause");
	return 0;
} //end of main