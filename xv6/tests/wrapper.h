#ifndef __wrapper_h__
#define __wrapper_h__

#include <string.h>
#include <stdlib.h>

static void *region;
static int region_size;

static inline void *InitWrapper(int sizeOfRegion) {
    region = Mem_Init(sizeOfRegion);
    region_size = sizeOfRegion;
    if (region_size % 4096)
        region_size += 4096 - (region_size % 4096); // round up
    if (region != NULL) {
        void *backup = malloc(region_size);
        assert(backup != NULL);
        memcpy(backup, region, region_size);

        while (Mem_Alloc(8) != NULL);

        memcpy(region, backup, region_size); 
        free(backup);
    }
    return region;
}

static inline void *AllocWrapper(int size) {
    void *ptr = Mem_Alloc(size);
    if (ptr != NULL) {
        assert(ptr >= region);
        assert(ptr + size <= region + region_size);
    }
    return ptr;
}

#endif
