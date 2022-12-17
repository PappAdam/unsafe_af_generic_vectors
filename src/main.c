#include <stdio.h>
#include "vector/vector.h"

int main(int argc, char const *argv[])
{
    Vector building_vec;
    Vector u32_vec;
    if (!create_vector_with_capacity(&building_vec, sizeof(Building), 128) ||
        !create_vector_with_capacity(&u32_vec, sizeof(uint32_t), 0))
        return -1;

    for (int i = 0; i < 0xFF; i++)
    {
        push(&building_vec, (generic) & (Building){.building_type = i, .flags = 1 << i % (sizeof(uint32_t))});
        // NOT BEING ABLE TO DO THIS
        // push(&u32_vec, (generic) & (uint32_t)(3));
        // But it works fine with i
        push(&u32_vec, (generic)&i);
    }

    printf("Building Vector:\n\tcapacity:%lu\n\tlen:%lu\n\tlast element: {type: %i; flags: %i}\n", building_vec.capacity, building_vec.len, ((Building *)building_vec.content)[building_vec.len - 1].building_type, ((Building *)building_vec.content)[building_vec.len - 1].flags);
    printf("U32 Vector:\n\tcapacity:%lu\n\tlen:%lu\n\tlast element: %u\n", u32_vec.capacity, u32_vec.len, ((uint32_t *)u32_vec.content)[u32_vec.len - 1]);
    destroy_vector(&building_vec);
    destroy_vector(&u32_vec);
    return 0;
}
