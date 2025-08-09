#ifndef MAP_H
#define MAP_H

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define HMAP_INIT_CAP 64 * 2

typedef struct bucket_t bucket_t;
typedef struct bucket_t
{
	char *key;
	void *value;
	bool taken;
	size_t vsize;
	bucket_t *next;
} bucket_t;

typedef struct hmap_t
{
	bucket_t *buckets;
	size_t size; // How much buckets are already taken and full
	size_t cap;  // How much buckets are already allocated
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

#endif // !MAP_H
