#include "asm.h"

void	printt_code(t_code *cd)
{
	t_code	*temp;

	temp = cd;
	while (temp)
	{
		printf("%s %s \n", temp->label, temp->cmnd);
		temp = temp->next;
	}
}	

void	creat_list(t_parce *pr, t_code *new)
{
	t_code	*temp;

	temp = pr->cd;
	if (pr->cd == NULL)
		pr->cd = new;
	else 
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	add_label(t_parce *pr)
{
	int		i;
	t_code	*new;
	
	i = check_label(pr);
	new = init_code();
	new->label = ft_strsub(pr->line, *pr->i, i);
	new->wait_code = 1;
	creat_list(pr, new);
	*pr->i =  i + 1;
	ft_skip_space(pr);
	if (pr->line[*pr->i])
		{
			if (check_command(pr) == 0)
			{
				printf("%s %d %d\n", "ERORR", pr->row, *pr->i);
				exit (0);
			}
			else
				add_command(pr);
		}
}

int		check_label(t_parce *pr)
{
	int i;

	i = *pr->i;
	while (ft_strchr(LABEL_CHARS, pr->line[i]))
		i++;
	if (pr->line[i] == LABEL_CHAR && i != *pr->i)	
		return (i);
	return (0); 
}