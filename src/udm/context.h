/*
 * Copyright (C) 2019-2022 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef UDM_CONTEXT_H
#define UDM_CONTEXT_H

#include "ogs-app.h"
#include "ogs-crypt.h"
#include "ogs-sbi.h"

#include "udm-sm.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int __udm_log_domain;

#undef OGS_LOG_DOMAIN
#define OGS_LOG_DOMAIN __udm_log_domain

typedef struct udm_context_s {
    ogs_list_t      udm_ue_list;
    ogs_hash_t      *suci_hash;
    ogs_hash_t      *supi_hash;

} udm_context_t;

struct udm_ue_s {
    ogs_sbi_object_t sbi;
    ogs_fsm_t sm;

    OpenAPI_auth_event_t *auth_event;
    OpenAPI_amf3_gpp_access_registration_t *amf_3gpp_access_registration;

    char *ctx_id;
    char *suci;
    char *supi;
    char *serving_network_name;

    char *ausf_instance_id;
    char *amf_instance_id;

    char *dereg_callback_uri;
    char *data_change_callback_uri;

    uint8_t k[OGS_KEY_LEN];
    uint8_t opc[OGS_KEY_LEN];
    uint8_t amf[OGS_AMF_LEN];
    uint8_t rand[OGS_RAND_LEN];
    uint8_t sqn[OGS_SQN_LEN];

    ogs_guami_t guami;

    OpenAPI_auth_type_e auth_type;
    OpenAPI_rat_type_e rat_type;

    ogs_list_t sess_list;
};

struct udm_sess_s {
    ogs_sbi_object_t sbi;
    ogs_fsm_t sm;

    uint8_t psi; /* PDU Session Identity */

    OpenAPI_smf_registration_t *smf_registration;

    char *smf_instance_id;

    /* Related Context */
    udm_ue_t *udm_ue;
};

void udm_context_init(void);
void udm_context_final(void);
udm_context_t *udm_self(void);

int udm_context_parse_config(void);

udm_ue_t *udm_ue_add(char *suci);
void udm_ue_remove(udm_ue_t *udm_ue);
void udm_ue_remove_all(void);
udm_ue_t *udm_ue_find_by_suci(char *suci);
udm_ue_t *udm_ue_find_by_supi(char *supi);
udm_ue_t *udm_ue_find_by_suci_or_supi(char *suci_or_supi);
udm_ue_t *udm_ue_find_by_ctx_id(char *ctx_id);

udm_sess_t *udm_sess_add(udm_ue_t *udm_ue, uint8_t psi);
void udm_sess_remove(udm_sess_t *sess);
void udm_sess_remove_all(udm_ue_t *udm_ue);
udm_sess_t *udm_sess_find_by_psi(udm_ue_t *udm_ue, uint8_t psi);

udm_ue_t *udm_ue_cycle(udm_ue_t *udm_ue);
udm_sess_t *udm_sess_cycle(udm_sess_t *sess);

int get_ue_load(void);

#ifdef __cplusplus
}
#endif

#endif /* UDM_CONTEXT_H */
