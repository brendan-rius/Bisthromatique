/*
** add.c for Bistromathique in /home/rius_b/rendu/Bistromathique
** 
** Made by brendan rius
** Login   <rius_b@epitech.net>
** 
** Started on  Mon Oct 27 15:55:31 2014 brendan rius
** Last update Sun Nov  9 20:58:02 2014 Louis Person
*/

#include <stdlib.h>
#include "boolean.h"
#include "bm_errno.h"
#include "bm_lexicon_utils.h"
#include "tokens.h"
#include "bm_base.h"
#include "my.h"

t_rcode	action_unary_plus(t_base *base,
			  t_token *n,
			  t_token *res)
{
  *res = *n;
  return (OK);
}

t_rcode		action_add_compute(t_base *base,
				   t_token *n1,
				   t_token *n2,
				   t_token *res)
{
  int		carry;
  int		cursor;
  int		shift_n1_n2;
  int		tmp;
  t_rcode	ret;

  if (n2->size > n1->size)
    reorder_tokens(&n1, &n2);
  if ((ret = malloc_token_dynamically(res, n1->size + 1)) != OK)
    return (ret);
  res->string_value[0] = base->string[0];
  carry = 0;
  cursor = n1->size - 1;
  shift_n1_n2 = n1->size - n2->size;
  while (cursor >= 0 || carry)
    {
      tmp = (get_value_at_index(base, n1->string_value, cursor) + carry +
	     get_value_at_index(base, n2->string_value, cursor - shift_n1_n2));
      carry = tmp >= base->size ? 1 : 0;
      res->string_value[cursor-- + 1] = base->string[tmp % base->size];
    }
  clean_number_str(base, res);
  return (OK);
}

t_rcode		action_add(t_base *base,
			   t_token *n1,
			   t_token *n2,
			   t_token *res)
{
  t_rcode	ret;

  if (n1->sign == NEGATIVE && n2->sign == POSITIVE)
    {
      n1->sign = POSITIVE;
      if ((ret = action_sub(base, n1, n2, res)) != OK)
	return (ret);
      res->sign = res->sign == NEGATIVE ? POSITIVE : NEGATIVE;
      return (OK);
    }
  if (n1->sign == POSITIVE && n2->sign == NEGATIVE)
    {
      n2->sign = POSITIVE;
      if ((ret = action_sub(base, n1, n2, res)) != OK)
	return (ret);
      return (OK);
    }
  if (n1->sign == NEGATIVE && n2->sign == NEGATIVE)
      res->sign = NEGATIVE;
  if ((ret = action_add_compute(base, n1, n2, res)) != OK)
    return (ret);
  bm_free_token(n1);
  bm_free_token(n2);
  return (OK);
}

t_rcode	extract_add(char *c,
		    t_token *token,
		    t_base *base,
		    t_token *previous)
{
  if (!c)
    return (NULL_REFERENCE);
  if (previous &&
      (previous->type == RPARENTHESIS || previous->type == NUMBER))
    {
      token->type = OPERATOR;
      token->operator.action = &action_add;
      token->operator.precedence = 5;
      token->size = 1;
      return (OK);
    }
  else
    {
      token->type = U_OPERATOR;
      token->operator.action = &action_unary_plus;
      token->operator.precedence = 15;
      token->size = 1;
      return (OK);
    }
}
