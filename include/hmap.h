#ifndef MAP_H
#define MAP_H

#include <stack.h>

// #define HMAP_LLIMPLEMENTATION // Linked List
// #define HMAP_DYN_ARRAY        // Array
#define HMAP_INIT_CAP 64 * 2

typedef struct bucket_t bucket_t;
typedef struct bucket_t
{
	char *key;
	void *value;
	size_t vsize;
	bool taken;
#ifdef HMAP_LLIMPLEMENTATION
	bucket_t *next;
#endif // HMAP_LLIMPLEMENTATION
} bucket_t;

#ifdef HMAP_DYN_ARRAY
	typedef struct bucket_cluster_t
	{
		bucket_t *buckets;
		size_t size, cap;
	} bucket_cluster_t;
#endif // HMAP_DYN_ARRAY

typedef struct hmap_t
{
#ifdef HMAP_LLIMPLEMENTATION
	bucket_t		*buckets;
#else
	bucket_cluster_t *clusters;
	t_stack			 *vacant;
#endif // HMAP_LLIMPLEMENTATION
	size_t size, cap; // How much buckets are already taken and full
} hmap_t;

unsigned long hmap_hash(char *key);
void destroy_hmap(hmap_t *hmap);
hmap_t *new_hmap(size_t cap);
void hmap_insert(hmap_t *hmap, char *key, void *value, size_t value_size);
bucket_t *hmap_find(hmap_t *hmap, char *key);
void *hmap_get(hmap_t *hmap, char *key);
void hmap_clear(hmap_t *hmap);
void hmap_delete(hmap_t *hmap, char *key);
void hmap_foreach(hmap_t *hmap, void (*func)(bucket_t *cell));
#ifdef HMAP_DYN_ARRAY
	int	hmap_find_pair(hmap_t *hmap, char *key, t_pair *pair);
	void cluster_expand(bucket_cluster_t *cluster);
#endif /* ifdef HMAP_DYN_ARRAY */

#endif // !MAP_H
