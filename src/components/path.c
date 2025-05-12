#include "../../components/path.h"
#include "stdlib.h"

void freePath(void *component_data)
{
    cPath *path = (cPath *)component_data;
    for (int i = 0; i < path->length; i++) {
        if (path->nodes[i] != NULL) {
            path->nodes[i] = NULL;
        }
    }
}
