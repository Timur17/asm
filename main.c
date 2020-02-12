#include "asm.h"

void	init(t_parce *pr)
{
	ft_bzero(pr, sizeof(pr));
	pr->row = 0;
	pr->cnt = 1;
	pr->zero = 0;
	pr->list = NULL;
}

t_code	*init_code()
{
	t_code	*code;

	if (!(code = (t_code *)ft_memalloc(sizeof(t_code))))
		ft_error("ERROR malloc");
	code->label = NULL;
	code->cmnd = NULL;
	code->ar1 = NULL;
	code->ar2 = NULL;
	code->ar3 = NULL;
	code->type_ar1 = NULL;
	code->type_ar2 = NULL;
	code->type_ar3 = NULL;
	return (code);
}

void		init_hd(header_t *head)
{
	ft_bzero(head->prog_name, sizeof(head->prog_name));
	ft_bzero(head->comment, sizeof(head->comment));
}

void		ft_error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

void		ft_error_pos(char *str, int row, int col)
{
	if (col == -1)
		printf("%s at row %d\n", str, row);
	else if (row != 0)
		printf("%s at row %d collum %d\n", str, row, ++col);
	else
		printf("%s\n", str);
	
	exit(EXIT_FAILURE);
}

void		ft_error_head(header_t *head)
{
	if (!(*head->prog_name))
		ft_error("EROOR: lack name");
	if (!(*head->comment))
		ft_error("EROOR: lack comment");
}

int main(int ac, char **av) 
{
	t_parce			pr;
	header_t		head;

	init(&pr);
	init_hd(&head);
	if (ac != 2)
		ft_error("Usage : ./asm <filename>");
	if ((pr.fd = open(av[1], O_RDONLY)) < 0)
		ft_error("Open error");
	parce(&pr, &head);
	if (close(pr.fd) < 0)
		ft_error("Close error");
	return (0);
}