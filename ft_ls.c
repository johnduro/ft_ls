
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include "ft_ls.h"

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	return (0);
}

