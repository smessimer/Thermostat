/*
 * Thermostat Control Application
 * ------------------------------
 *  Inputs
 *  - Set temp up:      stup    bool
 *  - Set temp down:    stdown  bool
 *  - Set temp:         stemp   uint8
 *  - Current temp:     ctemp   uint8
 *  - Fan mode:         fmode   enum{ AUTO, ON }
 *  - HVAC mode:        hmode   enum{ COOL, HEAT, OFF }
 *
 *  Outputs
 *  - Cool on:          y_coolon    bool
 *  - Heat on:          w_heaton    bool
 *  - Fan on:           g_fanon     bool
 */

#include <stdbool.h>
#include <stdio.h>

#include "thermostat.h"
/*
 * Debug - print debug info to console
 */
#define DEBUG

/*
 * Hysteresis
 * ----------
 *  Current temp must be above/below set temp by this
 *  much for thermostat to take action (turn cooler
 *  or heater on)
 */
#define HYSTERESIS 1

/*
 * Current target temp setting
 */
static char stemp = 0;

/*
 * Current fan relay setting
 */
static bool frelay_on = false;

/*
 * Current cooler relay setting
 */
static bool crelay_on = false;

/*
 * Current heater relay setting
 */
static bool hrelay_on = false;

/*
 * Main thermostat control loop.
 * Take hvi as input, populate hvo as output.
 * Return hvac_error, which can be HVE_NOERR.
 */
hvac_error control_loop( hvac_input* hvi, hvac_output* hvo) {
#ifdef DEBUG
    printf("hvac_input:\n");
    printf("hvi->stup = %s\n", hvi->stup ? "true" : "false");
    printf("hvi->stdown = %s\n", hvi->stdown ? "true" : "false");
    printf("hvi->stemp = %d\n", hvi->stemp);
    printf("hvi->ctemp = %d\n", hvi->ctemp);
    printf("hvi->fmode = %s\n", hvi->fmode == FAN_MODE_AUTO ? "AUTO" : "ON");
    printf("hvi->hmode = %s\n", hvi->hmode == HVAC_MODE_OFF ? "OFF" : hvi->hmode == HVAC_MODE_HEAT ? "HEAT" : "COOL");
#endif

    // Test for undefined conditions
    if( hvi->stup && hvi->stdown )
        return (HVE_UPANDDOWN);

    // Handle temperature up and down inputs
    if( hvi->stup )
        stemp++;
    if( hvi->stdown )
        stemp--;

    // Handle fan input
    if( hvi->fmode == FAN_MODE_ON )
        frelay_on = true;

    // If hvi->stemp is provided, set stemp no matter stup or stdown inputs
    if( hvi->stemp != 0 )
        stemp = hvi->stemp;

    /*
     * Handle hvac off
     * C and H relays turn off
     * F relay only on if set to ON
     *  - Covered above if ON
     */
    if( hvi->hmode == HVAC_MODE_OFF ) {
        if( hvi->fmode == FAN_MODE_AUTO )
            frelay_on = false;
        crelay_on = false;
        hrelay_on = false;
    }

    /*
     * Handle hvac COOL and HEAT
     */
    if( hvi->hmode == HVAC_MODE_COOL ) {
        hrelay_on = false;

        // If current temp is greater than HYSTERESIS above set temp, turn on
        if( (hvi->ctemp - stemp) >= HYSTERESIS ) {
            crelay_on = true;
            frelay_on = true;
        }
        // Else if current temp is HYSTERESIS below set temp, turn off
        else if( hvi->ctemp <= (stemp - HYSTERESIS) ) {
            crelay_on = false;
            if( hvi->fmode == FAN_MODE_AUTO )
                frelay_on = false;
        }
    }
    else if( hvi->hmode == HVAC_MODE_HEAT ) {
        crelay_on = false;

        // If current temp is less than HYSTERESIS below set temp, turn on
        if( hvi->ctemp <= (stemp - HYSTERESIS) ) {
            hrelay_on = true;
            frelay_on = true;
        }
        // Else if current temp is HYSTERESIS above set temp, turn off
        else if( hvi->ctemp >= (stemp + HYSTERESIS) ) {
            hrelay_on = false;
            if( hvi->fmode == FAN_MODE_AUTO )
                frelay_on = false;
        }
    }
    //return handle_relay_output(frelay_on, crelay_on, hrelay_on);
    hvo->hon = hrelay_on;
    hvo->con = crelay_on;
    hvo->fon = frelay_on;
}

hvac_error handle_relay_output(bool fr_on, bool cr_on, bool hr_on) {
    hvac_error ret;

    if( !set_frelay(fr_on) )
        return -HVE_FRELAYERR;
    if( !set_crelay(cr_on) )
        return -HVE_CRELAYERR;
    if( !set_hrelay(hr_on) )
        return -HVE_HRELAYERR;
    return HVE_NOERR;
}

char set_frelay(bool fr_on) {
    // TODO - implement
#ifdef DEBUG
    printf("Setting FAN relay to %s\n", fr_on ? "on" : "off");
#endif
}

char set_crelay(bool cr_on) {
    // TODO - implement
#ifdef DEBUG
    printf("Setting COOL relay to %s\n", cr_on ? "on" : "off");
#endif
}

char set_hrelay(bool hr_on) {
    // TODO - implement
#ifdef DEBUG
    printf("Setting HEAT relay to %s\n", hr_on ? "on" : "off");
#endif
}
