#include <hmap.h>

void	stack_expand(t_stack *stack)
{
	if (stack->size >= stack->cap)
	{
		stack->cap *= VEC_GROWTH_FAC;
		stack->items = realloc(stack->items, stack->cap * sizeof(*(stack->items)));
	}
}

t_stack	*stack_construct(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(*stack));
	stack->items = malloc(VEC_INIT_CAP * sizeof(*(stack->items)));
	stack->cap = VEC_INIT_CAP;
	stack->size = 0;
	return (stack);
}

void	stack_destroy(t_stack *stack)
{
	if (stack)
	{
		if (stack->items)
			free(stack->items);
		free(stack);
	}
}

t_pair *stack_find(t_stack *stack, size_t needle)
{
	for (size_t k = 0; k < stack->size; ++k)
	{
		if (stack->items[k].first == needle)
			return (stack->items + k);
	}
	return (NULL);
}
