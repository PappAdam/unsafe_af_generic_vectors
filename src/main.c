#include <stdio.h>
#include "vector/vector.h"

int main(int argc, char const *argv[])
{
    Vector vec;
    if (!create_vector_with_capacity(&vec, sizeof(Building), 128))
    {
        return -1;
    }

    int i;
    for (i = 0; i < 0xFF; i++)
    {
        Building new_tile = {.building_type = 12, .flags = 0};
        push(&vec, (generic)&new_tile);
    }

    destroy_vector(&vec);
    return 0;
}
