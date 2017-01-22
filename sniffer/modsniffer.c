#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "py/nlr.h"
#include "py/objlist.h"

#include "user_interface.h"
#include "py/runtime.h"
#include "py/mphal.h"

//add printf functionality
#include "py/obj.h"
#include "py/objstr.h"


mp_obj_t pyCallback = mp_const_none;
void pyCallbackFunction(uint8 *buf, uint16 len){
    if(mp_obj_is_callable(pyCallback)){
	mp_call_function_1(pyCallback, mp_obj_new_bytearray_by_ref(len,buf));
    }
    else {
	printf("Callback function does not appear to be callable. Disabling promiscuous mode.\r\n");
	wifi_promiscuous_enable(0);
    }
}

//Promiscuous Mode -- sniff.Sniffer( cb_handler() ) -the packets are sent to this function for processing (as a byte array)
STATIC mp_obj_t s_Sniffer(mp_obj_t func) {
    //clear connection first, and set op mode to station
    wifi_set_opmode(STATION_MODE);

    //make sure its actually off before its started 
    wifi_promiscuous_enable(0);
    
    //set up our function handler to take a user-defined python function
    pyCallback = func;

    //set the callback to our callback (that refers to the func arg)
    wifi_set_promiscuous_rx_cb(pyCallbackFunction);

    wifi_promiscuous_enable(1);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(s_Sniffer_obj, s_Sniffer);

//Change current channel (to sweep while listening -- recommended in environments with multiple routers) (1-14 typical, though 12-14 are reserved in NA)
STATIC mp_obj_t s_channel(mp_uint_t n_args, const mp_obj_t *args) {
    if (n_args == 0) {
        return mp_obj_new_int(wifi_get_channel());
    } else {
        wifi_set_channel(mp_obj_get_int(args[0]));
        return mp_const_none;
    }
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(s_channel_obj, 1, 14, s_channel);


STATIC const mp_map_elem_t mp_module_sniffer_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_sniff) },

    //allow access to custom functions
    { MP_OBJ_NEW_QSTR(MP_QSTR_Sniffer), (mp_obj_t)&s_Sniffer_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_channel), (mp_obj_t)&s_channel_obj }
};

STATIC MP_DEFINE_CONST_DICT(mp_module_sniffer_globals, mp_module_sniffer_globals_table);

const mp_obj_module_t sniffer_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_sniffer_globals,
};