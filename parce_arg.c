#include "asm.h"

void		add_arg(t_code *new, char *str, int *arg)
{
	if (*arg == 1)
		new->ar1 = str;
	if (*arg == 2)
		new->ar2 = str;
	if (*arg == 3)
		new->ar3 = str;
	(*arg)++;
}

void		skip_separator(t_parce *pr)
{
	int		i;

	i = *pr->i + 1;

	while (ft_space(pr->line[i]))
		i++;

	if (pr->line[i] != '\0')
		(*pr->i)++;
}

void		check_reg(t_parce *pr, int *arg, t_code *new)
{
	char		*str;
	int			i;
	int			num;
	int			len;

	num = 0;
	len = 0;
	i = *pr->i;
	(*pr->i)++;
	while (ft_isdigit(pr->line[(*pr->i)]))
	{
		(*pr->i)++;
		len++;
	}
	if (len > 2 || len == 0)
	 		ft_error("ERORR in argument 2");
	str = ft_strsub(pr->line, i + 1, len);
	num = ft_atoi(str);
	if (num <= 0 || num > 16)
			ft_error("ERORR in argument 3");
	free (str);
	str = ft_strsub(pr->line, i, len + 1);
	add_arg(new, str, arg);
	ft_skip_space(pr);
	if (pr->line[*pr->i] == SEPARATOR_CHAR)
		skip_separator(pr);
}

char		*add_arg_lable(t_parce *pr)
{
	int		i;
	char	*str;
	int		len;

	i = *pr->i;
	len = 0;
	while (ft_strchr(LABEL_CHARS, pr->line[*pr->i]))
	{
		len++;
		(*pr->i)++;
	}
	str = ft_strsub(pr->line, i, len);
	return (str);
}

char		*add_arg_digit(t_parce *pr)
{
	int num;
	char	*str;
	int		i;

	num = 0;
	i = *pr->i;
	while(ft_isdigit(pr->line[*pr->i]))
	{
		num++;
		(*pr->i)++;
	}
	if (num == 0)
	
			ft_error("ERORR in argument 1");
	str = ft_strsub(pr->line, i, num);
	return (str);
}

void		check_dir(t_parce *pr, int *arg, t_code *new)
{
	char	*str;

	(*pr->i)++;
	if (pr->line[*pr->i] == LABEL_CHAR)
	{
		(*pr->i)++;
		str = add_arg_lable(pr);
	}
	else
		str = add_arg_digit(pr);
	add_arg(new, str, arg);
	ft_skip_space(pr);
	if (pr->line[*pr->i] == SEPARATOR_CHAR)
		skip_separator(pr);
}


void		check_arg(t_parce *pr, t_code *new)
{
	int		*arg;
	int		temp;

	temp = 1;

	arg = &temp;
	while (pr->line[*pr->i])
	{
		ft_skip_space(pr);
		if (pr->line[*pr->i] == 'r')
			check_reg(pr, arg, new);
		 else if (pr->line[*pr->i] == '%')
		   	check_dir(pr, arg, new);
		else if (pr->line[*pr->i] != '\0')
			{
				printf("row %d  %d\n", pr->row, *pr->i);
				printf("test_=%s\n", pr->line + *pr->i);
				ft_error("ERORR in argument 5");
			}
	}
	printf("test%d\n", *pr->i);
	printf("arg1=%s\n", new->ar1);
	printf("arg2=%s\n", new->ar2);
	printf("arg3=%s\n", new->ar3);
	exit (0);
}