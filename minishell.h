/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:06:21 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 19:09:20 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <limits.h>
# include <string.h>

/*
* Global variables
*/

extern int	g_sig;


typedef struct s_vars
{
	pid_t			child;
	pid_t			last_child;
	//t_redirection	**redirection;
	//t_bool			exit;
	int				nb_cmd;
	int				cmd_index;
	char			**path;
	char			***cmd;
	char			**full_cmd;
	int				pipe_1[2];
	int				pipe_2[2];
	char			**env;
	int				exit_code;
	int				exit_code_signal;
	int				*pids;
}	t_vars;

typedef struct s_env
{
	char			*var_name;
	char			*value;
	char			*full_path;
	//t_bool			hide;
	struct s_env	*next;
}	t_env;

/*
* Env
*/

void							init_env(t_env **env, char **envp);
void							init_vars(t_vars *vars);

/*
* Signal
*/

void							run_signals(void);
void							ft_ctrl_c(int signal);

/*
* Utils
*/

void							ft_putstr_fd(char *s, int fd);
int								ft_strcmp(char *s1, char *s2);
int								ft_atoi(const char *str);
int								ft_strlen(char const *str);
char							*copy(char *s);
t_env							*ft_lstnew_env(void);
void							ft_lstadd_back_env(t_env **lst, t_env *new);
void							*ft_memset(void *s, int c, size_t n);
char							*ft_strdup(const char *s);
void							*ft_calloc(size_t nmemb, size_t size);
/*
* Utils ft_strjoin
*/

char							*ft_strjoin(char const *s1, char *s2);
char							*ft_strjoin_mod(char *s1, char *s2);


/*
* Init 
*/

char							*update_shlvl(int shlvl);

#endif