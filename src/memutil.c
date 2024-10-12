#include "vmath/internal/memutil.h"
#include <assert.h>

int32_t vm_mem_is_aligned(const void* const mem, const uint8_t align)
{
    assert(mem);
	return ((uintptr_t)mem % align) == 0;
}
