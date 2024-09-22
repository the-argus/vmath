#ifndef __VMATH_MEMUTIL_H
#define __VMATH_MEMUTIL_H

#include "vmath/internal/stdint.h"

// 1 if aligned, 0 if not
// example: assert(vm_mem_is_aligned(pointer_to_vec16, 64))
int32_t vm_mem_is_aligned(const void* mem, uint8_t align);

#endif
