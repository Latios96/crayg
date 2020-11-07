//
// Created by Jan Honsbrok on 07.11.20.
//

#include "Vector3fSimdImpl.h"


void *malloc_simd(const size_t size) {
#if defined WIN32
    return _aligned_malloc(size, 16);
#elif defined __linux__
    return memalign(16, size);
#elif defined __MACH__
    return malloc(size);
#else // use page-aligned memory for other systems
    return valloc(size);
#endif
}

void free_simd(void *v) {
#if defined WIN32
    return _aligned_free(v);
#else
    return free(v);
#endif
}

std::ostream &operator<<(std::ostream &os, const Vector3fSimdImpl &v) {
    os << "Vector3(" << v.x << ", "
       << v.y << ", "
       << v.z << ")";
    return os;
}
