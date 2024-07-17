/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:06:21 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/17 20:20:19 by tebandam         ###   ########.fr       */
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

typedef struct s_env
{
	char			*env_name;
	char			*env_value;
	char			*env_var;
	//t_bool			hide;
	struct s_env	*next;
}	t_env;

typedef enum type
{
	REDIRECTION_OUTFILE,
	REDIRECTION_INFILE,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC,
	UNASIGNED
}	e_redirection_type;

typedef struct s_redirection	t_redirection;
typedef struct s_redirection
{
	char				*content_to_expand;
	e_redirection_type	redirection_type;
	t_redirection		*next;	
}	t_redirection;

typedef struct s_argument		t_argument;
typedef struct s_argument
{
	char				*content_to_expand;
	t_argument			*next;	
}	t_argument;

typedef struct s_segment		t_segment;
typedef struct s_segment
{
	t_argument			*arguments;
	t_redirection		*redirections;
	t_segment			*next;	
}	t_segment;

typedef struct s_command_data
{
	int					exit_code;
	t_env				*env;
	t_segment			*segments;
}	t_command_data;


void 							parse_command_line(t_command_data *command_data, char *line);

/*
* Env
*/

int								init_env(t_env **env, char **envp);

/*
* Signal
*/

void							run_signals(void);
void							ft_ctrl_c(int signal);
void							set_interactive_mode(int set);

/*
* Utils
*/

void							ft_putstr_fd(char *s, int fd);
int								ft_strcmp(char *s1, char *s2);
int								ft_atoi(const char *str);
int								ft_strlen(char const *str);
char							*copy(char *s);
void							*ft_memset(void *s, int c, size_t n);
char							*ft_strdup(const char *s);
void							*ft_calloc(size_t nmemb, size_t size);
int								ft_strcspn(const char *s, char *reject);
t_env							*ft_lstnew_env(void);
void							ft_lstadd_back_env(t_env **head, t_env *new_element);
void							ft_lstclear_env(t_env **lst);
t_redirection					*ft_lstnew_redirection(char *content, e_redirection_type type);
t_segment						*ft_lstnew_segment(void);
t_argument						*ft_lstnew_argument(char *content);
void							ft_lstadd_back_segment(t_segment **head, t_segment *new_element);
void							ft_lstadd_back_redirection(t_redirection **head, t_redirection *new_element);
void							ft_lstadd_back_argument(t_argument **head, t_argument *new_element);
int								ft_redirection_lstsize(t_redirection *lst);
int								ft_argument_lstsize(t_argument *lst);
int								ft_segment_lstsize(t_segment *lst);
char							*skip_whitespace(char *str);

/*
* Utils ft_strjoin
*/

char							*ft_strjoin(char const *s1, char *s2);
char							*ft_strjoin_mod(char *s1, char *s2);

/*
* Init 
*/

char							*update_shlvl(int shlvl);
t_redirection					*initialize_redirection(void);
t_argument      				*initialize_argument(void);
t_segment						*initialize_segment(void);
t_command_data					*initialize_command_data(void);

/*
* free
*/

void    						free_arguments_struct(t_argument *argument);
void							free_redirections_struct(t_redirection *redirection);
void							free_segments_struct(t_segment *segment);
void							free_command_data_struct(t_command_data *command_data);

/*
* Test utils
*/

void							print_linked_lst_env(t_env *env);
void							ft_native_lst_print(t_command_data command_data, int fd);

#endif