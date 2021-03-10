#include <stdio.h>
 
char msg[] 		= {0x0, 0xf, 0x3, 0xc, 0x2, 0xd};		//plaintexts
char cipher[] 	= {0xe, 0x9, 0x6, 0xa, 0x7, 0xb};		//ciphertexts

char S[] = {0x6, 0x4, 0xc, 0x5, 0x0, 0x7, 0x2, 0xe, 0x1, 0xf, 0x3, 0xd, 0x8, 0xa, 0x9, 0xb};	//S-box
char R[] = {0x4, 0x8, 0x6, 0xa, 0x1, 0x3, 0x0, 0x5, 0xc, 0xe, 0xd, 0xf, 0x2, 0xb, 0x7, 0x9};	//inverse permutaion of S

char k0,k1,k2;
char u[16],v[16],w[16],x[16],c[16];

char bitXor(char x, char y);

int main(){
	int i;
	
	k0 = 0xc; //0x3;
	k1 = 0xa; //0x7;
	k2 = 0x2;
	
	for(i=0; i<6; i++){
		u[i] = bitXor(k0, msg[i]);
		v[i] = S[u[i]];
		w[i] = bitXor(k1, v[i]);
		x[i] = S[w[i]];
		c[i] = bitXor(k2, x[i]);
		
		printf("c[%d]: 0x%x\n", i, c[i]);
	}
}

// Bitwise exclusive OR
char bitXor(char x, char y) {
    char a = x & y;
    char b = ~x & ~y;
    char z = ~a & ~b;
    return z;
} 