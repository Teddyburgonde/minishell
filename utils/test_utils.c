/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tebandam <tebandam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:38:34 by tebandam          #+#    #+#             */
/*   Updated: 2024/07/16 19:48:09 by tebandam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_linked_lst_env(t_env *env)
{
	t_env *tmp;
	tmp = env;

	while(tmp)
	{
		printf("env_var : %s\n", tmp->env_var);
		printf("env_name : %s\n", tmp->env_name);
		printf("env_value : %s\n", tmp->env_value);
		tmp = tmp->next;
	}
}
