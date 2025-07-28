#include <hmap.h>

// Constuctor
hmap_t *new_hmap(size_t cap)
{
	hmap_t *hmap;

	hmap = malloc(sizeof(hmap_t));
	if (!hmap)
		return (NULL);
	memset(hmap, 0, sizeof(*hmap));
	hmap->cap = cap;
	hmap->buckets = malloc(sizeof(*hmap->buckets) * cap);
	memset(hmap->buckets, 0, sizeof(*hmap->buckets) * cap);
	return (hmap);
}

void destroy_hmap(hmap_t *hmap)
{
	if (hmap)
	{
		hmap_clear(hmap);
		free(hmap->buckets);
		free(hmap);
	}
}

bucket_t *hmap_find(hmap_t *hmap, char *key)
{
	bucket_t *cell;
	unsigned long index;

	index = (hmap_hash(key) % hmap->cap);
	cell = &hmap->buckets[index];
	while (cell != NULL)
	{
		if (cell->taken && !strcmp(cell->key, key))
			return (cell);
		cell = cell->next;
	}
	return (NULL);
}

void hmap_insert(hmap_t *hmap, char *key, void *value, size_t value_size)
{
	bucket_t *cell;
	unsigned long index;

	index = (hmap_hash(key) % hmap->cap);
	cell = &hmap->buckets[index];
	while (cell != NULL)
	{
		if (cell->taken && !strcmp(cell->key, key)) // @EXPLAINATON: In case keys are the same, we overrite with new data
			break ;
		if (cell->next == NULL) // U reached the end of the list but did not find any spot.
		{
			cell->next = malloc(sizeof(bucket_t));
			memset(cell->next, 0, sizeof(*cell->next));
			cell = cell->next;
			break ;
		}
		cell = cell->next;
	}
	if (cell->taken)
	{
		free(cell->value);
		free(cell->key);
	} else
		hmap->size++;
	cell->taken = true;
	cell->vsize = value_size;
	cell->value = malloc(value_size);
	cell->value = memcpy(cell->value, value, value_size);
	cell->key   = strdup(key);
}

void *hmap_get(hmap_t *hmap, char *key)
{

	bucket_t *cell = hmap_find(hmap, key);

	if (cell) // > FOUND
		return (cell->value);
	// < Not FOUND
	return (NULL);
}

void hmap_delete(hmap_t *hmap, char *key)
{
	bucket_t *cell = hmap_find(hmap, key);

	if (cell)
	{
		free(cell->key);
		free(cell->value);
		cell->value = NULL;
		cell->key = NULL;
		cell->taken = false;
		cell->vsize = 0;
		hmap->size--;
	}
}

void hmap_foreach(hmap_t *hmap, void (*func)(bucket_t *cell))
{
	bucket_t *cell;

	for (size_t i = 0; i < hmap->cap; i++)
	{
		cell = hmap->buckets[i].next;
		while (cell != NULL)
		{
			if (cell->taken)
				func(cell);
			cell = cell->next;
		}
	}
}

void hmap_clear(hmap_t *hmap)
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
}
