CipherTwo compilation:
 1) Compute k2: gcc -DK2 ciphertwo.c -o c2
 2) Compute k1 with found k2: gcc -D K1 ciphertwo.c -o c2
 3) Compute k0 with found k2,k1: gcc -D K0 ciphertwo.c -o c2

Verify keys:
 gcc encrypt_ciphertwo.c -o c2enc

** CipherThree usage:
From CipherThree we want to find 4 keys: k0,k1,k2,k3 - by starting from the end we guess k3, then k2 and so on. Use the makefile to compile computation for k3 first (make ciph3-k3), then for k2 (make ciph3-k2) and so forth.