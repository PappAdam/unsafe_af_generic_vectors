#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t *generic;

typedef struct Building
{
    uint32_t building_type;
    uint16_t flags;
} Building;

typedef struct Vector
{
    size_t len;
    uint64_t capacity;
    void *content;
    size_t instance_size;
    size_t first_empty_index;
} Vector;

uint8_t create_new_raw_vector(Vector *vector);
uint8_t create_vector_with_capacity(Vector *vector, size_t type_size, size_t size);

uint8_t push(Vector *vec, generic value);
uint8_t remove_by_index(Vector *vec, size_t index);
void seek_for_empty(Vector *vec);

#endif
