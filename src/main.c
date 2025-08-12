#include <hmap.h>
// #include <map>

void f(bucket_t *C)
{
	printf("%s -> %s\n", C->key, (char*)C->value);
}

#define Insert(m, k, v, l) hmap_insert(m, (char *)k, (void *)v, l)
#define Get(m, k) (char *)hmap_get(m, (char *)k)
#define Del(m, k) hmap_delete(m, (char *)k)

void fill_map(hmap_t *map)
{
	Insert(map, "1", "Omag", 5);
	Insert(map, "2", "wjiwjs", 7);
	Insert(map, "3", "Brolly", 7);
	Insert(map, "4", "Man", 4);
	Insert(map, "5", "Bat", 4);
	Insert(map, "6", "Sides", 6);
	Insert(map, "7", "Mallic", 7);
}

int main()
{
	hmap_t *mp = new_hmap(HMAP_INIT_CAP);
	{
		Insert(mp, "Hello, mdfkr", "Yea mdfkr", 10);
		Insert(mp, "Hello, mdfkr", "Another one", 12);
		char *v = Get(mp, "Hello, mdfkr");
		if (v)
			printf("Found %s\n", v);
		else
			printf("key %s does not exist\n", "Hello, mdfkr");
		Del(mp, "Hello, mdfkr");
		v = Get(mp, "Hello, mdfkr");
		if (v)
			printf("Found %s\n", v);
		else
			printf("key %s does not exist\n", "Hello, mdfkr");
		Del(mp, "Hello, mdfkr");
		Del(mp, "Hello, mdfkr");
		Del(mp, "Hello, mdfkr");
		Del(mp, "Hello, mdfkr");
		Del(mp, "Hello, mdfkr");
		Del(mp, "Hello, mdfkr");
		Del(mp, "Hello, mdfkr");
		assert(mp->size == 0 && "It is not zero for whatever reason");
		hmap_foreach(mp, f);

		fill_map(mp);
		assert(mp->size == 7 && "It is not zero for whatever reason");
		hmap_foreach(mp, f);
		Del(mp, "1");
		assert(mp->size == 6 && "It is not zero for whatever reason");
		Del(mp, "2");
		assert(mp->size == 5 && "It is not zero for whatever reason");

		Del(mp, "3");
		assert(mp->size == 4 && "It is not zero for whatever reason");

		Del(mp, "4");
		assert(mp->size == 3 && "It is not zero for whatever reason");

		Del(mp, "5");
		assert(mp->size == 2 && "It is not zero for whatever reason");

		Del(mp, "6");
		assert(mp->size == 1 && "It is not zero for whatever reason");

		Del(mp, "7");
		assert(mp->size == 0 && "It is not zero for whatever reason");

		hmap_foreach(mp, f);
		fill_map(mp);
		hmap_clear(mp);
		hmap_foreach(mp, f);
		assert(mp->size == 0 && "It is not zero for whatever reason");
	}
	destroy_hmap(mp);
	return (0);
}

// int main(int ac, char **av)
// {
// 	if (ac < 2)
// 		return (1);
// 	printf("Hash: %ld, Key: %s\n", hmap_hash(av[1]), av[1]);
// 	return (0);
// }
