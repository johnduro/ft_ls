
/* write */
/* opendir        DIR *opendir(const char *name); */
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
/* strerror		  char *strerror(int errnum);char *strerror(int errnum); */
/* exit			  void _exit(int status); */

#include "ft_ls.h"



t_lsDir		*newDir(char *name)
{
	t_lsDir		*dir;

	if ((dir = (t_lsDir*)malloc(sizeof(*dir))) == NULL)
		ft_exit("newDir", 1);
	dir->name = ft_strdup(name);
	if ((dir->dirPtr = opendir(name)) != NULL)
		dir->isFile = DISABLED;
	else
		dir->isFile = ENABLED;
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

void	getLsInfos(t_ls *ls)
{
	t_lsDir		*dirPtr;

	dirPtr = ls->lsDirs;
	while (dirPtr)
	{
		// a faire
		dirPtr = dirPtr->next;
	}
}

void	makeLs(t_ls *ls)
{
	getLsInfos(ls);
	printLs(ls);
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

