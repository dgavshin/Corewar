#include "corewar.h"

void	set_code(t_corewar *core)
{
	t_player	*p;
	t_list		*lst;
	int			i;

	i = 0;
	lst = core->players->head;
	ft_printf("-------\n");
	while (lst)
	{
		p = (t_player *)lst;
		ft_printf("%p\n", &p->header);
		p->pos = (MEM_SIZE / core->players_num) * i++;
		ft_memcpy(core->field + p->pos, p->code, p->header->size);
		lst = lst->next;
	}
}


void	init_game(t_corewar *core)
{
	set_code(core);
}

void	do_cycle(t_corewar *core)
{
//	set_op_code();
}