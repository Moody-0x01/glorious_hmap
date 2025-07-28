#include <hmap.h>

void f(bucket_t *C)
{
	printf("%s -> %s\n", C->key, (char*)C->value);
}

int main()
{
	hmap_t *mp = new_hmap(10);
	{
		hmap_insert(mp, "Hello, mdfkr", "Yea mdfkr", 10);
		hmap_insert(mp, "Hello, mdfkr", "Another one", 12);
		char *v = hmap_get(mp, "Hello, mdfkr");
		if (v)
			printf("Found %s\n", v);
		else
			printf("key %s does not exist\n", "Hello, mdfkr");
		hmap_delete(mp, "Hello, mdfkr");
		v = hmap_get(mp, "Hello, mdfkr");
		if (v)
			printf("Found %s\n", v);
		else
			printf("key %s does not exist\n", "Hello, mdfkr");
		hmap_delete(mp, "Hello, mdfkr");
		hmap_delete(mp, "Hello, mdfkr");
		hmap_delete(mp, "Hello, mdfkr");
		hmap_delete(mp, "Hello, mdfkr");
		hmap_delete(mp, "Hello, mdfkr");
		hmap_delete(mp, "Hello, mdfkr");
		hmap_delete(mp, "Hello, mdfkr");
		assert(mp->size == 0 && "It is not zero for whatever reason");
		hmap_foreach(mp, f);

		hmap_insert(mp, "1", "Omag", 5);
		hmap_insert(mp, "2", "wjiwjs", 7);
		hmap_insert(mp, "3", "Brolly", 7);
		hmap_insert(mp, "4", "Man", 4);
		hmap_insert(mp, "5", "Bat", 4);
		hmap_insert(mp, "6", "Sides", 6);
		hmap_insert(mp, "7", "Mallic", 7);
		assert(mp->size == 7 && "It is not zero for whatever reason");
		hmap_foreach(mp, f);
		hmap_delete(mp, "1");
		assert(mp->size == 6 && "It is not zero for whatever reason");
		hmap_delete(mp, "2");
		assert(mp->size == 5 && "It is not zero for whatever reason");

		hmap_delete(mp, "3");
		assert(mp->size == 4 && "It is not zero for whatever reason");

		hmap_delete(mp, "4");
		assert(mp->size == 3 && "It is not zero for whatever reason");

		hmap_delete(mp, "5");
		assert(mp->size == 2 && "It is not zero for whatever reason");
		
		hmap_delete(mp, "6");
		assert(mp->size == 1 && "It is not zero for whatever reason");

		hmap_delete(mp, "7");
		assert(mp->size == 0 && "It is not zero for whatever reason");

		hmap_foreach(mp, f);
	}
	destroy_hmap(mp);
	return (0);
}
