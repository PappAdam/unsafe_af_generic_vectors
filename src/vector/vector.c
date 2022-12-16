#include "vector.h"
#include <stdio.h>

uint8_t create_new_raw_vector(Vector *vector)
{
    Vector vec = {
        .len = 0,
        .capacity = 0,
        .content = (void *)malloc(0),
        .instance_size = 0,
        .first_empty_index = SIZE_MAX,
    };

    if (vector->content == NULL)
    {
        perror("Failed to create vector\n");
        return 0;
    }

    return 1;
}

uint8_t create_vector_with_capacity(Vector *vector, size_t type_size, size_t size)
{
    *vector = (Vector){
        .len = 0,
        .capacity = size,
        .content = (void *)malloc(type_size * size),
        .instance_size = type_size,
        .first_empty_index = SIZE_MAX,
    };
    if (!vector->capacity)
    {
        vector->capacity = 1;
    }

    if (vector->content == NULL)
    {
        perror("Failed to create vector\n");
        return 0;
    }

    return 1;
}

uint8_t expand_vec(Vector *vec)
{
    uint8_t result = 1;
    size_t new_size = vec->capacity * 2;
    vec->content = realloc(vec->content, vec->instance_size * new_size);
    if (!vec->content)
    {
        void *new_content = (void *)malloc(vec->instance_size * new_size);

        if (new_content)
        {
            for (size_t i = 0; i < vec->len && i < new_size; i++)
            {
                ((generic)new_content)[i] = ((generic)vec->content)[i];
            }
            vec->content = (void *)new_content;
        }
        else
        {
            result = 0;
        }
    }

    vec->capacity = new_size;
    return result;
}

uint8_t push_back(Vector *vec, generic value)
{
    uint8_t result = 1;
    if (vec->len + 1 >= vec->capacity)
    {
        if (!expand_vec(vec))
        {
            result = 0;
        }
    }

    for (size_t i = 0; i < (vec->instance_size); i++)
    {
        ((generic)vec->content)[(vec->instance_size) * vec->len + i] = value[i];
    }

    vec->len++;

    return result;
}

uint8_t push(Vector *vec, generic value)
{
    uint8_t result = 1;
    if (vec->first_empty_index != SIZE_MAX)
    {
        for (size_t i = 0; i < vec->instance_size; i++)
        {
            ((generic)vec->content)[vec->instance_size * vec->first_empty_index + i] = value[i];
        }
        seek_for_empty(vec);
    }
    else
    {
        if (!push_back(vec, value))
        {
            result = 0;
        }
    }

    return result;
}

uint8_t remove_by_index(Vector *vec, size_t index)
{
    if (index > vec->len - 1)
    {
        perror("index out of range");
        return 0;
    }

    for (size_t i = 0; i < vec->instance_size; i++)
    {
        ((generic)vec->content)[vec->instance_size * index + i] = 0;
    }

    if (index < vec->first_empty_index)
    {
        vec->first_empty_index = index;
    }

    return 1;
}

void seek_for_empty(Vector *vec)
{
    size_t empty = SIZE_MAX;
    for (uint16_t i = 0; i < vec->len; i++)
    {
        if (!((generic)vec->content)[vec->instance_size * i])
        {
            empty = i;
            break;
        }
    }

    vec->first_empty_index = empty;
}

void destroy_vector(Vector *vec)
{
    free(vec->content);
}