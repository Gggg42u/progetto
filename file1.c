#include <stdio.h>
#include <string.h>
#include <math.h>

// https://sieprog.ch/e9e14d66-meteoblue/
// donnees meteo


//Calcul des grammes par minute de TKN dans l'affluant

double TKN_affluant(double Qa, double TKN_in){ //Qa : débit affluant [m^3/min], TKN [g/m^3]
							
	double TKN_aff = Qa * TKN_in;						//TKN_aff [g/min]		
	return TKN_aff;
}

//Calcul des grammes par minute de COD dans l'affluant

double COD_affluant(double Qa, double COD_in){ 			//Qa : débit affluant [m^3/min], COD [g/m^3]
										   
	double COD_aff = Qa * COD_in;						//COD_aff [g/min]		
	return COD_aff;
}

//Calcul du taux de croissance des bactéries héterotrophes 

double croissance_hetero(double T, double COD_aff){ 	// T [°C]

	double µmax_h = 6.0 * exp(0.0693*T-1.386); ; 		// µmax_h [1/jour]
	double ks_h = 20;
	double µ_h = µmax_h * (COD_aff/(ks_h + COD_aff)); ; // µ_h [1/jour]
	double µ_min_h = pow((µ_h + 1),1.0/(24*60))-1;
	return µ_min_h; 									// µ_min_h [1/min]
} 

//Calcul du taux de croissance des bactéries autotrophes 

double croissance_auto(double T, double TKN) { 			// T [°C]
	
	double µmax_a = 0.85*exp(0.106*(t-20));				// µmax_a [1/jour]
	double ks_a = pow(10, 0.051*t - 1.158);
	double µ_a = µmax_a * exp(0.098*(t-15)) * TKN/(ks_a + TKN);		// µ_a [1/jour]
	double µ_min_a = pow((µ_a + 1),1.0/(24*60))-1;
	return µ_min_a;										// µ_min_h [1/min]
}

// Explication des fluxes
// Q affluent = Qa
// ( Q entre aération et décantation = Qi = Qa + Qr )
// Q boues recyclées = Qr 
// Q boues enlevées (purge) = Qp = Qa - Qe
// Q effluent = Qe

// V = Volume bacin aération [m3]

double total(double Qa, double Qe, double Qr, double V, double TKNa, double CDOa) {
	}

int main(int argc, char ** argv){
	
	double TKNa = TKN_affluant(5, 30);					// TKN_affluant(Qa [m^3/min], TKN_in [g/m^3]) 
	printf("Quantité de TKN: %.2f [g/min]\n", TKN_aff);
	
	double CODa = COD_affluant(5, 340);					// TKN_affluant(Qa [m^3/min], COD_in [g/m^3]) 
	printf("Quantité de COD: %.2f [g/min]\n", COD_aff);
	
	double µ_min_h = croissance_hetero(25, 340);
	printf("Taux de croissance par minute des bact. hétérotrophes: %.2f [1/min]\n", µ_min_h);
	
	double µ_min_a = croissance_auto(25, 30);
	printf("Taux de croissance par minute des bact. autotrophes: %.2f [1/min]\n", µ_min_a);
	
	
	
}
