ciph3-k3: 
	cc -DK3 cipherthree.c -o c3

ciph3-k2:
	cc -DK2 cipherthree.c -o c3

ciph3-k1:
	cc -DK2 -DK1 cipherthree.c -o c3

ciph3-k0:
	cc -DK2 -DK1 -DK0 cipherthree.c -o c3

clean:
	rm -rf c3