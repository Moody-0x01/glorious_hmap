#include <hmap.h>

int main()
{
	hmap_t *mp = new_hmap(10);
	hmap_insert(mp, "Hello, mdfkr", "Yea mdfkr", 10);
	char *v = hmap_get(mp, "Hello, mdfkr");
	if (v)
		printf("Found %s\n", v);
	else
		printf("key %s does not exist\n", "Hello, mdfkr");
	destroy_hmap(mp);
	return (0);
}
