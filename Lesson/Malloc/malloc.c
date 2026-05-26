#include <unistd.h>
#include <sys/types.h>

struct block_meta
{
    size_t size;
    struct block_meta *next;
    int free;
};

#define META_SIZE sizeof(struct block_meta)

void *global_base = NULL;

struct block_meta *find_free_block(struct block_meta **last, size_t size)
{

    struct block_meta *current = global_base;

    while (current != NULL)
    {

        if (current->free == 1 && current->size >= size)
        {
            return current;
        }

        *last = current;

        current = current->next;
    }

    return NULL;
}

struct block_meta *request_space(struct block_meta *last, size_t size)
{
    struct block_meta *block;
    block = sbrk(0);

    void *request = sbrk(size + META_SIZE);

    if (request == (void *)-1)
    {
        return NULL;
    }

    if (last)
    {

        last->next = block;
    }

    block->size = size;
    block->next = NULL;
    block->free = 0;

    return block;
}

void *my_malloc(size_t size)
{
    struct block_meta *block;

    if (size <= 0)
    {
        return NULL;
    }

    if (global_base == NULL)
    {

        block = request_space(NULL, size);

        if (!block)
        {
            return NULL;
        }

        global_base = block;
    }

    else
    {
        struct block_meta *last = global_base;

        block = find_free_block(&last, size);

        if (!block)
        {
            block = request_space(last, size);
            if (!block)
            {
                return NULL;
            }
        }
        else
        {
            block->free = 0;
        }
    }

    return (block + 1);
}

void my_free(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    struct block_meta *block = (struct block_meta *)ptr - 1;

    block->free = 1;
}