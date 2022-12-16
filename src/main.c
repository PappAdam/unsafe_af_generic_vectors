#include <stdio.h>
#include "vector/vector.h"

int main(int argc, char const *argv[])
{
    Vector vec;
    if (!create_vector_with_capacity(&vec, sizeof(uint8_t), 128))
    {
        return -1;
    }

    int i;
    for (i = 0; i < 0x1; i++)
    {
        push(&vec, (generic)&i);
        printf("At push:\n\tcapacity: %lu\n\tlen: %lu\n\tindex: %d\n\tvalue: %hhu\n", vec.capacity, vec.len, i, ((uint8_t *)vec.content)[i]);
    }

    destroy_vector(&vec);
    return 0;
}
