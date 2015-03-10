#include "ft_ls.h"

void	AddToFileList(t_lsFile **listfile, t_lsFile *file, t_ls *ls)
{
	t_lsFile *newF;

	newF = file;
	newF->next = NULL;
	newF->prev = NULL;
	if (*listfile == NULL)
		*listfile = newF;
	else
		sortLS(*listfile, file, ls);
}

char	getType(struct dirent *dp)
{
	char				c;

	if (dp->d_type == DT_FIFO) 
		(c = 'p');
	else if (dp->d_type == DT_CHR) 
		(c = 'c');
	else if (dp->d_type == DT_DIR) 
		(c = 'd');
	else if (dp->d_type == DT_BLK) 
		(c = 'b');
	else if (dp->d_type == DT_LNK) 
		(c = 'l');
	else if (dp->d_type == DT_SOCK) 
		(c = 's');
	else
		c = '-';
	return (c);
}


char		*fileMode(struct stat *buf, char *attr, char type)
{
	attr = (char*)malloc(sizeof(11));

	attr[0] = type;
	(buf->st_mode & S_IRUSR) ? (attr[1] = 'r') : (attr[1] = '-');
    (buf->st_mode & S_IWUSR) ? (attr[2] = 'w') : (attr[2] = '-');
    (buf->st_mode & S_IXUSR) ? (attr[3] = 'x') : (attr[3] = '-');
    (buf->st_mode & S_IRGRP) ? (attr[4] = 'r') : (attr[4] = '-');
    (buf->st_mode & S_IWGRP) ? (attr[5] = 'w') : (attr[5] = '-');
    (buf->st_mode & S_IXGRP) ? (attr[6] = 'x') : (attr[6] = '-');
    (buf->st_mode & S_IROTH) ? (attr[7] = 'r') : (attr[7] = '-');
    (buf->st_mode & S_IWOTH) ? (attr[8] = 'w') : (attr[8] = '-');
    (buf->st_mode & S_IXOTH) ? (attr[9] = 'x') : (attr[9] = '-');
    attr[10] = '\0';
    return (attr);
}

void	ret_list_start(t_lsFile	**listFile)
{
	t_lsFile	*tmp;

	tmp = *listFile;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	*listFile = tmp;
}

char	*cat_path(t_ls *ls, char *name)
{
	char				*scat;
	// char				*tmp;

	scat = (char*)malloc(ft_strlen(ls->currentDirBrowsed) + ft_strlen(name) + 2);
	scat[0]= '\0';
	// tmp = ft_strdup(ls->currentDirBrowsed);
	ft_strcat(scat, ls->currentDirBrowsed);
	ft_strcat(scat, "/");
	ft_strcat(scat, name);
	// free(scat);
	return (scat);
}

