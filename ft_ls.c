
/* write */
/* DIR *opendir(const char *name); */
/* readdir        struct dirent *readdir(DIR *dirp); */
/* closedir       int closedir(DIR *dirp); */
/* stat			  int stat(const char *path, struct stat *buf); */
/* lstat          int lstat(const char *path, struct stat *buf); */
/* getpwuid		  struct passwd *getpwuid(uid_t uid); */
/* getgrgid		  struct group *getgrgid(gid_t gid); */
/* listxattr	  ssize_t listxattr(const char *path, char *list, size_t size); */
/* getxattr		  ssize_t listxattr(const char *path, char *list, size_t size); */
/* time			  time_t time(time_t *t); */
/* ctime		  char *ctime(const time_t *timep); */
/* readlink		  ssize_t readlink(const char *path, char *buf, size_t bufsiz); */
/* malloc		  void *malloc(size_t size); */
/* free			  void free(void *ptr); */
/* perror		  void perror(const char *s); */
/* strerror		  char *strerror(int errnum); */
/* exit			  void _exit(int status); */

#include "ft_ls.h"

t_bool			check_rights(struct stat	buf)
{
	t_bool		boole;

	(buf.st_mode & S_IRUSR) ? (boole = ENABLED) : (boole = DISABLED);
	// (buf.st_mode & S_IRGRP) ? (boole = ENABLED) : (boole = DISABLED);
	// (buf.st_mode & S_IROTH) ? (boole = ENABLED) : (boole = DISABLED);
	// printf("boole : %d\n", boole);
	printf("user right : %d\n", buf.st_mode & S_IRUSR);
	printf("group right : %d\n", buf.st_mode & S_IRGRP);
	printf("other right : %d\n", buf.st_mode & S_IROTH);
	// printf("user : *%d*\n", ft_strc	mp(getpwuid(buf.st_uid)->pw_name, "ppellegr"));
	if ( !(buf.st_mode & S_IROTH) \
		&& ft_strcmp(getpwuid(buf.st_uid)->pw_name, "ppellegr"))
	{
		printf("user\n");
		boole = DISABLED;
	}

	if ( !(buf.st_mode & S_IRGRP) \
		&& ft_strcmp(getgrgid(buf.st_gid)->gr_name, "2013_paris"))
	{
		printf("group\n");
		boole = DISABLED;
	}
	return (boole);
}

void		opendir_err(char *name)
{
		char		*scat;

		scat = (char*)malloc(8 + ft_strlen(name));
		ft_strcat(scat, "ft_ls: ");
		ft_strcat(scat, name);
		perror(scat);

}

t_lsDir		*newDir(char *name)
{
	t_lsDir		*dir;
	struct stat	buf;
	// t_bool		boole;

	printf("newdir -> name : %s\n", name);

	if ((dir = (t_lsDir*)malloc(sizeof(*dir))) == NULL)
		ft_exit("newDir", 1);
	dir->name = ft_strdup(name);

	
	if (stat(name, &buf) == -1)// Gestion d'erreur
	{
		printf("Name error : %s\n", name);
	}

	// boole = check_rights(buf);
	// if (boole)
	// 	printf("%s, ENABLED\n", name);
	// else
	// 	printf("%s, DISABLED\n", name);

	if (S_ISREG(buf.st_mode)) // Gestion d'erreur
	{
		printf("%s is a file\n", name);
		dir->isFile = ENABLED;
	}

	if (S_ISDIR(buf.st_mode))
	{
		printf("%s is a directory\n", name);
		dir->isFile = DISABLED;
	}
	
	dir->dirPtr = NULL;
	// if (dir->isFile == DISABLED && boole == ENABLED)
	if ((dir->dirPtr = opendir(name)) == NULL)
		opendir_err(name);
	
	dir->start = NULL;
	dir->end = NULL;
	dir->next = NULL;
	dir->prev = NULL;
	return (dir);
}

void	addToLsDirs(t_lsDir *listPtr, t_lsDir *dir)
{
	while (listPtr->next)
		listPtr = listPtr->next;
	dir->prev = listPtr;
	listPtr->next = dir;
	return ;
}

void	makeLs(t_ls *ls)
{
	getLsInfos(ls);
	if (ls->opt.ROpt == ENABLED)
		openDirRec(ls, ls->lsDirs->files);
	printf("current : %s\n", ls->currentDirBrowsed);
	// printLs(ls);
	return ;
}

int		main(int argc, char **argv)
{
	t_ls		*ls;

	(void)argc;
	argv++;
	ls = initLs(argv);

	makeLs(ls);
	debugLs(ls);
	freeLs(&ls);
	return (0);
}

