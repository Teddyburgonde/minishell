/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:12:37 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 19:08:22 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	construct_full_path(t_env *new, char **envp, int i)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strcmp(new->var_name, "SHLVL") == 0)
	{
		tmp = ft_strjoin(new->var_name, "=");
		new->full_path = ft_strjoin_mod(tmp, new->value);
	}
	else
		new->full_path = copy(envp[i]);
}

static char	*get_name(char *line, int j)
{
	char	*tab;
	int		i;

	tab = ft_strdup(line);
	tab = malloc(sizeof(char) * (j + 1));
	if (!tab)
	{
		ft_putstr_fd("Allocation error for env name\n",2);
		return (NULL);
	}
	i = 0;
	while (i != j)
	{
		tab[i] = line[i]; 	// voir henry pour strdup ???
							// ne pas oublier de free si strdup 
		i++;
	}
	tab[i] = 0;
	return (tab);
}

// static void	shlvl_variable_management(t_env **new, char **envp)
// {
// 	if (ft_strcmp((*new)->var_name, "SHLVL") == 0)
// 		(*new)->value = update_shlvl(ft_atoi(&envp[i][j + 1]) + 1);
// 	else
// 		(*new)->value = ft_strdup(&envp[i][j + 1]);
// }

static void	create_and_initialize_new_element_list(t_env **new,
	char *envp, int j)
{
	*new = ft_lstnew_env();
	(*new)->var_name = get_name(envp, j);
	if (ft_strcmp((*new)->var_name, "SHLVL") == 0)
		(*new)->value = update_shlvl(ft_atoi(&envp[j + 1]) + 1);
	//(*new)->hide = FALSE;
	else
		(*new)->value = ft_strdup(&envp[j + 1]);
}

void	init_env(t_env **env, char **envp)
{
	t_env	*new;
	int		i;
	int		j;

	if (!envp || !envp[0])
	{
		*env = NULL;
		ft_putstr_fd("envp doesn't exist\n", 2);
		return ;
	}
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		create_and_initialize_new_element_list(&new, &envp[i][j], j);
		//shlvl_variable_management(&new, &envp[i][j]);
		construct_full_path(new, envp, i);
		ft_lstadd_back_env(env, new);
		i++;
	}
}
