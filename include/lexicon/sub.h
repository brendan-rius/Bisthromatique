/*
** sub.h for Bistromathique in /home/rius_b/rendu/Bistromathique
** 
** Made by brendan rius
** Login   <rius_b@epitech.net>
** 
** Started on  Mon Oct 27 15:54:43 2014 brendan rius
** Last update Tue Oct 28 15:26:30 2014 brendan rius
*/

#ifndef SUB_H_
# define SUB_H_

# include "bm_errno.h"

struct s_token;

t_rcode	action_sub_compute(struct s_base *base,
			   struct s_token *n1,
			   struct s_token *n2,
			   struct s_token *res);

t_rcode	action_sub(struct s_base *base,
		   struct s_token *n1,
		   struct s_token *n2,
		   struct s_token *res);

t_rcode	extract_sub(char *,
		    struct s_token *,
		    struct s_base *,
		    struct s_token *);

t_rcode	action_negate(struct s_base *base,
		      struct s_token *n,
		      struct s_token *res);

t_rcode	extract_negate(char *c,
		       struct s_token *token);

#endif /* !SUB_H_ */
