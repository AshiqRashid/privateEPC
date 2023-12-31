
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "change_item.h"

OpenAPI_change_item_t *OpenAPI_change_item_create(
    OpenAPI_change_type_e op,
    char *path,
    char *from,
    bool is_orig_value_null,
    OpenAPI_any_type_t *orig_value,
    bool is_new_value_null,
    OpenAPI_any_type_t *new_value
)
{
    OpenAPI_change_item_t *change_item_local_var = ogs_malloc(sizeof(OpenAPI_change_item_t));
    ogs_assert(change_item_local_var);

    change_item_local_var->op = op;
    change_item_local_var->path = path;
    change_item_local_var->from = from;
    change_item_local_var->is_orig_value_null = is_orig_value_null;
    change_item_local_var->orig_value = orig_value;
    change_item_local_var->is_new_value_null = is_new_value_null;
    change_item_local_var->new_value = new_value;

    return change_item_local_var;
}

void OpenAPI_change_item_free(OpenAPI_change_item_t *change_item)
{
    OpenAPI_lnode_t *node = NULL;

    if (NULL == change_item) {
        return;
    }
    if (change_item->path) {
        ogs_free(change_item->path);
        change_item->path = NULL;
    }
    if (change_item->from) {
        ogs_free(change_item->from);
        change_item->from = NULL;
    }
    if (change_item->orig_value) {
        OpenAPI_any_type_free(change_item->orig_value);
        change_item->orig_value = NULL;
    }
    if (change_item->new_value) {
        OpenAPI_any_type_free(change_item->new_value);
        change_item->new_value = NULL;
    }
    ogs_free(change_item);
}

cJSON *OpenAPI_change_item_convertToJSON(OpenAPI_change_item_t *change_item)
{
    cJSON *item = NULL;
    OpenAPI_lnode_t *node = NULL;

    if (change_item == NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [ChangeItem]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (change_item->op == OpenAPI_change_type_NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [op]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "op", OpenAPI_change_type_ToString(change_item->op)) == NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [op]");
        goto end;
    }

    if (!change_item->path) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [path]");
        return NULL;
    }
    if (cJSON_AddStringToObject(item, "path", change_item->path) == NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [path]");
        goto end;
    }

    if (change_item->from) {
    if (cJSON_AddStringToObject(item, "from", change_item->from) == NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [from]");
        goto end;
    }
    }

    if (change_item->orig_value) {
    cJSON *orig_value_object = OpenAPI_any_type_convertToJSON(change_item->orig_value);
    if (orig_value_object == NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [orig_value]");
        goto end;
    }
    cJSON_AddItemToObject(item, "origValue", orig_value_object);
    if (item->child == NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [orig_value]");
        goto end;
    }
    } else if (change_item->is_orig_value_null) {
        if (cJSON_AddNullToObject(item, "origValue") == NULL) {
            ogs_error("OpenAPI_change_item_convertToJSON() failed [orig_value]");
            goto end;
        }
    }

    if (change_item->new_value) {
    cJSON *new_value_object = OpenAPI_any_type_convertToJSON(change_item->new_value);
    if (new_value_object == NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [new_value]");
        goto end;
    }
    cJSON_AddItemToObject(item, "newValue", new_value_object);
    if (item->child == NULL) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed [new_value]");
        goto end;
    }
    } else if (change_item->is_new_value_null) {
        if (cJSON_AddNullToObject(item, "newValue") == NULL) {
            ogs_error("OpenAPI_change_item_convertToJSON() failed [new_value]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_change_item_t *OpenAPI_change_item_parseFromJSON(cJSON *change_itemJSON)
{
    OpenAPI_change_item_t *change_item_local_var = NULL;
    OpenAPI_lnode_t *node = NULL;
    cJSON *op = NULL;
    OpenAPI_change_type_e opVariable = 0;
    cJSON *path = NULL;
    cJSON *from = NULL;
    cJSON *orig_value = NULL;
    OpenAPI_any_type_t *orig_value_local_object = NULL;
    cJSON *new_value = NULL;
    OpenAPI_any_type_t *new_value_local_object = NULL;
    op = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "op");
    if (!op) {
        ogs_error("OpenAPI_change_item_parseFromJSON() failed [op]");
        goto end;
    }
    if (!cJSON_IsString(op)) {
        ogs_error("OpenAPI_change_item_parseFromJSON() failed [op]");
        goto end;
    }
    opVariable = OpenAPI_change_type_FromString(op->valuestring);

    path = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "path");
    if (!path) {
        ogs_error("OpenAPI_change_item_parseFromJSON() failed [path]");
        goto end;
    }
    if (!cJSON_IsString(path)) {
        ogs_error("OpenAPI_change_item_parseFromJSON() failed [path]");
        goto end;
    }

    from = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "from");
    if (from) {
    if (!cJSON_IsString(from) && !cJSON_IsNull(from)) {
        ogs_error("OpenAPI_change_item_parseFromJSON() failed [from]");
        goto end;
    }
    }

    orig_value = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "origValue");
    if (orig_value) {
    if (!cJSON_IsNull(orig_value)) {
    orig_value_local_object = OpenAPI_any_type_parseFromJSON(orig_value);
    }
    }

    new_value = cJSON_GetObjectItemCaseSensitive(change_itemJSON, "newValue");
    if (new_value) {
    if (!cJSON_IsNull(new_value)) {
    new_value_local_object = OpenAPI_any_type_parseFromJSON(new_value);
    }
    }

    change_item_local_var = OpenAPI_change_item_create (
        opVariable,
        ogs_strdup(path->valuestring),
        from && !cJSON_IsNull(from) ? ogs_strdup(from->valuestring) : NULL,
        orig_value && cJSON_IsNull(orig_value) ? true : false,
        orig_value ? orig_value_local_object : NULL,
        new_value && cJSON_IsNull(new_value) ? true : false,
        new_value ? new_value_local_object : NULL
    );

    return change_item_local_var;
end:
    if (orig_value_local_object) {
        OpenAPI_any_type_free(orig_value_local_object);
        orig_value_local_object = NULL;
    }
    if (new_value_local_object) {
        OpenAPI_any_type_free(new_value_local_object);
        new_value_local_object = NULL;
    }
    return NULL;
}

OpenAPI_change_item_t *OpenAPI_change_item_copy(OpenAPI_change_item_t *dst, OpenAPI_change_item_t *src)
{
    cJSON *item = NULL;
    char *content = NULL;

    ogs_assert(src);
    item = OpenAPI_change_item_convertToJSON(src);
    if (!item) {
        ogs_error("OpenAPI_change_item_convertToJSON() failed");
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

    OpenAPI_change_item_free(dst);
    dst = OpenAPI_change_item_parseFromJSON(item);
    cJSON_Delete(item);

    return dst;
}

