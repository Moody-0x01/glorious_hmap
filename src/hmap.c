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

#ifdef HMAP_LLIMPLEMENTATION
	hmap->buckets = malloc(sizeof(*hmap->buckets) * cap);
	memset(hmap->buckets, 0, sizeof(*hmap->buckets) * cap);
#else
	// #ifdef HMAP_PROBE
	// 	cap = 1;
	// #endif /* ifdef HMAP_PROBE */
	hmap->clusters = malloc(sizeof(*hmap->clusters) * cap);
	memset(hmap->clusters, 0, sizeof(*hmap->clusters) * cap);
	for (size_t i = 0; i < cap; ++i)
	{
		// #ifdef HMAP_PROBE
		// 	hmap->clusters[i].cap = INIT_PROBING_SIZE;
		// #else
		hmap->clusters[i].cap = INIT_BUCKET;
		// #endif /* ifdef HMAP_PROBE */
		hmap->clusters[i].buckets = malloc(sizeof(*hmap->clusters[i].buckets) * hmap->clusters[i].cap);
		memset(hmap->clusters[i].buckets, 0, sizeof(*hmap->clusters[i].buckets) * hmap->clusters[i].cap);
	}
	hmap->vacant = stack_construct();
#endif // !HMAP_LLIMPLEMENTATION
	return (hmap);
}

void destroy_hmap(hmap_t *hmap)
{
	if (hmap)
	{
		hmap_clear(hmap);
#ifdef HMAP_LLIMPLEMENTATION
		free(hmap->buckets);
#else
		stack_destroy(hmap->vacant);
		for (size_t i = 0; i < hmap->cap; ++i)
			free(hmap->clusters[i].buckets);
		free(hmap->clusters);
#endif // HMAP_LLIMPLEMENTATION
		free(hmap);
	}
}

#ifdef HMAP_DYN_ARRAY
	void	cluster_expand(bucket_cluster_t *cluster)
	{
		if (cluster->size >= cluster->cap)
		{
			cluster->cap *= VEC_GROWTH_FAC;
			cluster->buckets = realloc(cluster->buckets, cluster->cap * sizeof(*(cluster->buckets)));
		}
	}
	int	hmap_find_pair(hmap_t *hmap, char *key, t_pair *pair)
	{
		bucket_cluster_t *cluster;
		bucket_t *cell;
		unsigned long index;

		index = (hmap_hash(key) % hmap->cap);
		pair->first = index;
		cluster = &hmap->clusters[index];
		for (size_t j = 0; j < cluster->size; j++)
		{
			cell = &cluster->buckets[j];
			if (cell->taken && !strcmp(cell->key, key))
			{
				pair->second = j;
				return (1);
			}
		}
		return (0);
	}
#endif /* ifdef HMAP_DYN_ARRAY */

bucket_t *hmap_find(hmap_t *hmap, char *key)
{

#ifdef HMAP_LLIMPLEMENTATION
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
#else
	t_pair loc;
	if (hmap_find_pair(hmap, key, &loc))
		return &hmap->clusters[loc.first].buckets[loc.second];
#endif /* ifdef HMAP_LLIMPLEMENTATION */
	return (NULL);
}

void hmap_insert(hmap_t *hmap, char *key, void *value, size_t value_size)
{
	bucket_t *cell;
	unsigned long index;

	index = (hmap_hash(key) % hmap->cap);
#ifdef HMAP_LLIMPLEMENTATION
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
#else
	bucket_cluster_t *cluster;
	t_pair			 *vacant_slot;

	cluster = &hmap->clusters[index];
	vacant_slot = stack_find(hmap->vacant, index);
	if (vacant_slot)
	{
		cell = &cluster->buckets[vacant_slot->second];
		stack_remove(hmap->vacant, vacant_slot); // Remove the vacant slot from the stack
	}
	else {
		cluster_expand(cluster);
		cell = &cluster->buckets[cluster->size++];
	}
#endif
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
	// TODO: the delete is different for a linked list impl and an Array impl
	bucket_t *cell;
#ifdef HMAP_DYN_ARRAY
	t_pair loc;
	if (!hmap_find_pair(hmap, key, &loc))
		return ;
	cell = &hmap->clusters[loc.first].buckets[loc.second];
	stack_push_back(hmap->vacant, loc);
#else
	cell = hmap_find(hmap, key);
#endif /* ifdef HMAP_DYN_ARRAY */
	if (cell)
	{
		free(cell->key);
		free(cell->value);
		memset(cell, 0, sizeof(*cell));
		hmap->size--;
	}
}

void hmap_foreach(hmap_t *hmap, void (*func)(bucket_t *cell))
{
	bucket_t *cell;

#ifdef HMAP_LLIMPLEMENTATION
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
#else
	for (size_t i = 0; i < hmap->cap; ++i)
	{
		for (size_t j = 0; j < hmap->clusters[i].size; j++)
		{
			cell = &hmap->clusters[i].buckets[j];
			if (cell->taken)
				func(cell);
		}
	}
#endif // HMAP_LLIMPLEMENTATION
}

void hmap_clear(hmap_t *hmap)
{
	bucket_t *cell;
	#ifdef HMAP_LLIMPLEMENTATION
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
					hmap->size--;
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
				hmap->size--;
			}
		}
	#else
		for (size_t i = 0; i < hmap->cap; ++i)
		{
			for (size_t j = 0; j < hmap->clusters[i].size; j++)
			{
				cell = &hmap->clusters[i].buckets[j];
				if (cell->taken)
				{
					free(cell->key);
					free(cell->value);
					hmap->size--;
				}
				memset(cell, 0, sizeof(*cell));
			}
			hmap->clusters[i].size = 0;
		}

		hmap->vacant->size = 0;
	#endif // HMAP_LLIMPLEMENTATION
}

char *get_impl_desc(void)
{
	#ifdef HMAP_LLIMPLEMENTATION
		return "Linked List";
	#else
		return "Array";
	#endif /* ifdef HMAP_LLIMPLEMENTATION */
}
