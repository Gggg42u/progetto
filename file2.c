#include <stdio.h>
#include <string.h>
#include <math.h>

// V [m3]: volume du bacin
// Qa [m^3/min]: débit affluant [m^3/min]
// S_aff [g/m3]
// g_bacteres [g]
// T [°C] 
// t [min]

void COD_TKN_actualise(double V, double Qa, double COD_aff, double TKN_aff, double g_bacteres_he_i, double g_bacteres_au_i, double T, double t){ 
	
	double g_bacteres_he = g_bacteres_he_i;
	double g_bacteres_au = g_bacteres_au_i;
	double COD = COD_aff;
	double TKN = TKN_aff;
	
	for (int i=0; i<t; i++) {
		
		//Calcul du taux de croissance des bactéries héterotrophes 
		double µmax_he = 6.0 * exp(0.0693*T-1.386); ; 					// µmax_he [1/jour]
		double ks_he = 20;
		double µ_he = µmax_he * (COD/(ks_he + COD)); ; 			// µ_he [1/jour]
		double µ_min_he = pow((µ_he + 1),1.0/(24*60))-1;
		
		//Calcul du taux de croissance des bactéries autotrophes 	
		double µmax_au = 0.85*exp(0.106*(T-20));						// µmax_au [1/jour]
		double ks_au = pow(10, 0.051*T - 1.158);
		double µ_au = µmax_au * exp(0.098*(T-15)) * TKN/(ks_au + TKN);	// µ_au [1/jour]
		double µ_min_au = pow((µ_au + 1),1.0/(24*60))-1;
	
		// Calcul grammes de bactéres actuels dans le bacin
		g_bacteres_he += µ_min_he * g_bacteres_he;						// [g]
		g_bacteres_au += µ_min_au * g_bacteres_au; // QUI BISOGNA ANCORA TOGLIERE I G DI BATTERI CHE SONO IN GIRO E NON NEL BACINO
	
		// Chaque minute on a [S]aff qui rentre par l'affluent et [S]bact qui vient consommé par le bactères
		// Donc [S] = [S] + [S]aff - [S]bact
		// [S] de l'affluent dans le nouveau volume est: [S]aff * Vaff / V avec Vaff = Q * 1min et V le volume du bacin
		// [S]bact est: g_S / V avec g_S = g_bacteres * qte_consommé_par_g_bactere
		// Donc [S] = [S] + ([S]aff * Vaff / V) - S/V
		
		COD += (COD_aff * Qa / V) - (g_bacteres_he * 0.67 / V) ;									// [g/m3]
		TKN += (TKN_aff * Qa / V) - (g_bacteres_he * 0.01675 / V) - (g_bacteres_au * 6.19 / V) ;	// [g/m3]
		printf("Les g de bact he: %f\n", g_bacteres_he);

	}
	printf("Le niveau de COD est: %f\n", COD);
	printf("Le niveau de TKN est: %f\n", TKN);
	printf("Les g de bact he: %f\n", g_bacteres_he);
	printf("Les g de bact au: %f\n", g_bacteres_au);
}


int main(int argc, char * argv[]){
	
	COD_TKN_actualise(10000, 5, 340, 30, 1, 1, 15, 28800);
	
}

// Ad un certo punto stampa "NAN" = Not A Number e deve probabilmente esserci un operazione 
// che fa flascare ad un certo punto (come radice di un numero negativo)

// Manca il fatto che vi sia un flusso esterno che rientra; implica una perdita di g di batteri nel
// volume del bacino, il che diminuisce la loro conc e quindi va preso in considerazione
