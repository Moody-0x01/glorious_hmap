#include <hmap.h>

void	stack_push_back(t_stack *stack, t_pair  item)
{
	stack_expand(stack);
	stack->items[stack->size].first = item.first;
	stack->items[stack->size].second = item.second;
	stack->size++;
}

t_pair *stack_pop(t_stack *stack)
{
	if (stack && stack->size)
		return (&stack->items[--stack->size]);
	return (NULL);
}

t_pair *stack_peek(t_stack *stack)
{
	if (stack && stack->size)
		return (&stack->items[-1 + stack->size]);
	return (NULL);
}

void	stack_remove(t_stack *stack, t_pair	*element)
{
	if (!element || !stack->size || element < stack->items)
		return ;

	size_t index;
	index = (element - stack->items); // Get the index of the element to be removed
    memmove(element, (element + 1), (stack->size - index - 1)); // Move
	stack->size--;
}
