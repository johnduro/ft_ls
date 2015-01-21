
#include "ft_ls.h"


void	firstInitLs(t_ls *ls)
{
	ft_bzero(&(ls->opt), sizeof(t_options));
	ls->isOptions = DISABLED;
	ls->lsDirs = NULL;
}

void	initOptions(t_ls *ls, char *arg)
{
	ls->isOptions = ENABLED;
	while (*arg)
	{
		if (*arg == 'l')
			ls->opt.lOpt = ENABLED;
		else if (*arg == 'R')
			ls->opt.ROpt = ENABLED;
		else if (*arg == 'a')
			ls->opt.aOpt = ENABLED;
		else if (*arg == 'r')
			ls->opt.rOpt = ENABLED;
		else if (*arg == 't')
			ls->opt.tOpt = ENABLED;
		arg++;
	}
	return ;
}

t_lsDir	*initCurrentDir(void)
{
	t_lsDir		*lsDirs;

	if ((lsDirs = (t_lsDir*)malloc(sizeof(*lsDirs))) == NULL)
		ft_exit("initCurrentDir", 1);
	if ((lsDirs->name = (char *)malloc(sizeof(char))) == NULL)
		ft_exit("initCurrentDir", 1);
	lsDirs->name[0] = '.';
	lsDirs->start = NULL;
	lsDirs->end = NULL;
	lsDirs->next = NULL;
	lsDirs->prev = NULL;
	return (lsDirs);
}

void	initDirs(t_ls *ls, char *arg)
{
	t_lsDir		*dir;

	dir = newDir(arg);
	if (ls->lsDirs == NULL)
		ls->lsDirs = dir;
	else
		addToLsDirs(ls->lsDirs, dir);
}

t_ls	*initLs(char **argv)
{
	t_ls		*ls;

	if ((ls = (t_ls*)malloc(sizeof(*ls))) == NULL)
		ft_exit("initLs", 1);
	firstInitLs(ls);
	if (*argv != NULL)
	{
		while (*argv)
		{
			if ((*argv)[0] == '-')
				initOptions(ls, *argv);
			else
				initDirs(ls, *argv);
			argv++;
		}
	}
	if (ls->lsDirs == NULL)
		ls->lsDirs = initCurrentDir();
	return (ls);
}

