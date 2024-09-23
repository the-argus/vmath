#include "vmath/internal/memutil.h"

int32_t vm_mem_is_aligned(const void* const mem, const uint8_t align)
{
	return ((uintptr_t)mem % align) == 0;
}
