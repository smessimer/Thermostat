#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "thermostat.h"

/*
 * Thoughts on how to test.
 * -Make make simulator that takes relay states and simulates temp changes.
 *      -Need to make separate thread
 * -Change inputs for control structure and observe outputs/control signals.
 */

void testStandardCool() {
    hvac_input hi = {   .stup = false,
                        .stdown = false,
                        .stemp = 70,
                        .ctemp = 72,
                        .fmode = FAN_MODE_AUTO,
                        .hmode = HVAC_MODE_COOL
    };

    hvac_output ho;

    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == true ); assert( ho.fon == true );
    printf("\n\n");
    hi.ctemp = 71;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == true ); assert( ho.fon == true );
    printf("\n\n");
    hi.ctemp = 70;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == true ); assert( ho.fon == true );
    printf("\n\n");
    hi.ctemp = 69;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == false ); assert( ho.fon == false );
    printf("\n\n");
    hi.ctemp = 68;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == false ); assert( ho.fon == false );
    printf("\n\n");
    hi.ctemp = 69;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == false ); assert( ho.fon == false );
    printf("\n\n");
    hi.ctemp = 70;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == false ); assert( ho.fon == false );
    printf("\n\n");
    hi.ctemp = 71;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == true ); assert( ho.fon == true );
}

void testStandardHeat() {
    hvac_input hi = {   .stup = false,
                        .stdown = false,
                        .stemp = 70,
                        .ctemp = 68,
                        .fmode = FAN_MODE_AUTO,
                        .hmode = HVAC_MODE_HEAT
    };

    hvac_output ho;

    control_loop( &hi, &ho );
    assert( ho.hon == true ); assert( ho.con == false ); assert( ho.fon == true );
    printf("\n\n");
    hi.ctemp = 69;
    control_loop( &hi, &ho );
    assert( ho.hon == true ); assert( ho.con == false ); assert( ho.fon == true );
    printf("\n\n");
    hi.ctemp = 70;
    control_loop( &hi, &ho );
    assert( ho.hon == true ); assert( ho.con == false ); assert( ho.fon == true );
    printf("\n\n");
    hi.ctemp = 71;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == false ); assert( ho.fon == false );
    printf("\n\n");
    hi.ctemp = 72;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == false ); assert( ho.fon == false );
    printf("\n\n");
    hi.ctemp = 71;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == false ); assert( ho.fon == false );
    printf("\n\n");
    hi.ctemp = 70;
    control_loop( &hi, &ho );
    assert( ho.hon == false ); assert( ho.con == false ); assert( ho.fon == false );
    printf("\n\n");
    hi.ctemp = 69;
    control_loop( &hi, &ho );
    assert( ho.hon == true ); assert( ho.con == false ); assert( ho.fon == true );
}

int main() {
    testStandardCool();
    testStandardHeat();
    return 0;
}
