/*
 * timer.c
 *
 *  Created on: 18 mars 2026
 *      Author: thierry
 */
#include "timer.h"
#include "debug.h"




void timer_init_countdown(uint32_t start_val, uint32_t reload_val) {
    // 1. Arrêter le timer avant configuration
    *TIMER_CTRL = 0;

    // 2. Charger les valeurs
    *TIMER_COUNT  = start_val;
    *TIMER_RELOAD = reload_val;

    // 3. Acquitter une éventuelle interruption résiduelle (W1C)
    *TIMER_STAT = TIMER_IRQ_FLAG;
}

void timer_start(int enable_irq) {
    uint32_t config = TIMER_EN | TIMER_DOWN; // Mode décompteur
    if (enable_irq) {
        config |= TIMER_IRQ_EN;
    }
    *TIMER_CTRL = config;
}

void timer_stop() {
    *TIMER_CTRL &= ~TIMER_EN;
}

void timer_init() {

    // 1. Arrêter le timer et désactiver les interruptions pour ce délai
    *TIMER_CTRL = 0;
    *TIMER_COUNT  = 0x55AA55AA;
    *TIMER_RELOAD = 0xAA55AA55;
    *TIMER_STAT = TIMER_IRQ_FLAG;


}

void delay_ticks(uint32_t ticks) {
    if (ticks == 0) return;

    // 1. Arrêter le timer et désactiver les interruptions pour ce délai
    *TIMER_CTRL = 0;

    // 2. Effacer le flag d'interruption précédent (W1C)
    *TIMER_STAT = TIMER_IRQ_FLAG;

    // 3. Initialiser le compteur avec le nombre de ticks souhaités
    // On met RELOAD à 0 pour qu'il ne redémarre pas tout seul
    *TIMER_COUNT  = ticks;
    *TIMER_RELOAD = 0;

    // 4. Lancer le timer en mode décompteur (sans IE)
    *TIMER_CTRL = TIMER_EN | TIMER_DOWN;

    //view_timer_regs();

    // 5. Attendre (Polling) que le flag "event_trigger" passe à 1
    while (!(*TIMER_CTRL & 0x8)) {
        // On attend...
    }
    //view_reg((uint32_t)TIMER_BASE + 0x08);


    // 6. Arrêter le timer après le délai
    *TIMER_CTRL = 0;
    *TIMER_COUNT  = 0;
    *TIMER_RELOAD = 0;
    *TIMER_STAT = TIMER_IRQ_FLAG; // Nettoyage final

    //view_reg((uint32_t)TIMER_BASE + 0x00);
}


