

#ifndef FT_LS
# define FT_LS

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include "libft.h"

# define ENABLED 1
# define DISABLED 0
# define DIRECTORY 1

typedef char				t_opt;
typedef char				t_bool;
typedef char				t_type;
typedef struct s_lsFile		t_lsFile;
typedef struct s_lsDir		t_lsDir;

typedef struct				s_options
{
	t_opt					lOpt;
	t_opt					ROpt;
	t_opt					aOpt;
	t_opt					rOpt;
	t_opt					tOpt;
}							t_options;

struct						s_lsFile
{
	char					*name;
	t_type					type;
	t_lsDir					*dir;
	t_lsFile				*next;
	t_lsFile				*prev;
};

struct						s_lsDir
{
	char					*name; // ?
	t_bool					isFile;
	DIR						*dirPtr;
	t_lsFile				*start;
	t_lsFile				*end;
	t_lsDir					*next;
	t_lsDir					*prev;
};

typedef struct				s_ls
{
	t_options				opt;
	t_bool					isOptions;
	t_lsDir					*lsDirs;
}							t_ls;



t_lsDir		*newDir(char *name);
void	addToLsDirs(t_lsDir *listPtr, t_lsDir *dir);



/*
** INITLS_C
*/
void			firstInitLs(t_ls *ls);
void			initOptions(t_ls *ls, char *arg);
t_lsDir			*initCurrentDir(void);
void			initDirs(t_ls *ls, char *arg);
t_ls			*initLs(char **argv);


/*
** FREELS_C
*/
void			freeLs(t_ls **ls);
void			freeLsDirs(t_lsDir *dir);


/*
** DEBUG
*/
void	debugLsOptions(t_options opt);
void	debugLsFile(t_lsFile *file);
void	debugLsDirs(t_lsDir *dir);
void	debugLs(t_ls *ls);


#endif /* FT_LS */
