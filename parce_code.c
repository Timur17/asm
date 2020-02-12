#include "asm.h"

void	printt_code(t_code *cd)
{
	t_code	*temp;

	temp = cd;
	while (temp)
	{
		printf("%s %s %d\n", temp->label, temp->cmnd, temp->l_conect);
		printf("ar1=%s ar2=%s ar3=%s\n", temp->ar1, temp->ar2, temp->ar3);
		printf("t_ar1=%s t_ar2=%s t_ar3=%s\n", temp->type_ar1, temp->type_ar2, temp->type_ar3);
		printf("-------\n");
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
	new->l_conect = pr->cnt;
	creat_list(pr, new);
	*pr->i =  i + 1;
	ft_skip_space(pr);
	if (pr->line[*pr->i] && pr->line[*pr->i] != COMMENT_CHAR)
		{
			if (check_command(pr) == 0)
				ft_error_pos("ERROR: Unexpected symvol after label", pr->row, *pr->i);
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