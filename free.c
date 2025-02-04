/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 20:21:20 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 18:36:15 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_lst(t_cmd_lst *tmp_cmd_lst)
{
	t_cmd_lst	*tmp;

	while (tmp_cmd_lst)
	{
		tmp = tmp_cmd_lst->next;
		free(tmp_cmd_lst->cmd);
		if (tmp_cmd_lst->args)
		{
			free_args(tmp_cmd_lst);
			free(tmp_cmd_lst->args);
			tmp_cmd_lst->args = NULL;
		}
		free(tmp_cmd_lst->heredoc);
		free(tmp_cmd_lst->red_in);
		free(tmp_cmd_lst->red_out);
		free(tmp_cmd_lst->red_append);
		free(tmp_cmd_lst);
		tmp_cmd_lst = tmp;
	}
}

void	free_args(t_cmd_lst *tmp_cmd_lst)
{
	int	i;

	i = 0;
	while (tmp_cmd_lst->args[i])
	{
		free_set_null(tmp_cmd_lst->args[i]);
		i++;
	}
	free_set_null(tmp_cmd_lst->args[i]);
}

void	free_tok_lst(t_token *tok_lst)
{
	t_token	*tmp;

	while (tok_lst)
	{
		tmp = tok_lst;
		if (tmp->context)
		{
			free(tmp->context);
			tmp->context = NULL;
		}
		free(tmp);
		tok_lst = tok_lst->next;
	}
	free(tok_lst);
	tok_lst = NULL;
}

void	free_env_lst(t_env *env_lst)
{
	t_env	*temp;

	while (env_lst)
	{
		temp = env_lst->next;
		if (env_lst->key)
		{
			free(env_lst->key);
			env_lst->key = NULL;
		}
		if (env_lst->value)
		{
			free(env_lst->value);
			env_lst->value = NULL;
		}
		free(env_lst);
		env_lst = temp;
	}
	free(env_lst);
	env_lst = NULL;
}

void	free_doll_lst(t_dollar *doll_lst)
{
	t_dollar	*tmp;

	tmp = doll_lst;
	while (doll_lst)
	{
		tmp = doll_lst->next;
		free(doll_lst->u_key);
		doll_lst->u_key = NULL;
		free(doll_lst->value);
		doll_lst->value = NULL;
		free(doll_lst);
		doll_lst = tmp;
	}
	free(doll_lst);
	doll_lst = NULL;
}
