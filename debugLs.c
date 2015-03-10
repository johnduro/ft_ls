
#include "ft_ls.h"

void		debugLsOptions(t_options opt)
{
	printf("> DEBUG OPTIONS\n[");
	if (opt.lOpt)
		printf(" l");
	if (opt.ROpt)
		printf(" R");
	if (opt.aOpt)
		printf(" a");
	if (opt.rOpt)
		printf(" r");
	if (opt.tOpt)
		printf(" t");
	printf(" ]\n");
}

void	debugLsFile(t_lsFile *file)
{
	while (file)
	{
		printf("FILE > %s\n", file->name);
		// rajouter type
		if (file->dir)
			debugLsDirs(file->dir);
		file = file->next;
	}
}

void	debugLsDirs(t_lsDir *dir)
{
	while (dir)
	{
		printf("-->> DEBUG DIR : %s\n", dir->name);
		if (dir->start)
			debugLsFile(dir->start);
		dir = dir->next;
	}
}

void	debugLs(t_ls *ls)
{
	printf("***** DEBUG LS *****\n");
	if (ls->isOptions == ENABLED)
		debugLsOptions(ls->opt);
	if (ls->lsDirs)
		debugLsDirs(ls->lsDirs);
}

/*void	debugLsInfos(t_ls *ls)
{
	
}*/