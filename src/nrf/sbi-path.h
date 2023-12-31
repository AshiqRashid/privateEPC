/*
 * Copyright (C) 2019-2023 by Sukchan Lee <acetcom@gmail.com>
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

#ifndef NRF_SBI_PATH_H
#define NRF_SBI_PATH_H

#include "ogs-sbi.h"
#include "nnrf-build.h"

#ifdef __cplusplus
extern "C" {
#endif

int nrf_sbi_open(void);
void nrf_sbi_close(void);

bool nrf_nnrf_nfm_send_nf_status_notify(
        ogs_sbi_subscription_data_t *subscription_data,
        OpenAPI_notification_event_type_e event,
        ogs_sbi_nf_instance_t *nf_instance);
bool nrf_nnrf_nfm_send_nf_status_notify_all(
        OpenAPI_notification_event_type_e event,
        ogs_sbi_nf_instance_t *nf_instance);

#ifdef __cplusplus
}
#endif

#endif /* NRF_SBI_PATH_H */
