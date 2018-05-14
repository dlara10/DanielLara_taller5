#include "iostream"
#include "fstream"
#include "math.h"


using namespace std;



float L = 5.0;
float l = 2.0;
float d = 1.0;
float h = 5.0/512.0;
float Vo = 100;
int n=2*pow((L/h),2);
int e[n-1][n-1];
float va[n-1][n-1];
float vn[n-1][n-1];
float campo[n-1][n-1][2];

void inicializar();
void relajacion();
void imprimir();


int main()
{

	inicializar();

	for (int k = 0; k < int(0.01*2*pow(n,2)); ++k)
	{
		relajacion();
	}

	imprimir();
	return 0;
}


//Metodo para crear e inicializar las matrices de voltajes anterior y nueva
void inicializar()
{
	// Inicializar el espacio en cero
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			e[i][j] = 0; 
		}
	}
	 //Inicializar los bordes
	for (int i = 0; i < n; ++i)
	{
	  e[0][i] = 2; // borde sup
	  e[n-1][0] = 2; // borde inf
		e[i][0] = 2; // borde izq
		e[i][n-1] = 2; // borde derecho
	}
  
  for (int i = 0; i < L; i++)
  {
    if (i == rint((L-l)/2))
    {
      for (int j = 0; j < L; j++)
      {
        while(j>=rint((L-d)/2) && j<=rint((L+d)/2))
        {
          e[i][j]=-1
        }
      }
    }
    else if (i == rint((L+l)/2))
    {
      for (int j = 0; j < L; j++)
      {
        while(j>=rint((L-d)/2) && j<=rint((L+d)/2))
        {
          e[i][j]=1
        }
      }
    }
  }
	// Se llenan las matrices de voltaje
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
		  if (e[i][j]==1)
		  {
		    va[i][j] = Vo;
		  }
		  else if (e[i][j]==-1)
		  {
		    va[i][j] = -Vo;
		  }
			else 
			{ // los nodos centrales y los bordes tienen voltaje inicial 0
				va[i][j] = 0.0;
			}
			vn[i][j] = va[i][j];
		}
	}
}

// Metodo de relajacion para los nodos interiores 
void relajacion()
{	
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if(d[i][j]==0)
			//Se determinan los nodos interiores como la sumatoria de los nodos adyacentes
			{ 
				vn[i][j] = va[i][j-1] + va[i-1][j] + va[i+1][j] + va[i][j+1]  ;
				vn[i][j] = vn[i][j]/4.0;
			}
		}

	}
	//Actualizar matriz de voltajes
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			va[i][j] = vn[i][j];
		}
	}
}

//Impresion
void imprimir()
{
	//Se leen los datos
	ofstream d("datos_placas.txt");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			d << va[i][j] << ",";
			//Campo electrico en los bordes para X y Y.
			if(e[i][j] == 2)
			{
			  E[i][j][0] = 0.0;
				E[i][j][1] = 0.0;
			}
			//Campo electrico en X y Y para los nodos interiores siguiendo la definicion del campo electrico
			else 
			{ 
				campo[i][j][0] = -(vn[i][j]-vn[i][j-1])/h;
				campo[i][j][1] = -(vn[i][j]-vn[i-1][j])/h;
			}
		}
		d << endl;
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			d << E[i][j][0] << "," << E[i][j][1] << endl;
		}
	}
}