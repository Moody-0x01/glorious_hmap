#include <map.h>

unsigned long djb2_hash(unsigned char *key)
{
	unsigned long hash_ = 5381;
	int c;
	while ((c = *key++))
		hash_ = ((hash_ << 5) + hash_) + c;
	return hash_;
}
