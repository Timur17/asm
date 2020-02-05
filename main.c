#include "asm.h"

void	init(t_parce *pr)
{
	ft_bzero(pr, sizeof(pr));
	pr->row = 0;
	pr->comment = NULL;
	pr->name	= NULL;
}

t_code	*init_code()
{
	t_code	*code;

	if (!(code = (t_code *)ft_memalloc(sizeof(t_code))))
		ft_error("ERROR malloc");
	code->label = NULL;
	code->wait_code = 0;
	code->cmnd = NULL;
	code->ar1 = NULL;
	code->ar2 = NULL;
	code->ar3 = NULL;
	return (code);
}

void		ft_error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

int main(int ac, char **av) 
{
	t_parce			pr;

	init(&pr);
	if (ac != 2)
		ft_error("Usage : ./asm <filename>");
	if ((pr.fd = open(av[1], O_RDONLY)) < 0)
		ft_error("Open error");
	parce(&pr);
	if (close(pr.fd) < 0)
		ft_error("Close error");
	return (0);
}