#include <hmap.h>

static unsigned long djb2_hash(unsigned char *key)
{
	unsigned long hash_ = 5381;

	for (size_t c = 0; key[c]; c++)
		hash_ = ((hash_ << 5) + hash_) + key[c];
	return hash_;
}

unsigned long hmap_hash(char *key)
{
	return djb2_hash((unsigned char *)key);
}
