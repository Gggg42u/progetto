#include <stdio.h>
#include <string.h>
#include <math.h>

// V [m3]: 			volume du bacin
// Qa [m3/min]: 	débit affluant 
// Qe [m3/min]: 	débit effluant
// Qp [m3/min]: 	débit boues enlevées (purge)
// Qi [m3/min]: 	débit entre aération et décantation
// ratio = Qr/Qp
// S_aff [g/m3]: 	conc. substrat dans l'affluant
// X [g]: 			grammes bactères dans le bacin d'aération
// Xp [g]: 			grammes bactères dans les bouées enlevées
// Xe [g]: 			grammes bactères dans l'effluent
	// Nous supposons que le bassin de décantation est très efficace dans la 
	// sédimentation e donc Xe ≈ 0
// densite [g/m3]:	densité biomasse dans les boues 
// T [°C] 

void totale(double V, double Qa, double COD_aff, double TKN_aff, double densite, double T){ 
	
	// On considère un sytème à l'equilibre où les grammes de bactères
	// enlevées par Qp sont égales aux grammes produits par reproduction 
	// des bactères. Comme ça on a un système dans lequel la biomasse
	// est constante et les bactères sont toujours en phase exponentielle.
	// Il en découle que les concentrations de COD et TKN dans le bacin
	// d'aération devraient rester constantes.
	
	// Chaque minute on a [S]aff qui rentre par l'affluent et [S]bact qui vient consommé par le bactères
	// Donc [S] = [S] + [S]aff - [S]bact
	// Le nouveau [S] de l'affluent dans le volume est: [S]aff * Vaff / V avec Vaff = Q * 1min et V le volume du bacin
	// [S]bact est: g_S / V avec g_S = g_bacteres * qte_consommé_par_g_bactere
	// Donc [S] = [S] + ([S]aff * Vaff / V) - S/V
	// Les nouvelles conc de COD et TKN sont donc données par:
	// COD += (COD_aff * Qa / V) - (X_he * 0.67 / V);							// [g/m3]
	// TKN += (TKN_aff * Qa / V) - (X_he * 0.01675 / V) - (X_au * 6.19 / V) ;	// [g/m3]
	
	// On impose maintenant que COD = 30 [g/m3] et TKN = 2 [g/m3] (limites tolérées par la loi)
	double COD = 30; 												// [g/m3]
	double TKN = 2; 												// [g/m3]

	// On obtient: 
	// 0 = (COD_aff * Qa / V) - (X_he * 0.67 / V);	
	// 0 = (TKN_aff * Qa / V) - (X_he * 0.01675 / V) - (X_au * 6.19 / V) 
	// et avec un peu de manipulations on trouve:
	double X_he = COD_aff * Qa/0.67 ; 
	double X_au = Qa*(TKN_aff - COD_aff*0.01675/0.67)/6.19 ;
			
	//Calcul du taux de croissance des bactéries héterotrophes 
	double µmax_he = 6.0 * exp(0.0693*T-1.386); ; 						// µmax_he [1/jour]
	double ks_he = 20;
	double µ_he = µmax_he * (COD/(ks_he + COD)); ; 						// µ_he [1/jour]
	double µ_min_he = pow((µ_he + 1),1.0/(24*60))-1;
	
	//Calcul du taux de croissance des bactéries autotrophes 	
	double µmax_au = 0.85*exp(0.106*(T-20.0));							// µmax_au [1/jour]
	double ks_au = pow(10, 0.051*T - 1.158);
	double µ_au = µmax_au * (TKN/(ks_au + TKN))* exp(0.098*(T-15.0));	// µ_au [1/jour]
	double µ_min_au = pow((µ_au + 1),1.0/(24*60))-1; 
		
	// On considère un sytème à l'equilibre où les grammes de bactères
	// enlevées par Qp est égal aux grammes produits par reproduction 
	// des bactères. Comme ça on a un système dans lequel la biomasse
	// est constante et les bactères sont toujours en phase exponentielle 
	// On a donc X*µ = Xp 
	double Xp_he = X_he * µ_min_he ; 									// [g/min] qui sortent
	double Xp_au = X_au * µ_min_au ;									// [g/min] qui sortent
		
	// Calcul de Qp en utilisant Xp = Qp * densite <=> Qp = Xp/densite avec Xp = Xp_he + Xp_au
	double Qp = (Xp_he + Xp_au)/densite ;
		
	// Maintenant on peut calculer Qe en utilisant Qa = Qe + Qp <=> Qe = Qa - Qp
	double Qe = Qa - Qp;
		
	// Le "cell retention time" est cell_time = V * X/(Qp * Xp) avec X = X_he + X_au
	double cell_time = V * (X_he + X_au)/(Qp * (Xp_he + Xp_au)) /(60*24);
	double hydraulic_time = V/(Qa*60*24);
	

	printf("µ_min_he: %f\n", µ_min_he);
	printf("µ_min_au: %f\n", µ_min_au);
	printf("X_he: %f\n", X_he);
	printf("X_au: %f\n", X_au);
	printf("Xp_he: %f\n", Xp_he);
	printf("Xp_au: %f\n", Xp_au);
	printf("Cell retention time: %0.2f\n", cell_time);
	printf("hydraulic retention time d: %f\n", hydraulic_time);
	printf("Qp: %f\n", Qp);
	printf("Qe: %f\n", Qe);
}

int main(int argc, char * argv[]){
	
	totale(10000, 5, 340, 30, 60000, 15);
	
}

