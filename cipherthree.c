/* ********************************************************************
	Homework 1, exercise 1.2: CipherThree
		Use differential cryptanalysis and the characteristic f->d->c 
		of probability about 1/4 to find k3, considering CipherThree 
		from the lecture notes 
 ******************************************************************** */

#include <stdio.h>
#include <string.h>

void reset();
char bitXor(char x, char y);

char S[] = {0x6, 0x4, 0xc, 0x5, 0x0, 0x7, 0x2, 0xe, 0x1, 0xf, 0x3, 0xd, 0x8, 0xa, 0x9, 0xb};	//S-box
char R[] = {0x4, 0x8, 0x6, 0xa, 0x1, 0x3, 0x0, 0x5, 0xc, 0xe, 0xd, 0xf, 0x2, 0xb, 0x7, 0x9};	//inverse permutaion of S

/* 
	The following message/ciphertext pairs are given in the exercise,
	all encrypted under the same key (k0,k1,k2,k3 four bits each).

	The array have been sorted such that {msg[i], msg[i+1]} are pairs.
	(Thus a total of 8 paris to work on).
*/
char msg[] = {0x0, 0xf, 0x1, 0xe, 0x2, 0xd, 0x3, 0xc, 0x4, 0xb, 0x5, 0x9, 0x6, 0xa, 0x7, 0x8};
char ciph[] = {0x1, 0x9, 0xd, 0x7, 0x8, 0xb, 0xa, 0x5, 0x4, 0xc, 0x3, 0xe, 0x0, 0x6, 0x2, 0xf};

// K = {k0, k1, k2, k3}
char k0, k1, k2, k3;
	
int main(){
	
	// Prepare set with all possible key candidates in keyspace
	char keys[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};

	// Use index as key candidate value and assign its respective count (initially 0)
	char cnt[16];
	memset(&cnt[0], 0, sizeof(char)*16);

	int i, t;
	char idx1, idx2;
	
#ifdef K3
	puts("Guessing k3..");
	for(t=0; t<16; t++){				// search keyspace of k3
		for(i=0; i<=8; i+=2){			// search msg/cipher pairs for the given key value
			idx1 = bitXor(t, ciph[i]);
			idx2 = bitXor(t, ciph[i+1]);
			
			if( bitXor(R[idx1], R[idx2]) == 0xc){
				 cnt[t]++;
			 } 
		}
		printf("key: 0x%x\tcount: %d\n", t, cnt[t]);
	}
	memset(&cnt[0], 0, sizeof(char)*16);
#endif
#ifdef K2	
	// choose based on max count
	k3 = 0x6;		
	char y[16];
	int j;
	puts("\nGuessing k2..");
	for(j=0; j<16; j++){
		// compute y part of the chain as the new cipher
		y[j] = R[bitXor(k3, ciph[j])];		
	}
	for(t=0; t<16; t++){						// search keyspace of k2
		for(i=0; i<=8; i+=2){					// search msg/cipher pairs for the given key value
			idx1 = bitXor(t, y[i]);
			idx2 = bitXor(t, y[i+1]);
			
			if( bitXor(R[idx1], R[idx2]) == 0xd){
				cnt[t]++;
			} else{}
		}
		printf("key: 0x%x\tcount: %d\n", t, cnt[t]);
	}
	// clear counts for next round
	memset(&cnt[0], 0, sizeof(char)*16);

	#ifdef K1
		// choose based on max count
		k2 = 0x3;	
		char x[16];

		puts("\nGuessing k1..");
		// compute x part of the chain as the new cipher
		for(j=0; j<16; j++){			
			x[j] = bitXor(k2, y[j]);
		}
		for(t=0; t<16; t++){
			for(i=0; i<=8; i+=2){
				if(	bitXor(msg[i], msg[i+1]) == 
					bitXor(
						R[bitXor(t, R[x[i]])],
						R[bitXor(t, R[x[i+1]])]
												)
					){
							cnt[t]++;
				} else{}
			}
			printf("key: 0x%x\tcount: %d\n", t, cnt[t]);
		}
		#ifdef K0	
			// choose based on max count
			k1 = 0x4;			
			
			puts("\nSearch k0..");
			for(t=0; t<16; t++){
				if(S[bitXor(S[bitXor(msg[0], t)], k1)] == x[0]){
					k0 = t;
				}
			}
			printf("\nK0: 0x%x\n", k0);
		#endif
	#endif
#endif

	return 0;
}

// Bitwise exclusive OR
char bitXor(char x, char y) {
    char a = x & y;
    char b = ~x & ~y;
    char z = ~a & ~b;
    return z;
} 

