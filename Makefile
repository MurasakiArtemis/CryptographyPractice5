all: ModifiedAES.out

ModifiedAES.out: ModifiedAES.cpp modified-aes.o
	g++ modified-aes.o ModifiedAES.cpp -o ModifiedAES.out
modified-aes.o: modified-aes.c modified-aes.h
	g++ modified-aes.c -c
