/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:32:50 by tumolabs          #+#    #+#             */
/*   Updated: 2025/01/17 11:03:50 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_shell *general) //char *arg
{
	char	*new;
	int		i;

	i = 0;
	if (!general->tok_lst->next)
		return (SUCCESS_EXIT);
	new = general->tok_lst->next->next->context;
	while (new && new[i])
	{
		if (new[i] == '=')
			return (printf("minisHell: unset: `%s': not a valid identifier\n", new), FAILURE_EXIT);
		i++;
	}
	// printf("kaxamb\n");
	return (unset_exp_var(general, new));
}

int	unset_exp_var(t_shell *general, char *new)
{
	t_env	*tmp;

	tmp = general->env_lst;
	// print_env(tmp, 1);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, new) == 0)
			return (delete_exp_node(&general->env_lst, tmp));
		tmp = tmp->next;
	}
	return (SUCCESS_EXIT);
}

int	delete_exp_node(t_env **lst, t_env *nodik)
{
	t_env	*prev;
	t_env	*tmp;

	prev = NULL;
	tmp = *lst;
	if (*lst == nodik)
	{
		tmp = (*lst)->next;
		free_node(*lst);
		return (SUCCESS_EXIT);
	}
	while (tmp)
	{
		if (tmp == nodik)
		{
			prev->next = tmp->next;
			free_node(tmp);
			return (SUCCESS_EXIT);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (SUCCESS_EXIT);
}
