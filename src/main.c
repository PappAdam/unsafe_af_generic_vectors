#include <stdio.h>
#include "vector/vector.h"

int main(int argc, char const *argv[])
{
    Vector vec;
    if (!create_vector_with_capacity(&vec, sizeof(uint32_t), 0))
    {
        return -1;
    }

    uint32_t value = 3;
    push(&vec, (generic)&value);

    printf("capacity: %i, len: %i, value at: %i is %i\n", vec.capacity, vec.len, 0, ((uint32_t *)vec.content)[0]);

    destroy_vector(&vec);

    return 0;
}
