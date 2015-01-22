#include "ft_ls.h"

void	getLsInfos(t_ls *ls)
{
	t_lsDir		*Ptr;

	Ptr = ls->lsDirs;
	while (Ptr)
	{
		
		Ptr = Ptr->next;
	}
}


void	ft_exit(char* str, int i)
{
	printf("%s\n", str);
	exit(i);
}