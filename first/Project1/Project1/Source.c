#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "myStruct.h"
#include <math.h>
#define NUM_WAYS 4
#define WORD_SIZE 32

FILE *stuff;

int main()
{
	int bo = 0;     //xrisi metavlitis gia to block offset 
	int flush = 0;  //xrisi metavlitis gia ton arithmo twn flush
	int words = 0;  //xrisi metavlitis posa words 8a exei ena block sto data
	int ch;			//xrisi metavlitis gia na diavazi apo to arxeio dedwmenwn 
	int address;    //xrisi metavlitis gia na perna ton arithmo dieuthinsis(ton dekadiko) apo to arxio dedwmenwn
	int times;	    //xrisi metavlitis gia to poses fores na kani reference(entries) 
	int krifi;	    //xrisi metavlitis gia na apothikeusi to megethos tis cache memory
	int bitsRam;	//xrisi metavlitis gia ta bits pou tha exi i Ram
	int bitsCache;  //xrisi metavlitis gia na kratai ta bits tis cache memory
	int size;    //size pu dinume gia ti cache
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


		// elegxos an o arithmos pio pano sto #define NUM_WAYS, ine se dinami tu 2, alios termatizi to programa
	s = NUM_WAYS && !(NUM_WAYS & (NUM_WAYS - 1));
		if(s==0){
			printf("Please give a number for the NUM_WAYS in power 2,excluding zero! and rerun the program\n");
			system("pause");
			exit(0);
		}
	//perni to megethos tis kirias mnimis ke elegxi ean ine se dinami tu 2
	do{
		if(blu==0)
			printf("Give me the size of the main memory in bytes\n");
	if(blu!=0)
		printf("Give me the size of the main memory in power of 2 please!\n"); 
	scanf_s("%d",&size);
	s = size && !(size & (size - 1));
	blu++;
	}while(s==0);

	blu=0; //midenizi to metriti gia epomeni xrisi tu
	//perni to megethos tis krifis mnimis ke elegxi ean ine se dinami tu 2
	do{
		if(blu==0)
			printf("Give me the size of the cache memory in bytes\n");
		if(blu!=0) {
			printf("The size of the Cache must be in power of 2 please!\n");
			printf("and the size of the cache must be smaller than Ram's\n");
			printf("Make sure that the values you give are correct this time\n");
		 }
	scanf_s("%d",&krifi);
	s = krifi && !(krifi & (krifi - 1));
	blu++;
	}while (s==0 || size<krifi);

	blu=0; //midenizi to metriti gia epomeni xrisi tu
	//perni twn arithmo twn reference pu prepi na kani stin krifi mnimi 
	do{
		if(blu==0)
			printf("Give me the times you want to make reference to cache memory\n");
		if(blu!=0)
			printf("The references to the cache memory,must be a positive number! (excluding zero)\n");
		blu++;
	scanf_s("%d",&times);
	}while (times<=0);

	blu=0; //midenizi to metriti gia epomeni xrisi tu
	//perni ton arithmo pu theli na kani flush sti krifi mnimi
	do{
		if(blu==0)
			printf("How much times at least you want flush to operate?\n");
		if(blu!=0)
			printf("The times you want the flush to operate,must be a positive number!\n");
		blu++;
	scanf_s("%d",&flush);
	}while (flush<0);

	blu=0; //midenizi to metriti gia epomeni xrisi tu
	//perni twn arithmo twn lexewn pu tha periexi ena block
	do{
		if(blu==0)
			printf("How many words you want in the data?\n");
		if(blu!=0)
			printf("How many words you want in the data?, it must be in power of 2!\n");
		blu++;
	scanf_s("%d",&words);
	s = words && !(words & (words - 1));
	}while (s== 0);

	size = size / bytesWord;   //ipologismos twn 8esewn(arithmos twn blocks tis kirias mnimis)
	krifi = krifi / bytesWord; //ipologismos twn 8esewn(arithmos twn blocks tis krifis mnimis)
	
	bitsRam = logarithmos_dio(size);
	printf("Bits for the main memory %d\n",bitsRam);
	bitsCache = logarithmos_dio(krifi);
	printf("Bits for the cache memory %d\n",bitsCache);
		
	printf("What type you would like the cache memory to be?\n");
	do{
	printf("1) Direct Mapped ");
	printf("  2) N-way set Assiocative ");
	printf("  3) Full set Assiocative\n");

	scanf_s("%d",&choice);
	}while(( (choice<=0) || (choice>3) ));

// ginete diadikasia ipologismu twn pediwn dieuthintodotisis vasi twn pliroforiwn pio panw
	if(choice==1){
		if(words>1){
			bo = logarithmos_dio(words);
			index = logarithmos_dio(krifi/words);
		  } else {
		index = bitsCache;
			}
	  } else if(choice==2){
			if(words>1){
				bo = logarithmos_dio(words);
				index = logarithmos_dio((krifi/(NUM_WAYS))) - logarithmos_dio(words);
			  } else {
					index = logarithmos_dio(krifi/NUM_WAYS);
		        }
	   } else if(choice==3){
		   printf("There are no index-set bits here!\n");
		   index = 0;
		   if(words>1)
				bo = logarithmos_dio(words);
	   } else{
		printf("you did not choose something!!!\n");
		exit(0);
	}

tag = bitsRam - index - bo;
	
printf("the tag is %d bits \n",tag);
printf("the index is %d bits \n",index);

if(flush!=0)
	flusho = ((times*size) / flush); //ypologismos gia to kathe poses fores iparxi periptosi na epilegi to flush
else 
	flusho = flush;

if(words>1)
	printf("the block offset %d bits \n",bo);

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
				r = (rand() % (size+1-min))+min;
				i = (rand() % (3+1-min))+min;
				if(i==3) {
					flush--;
					counter=0;
				  }
				//printf("%c %d\n",work[i],r);
				fprintf_s(stuff,"%c %d\n",work[i],r);
			}
			else{
				r = (rand() % (size+1-min))+min;
				i = (rand() % (3-min))+min;
				//printf("%c %d\n",work[i],r);
				fprintf_s(stuff,"%c %d\n",work[i],r);
			}
		counter++; //auxisi tou counter gia ipologismo twn forwn pu den egine to flush
		}//end of for loop
	
	fclose(stuff); //klisimo arxiou dedwmenwn 
	fopen_s(&stuff,"dedwmena.txt","r"); //anigma xana tou arxiou dedwmenwn gia diavasma

	for(i=0;i<(size*times);i++){
	fscanf_s(stuff,"%c",&ch,1);
	fscanf_s(stuff,"%d\n",&address,4);
	checkAction((char)ch,(long int)address,bitsRam,index,bo,choice);
	}
	//ch = getc(stuff);  // read in the character at the current position in the inputfile
	//printf("am here!, %c %d\n",(char)ch,(int)address);
	
	fclose(stuff);
	system("pause");
	return 0;
} //end of main