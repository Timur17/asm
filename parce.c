#include "asm.h"


int				read_file(t_parce *pr)
{
	int			n;


	if ((n = gnl(pr->fd, &pr->line)) == -1)
		ft_error("Error reading");
	pr->row++;
	return (n);
}

void	ft_skip_space(t_parce *pr)
{
	while (ft_space(pr->line[*pr->i]))
		(*pr->i)++;
}

int			ft_skip_comment(t_parce *pr)
{
	if (pr->line[*pr->i] == '#')
			return (1);
	return (0);
}

void	valid_end_line(t_parce *pr, int i)
{
	i++;
	while (ft_space(pr->line[i]))
		i++;
	if (pr->line[i] && pr->line[i] != '#')
	{
		printf("test %s\n", pr->line + i);
		printf("row %d i %d\n", pr->row, i);
		ft_error("ERORR unexpected symbol in the end");
	}
}

char	*ft_search_end2(t_parce *pr, char *str)
{
	char	*end;
	char	*temp;

	while(read_file(pr) > 0)
	{
		if ((end = ft_strchr(pr->line, '\"')))
		{
			valid_end_line(pr, end - pr->line);
			temp = ft_strsub(pr->line, 0, end - pr->line);
			pr->leak = str;
			str = ft_strjoin(str, temp);
			free (pr->leak);
			free (temp);
			return (str);
		}
	pr->leak = str;
	str = ft_strjoin(str, pr->line);
	free (pr->leak);
	}
	return (NULL);
}

char	*ft_search_end(t_parce *pr)
{
	int		begin;
	char	*str;
	

	begin = ++(*pr->i);
	str = NULL;
	while(pr->line[*pr->i] != '\"' && pr->line[*pr->i] != '\0')
		(*pr->i)++;
	str = ft_strsub(pr->line, begin, *pr->i - begin);
	if (pr->line[*pr->i] == '\"')
	{
		valid_end_line(pr, *pr->i);
		return(str);
	}
	if ((str = ft_search_end2(pr, str)) == NULL)
	{
		printf("row %d i %d\n", pr->row, *pr->i);
		ft_error("Error in whith \"");
	}
	return(str);
}

char	*add_name_comment(t_parce *pr)
{
	char *str;

	ft_skip_space(pr);
	
	if (pr->line[*pr->i] == '\"')
		str = ft_search_end(pr);
	else
		{
			printf("row %d i %d\n", pr->row, *pr->i);
			ft_error("Error in whith \"");
		}
return (str);
}

char	*add_(t_parce *pr, char *dst, int d, int len)
{
	char	*str;
	int		length;

	*pr->i = *pr->i + d;
	if(!(*dst))
		str = add_name_comment(pr);	
	else
		ft_error("ERROR: too much name or comment");
	if ((length = (ft_strlen(str)) > len))
		ft_error("ERROR: too big length of name or comment");
	return (str);
}

int		skip_comment(t_parce *pr)
{
	int zero;

	zero = 0;
	if (pr->line[*pr->i] != '#')
		return (0);
	read_file(pr);
	pr->i = &zero;
	return (1);

}

void	parce_name_comment(t_parce *pr, header_t *head)
{
	int		i;

	while (read_file(pr))
	{
		i = 0;
		pr->i = &i;
		ft_skip_space(pr);
		if (pr->line[*pr->i] == '#')
			ft_skip_comment(pr);
		else if (pr->line[*pr->i] == '\0')
			continue ;
		else if (ft_strncmp(pr->line + *pr->i, NAME_CMD_STRING, 5) == 0)
			ft_strcat(head->prog_name, add_(pr, head->prog_name, 5, PROG_NAME_LENGTH));
		else if (ft_strncmp(pr->line + *pr->i, COMMENT_CMD_STRING, 8) == 0)
			ft_strcat(head->comment, add_(pr, head->comment, 8, COMMENT_LENGTH));
		else if (check_label(pr))
			add_label(pr);
		else if (check_command(pr))
			add_command(pr);
		else
		{
			printf("row %d and collum %d\n", pr->row, *pr->i);
			ft_error("Unexpected symvol in row %d");
		}
	}
		if (!(*head->prog_name))
			ft_error("EROOR in name");
		if (!(*head->comment))
			ft_error("EROOR in comment");
}

void	parce(t_parce *pr, header_t *head)
{	
	parce_name_comment(pr, head);
	read_file(pr);
	printf ("header name=%s\n", head->prog_name);
	printf ("header comment=%s\n", head->comment);
	printf ("line=%s\n", pr->line);
	printt_code(pr->cd);
}