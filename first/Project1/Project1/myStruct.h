#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define NUM_WAYS 4

FILE *stream;

int logarithmos_dio(int number){
	int result;
	result = log(number)/log(2);
	return result;
}

void checkAction(char action,long int num,int len,int indexNo,int offset,int choice){
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
	 // printf(" Index Bits: ");
	 if(indexNo>0){
		fprintf(stream," Index Bits: ");
		for(i;i>=offset;i--) {
			// printf("%ld",ipolipo[i]);
			 fprintf(stream,"%ld",ipolipo[i]);
		}
	 }
	 // printf(" Block Bits: ");
	  fprintf_s(stream," Block Bits: ");
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	   }
	}
	else {
	  for(i=length-1;i>=0;i--) {
	  //  printf("%ld",ipolipo[i]);
	    fprintf(stream,"%ld",ipolipo[i]);
	  }
	// printf(" Tag Bits: ");
	 for(i=length-1;i>=indexNo;i--) {
		// printf("%d",ipolipo[i]);
		 fprintf(stream,"%d",ipolipo[i]);
	   }
	//  printf(" Index Bits: ");
	  fprintf(stream," Index Bits: ");
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%d",ipolipo[i]);
	 }
	}
 }
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
	  //printf(" Index Bits: ");
	  if(indexNo>0){
		fprintf(stream," Index Bits: ");
		for(i;i>=offset;i--) {
			// printf("%ld",ipolipo[i]);
			fprintf(stream,"%ld",ipolipo[i]);
		  }
	  }
	//  printf(" Block Bits: ");
	  fprintf(stream," Block Bits: ");
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	   }
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
	 if(indexNo>0){
	 // printf(" Index Bits: ");
     fprintf(stream," Index Bits: ");
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	    }
	 }
  }//end of else
numRan = rand() % (NUM_WAYS ) + 1;
//printf(" way:%d",numRan);
fprintf(stream," way:%d",numRan);

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
	 // printf(" Block Bits: ");
	  fprintf(stream," Block Bits: ");
	 for(i;i>=0;i--) {
		// printf("%ld",ipolipo[i]);
		 fprintf(stream,"%ld",ipolipo[i]);
	 }
 }

	//printf("\n");
	fprintf(stream,"\n");
	if( stream )
   {
      err = fclose( stream );
   }
}//end of function checkAction
