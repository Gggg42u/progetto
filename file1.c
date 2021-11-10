
#include <stdio.h>
#include <string.h>
#include <math.h>

// https://sieprog.ch/e9e14d66-meteoblue/
// donnees meteo


//Calcul des grammes par minute de TKN dans l'affluant

double TKN_affluant(double Q, double TKN_in){ 			//Q : débit [m^3/min], TKN [g/m^3], T [°C] 
												   
	double TKN_aff = Q * TKN_in;						//TKN_aff [g/min]		
	return TKN_aff;
}

//Calcul des grammes par minute de COD dans l'affluant

double COD_affluant(double Q, double COD_in){ 			//Q : débit [m^3/min], COD [g/m^3], T [°C] 
										   
	double COD_aff = Q * COD_in;						//COD_aff [g/min]		
	return COD_aff;
}

//Calcul du taux de croissance des bactéries héterotrophes 

double croissance_hetero(double t, double COD_aff){ 	// t [jours]

	double µmax_h = 6.0 * exp(0.0693*t-1.386); ; 		// µmax_h [1/jour]
	double ks_h = 20;
	double µ_h = µmax_h * (COD_aff/(ks_h + COD_aff)); ; // µ_h [1/jour]
	double µ_min_h = pow((µ_h + 1),1.0/(24*60))-1;
	return µ_min_h; 									// µ_min_h [1/min]
} 

//Calcul du taux de croissance des bactéries autotrophes 

double croissance_auto(double t, double TKN) { 			// t [jours]
	
	double µmax_a = 0.85*exp(0.106*(t-20));				// µmax_a [1/jour]
	double ks_a = pow(10, 0.051*t - 1.158);
	double µ_a = µmax_a * exp(0.098*(t-15)) * TKN/(ks_a + TKN);		// µ_a [1/jour]
	double µ_min_a = pow((µ_a + 1),1.0/(24*60))-1;
	return µ_min_a;										// µ_min_h [1/min]
}

double production(double bact, double t, double Q, double COD_in ){
	double COD = COD_affluant(Q,COD_in);
	double i = 0;
	while ( COD > 30){
		double bact_prod = croissance_hetero(t,COD) * bact;
		COD -= bact_prod * 0.67;
		bact += bact_prod;
		i += 1;
	}
	return i;
}
	
	
int main(int argc, char ** argv){
	
	double a = production(300,1,5,340);
	printf("%f\n",a);
	
	double TKN_aff = TKN_affluant(5, 30);
	printf("Quantité de TKN: %.2f [g/min]\n", TKN_aff);
	
	double COD_aff = COD_affluant(340, 30);
	printf("Quantité de COD: %.2f [g/min]\n", COD_aff);
	
	double µ_min_h = croissance_hetero(100, 340);
	printf("Taux de croissance par minute des bact. hétérotrophes: %.2f [1/min]\n", µ_min_h);
	
	double µ_min_a = croissance_auto(100, 30);
	printf("Taux de croissance par minute des bact. autotrophes: %.2f [1/min]\n", µ_min_a);
	
}
