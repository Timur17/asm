#include "asm.h"

void						print_line(t_list *list)
{
	t_list		*temp;

	temp = list;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}

t_list			*init_list(char *str)
{
	t_list	*new;

	if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		ft_error("ERROR malloc");
	new->content = str;
	new->content_size = 0;
	return (new);
}			


void			ft_add_line(t_parce *pr)
{
	t_list		*temp;
	t_list		*new;
	static int			i;

	new = init_list(pr->line);  
	temp = pr->list;
	if (pr->list == NULL)
		pr->list = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int				read_file(t_parce *pr)
{
	int			n;

	if ((n = gnl(pr->fd, &pr->line)) == -1)
		ft_error("Error reading file");
	pr->row++;
	if (n > 0)
		ft_add_line(pr);
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
		ft_error_pos("ERROR: unexpected symbol", pr->row, *pr->i);
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
		ft_error("ERROR: miss ends quotes in name or comment");
	return(str);
}

char	*add_name_comment(t_parce *pr)
{
	char *str;

	ft_skip_space(pr);
	
	if (pr->line[*pr->i] == '\"')
		str = ft_search_end(pr);
	else
		ft_error_pos("EROOR: miss quotes", pr->row, *pr->i);
	return (str);
}

char	*add_(t_parce *pr, char *dst, int d, int len)
{
	char	*str;
	int		length;

	*pr->i = *pr->i + d;
	if(!(*dst))
		str = add_name_comment(pr);	
	else if (d == 5)
		ft_error_pos("ERROR: unnecessary name", pr->row, -1);
	else
		ft_error_pos("ERROR: unnecessary comment", pr->row, -1);
	if ((length = (ft_strlen(str)) > len) && len == PROG_NAME_LENGTH)
		ft_error_pos("ERROR: too big length of name", pr->row, -1);
	else if ((length = (ft_strlen(str)) > len) && len == COMMENT_LENGTH)
		ft_error_pos("ERROR: too big length of comment", pr->row, -1);
	return (str);
}

void		skip_comment(t_parce *pr)
{
	while (pr->line[*pr->i])
		(*pr->i)++;
}

void	parce_name_comment(t_parce *pr, header_t *head)
{
	int		i;

	while (read_file(pr))
	{
		i = 0;
		pr->i = &i;
		ft_skip_space(pr);
		if (pr->line[*pr->i] == COMMENT_CHAR || pr->line[*pr->i] == '\0')
			continue ;
		else if (ft_strncmp(pr->line + *pr->i, NAME_CMD_STRING, 5) == 0)
			ft_strcat(head->prog_name, add_(pr, head->prog_name, 5, PROG_NAME_LENGTH));
		else if (ft_strncmp(pr->line + *pr->i, COMMENT_CMD_STRING, 8) == 0)
		 	ft_strcat(head->comment, add_(pr, head->comment, 8, COMMENT_LENGTH));
		else if (check_label(pr))
			add_label(pr);
		 else if (check_command(pr))
		 	add_command(pr);
		else if (pr->line[*pr->i] != '\0')
			ft_error_pos("ERROR: Unexpected symvol", pr->row, *pr->i);
	}
	ft_error_head(head);
}

void	parce(t_parce *pr, header_t *head)
{	
	parce_name_comment(pr, head);
	printf ("header name=%s\n", head->prog_name);
	printf ("header comment=%s\n", head->comment);
	printt_code(pr->cd);
//	print_line(pr->list);
}