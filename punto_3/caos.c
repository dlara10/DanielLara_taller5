#include "iostream"
#include "fstream"
#include "math.h"


using namespace std;

float a = 1/(2*pow(2,0.5));
float dt = 0.006;
float t = 3000.0;
int n = 10000;
float q1[n], q2[n], p1[n], p2[n];
float q1rk[4], q2rk[4], p1rk[4], p2rk[4];
float q1[0] = a, q2[0] = -a, p1[0] = 0.0, p2[0] = 0.0;
float e = 1.0/1000;

float sol(float a1, float a2, float b1, float b2, int i);
void rungekutta();
void actualizar();


int main()
{
  //Se leen los datos
	ofstream d("datos_caos.txt");

  rungekutta();
	actualizar();
		
	for (int i = 0; i < n-1; ++ i)
	{
		d << q1[i] << " " << q2[i] << " " << p1[i] << " " << p2[i];
		d << endl;
	}
	return 0;
}

//Soluciones a las ecuaciones
float sol(float a1, float a2, float b1, float b2, int i)
{
  //Soluciones
  float s1;
  float s2;
  float s3;
  float s4;
  //Dependiendo del int se devuelve la solucion correspondiente
	if (i==0)
	{
		return s1 = b1;
	}
	else if (i==1)
	{
		return s2 = b2;	
	}
	else if (i==2)
	{
		return s3 = -(2*a1)/(pow(4.0*pow(a1,2)+ pow(e,2),1.5));
	}
	else 
	{
		return s4 = (a1-a2)/(pow( pow((a1-a2),2)+pow(e,2)/4.0 ,1.5) - (a1+a2)/(pow( pow((a1+a2),2)+pow(e,2)/4.0 ,1.5);	
	}
}

//Metodo de Runge Kutta de cuarto orden
void rungekutta()
{
  //Paso 1
	for (int i = 0; i < n; i++)
	{
	  q1rk[0] = sol(0, q1[i], q2[i], p1[i], p2[i]);
	  q2rk[0] = sol(1, q1[i], q2[i], p1[i], p2[i]);
	  p1rk[0] = sol(2, q1[i], q2[i], p1[i], p2[i]);
	  p2rk[0] = sol(3, q1[i], q2[i], p1[i], p2[i]);
	}
	//Paso 2
  for (int i = 0; i < n; i++)
  {
    float a = q1[i]+0.5*dt*q1rk[0];
    float b = q2[i]+0.5*dt*q2rk[0];
    float c = p1[i]+0.5*dt*p1rk[0];
    float d = p2[i]+0.5*dt*p2rk[0];
    q1rk[1] = sol(0, a, b, c, d);
  	q2rk[1] = sol(1, a, b, c, d);
	  p1rk[1] = sol(2, a, b, c, d);
	  p2rk[1] = sol(3, a, b, c, d);
  }
	//Paso 3
	for (int i = 0; i < n; i++)
	{
	  float a = q1[i]+0.5*dt*q1rk[1];
	  float b = q2[i]+0.5*dt*q2rk[1];
	  float c = p1[i]+0.5*dt*p1rk[1];
	  float d = p2[i]+0.5*dt*p2rk[1];
	  q1rk[2] = sol(0, a, b, c, d);
	  q2rk[2] = sol(1, a, b, c, d);
	  p1rk[2] = sol(2, a, b, c, d);
	  p2rk[2] = sol(3, a, b, c, d);
	}
	//Paso 4
	for (int i = 0; i < n; i++)
	{
	  float a = q1[i]+1.0*dt*q1rk[2];
	  float b = q2[i]+1.0*dt*q2rk[2];
	  float c = p1[i]+1.0*dt*p1rk[2];
	  float d = p2[i]+1.0*dt*p2rk[2];
	  q1rk[3] = sol(0, a, b, c, d);
	  q2rk[3] = sol(1, a, b, c, d);
	  p1rk[3] = sol(2, a, b, c, d);
	  p2rk[3] = sol(3, a, b, c, d);
	}
}
//Actualizar
void actualizar()
{
  for (int i = 0; i < n; i++)
  {
    q1[i+1] = q1[i] + dt/6.0*( q1rk[0] + 2*q1rk[1] + 2*q1rk[2] +q1rk[3] );
	  q2[i+1] = q2[i] + dt/6.0*( q2rk[0] + 2*q2rk[1] + 2*q2rk[2] +q2rk[3] );
	  p1[i+1] = p1[i] + dt/6.0*( p1rk[0] + 2*p1rk[1] + 2*p1rk[2] +p1rk[3] );
	  p2[i+1] = p2[i] + dt/6.0*( p2rk[0] + 2*p2rk[1] + 2*p2rk[2] +p2rk[3] );
  }
}