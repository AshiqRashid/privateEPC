
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "condition_data.h"

OpenAPI_condition_data_t *OpenAPI_condition_data_create(
    char *cond_id,
    bool is_activation_time_null,
    char *activation_time,
    bool is_deactivation_time_null,
    char *deactivation_time,
    OpenAPI_access_type_e access_type,
    OpenAPI_rat_type_e rat_type
)
{
    OpenAPI_condition_data_t *condition_data_local_var = ogs_malloc(sizeof(OpenAPI_condition_data_t));
    ogs_assert(condition_data_local_var);

    condition_data_local_var->cond_id = cond_id;
    condition_data_local_var->is_activation_time_null = is_activation_time_null;
    condition_data_local_var->activation_time = activation_time;
    condition_data_local_var->is_deactivation_time_null = is_deactivation_time_null;
    condition_data_local_var->deactivation_time = deactivation_time;
    condition_data_local_var->access_type = access_type;
    condition_data_local_var->rat_type = rat_type;

    return condition_data_local_var;
}

void OpenAPI_condition_data_free(OpenAPI_condition_data_t *condition_data)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == condition_data) {
        return;
    }
    if (condition_data->cond_id) {
        ogs_free(condition_data->cond_id);
        condition_data->cond_id = NULL;
    }
    if (condition_data->activation_time) {
        ogs_free(condition_data->activation_time);
        condition_data->activation_time = NULL;
    }
    if (condition_data->deactivation_time) {
        ogs_free(condition_data->deactivation_time);
        condition_data->deactivation_time = NULL;
    }
    ogs_free(condition_data);
}

