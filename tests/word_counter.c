#include <hmap.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

long    get_timestamp(void);
char *read_file(int fd);
char *slurp_file(char *file);

void print(bucket_t *cell)
{
	printf("%s => %zu\n", cell->key, *(size_t*)cell->value);
}

int main(int ac, char **av)
{

	hmap_t *mp = new_hmap(HMAP_INIT_CAP);
	if (ac != 2)
	{
		fprintf(stderr, "[ERROR] This program accepts only 2 arguments only.\n");
		fprintf(stderr, "[USAGE] %s <file_name_to_use>\n", av[0]);
		return (1);
	}
	char *data = slurp_file(av[1]);
	long s = get_timestamp();
    char *word = strtok(data, "\n\t ");
	while (word)
	{
		size_t *ptr;
		size_t count = 0;
		ptr = hmap_get(mp, word);
		if (ptr) // FOUND
		{
			(*ptr)++;
		} else {
			count = 1;
			hmap_insert(mp, word, &count, sizeof(size_t));
		}
		word = strtok(NULL, "\n\t ");
	}
	hmap_foreach(mp, print);
	destroy_hmap(mp);
	free(data);
	printf("[ %s ] Took: %ldms\n", get_impl_desc(), get_timestamp() - s);
	return (0);
}

static long lget_file_size(int Stream) 
{
	long size = lseek(Stream, 0L, SEEK_END);
	lseek(Stream, 0L, SEEK_SET);
	return size;
}

char *read_file(int fd)
{
	long size = lget_file_size(fd);
	char *data = malloc(size + 1);
	read(fd, data, size);
	data[size] = 0;
	return (data);
}

char *slurp_file(char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("slurp_file");
		return (NULL);
	}
	char *data = read_file(fd);
	close(fd);
	return (data);
}

long    get_timestamp(void)
{
        struct timeval  tv;

        gettimeofday(&tv, NULL);
        return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
