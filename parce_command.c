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

t_code			*check_wait_label(t_parce *pr)
{
	t_code	*temp;

	temp = pr->cd;
	while (temp)
	{
		if (temp->wait_code == 1)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	add_cmnd(t_parce *pr, t_code *temp, int i)
{
	while ((temp = check_wait_label(pr)))
	{
		temp->cmnd = ft_strsub(pr->line, *pr->i, i);
		temp->wait_code = 0;
	}
}

void	add_command(t_parce *pr)
{
	int		i;
	t_code	*new;
	t_code	*temp;
	
	i = check_command(pr);
//	printf("%s\n", pr->line + *pr->i + i);
	if ((temp = check_wait_label(pr)))
		add_cmnd(pr, temp, i);
	//	while ((temp = check_wait_label(pr)))
	//			temp->cmnd = ft_strsub(pr->line, *pr->i, i);
	else
	{
		new = init_code();
		new->cmnd = ft_strsub(pr->line, *pr->i, i);
		creat_list(pr, new);
	}
}