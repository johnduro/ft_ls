#include "ft_ls.h"

int			checkDir(char *name)
{
	if ( (name[0] == '.' && name[1] == '.' && name[2] == '\0') || \
		(name[0] == '.' && name[1] == '\0'))
		return (0);
	return (1);
}

void		saveDir(t_ls *ls, char *name, char **tmp)
{
	char			*saveDir;

	if (*tmp == NULL)
	{
		*tmp = (char*)malloc(ft_strlen(name) + ft_strlen(ls->currentDir) + 2);
		*tmp[0] = '\0';
		ft_strcat(*tmp, ls->currentDir);
		ft_strcat(*tmp, "/");
		ft_strcat(*tmp, name);
	}
	else
	{
		saveDir = *tmp;
		*tmp = (char*)malloc(ft_strlen(name) + ft_strlen(*tmp) + 3);
		*tmp[0] = '\0';
		ft_strcat(*tmp, saveDir);
		free(saveDir);
		ft_strcat(*tmp, "/");
		ft_strcat(*tmp, name);
	}
	ls->currentDirBrowsed = *tmp;
}

void		changePath(t_ls *ls, char **tmp)
{
	*tmp = ft_strsub(*tmp, 0, ft_strlen(*tmp) - ft_strlen(ft_strrchr(*tmp, '/')));
	ls->currentDirBrowsed = *tmp;
}

void		DirRec(t_ls *ls, char *name)
{
	static char				*tmp;

	saveDir(ls, name, &tmp);
	ls->lsDirs = newDir(tmp);
	if (ls->lsDirs->dirPtr)
	{
		getLsInfos(ls);
		openDirRec(ls, ls->lsDirs->files);
	}
	changePath(ls, &tmp);
}

void		openDirRec(t_ls *ls, t_lsFile *list)
{
	t_lsFile	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->infos->type == 'd' && checkDir(tmp->name))
		{
			printf("direct : %s\n", tmp->name);
			DirRec(ls, tmp->name);
		}
		tmp = tmp->next;
	}
}