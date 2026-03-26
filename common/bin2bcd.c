/*
 * bin2bcd.c
 *
 *  Created on: 2 mars 2026
 *      Author: thierry
 */
#include <stdio.h>
#include <stdint.h>

/**
 * Convertit un binaire en BCD avec une limite de digits.
 * @param bin      : Le nombre binaire à convertir.
 * @param bcd      : Pointeur vers le tableau de sortie (1 octet par digit).
 * @param nb_digit : Nombre de digits souhaités.
 * @return         : 0 si OK, 1 si le nombre binaire dépasse la capacité nb_digit.
 */
//__attribute__((optimize("no-tree-loop-distribute-patterns")))
uint8_t bin2bcd(uint32_t bin, uint8_t *bcd, uint8_t nb_digit) {
    uint8_t overflow = 0;

    // Initialisation du tableau BCD à zéro
    for (uint8_t i = 0; i < nb_digit; i++) {
        bcd[i] = 0;
    }

    // On traite les 32 bits du nombre d'origine
    for (int i = 0; i < 32; i++) {

        // 1. Règle du Add-3 pour chaque digit BCD
        for (uint8_t j = 0; j < nb_digit; j++) {
            if (bcd[j] >= 5) {
                bcd[j] += 3;
            }
        }

        // 2. Récupération du bit de poids fort de 'bin'
        uint8_t shift_in = (bin & 0x80000000) ? 1 : 0;
        bin <<= 1;

        // 3. Décalage des digits BCD avec propagation de la retenue
        for (int j = nb_digit - 1; j >= 0; j--) {
            uint8_t shift_out = (bcd[j] & 0x08) ? 1 : 0; // Le bit qui va sortir du digit
            bcd[j] = ((bcd[j] << 1) & 0x0F) | shift_in;
            shift_in = shift_out;

            // Si un bit sort du digit le plus à gauche, il y a overflow potentiel
            if (j == 0 && shift_out) {
                overflow = 1;
            }
        }
    }

    // Vérification finale : si bin n'est pas vide mais qu'on a fini les bits
    // ou si une retenue a été perdue lors du dernier décalage.
    return overflow;
}



//__attribute__((optimize("no-tree-loop-distribute-patterns")))
uint8_t bin2bcd_signed(int32_t bin, uint8_t *bcd, uint8_t nb_digit) {
    uint32_t val;
    if (nb_digit<1) {
        return 1;
    }

    if (bin==0) {
        for (uint8_t i=0;i<nb_digit;i++) {
            bcd[i] = 0;
        }
        return 0;
    } else if (bin<0) {
        val = (bin == -2147483648) ? 2147483648U : (uint32_t)(-bin);
    } else {
        val = bin;
    }

    return bin2bcd(val, bcd, nb_digit);
}


#include "unistd.h"
extern uint16_t _write(uint16_t fd, const char *buff, uint16_t len);



//__attribute__((optimize("no-tree-loop-distribute-patterns")))
void print_bcd(int32_t val) {
	const char d[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
	uint8_t nb_digit = 10;
	uint8_t bcd[nb_digit];

	if (bin2bcd_signed(val, bcd, nb_digit)) {
		for (int i=0;i<10;i++) {
			_write(STDOUT_FILENO, &d[10], 1);
		}
	} else {
	    if (val < 0) {
	    	_write(STDOUT_FILENO, &d[10], 1);
	    }

	    int started = 0; // Pour ignorer les zéros de tête
	    for (int i = 0; i < nb_digit; i++) {
	        if (bcd[i] != 0 || i == nb_digit - 1) { // On garde le dernier zéro si le nombre est 0
	            started = 1;
	        }
	        if (started) {
	        	_write(STDOUT_FILENO, &d[bcd[i]], 1);
	        }
	    }
	}
}



#ifdef _TEST
int main(void) {
    printf("bin2bcd\n");
    uint8_t nb_digit = 7;
    uint8_t mon_bcd[nb_digit];
    int32_t valeur = 8125000;

    uint8_t status = bin2bcd_signed(valeur, mon_bcd, nb_digit);

    if (status) {
        printf("Erreur : Dépassement de capacité !\n");
    }


    print_result(valeur, mon_bcd, 6);
}
#endif
