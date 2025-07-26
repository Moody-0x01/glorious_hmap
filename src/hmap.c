#include <hmap.h>

// typedef struct bucket_t
// {
// 	char *key;
// 	void *value;
// 	bool taken;
// 	size_t vsize;
// 	bucket_t *next;
// } bucket_t;
//
// typedef struct hmap_t
// {
// 	bucket_t *buckets;
// 	size_t size; // How much buckets are already taken and full
// 	size_t cap;  // How much buckets are already allocated
// } hmap_t;

// Constuctor
hmap_t *new_hmap(size_t cap)
{
	hmap_t *hmap;

	hmap = malloc(sizeof(hmap_t));
	if (!hmap)
	{
		return (NULL);
	}
	memset(hmap, 0, sizeof(hmap_t));
	hmap->cap = cap;
	hmap->buckets = malloc(sizeof(*hmap->buckets) * cap);
	memset(hmap->buckets, 0, sizeof(*hmap->buckets) * cap);
	return (hmap);
}

void destroy_hmap(hmap_t *hmap)
{
	bucket_t *cell;
	bucket_t *next;

	for (size_t i = 0; i < hmap->cap; i++)
	{
		cell = hmap->buckets[i].next;
		while (cell != NULL)
		{
			next = cell->next;
			if (cell->taken)
			{
				free(cell->key);
				free(cell->value);
			}
			free(cell);
			cell = next;
		}
		hmap->buckets[i].next = NULL;
		if (hmap->buckets[i].taken)
		{
			free(hmap->buckets[i].key);
			free(hmap->buckets[i].value);
			hmap->buckets[i].taken = false;
		}
	}
	free(hmap->buckets);
	free(hmap);
}

void hmap_insert(hmap_t *hmap, char *key, void *value, size_t value_size)
{
	bucket_t *cell;
	unsigned long index;

	index = (hmap_hash(key) % hmap->cap);
	cell = &hmap->buckets[index];
	while (cell->taken && cell != NULL)
	{
		if (cell->next == NULL) // U reached the end of the list but did not find any spot.
		{
			cell->next = malloc(sizeof(bucket_t));
			cell = cell->next;
			break;
		}
		cell = cell->next;
	}
	cell->taken = true;
	cell->vsize = value_size;
	cell->value = malloc(value_size);
	cell->value = memcpy(cell->value, value, value_size);
	cell->key   = strdup(key);
}

void *hmap_get(hmap_t *hmap, char *key)
{
	bucket_t *cell;
	unsigned long index;

	index = (hmap_hash(key) % hmap->cap);
	cell = &hmap->buckets[index];
	while (cell != NULL)
	{
		if (!strcmp(cell->key, key))
			return (cell->value);
		cell = cell->next;
	}
	return (NULL);
}
