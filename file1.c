
#include <stdio.h>
#include <string.h>

void afficherMatrice33(double matrice[][4]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("%10.0f", matrice[x][y]);
        }
        printf("\n");
    }
}

void afficherMatrice33T(double matrice[][4]) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            printf("%10.0f", matrice[y][x]);
        }
        printf("\n");
    }
}


int main(int argc, char ** argv) {
    double matrice[4][4] = {
		{1, 2, 3, 4}, 
		{5, 6, 7, 8}, 
		{9, 10, 11, 12}, 
		{13, 14, 15, 16}
		};
	printf("%s","The Matrix is:\n");
    afficherMatrice33(matrice);
    printf("%s","And its tranpose reppresentation is:\n");
    afficherMatrice33T(matrice);
    return 0;
}
