
#include "ft_ls.h"


static void		freeLsFiles(t_lsFile *file)
{
	t_lsFile	*keep;

	while (file)
	{
		keep = file->next;
		if (file->name)
			free(file->name);
		if (file->dir)
			freeLsDirs(file->dir);
		free(file);
		file = keep;
	}
}

void			freeLsDirs(t_lsDir *dir)
{
	t_lsDir		*keep;

	while (dir)
	{
		keep = dir->next;
		if (dir->name)
			free(dir->name);
	/*	if (dir->dirPtr)
			closedir(dir->dirPtr);*/
		if (dir->start)
			freeLsFiles(dir->start);
		free(dir);
		dir = keep;
	}
}


void			freeLs(t_ls **ls)
{
	if ((*ls)->lsDirs)
		freeLsDirs((*ls)->lsDirs);
	free(*ls);
}

