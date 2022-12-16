#include "vector.h"
#include <stdio.h>

uint8_t create_new_raw_vector(Vector *vector)
{
    Vector vec = {
        .len = 0,
        .capacity = 0,
        .content = (void *)malloc(0),
        .instance_size = 0,
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
    uint8_t result = 0;
    size_t new_size = vec->instance_size * vec->capacity << 1;
    if (!realloc(vec->content, new_size))
    {
        void *new_content = (void *)malloc(new_size);

        if (!new_content)
        {
            for (size_t i = 0; i < vec->len && i < new_size; i++)
            {
                ((generic)new_content)[i] = ((generic)vec->content)[i];
            }
            vec->content = (void *)new_content;
        }

        result = 1;
    }
    return result;
}

uint8_t push(Vector *vec, generic value)
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

void destroy_vector(Vector *vec)
{
    free(vec->content);
}