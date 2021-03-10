# Homework 1: Differential cryptanalysis

## Exercise 1.1: CipherTwo

#### CipherTwo compilation
 1) Compute k2: gcc -DK2 ciphertwo.c -o c2
 2) Compute k1 with found k2: gcc -D K1 ciphertwo.c -o c2
 3) Compute k0 with found k2,k1: gcc -D K0 ciphertwo.c -o c2

Verify keys:
 gcc encrypt_ciphertwo.c -o c2enc

## Exercise 1.2: CipherThree

#### Find k0,k1,k2,k3 using cipherthree.c

From CipherThree we want to find 1 key divided into 4 keyparts each of 4 bits: K={k0,k1,k2,k3} thus keyspace=2^4=16 - by starting from the end we guess k3, then k2 etc. Use the makefile to compile computation for k3 first (make ciph3-k3), then for k2 (make ciph3-k2) and so forth. Output is a table mapping all key values in the keyspace and their respective count - choose the key with highest count to find the next keypart.