void	getLsInfos(t_ls *ls) /* Penser a free */
{
	t_lsDir				*Ptr;
	struct dirent		*dp;
	struct stat			buf;
	t_lsFile			*newFile;
	t_lsFile			*listFile;
	t_infos				*fileInfos;
	char				*attr;
	char				*scat;


	attr = NULL;
	listFile = NULL;
	Ptr = ls->lsDirs;
	if (!Ptr->dirPtr)
	{
		printf("Yo!\n");
		return ;
	}
	while (Ptr)
	{
		// printf("00\n");
		while ((dp = readdir(Ptr->dirPtr)) != NULL)
		{
			// printf("01\n");
			scat = NULL;
			// buf = NULL;
			// buf = (struct stat*)malloc(sizeof(struct stat));
			newFile = (t_lsFile*)malloc(sizeof(t_lsFile));
			fileInfos = (t_infos*)malloc(sizeof(t_infos));
			
			fileInfos->type = getType(dp);

			// scat = (char*)malloc(ft_strlen(ls->lsDirs->name) + ft_strlen(dp->d_name) + 2);
			// ft_strcat(scat, ls->lsDirs->name);
			// ft_strcat(scat, "/");
			

			// printf("scat: %s\n", cat_path(ls, dp->d_name));

			if (fileInfos->type == 'l')
			{
				if (lstat((scat = cat_path(ls, dp->d_name)), &buf) == -1)
					printf("stat error link : %s\n", scat);
			}
			else 
			{
				if (stat((scat = cat_path(ls, dp->d_name)), &buf) == -1)
					printf("stat error : %s\n", scat);
			}

			free(scat);
			newFile->name = ft_strdup(dp->d_name);
			// printf("*tocheck >>%s\n", newFile->name);
			// printf("type : %c name : %s\n", fileInfos->type, newFile->name);
			// fileInfos->statInf = buf;
			

			// printf("UID : %lld\n", (long long)getpwuid(buf.st_uid)->pw_uid);
			// printf("UID : %s\n", getpwuid(buf.st_uid)->pw_class);
			// printf("UID : %s\n", getpwuid(buf.st_uid)->pw_gecos);
			// printf(">> : %d\n", (int)buf.st_uid);

			if (getpwuid(buf.st_uid))
				fileInfos->user = ft_strdup(getpwuid(buf.st_uid)->pw_name);
			else
				fileInfos->user = ft_itoa((int)buf.st_uid);

			// printf("buf.st_gid : %d\n", (int)buf.st_gid);
			if (getgrgid(buf.st_gid))
				fileInfos->grp = ft_strdup(getgrgid(buf.st_gid)->gr_name);
			else
				fileInfos->grp = ft_itoa((int)buf.st_gid);
			
			fileInfos->timeInf = buf.st_mtime;
			fileInfos->attr = fileMode(&buf, attr, fileInfos->type);
			// printf("%s name : %s\n", fileInfos->attr, newFile->name);


			newFile->infos = fileInfos;
			AddToFileList(&listFile, newFile, ls);
			// free(buf);
			free(attr);
			ret_list_start(&listFile);
		}
		if (Ptr)
			Ptr->files = listFile;
		if (closedir(Ptr->dirPtr) == -1)
		{
			printf("Bad closure !!\n");
		}
		// printf("Ptr : %p, Ptr->start : %p\n", Ptr, Ptr->start);
		Ptr = Ptr->next;
	}
	// printf("listFile : %p\n", listFile);
	/* Test */ 
	t_lsFile *tmp;
	tmp = listFile;
	char *strtmp;
	if ((ls->opt.tOpt == ENABLED && ls->opt.rOpt == ENABLED) || (ls->opt.tOpt == DISABLED && ls->opt.rOpt == DISABLED))
	{
		while (tmp != NULL)
		{
			printf("%s ", tmp->infos->attr);
			printf("%s ", tmp->infos->user);
			printf("%s ", tmp->infos->grp);
			strtmp = ft_strsub(ctime(&tmp->infos->timeInf), 0, ft_strlen(ctime(&tmp->infos->timeInf)) - 1);
			printf("%s ", strtmp);
			// printf("%d ", (int)(tmp->infos->statInf)->st_size);
			// printf("%d ", (int)(tmp->infos->statInf)->st_nlink);
			printf("%s\n", tmp->name);
			tmp = tmp->next;
		}
	}
	if ((ls->opt.tOpt == DISABLED && ls->opt.rOpt == ENABLED) || (ls->opt.tOpt == ENABLED && ls->opt.rOpt == DISABLED))
	{	
	while(tmp->next)
		tmp = tmp->next;
	while (tmp != NULL)
		{
			printf("%s ", tmp->infos->attr);
			// printf("%s ", tmp->infos->grp);
			// printf("%s ", tmp->infos->user);
			strtmp = ft_strsub(ctime(&tmp->infos->timeInf), 0, ft_strlen(ctime(&tmp->infos->timeInf)) - 1);
			printf("%s ", strtmp);
			// printf("%d ", (int)(tmp->infos->statInf)->st_size);
			// printf("%d ", (int)(tmp->infos->statInf)->st_nlink);
			printf("%s\n", tmp->name);
			tmp = tmp->prev;
		}
	}
	/* !Test */

}


void	ft_exit(char* str, int i)
{
	ft_putendl(str);
	exit(i);
}