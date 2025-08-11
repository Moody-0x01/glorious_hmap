/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:43:41 by mbouhia           #+#    #+#             */
/*   Updated: 2025/03/24 19:43:41 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
# include <stdlib.h>
#define VEC_GROWTH_FAC 2
#define VEC_INIT_CAP 32

typedef struct t_pair
{
	size_t first;
	size_t second;
} t_pair;

typedef struct s_stack
{
	t_pair  *items;
	size_t	size;
	size_t	cap;
}			t_stack;

t_pair		*stack_find(t_stack *stack, size_t needle);
void		stack_expand(t_stack *vec);
void		stack_push_back(t_stack *vec, t_pair item);
t_stack		*stack_construct(void);
t_pair		*stack_pop(t_stack *stack);
void		stack_destroy(t_stack *stack);
t_pair		*stack_peek(t_stack *stack);
void		stack_remove(t_stack *stack, t_pair	*element);
#endif // !STACK_H
