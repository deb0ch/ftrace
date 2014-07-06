/*
** graph.h for ftrace in /home/max/e-wip/ftrace
** 
** Made by bourge_i
** Login   <max@epitech.net>
** 
** Started on  Fri Jun 27 17:29:47 2014 bourge_i
** Last update Sun Jul  6 16:31:10 2014 bourge_i
*/

#ifndef _GRAPH_H_
# define _GRAPH_H_

# include <stdio.h>

typedef struct          s_graph_node
{
  int                   id;
  int                   parent_id;
  char                  *fct_name;
  struct s_graph_node   *next;
}                       t_graph_node;

typedef struct  s_graph
{
  t_graph_node          *current;
  t_graph_node          *graph_list;
  FILE                  *graph_file;
  t_graph_node          *(*add_node)(struct s_graph *, char *,
                                     t_graph_node *, int);
  void                  (*pop)(struct s_graph *);
  int                   (*close_graph)(struct s_graph *);
}                       t_graph;

t_graph*                graph_init();
int                     create_graph(t_graph *);
int                     print_graph(t_graph *);
int                     free_graph(t_graph *);
char                    *find_parent_name(t_graph *, t_graph_node *);
t_graph_node            *find_parent_node(t_graph *, t_graph_node *);

#endif /* _GRAPH_H_ */









