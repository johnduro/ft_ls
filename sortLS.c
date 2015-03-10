#include "ft_ls.h"

void			sortLS(t_lsFile *listfile, t_lsFile *file, t_ls *ls)
{

	if (ls->opt.tOpt == ENABLED)
		sortLSTimeReverse(listfile, file);
	else if (ls->opt.tOpt == DISABLED)
		sortLSAscii(listfile, file);
}

void			sortLSAscii(t_lsFile *listfile, t_lsFile *file)
{
	t_lsFile		*tmp;
	int				cnt;
	t_lsFile		*tmp0;

	tmp = listfile;
	while (tmp->next != NULL) {
		cnt = ft_strcmp(tmp->name, file->name);
		if (cnt >= 0) 
		{
			tmp0 = tmp->prev;
			if (tmp->prev && tmp->next)
			{
				tmp->prev = file;
				file->next = tmp;
				file->prev = tmp0;
				tmp0->next = file;
				return ;
			}
		}
		tmp = tmp->next;
	}
	tmp->next = file;
	file->prev = tmp;
}

void			sortLSTimeReverse(t_lsFile *listfile, t_lsFile *file)
{
	t_lsFile		*tmp;
	double			cnt;
	t_lsFile		*tmp0;

	tmp = listfile;
	while (tmp != NULL) {
		cnt = difftime((time_t)tmp->infos->timeInf, (time_t)file->infos->timeInf);
		if (cnt >= 0.0)
		{
			if (tmp->prev)
			{
				tmp0 = tmp->prev;
				tmp0->next = file;
				file->prev = tmp0;
				tmp->prev = file;
				file->next = tmp;
			}
			else
			{
				tmp->prev = file;
				file->next = tmp;
			}
			return ;
		}
		tmp = tmp->next;
	}
}