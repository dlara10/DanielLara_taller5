#include "iostream"
#include "fstream"
#include "math.h"

using namespace std;

//Constantes


int N=101;
float T = 40.0, rho = 10.0, L = 100.0, t = 200.0;
float c = pow((T/rho), 0.5);
float dx = L/float(N-1);
float dt = sqrt(0.5)*dx/c;
float r = pow(c,2)*pow(dt,2)/(pow(dx,2));
float a[nt][N];
float x[N];

ofstream d("datos_cuerda.txt");

void inicializar();
void imprimir(int i);
void actualizar(int i);


int main()
{
	inicializar();
	for (int i = 1; i < t; ++i)
	{
		actualizar(i);
	}
	return 0;
}


void inicializar()
{
  //Se inicializa
	for (int i = 0; i < N; ++i)
	{
		x[i] = float(i*dx);
    if (x[i] <= 0.8*L)
    {
      a[0][i] = 1.25*x[i]/L;
    }
		else
		{
			a[0][i] = 5.0 - 5.0*x[i]/L;
		}
	}
	for (int i = 0; i < N; ++i)
	{
		a[1][i] = a[0][i]*0.99;
	}
}

void imprimir(int in)
{

	d << endl;
	for (int i = 0; i < N; ++i)
	{
		d << a[in][i] << " ";
	}	
}

void actualizar(int in)
{	
	for (int i = 0; i < N; ++i)
	{
	  if (i == 0 & i == N-1)
	  {
	    a[in+1][i] = 0.0;
	  }
		else
		{ 
			a[in+1][i] = 2.0*a[in][i]-a[in-1][i]+r*(a[in][i-1]+a[in][i+1]-2.0*a[in][i]);
		}
		a[in][i] = a[in][i];
	}

	imprimir(in);

}


