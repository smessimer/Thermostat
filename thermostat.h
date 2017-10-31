#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <stdbool.h>

/*
 * Input Enums
 */
typedef enum fan_mode {
    FAN_MODE_AUTO,
    FAN_MODE_ON
} fan_mode;

typedef enum hvac_mode {
    HVAC_MODE_COOL,
    HVAC_MODE_HEAT,
    HVAC_MODE_OFF
} hvac_mode;

typedef enum hvac_error {
    HVE_NOERR,
    HVE_UPANDDOWN,
    HVE_FRELAYERR,
    HVE_CRELAYERR,
    HVE_HRELAYERR
} hvac_error;

typedef struct hvac_input {
    bool            stup;
    bool            stdown;
    char            stemp;
    char            ctemp;
    enum fan_mode   fmode;
    enum hvac_mode  hmode;
} hvac_input;
        
/*
 * Output Enums - not currently used.
 * Outputs handled directly in control function and w/ static vars.
 * May use these in the future.
 */
typedef enum relay_state {
    RELAY_STATE_OFF,
    RELAY_STATE_ON
} relay_state;

typedef struct hvac_output {
    bool            hon;
    bool            con;
    bool            fon;
} hvac_output;

/*
 * Function declarations
 */
hvac_error control_loop( hvac_input* hvi, hvac_output* hvo );
hvac_error handle_relay_output(bool fr_on, bool cr_on, bool hr_on);
char set_frelay(bool fr_on);
char set_crelay(bool cr_on);
char set_hrelay(bool hr_on);
#endif
