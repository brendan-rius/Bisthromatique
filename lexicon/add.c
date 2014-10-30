/*
** add.c for Bistromathique in /home/rius_b/rendu/Bistromathique
** 
** Made by brendan rius
** Login   <rius_b@epitech.net>
** 
** Started on  Mon Oct 27 15:55:31 2014 brendan rius
** Last update Thu Oct 30 13:42:47 2014 brendan rius
*/

#include <stdio.h>
#include <stdlib.h>
#include "bm_errno.h"
#include "tokenizer.h"
#include "bm_base.h"
#include "my.h"

void			reorder_tokens(struct s_token **n1,
				       struct s_token **n2)
{
  struct s_token	*tmp;

  if ((*n2)->size <= (*n1)->size)
    return;
  tmp = *n1;
  *n1 = *n2;
  *n2 = tmp;
}

int	get_value_at_index(struct s_base *base, char *number, int index)
{
  if (index >= 0)
    return (base->array[(unsigned char) number[index]]);
  else
    return (0);
}

t_rcode	action_add(struct s_base *base,
		   struct s_token *n1,
		   struct s_token *n2,
		   struct s_token *res)
{
  int	cursor;
  int	shift;
  int	carry;
  int	tmp;

  reorder_tokens(&n1, &n2);
  if (n1->string_value[0] == '0')
    res->size = n1->size;
  else
    res->size = n1->size + 1;
  if (!(res->string_value = malloc(res->size + 1)))
    return (COULD_NOT_MALLOC);
  res->string_value[res->size] = '\0';
  shift = n1->size - n2->size;
  cursor = n1->size - 1;
  carry = 0;
  while (cursor >= 0 || shift)
    {
      tmp = (get_value_at_index(base, n1->string_value, cursor) +
	     get_value_at_index(base, n2->string_value, cursor - shift) +
	     carry);
      if (tmp >= base->size)
	carry = 1;
      else
	carry = 0;
      res->string_value[cursor + 1] = base->string[tmp % base->size];
      --cursor;
    }
  if (!carry)
    res->string_value[0] = '0';
  return (OK);
}

unsigned int	extract_add(char *c, t_token *token, t_token *previous)
{
  if (!c)
    return (0);
  if (c[0] == '+' &&
      (previous &&
       (previous->type == RPARENTHESIS || previous->type == NUMBER)))
    {
      token->type = OPERATOR;
      token->operator.action = &action_add;
      token->operator.precedence = 5;
      token->size = 1;
      return (token->size);
    }
  return (0);
}
