#include "asm.h"


int		check_command(t_parce *pr)
{
	if (!(ft_strncmp(pr->line + *pr->i, LIVE, 4)) ||
	!(ft_strncmp(pr->line + *pr->i, ZJMP, 4)) || !(ft_strncmp(pr->line + *pr->i, FORK, 4))
	|| !(ft_strncmp(pr->line + *pr->i, LLDI, 4)))
		return (4);
	if (!(ft_strncmp(pr->line + *pr->i, ADD, 3)) || !(ft_strncmp(pr->line + *pr->i, SUB, 3))
	|| !(ft_strncmp(pr->line + *pr->i, AND, 3)) || !(ft_strncmp(pr->line + *pr->i, XOR, 3))
	|| !(ft_strncmp(pr->line + *pr->i, LDI, 3)) || !(ft_strncmp(pr->line + *pr->i, STI, 3))
	|| !(ft_strncmp(pr->line + *pr->i, LLD, 3)) || !(ft_strncmp(pr->line + *pr->i, AFF, 3)))
		return (3);
	if (!(ft_strncmp(pr->line + *pr->i, LD, 2)) || !(ft_strncmp(pr->line + *pr->i, ST, 2))
	|| !(ft_strncmp(pr->line + *pr->i, OR, 2)))
		return (2);
	if (!(ft_strncmp(pr->line + *pr->i, LFORK, 5)))
		return (5);
	return (0);
}

void	add_command(t_parce *pr)
{
	int		i;
	t_code	*new;
	t_code	*temp;
	
	i = check_command(pr);
	new = init_code();
	new->cmnd = ft_strsub(pr->line, *pr->i, i);
	new->l_conect = pr->cnt++;
	*pr->i = *pr->i + i;
	check_arg(pr, new);
	creat_list(pr, new);
}