# ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include "op.h"
# include "command.h"

# define DIR			"DIR"
# define IND			"IND"
# define REG			"REG"

typedef struct			s_code
{
	int					l_conect;
	char				*label;
	char				*cmnd;
	char				*ar1;
	char				*ar2;
	char				*ar3;
	char				*type_ar1;
	char				*type_ar2;
	char				*type_ar3;
	struct s_code		*next;
}						t_code;

typedef struct              s_parce
{
	int						zero;
	int						cnt;
	int						fd;
	char					*line;
	int						row;
	int						*i;
	char					*leak;
	t_list					*list;
	t_code					*cd;
}							t_parce;

void						parce(t_parce *pr, header_t *head);
void						ft_error(char *str);
void						ft_error_pos(char *str, int row, int col);
void						ft_error_head(header_t *head);
int							check_label(t_parce *pr);
int							check_command(t_parce *pr);
void						check_arg(t_parce *pr, t_code *new);
void						add_label(t_parce *pr);
void						add_command(t_parce *pr);
t_code						*init_code();
void						creat_list(t_parce *pr, t_code *new);
void						ft_skip_space(t_parce *pr);

void						skip_comment(t_parce *pr);
int							ft_skip_comment(t_parce *pr);



void						print_line(t_list *list);




void	printt_code(t_code *cd);



# endif