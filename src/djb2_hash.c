#include <hmap.h>

unsigned long djb2_hash(unsigned char *key)
{
	unsigned long hash_ = 5381;

	for (size_t c = 0; key[c]; c++)
		hash_ = ((hash_ << 5) + hash_) + key[c];
	return hash_;
}

uint32_t fnv1a_hash(const unsigned char* str) {
    uint32_t hash = 2166136261u; // FNV offset basis
    while (*str) {
        hash ^= (uint32_t)*str++;
        hash *= 16777619u; // FNV prime
    }
	// printf("HaSh %u\n", hash);
    return hash;
}

uint64_t fnv1a_hash64(const unsigned char* str) {
    uint64_t hash = 14695981039346656037ULL;
    while (*str) {
        hash ^= (uint64_t)*str++;
        hash *= 1099511628211ULL;
    }
    return hash;
}

unsigned long hmap_hash(char *key)
{
	return djb2_hash((unsigned char *)key);
}
