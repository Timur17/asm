#include "asm.h"

void		must_be_reg_dir(t_parce *pr, t_code *new, int arg)
{
	char *type;

	if (arg == 1)
		type = new->type_ar1;
	else if (arg == 2)
		type = new->type_ar2;
	else
		type = new->type_ar3;

	if (ft_strcmp(REG, type) && ft_strcmp(DIR, type))
	{
		printf("2ERROR: Invalid type of arg - %d at row %d\n", arg, pr->row);
		exit (0);
	}
	printf("arg right %d\n",arg);
}

void		must_be_dir_ind(t_parce *pr, t_code *new, int arg)
{
	char *type;

	if (arg == 1)
		type = new->type_ar1;
	else if (arg == 2)
		type = new->type_ar2;
	else
		type = new->type_ar3;

	if (ft_strcmp(IND, type) && ft_strcmp(DIR, type))
	{
		printf("2ERROR: Invalid type of arg - %d at row %d\n", arg, pr->row);
		exit (0);
	}
	printf("arg right %d\n",arg);
}


void		must_be_reg(t_parce *pr, t_code *new, int arg)
{
	char	*type;

	if (arg == 1)
		type = new->type_ar1;
	else if (arg == 2)
		type = new->type_ar2;
	else
		type = new->type_ar3;
	printf(" here %s %d %d\n", type, arg, pr->row);
	if (ft_strcmp(REG, type))
	{
		printf("1ERROR: Invalid type of arg - %d at row %d\n", arg, pr->row);
		exit (0);
	}
	printf("arg right %d\n", arg);
}

void		must_be_dir(t_parce *pr, t_code *new)
{
	printf(" here %s %d\n", new->type_ar1, pr->row);
	if (ft_strcmp(DIR, new->type_ar1))
	{
		printf("1ERROR: Invalid type of at row %d\n", pr->row);
		exit (0);
	}
}

void		must_be_reg_ind(t_parce *pr, t_code *new, int arg)
{
	char *type;

	if (arg == 1)
		type = new->type_ar1;
	else if (arg == 2)
		type = new->type_ar2;
	else
		type = new->type_ar3;

	if (ft_strcmp(IND, type) && ft_strcmp(REG, type))
	{
		printf("2ERROR: Invalid type of arg - %d at row %d\n", arg, pr->row);
		exit (0);
	}
	printf("arg right %d\n",arg);
}

void		valid_3_args(t_parce *pr, t_code *new, int arg)
{
	printf("%d\n", arg);
	if ((arg == 1 && (!(ft_strcmp(new->cmnd, ADD)) || !(ft_strcmp(new->cmnd, SUB)) 
	|| !(ft_strcmp(new->cmnd, STI)))) 
	|| (arg == 3 && (!(ft_strcmp(new->cmnd, ADD)) || !(ft_strcmp(new->cmnd, SUB))
	|| !(ft_strcmp(new->cmnd, AND)) || !(ft_strcmp(new->cmnd, OR)) || !(ft_strcmp(new->cmnd, XOR)) 
	|| !(ft_strcmp(new->cmnd, LDI)) || !(ft_strcmp(new->cmnd, LLDI)))) 
	|| (arg == 2 && (!(ft_strcmp(new->cmnd, ADD)) || !(ft_strcmp(new->cmnd, SUB)))))
		must_be_reg(pr, new, arg);
	else if ((arg == 2 && (!(ft_strcmp(new->cmnd, LDI)) || !(ft_strcmp(new->cmnd, LLDI)))) 
	|| (arg == 3 && (!(ft_strcmp(new->cmnd, STI)))))
		must_be_reg_dir(pr, new, arg);
}

void		valid_2_args(t_parce *pr, t_code *new, int arg)
{
	if ((arg == 1 && (!(ft_strcmp(new->cmnd, LD)) || !(ft_strcmp(new->cmnd, LLD))))) 
		must_be_dir_ind(pr, new, arg);
	else if ((arg == 2 && (!(ft_strcmp(new->cmnd, LD)) || !(ft_strcmp(new->cmnd, LLD)))) 
	||  (arg == 1 && (!(ft_strcmp(new->cmnd, ST))))) 
		must_be_reg(pr, new, arg);
	else if (arg == 2 && (!(ft_strcmp(new->cmnd, ST))))
		must_be_reg_ind(pr, new, arg);
}

void		valid_arg(t_parce *pr, t_code *new)
{
	if (!(ft_strcmp(new->cmnd, LIVE)) || !(ft_strcmp(new->cmnd, ZJMP)) 
	|| !(ft_strcmp(new->cmnd, FORK)) || !(ft_strcmp(new->cmnd, LFORK))) 
		must_be_dir(pr, new);
	else if (!(ft_strcmp(new->cmnd, AFF)))
		must_be_reg(pr, new, 1);
}

void	check_three_args(t_parce *pr, t_code *new)
{
	if (ft_strcmp(new->cmnd, ADD) && ft_strcmp(new->cmnd, SUB) && ft_strcmp(new->cmnd, AND) 
	&& ft_strcmp(new->cmnd, OR) && ft_strcmp(new->cmnd, XOR) && ft_strcmp(new->cmnd, LDI) 
	&& ft_strcmp(new->cmnd, STI) && ft_strcmp(new->cmnd, LLDI))
		ft_error_pos("ERROR: too much args at", pr->row, -1);
}

void	check_two_args(t_parce *pr, t_code *new)
{
	if (ft_strcmp(new->cmnd, LD) && ft_strcmp(new->cmnd, ST) && ft_strcmp(new->cmnd, LLD))
		ft_error_pos("ERROR: too much args at", pr->row, -1);
}

void	check_one_arg(t_parce *pr, t_code *new)
{
	if (ft_strcmp(new->cmnd, LIVE) && ft_strcmp(new->cmnd, ZJMP) && ft_strcmp(new->cmnd, FORK) 
	&& ft_strcmp(new->cmnd, LFORK) && ft_strcmp(new->cmnd, AFF))
		ft_error_pos("ERROR: too much args at", pr->row, -1);
}



void		valid_args(t_parce *pr, t_code *new)
{
	if (new->ar1 && new->ar2 && new->ar3)
	{
		check_three_args(pr, new);
		valid_3_args(pr, new, 1);
		valid_3_args(pr, new, 2);
		valid_3_args(pr, new, 3);
	}
	else if (new->ar1 && new->ar2)
	{
		check_two_args(pr, new);
		valid_2_args(pr, new, 1);
		valid_2_args(pr, new, 2);
	}
	else
	{
		check_one_arg(pr, new);
		valid_arg(pr, new);
	}

}


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
	valid_args(pr, new);
	creat_list(pr, new);
}