cJSON *OpenAPI_condition_data_convertToJSON(OpenAPI_condition_data_t *condition_data)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (condition_data == NULL) {
        ogs_error("OpenAPI_condition_data_convertToJSON() failed [ConditionData]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!condition_data->cond_id) {
        ogs_error("OpenAPI_condition_data_convertToJSON() failed [cond_id]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "condId", condition_data->cond_id) == NULL) {
        ogs_error("OpenAPI_condition_data_convertToJSON() failed [cond_id]");
        goto end;
    }

    if (condition_data->activation_time) {
    if (cJSON_AddStringToObject(item, "activationTime", condition_data->activation_time) == NULL) {
        ogs_error("OpenAPI_condition_data_convertToJSON() failed [activation_time]");
        goto end;
    }
    } else if (condition_data->is_activation_time_null) {
        if (cJSON_AddNullToObject(item, "activationTime") == NULL) {
            ogs_error("OpenAPI_condition_data_convertToJSON() failed [activation_time]");
            goto end;
        }
    }

    if (condition_data->deactivation_time) {
    if (cJSON_AddStringToObject(item, "deactivationTime", condition_data->deactivation_time) == NULL) {
        ogs_error("OpenAPI_condition_data_convertToJSON() failed [deactivation_time]");
        goto end;
    }
    } else if (condition_data->is_deactivation_time_null) {
        if (cJSON_AddNullToObject(item, "deactivationTime") == NULL) {
            ogs_error("OpenAPI_condition_data_convertToJSON() failed [deactivation_time]");
            goto end;
        }
    }

    if (condition_data->access_type != OpenAPI_access_type_NULL) {
    if (cJSON_AddStringToObject(item, "accessType", OpenAPI_access_type_ToString(condition_data->access_type)) == NULL) {
        ogs_error("OpenAPI_condition_data_convertToJSON() failed [access_type]");
        goto end;
    }
    }

    if (condition_data->rat_type != OpenAPI_rat_type_NULL) {
    if (cJSON_AddStringToObject(item, "ratType", OpenAPI_rat_type_ToString(condition_data->rat_type)) == NULL) {
        ogs_error("OpenAPI_condition_data_convertToJSON() failed [rat_type]");
        goto end;
    }
    }

end:
    return item;
}

OpenAPI_condition_data_t *OpenAPI_condition_data_parseFromJSON(cJSON *condition_dataJSON)
{
    OpenAPI_condition_data_t *condition_data_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *cond_id = NULL;
    cJSON *activation_time = NULL;
    cJSON *deactivation_time = NULL;
    cJSON *access_type = NULL;
    OpenAPI_access_type_e access_typeVariable = 0;
    cJSON *rat_type = NULL;
    OpenAPI_rat_type_e rat_typeVariable = 0;
    cond_id = cJSON_GetObjectItemCaseSensitive(condition_dataJSON, "condId");
    if (!cond_id) {
        ogs_error("OpenAPI_condition_data_parseFromJSON() failed [cond_id]");
        goto end;
    }
    if (!cJSON_IsString(cond_id)) {
        ogs_error("OpenAPI_condition_data_parseFromJSON() failed [cond_id]");
        goto end;
    }

    activation_time = cJSON_GetObjectItemCaseSensitive(condition_dataJSON, "activationTime");
    if (activation_time) {
    if (!cJSON_IsNull(activation_time)) {
    if (!cJSON_IsString(activation_time) && !cJSON_IsNull(activation_time)) {
        ogs_error("OpenAPI_condition_data_parseFromJSON() failed [activation_time]");
        goto end;
    }
    }
    }

    deactivation_time = cJSON_GetObjectItemCaseSensitive(condition_dataJSON, "deactivationTime");
    if (deactivation_time) {
    if (!cJSON_IsNull(deactivation_time)) {
    if (!cJSON_IsString(deactivation_time) && !cJSON_IsNull(deactivation_time)) {
        ogs_error("OpenAPI_condition_data_parseFromJSON() failed [deactivation_time]");
        goto end;
    }
    }
    }

    access_type = cJSON_GetObjectItemCaseSensitive(condition_dataJSON, "accessType");
    if (access_type) {
    if (!cJSON_IsString(access_type)) {
        ogs_error("OpenAPI_condition_data_parseFromJSON() failed [access_type]");
        goto end;
    }
    access_typeVariable = OpenAPI_access_type_FromString(access_type->valuestring);
    }

    rat_type = cJSON_GetObjectItemCaseSensitive(condition_dataJSON, "ratType");
    if (rat_type) {
    if (!cJSON_IsString(rat_type)) {
        ogs_error("OpenAPI_condition_data_parseFromJSON() failed [rat_type]");
        goto end;
    }
    rat_typeVariable = OpenAPI_rat_type_FromString(rat_type->valuestring);
    }

    condition_data_local_var = OpenAPI_condition_data_create (
        ogs_strdup(cond_id->valuestring),
        activation_time && cJSON_IsNull(activation_time) ? true : false,
        activation_time && !cJSON_IsNull(activation_time) ? ogs_strdup(activation_time->valuestring) : NULL,
        deactivation_time && cJSON_IsNull(deactivation_time) ? true : false,
        deactivation_time && !cJSON_IsNull(deactivation_time) ? ogs_strdup(deactivation_time->valuestring) : NULL,
        access_type ? access_typeVariable : 0,
        rat_type ? rat_typeVariable : 0
    );

    return condition_data_local_var;
end:
    return NULL;
}

OpenAPI_condition_data_t *OpenAPI_condition_data_copy(OpenAPI_condition_data_t *dst, OpenAPI_condition_data_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_condition_data_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_condition_data_convertToJSON() failed");
        return NULL;
    }

    content = cJSON_Print(item);
    cJSON_Delete(item);

    if (!content) {
        ogs_error("cJSON_Print() failed");
        return NULL;
    }

    item = cJSON_Parse(content);
    ogs_free(content);
    if (!item) {
        ogs_error("cJSON_Parse() failed");
        return NULL;
    }

    OpenAPI_condition_data_free(dst);
    dst = OpenAPI_condition_data_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

