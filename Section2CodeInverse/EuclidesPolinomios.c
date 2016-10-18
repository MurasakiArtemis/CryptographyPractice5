#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int polynomialEuclides(unsigned int a, unsigned int m);
int deg(unsigned int n);
unsigned int mul(int j, unsigned int p, unsigned int m);
unsigned int fMask(unsigned int m);
unsigned int xorMask(unsigned int m);
unsigned char transform(char input);

int main(int argc, char** argv)
{
	if ( argc!=3 ) 
	{
	printf("El modo de uso es: %s a(x) m(x)\n", argv[0] );
	exit(0);
	}

int i;
unsigned int a=0, m=0, auxMask=0;

	for (i=0; i<strlen(argv[1]); i++)
	{
	auxMask=transform( argv[1][ strlen(argv[1]) - 1 - i ] );
	a = a | (auxMask << 4*i);
	}

	for (i=0; i<strlen(argv[2]); i++)
	{
	auxMask=transform( argv[2][ strlen(argv[2]) - 1 - i ] );
	m = m | (auxMask << 4*i);
	}

printf("a(x) = 0x%x\n", a);
printf("m(x) = 0x%x\n", m);
printf("El inverso de a(x) en m(x) es: 0x%x\n\n", polynomialEuclides(a, m) );
return 0;
}



//Funcion Extendido de Euclides Polinomios
unsigned int polynomialEuclides(unsigned int a, unsigned int m)
{
unsigned int u, v, g1=0x01, g2=0x00, aux, mask, maskXOR;
u=a;
v=m;
int j, i=1;
mask=fMask(m);
maskXOR=xorMask(m);

	while ( u != 0x00000001 )
	{
	j=deg(u)-deg(v);

		if ( j<0 )
		{
		aux = u;
		u = v;
		v = aux;
		aux = g1;
		g1 = g2;
		g2 = aux;
		j=-j;
		}

	aux=u ^ mul(j, v, m);
	u=aux;

		if ( deg(u)==deg(m) )
		{
		u=u&mask;
		u=u^maskXOR;
		}

	i++;
	aux=g1 ^ mul (j, g2, m);
	g1=aux;
	}


return g1;
}

int deg(unsigned int n)
{
int degree=0, i;
unsigned int mask=0X01;

	for ( i=0; i<32; i++ )
	{
		if ( (mask & n) == mask ) degree=i;

	mask=mask<<1;
	}

return degree;
}


unsigned int mul(int j, unsigned int p, unsigned int m)
{
int i;
unsigned int mask=0X01, auxMask, auxMask2, auxMask3, mul=p;


	for ( i=0; i<8*sizeof(unsigned int); i++ )
	{
		if ( (mask & m) == mask ) 
		{
		auxMask=mask^m;
		auxMask2=mask;
		}

	mask=mask<<1;
	}

auxMask3=auxMask2>>1;
i=0;

	while ( (auxMask2 >> i) != 0 ) 
	{
	auxMask3 = auxMask3 | ( auxMask3 >> i );
	i++;
	}

	for ( i=0; i<j; i++ )
	{
	
		if ( (auxMask2 & (mul<<1) ) == auxMask2 )
		{
		mul=mul<<1;
		mul=mul^auxMask;
		}
		else
		{
		mul=mul<<1;
		}

	mul=mul&auxMask3;	//Limpiar parte izquierda		
	}

return mul;
}

unsigned int fMask(unsigned int m)
{
int i;
unsigned int mask=0X01, auxMask2, auxMask3;


	for ( i=0; i<32; i++ )
	{
		if ( (mask & m) == mask ) 
		{
		auxMask2=mask;
		}

	mask=mask<<1;
	}

auxMask3=auxMask2>>1;
i=0;

	while ( (auxMask2 >> i) != 0 ) 
	{
	auxMask3 = auxMask3 | ( auxMask3 >> i );
	i++;
	}

return auxMask3;
}

unsigned int xorMask(unsigned int m)
{
int i;
unsigned int mask=0X01, auxMask;


	for ( i=0; i<32; i++ )
	{
		if ( (mask & m) == mask ) 
		{
		auxMask=mask^m;
		}

	mask=mask<<1;
	}

return auxMask;
}

unsigned char transform(char input)
{
unsigned char res=0;
input = tolower(input);

	if ( input=='0' ) res=0x00;
	if ( input=='1' ) res=0x01;
	if ( input=='2' ) res=0x02;
	if ( input=='3' ) res=0x03;
	if ( input=='4' ) res=0x04;
	if ( input=='5' ) res=0x05;
	if ( input=='6' ) res=0x06;
	if ( input=='7' ) res=0x07;
	if ( input=='8' ) res=0x08;
	if ( input=='9' ) res=0x09;
	if ( input=='a' ) res=0x0a;
	if ( input=='b' ) res=0x0b;
	if ( input=='c' ) res=0x0c;
	if ( input=='d' ) res=0x0d;
	if ( input=='e' ) res=0x0e;
	if ( input=='f' ) res=0x0f;

return res;
}

