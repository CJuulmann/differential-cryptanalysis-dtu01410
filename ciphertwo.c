/* ********************************************************************
	Homework 1, exercise 1.1: CipherTwo
		Find the values ofk0, k1andk2used in the encryption using 
		differential cryptanalysis and the characteristic f->d
 ******************************************************************** */

#include <stdio.h>
#include <string.h>

#define KSIZE 16	// key space of key parts
#define CSIZE 16	// candidates for secret keys

char bitXor(char x, char y);

/* 
	The following message/ciphertext pairs are given in the exercise,
	all encrypted under the same key (k0,k1,k2,k3 four bits each).

	The array have been sorted such that {msg[i], msg[i+1]} are pairs.
	(Thus a total of 8 paris to work on).
*/
char msg[] 	= {0x0, 0xf, 0x3, 0xc, 0x2, 0xd};
char cipher[] = {0xe, 0x9, 0x6, 0xa, 0x7, 0xb};

char S[] = {0x6, 0x4, 0xc, 0x5, 0x0, 0x7, 0x2, 0xe, 0x1, 0xf, 0x3, 0xd, 0x8, 0xa, 0x9, 0xb};	//S-box
char R[] = {0x4, 0x8, 0x6, 0xa, 0x1, 0x3, 0x0, 0x5, 0xc, 0xe, 0xd, 0xf, 0x2, 0xb, 0x7, 0x9};	//inverse permutaion of S

int cand_cnt[CSIZE];

int i, t;
//char keyspace[KSIZE];
char k0, k1, k2;

int main(){
	
	// Prepare set with all possible key candidates in keyspace
	char keyspace[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
	
	// Use index as candidate value and assign its respective count (initially 0)
	for(i=0; i<CSIZE; i++){
		cand_cnt[i] = 0;
	}	

#ifdef K2	
	// Guess k2
	char idx1, idx2;	
	for(t=0; t<KSIZE; t++){
		for(i=0; i<=4; i+=2){
			idx1 = bitXor(keyspace[t], cipher[i]);
			idx2 = bitXor(keyspace[t], cipher[i+1]);
			
			// Verify key
			if(bitXor(R[idx1], R[idx2]) == 0xd){
				cand_cnt[t]++;
			} else{}
		}
	}		
		printf("\nGuessing k2..\n");
		for(i=0; i<CSIZE; i++){
			printf("key: 0x%x\t count: %d\n", keyspace[i], cand_cnt[i]);
		}
#endif	
		
#ifdef K1
	// Guess k1 with candidate value of k2
	k2 = 0x2;
	
	for(i=0; i<CSIZE; i++){
		cand_cnt[i] = 0;
	}	
	
	char m0, m1, w0,w1,v0,v1;
	for(i=0; i<=4; i+=2){
		
		m0 = msg[i];
		m1 = msg[i+1];
		w0 = R[bitXor(k2,cipher[i])];
		w1 = R[bitXor(k2,cipher[i+1])];
		
		for(t=0; t<KSIZE; t++){
			v0 = bitXor(t,w0);
			v1 = bitXor(t,w1);
			
			if(bitXor(R[v0],R[v1])==bitXor(m0,m1)){
				cand_cnt[t]++;
			}
		}
	}

	printf("\nK1 Guesses\n");
	for(i=0; i<CSIZE; i++){
		printf("key: 0x%x\t count: %d\n", keyspace[i], cand_cnt[i]);
	}
#endif
	
#ifdef K0	
	// Compute k0 with candidate values of k1, k2
	k2 = 0x2;
	k1 = 0x7;
	//k1 = 0xa;
	
	char u0;
	u0 = R[bitXor(k1, R[bitXor(k2, cipher[0])])];
	k0 = bitXor(msg[0], u0);		
		
	printf("\nk2: 0x%x\nk1: 0x%x\nk0: 0x%x\n", k2, k1, k0);
#endif
	
	return 0;
}

// Bitwise exclusive OR
char bitXor(char x, char y) 
{
    char a = x & y;
    char b = ~x & ~y;
    char z = ~a & ~b;
    return z;
} 