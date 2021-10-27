#include <stdio.h>
#include <string.h>
#include <math.h>

// https://sieprog.ch/e9e14d66-meteoblue/
// donnees meteo


double affluantCOD_TKN(double eau, double COD_TKN) //eau (m^3/min), COD/TKN (g/m^3), T (°C) 
{																   
	double MO_N = eau * COD_TKN;		//MO/N (1/min)		
	return MO_N;
}

double croissance_hetero(double t, double COD)
{
	double µ_max = 6.0 * exp(0.0693*t-1.386);
	double k_s = 20;
	double µ = µ_max * (COD/(k_s + COD));
	double µ_min = pow((µ + 1),1/(24*60))-1;
	return µ_min;
} 

//Calcul du taux de croissance des bactéries autotrophes 

double croissance_auto(double t, double TKN) {
	double µmax_a = 0.85*exp(0.106*(t-20));
	double ks_a = pow(10, 0.051*t - 1.158);
	double µ_a = µmax_a * exp(0.098(t-15)) * TKN/(ks + TKN);
	double greco = 1;
	
int main(int argc, char ** argv)
{
    printf("%lf", croissance_hetero(5,10));
}
