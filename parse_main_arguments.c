# include "includes/cube3d.h"

int check_screen_arg(t_mlx *mlx, char *buffer)
{
  int i;
  
  i = 0;
  while(!ft_isdigit(buffer[i]))
    i++;
  mlx->args.screen_w = ft_atoi(&buffer[i]);
  while(ft_isdigit(buffer[i]))
    i++;
  mlx->args.screen_h = ft_atoi(&buffer[i]);
  if (mlx->args.screen_h <= 0 || mlx->args.screen_w <= 0)
		return (0);
  if (mlx->args.screen_h >= MAX_SCREEN_H)
    mlx->args.screen_h = MAX_SCREEN_H;
  if  (mlx->args.screen_w >= MAX_SCREEN_W)
    mlx->args.screen_w = MAX_SCREEN_W;
  return (SUCCESS);
}

t_map	*ft_lstn(char *content)
{
	t_map	*new_elem;

	if (!(new_elem = malloc(sizeof(t_map))))
		return (0);
	new_elem->line = ft_strdup(content);
	new_elem->next = 0;
	return (new_elem);
}

t_map	*ft_lstl(t_map *lst)
{
	t_map	*last_lst;

	last_lst = lst;
	if (!lst)
		return (0);
	while (lst->next)
	{
		last_lst = lst;
		lst = lst->next;
	}
	if (!lst->next)
		return (lst);
	return (last_lst);
}

void	ft_lstadd_b(t_map **lst, t_map *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	ft_lstl(*lst)->next = new;
	new->next = 0;
}

int map_to_list(t_mlx *mlx, char *buffer)
{
    // printf("%s\n", buffer);
    ft_lstadd_b(&mlx->args.map, ft_lstn(buffer)); 
    return (SUCCESS);
}

int check_arguments(t_mlx *mlx, char *buffer)
{
    if (buffer[0] == '\0' || buffer[0] ==  '\n')
      return (SUCCESS);
    if (buffer[0] == 'R')
      if (check_screen_arg(mlx, buffer) != SUCCESS)
        return (ERROR); 
    if (ft_strchr("NSWE", buffer[0]))
      if (check_texture_arg(mlx, buffer) != SUCCESS)
        return (ERROR);  
    if (ft_strchr("FC", buffer[0]))
      if (check_fc_arg(mlx, buffer) != SUCCESS)
        return (ERROR);
    if (ft_strchr(buffer, '1') && !ft_strchr("RNSEWFC", buffer[0]))
      if (map_to_list(mlx, buffer) != SUCCESS)
        return (ERROR);
    if (!ft_isdigit(buffer[0]) && !ft_strchr("RNSEWFC ", buffer[0]))
      return (ERROR);
    return (SUCCESS);
}