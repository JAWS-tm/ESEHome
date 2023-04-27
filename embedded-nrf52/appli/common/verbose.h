/*
 * verbose.h
 *
 *  Created on: 8 févr. 2023
 *      Author: jules
 */


#ifndef VERBOSE_H
#define VERBOSE_H

#include "nrf_esb.h"
#include <stdint.h>
#include "parameters.h"
#include "rf_dialog.h"

char * VERBOSE_object_id_to_string(uint8_t id);
char * VERBOSE_message_id_to_string(msg_id_e id);
char * VERBOSE_parameter_id_to_string(param_id_e id);

void VERBOSE_add_message_to_process(nrf_esb_payload_t * payload);
void VERBOSE_process_main(void);

/* parse a message and print it to the debug uart */
char * VERBOSE_trame_message(nrf_esb_payload_t * payload);

#endif
