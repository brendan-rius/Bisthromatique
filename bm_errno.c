/*
** bm_errno.c for Bistromathique in /home/rius_b/rendu/Bistromathique
** 
** Made by brendan rius
** Login   <rius_b@epitech.net>
** 
** Started on  Tue Oct 28 08:47:48 2014 brendan rius
** Last update Tue Oct 28 13:34:08 2014 brendan rius
*/

#include "bm_errno.h"

char	*bm_get_error(t_rcode code)
{
  if (code == MISMATCHED_P)
    return ("Mismatched parenthesis\n");
  else
    return ("Unknown error\n");
}