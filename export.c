/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:35:06 by algaboya          #+#    #+#             */
/*   Updated: 2024/12/11 11:42:54 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_builtin(t_shell *general, char *command)
{
	int	i;

	if (ft_strcmp(command, "env") == 0 && !general->tok_lst->next)
	{
		printf("sxtor\n");
		return (print_env(general->sorted_env_lst, 0), 0);
	}
	if (ft_strcmp(command, "export") == 0 && !general->tok_lst->next)
	{
		printf("sxtor\n");
		return (print_env(general->env_lst, 1), 0);
	}
	if (export_valid(general->tok_lst->next) == FAILURE_EXIT)
	{
		printf("val err\n");
		return (FAILURE_EXIT);
	}
	else if (ft_strchr(general->tok_lst->next->context, '=') >= 0)
	{
		i = ft_strchr(general->tok_lst->next->context, '=');
		add_env_lst_var(*general->tok_lst->next, general, i);
	}
	else
		add_env_no_var(general->tok_lst->next->context, general);
	return (SUCCESS_EXIT);
}

int	export_valid(t_token *token_list)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (token_list)
	{
		// while (token_list && token_list->context == ' ')
		// 	token_list = token_list->next;
		if (!ft_isalpha(token_list->context[0])
			|| ft_isdigit(token_list->context[0]))
		{
			error_message(token_list->context);
			exit_status = 1;
		}
		token_list = token_list->next;
	}
	return (exit_status);
}

t_env	**add_env_no_var(char *context, t_shell *general)
{
	t_env	*lol;
	t_env	*tmp;

	tmp = general->env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, context) == 0)
		{
			lol = my_lstnew(context, NULL);
			return (NULL);
		}
		tmp = tmp->next;
	}
	lol = my_lstnew(context, NULL);
	ft_lstadd_back(general->env_lst, lol);
	return (NULL);
}

t_env	**add_env_lst_var(t_token cur_node, t_shell *general, int i)
{
	char	*val;
	char	*key;
	t_env	*tmp;
	t_env	*lol;

	tmp = general->env_lst;
	key = my_substr(cur_node.context, 0, i);
	val = my_substr(cur_node.context, i + 1, ft_strlen(cur_node.context) - i);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(val);
			lol = my_lstnew(key, val);
			return (NULL);
		}
		tmp = tmp->next;
	}
	lol = my_lstnew(key, val);
	if (!lol)
		return (NULL);
	ft_lstadd_back(general->env_lst, lol);
	ft_lstadd_back(general->sorted_env_lst, lol);
	return (NULL);
}

char	**list_to_array(t_env *env)
{
	int		i;
	int		len;
	char	*tmp;
	char	**str;
	t_env	*env_temp;

	len = count_lst_len(env);
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	env_temp = env;
	while (env_temp)
	{
		tmp = str_join(env_temp->key, "=");
		str[i] = str_join(tmp, env_temp->value);
		free(tmp);
		if (!str[i])
			return (free_array(str), NULL);
		i++;
		env_temp = env_temp->next;
	}
	str[i] = NULL;
	return (str);
}

int	count_lst_len(t_env *env_lst)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

// int	is_same_key(t_env *env_lst, char *key)
// {
	// t_env	*tmp;

	// tmp = env_lst;
	// while (tmp)
	// {
	// 	if (ft_strcmp(tmp->key, key) == 0)
	// 		return (0);
	// 	tmp = tmp->next;
	// }
// 	return (1);
// }

// t_env	** remove_node(t_shell *general, t_env *tmp)
// {
// 	t_env	*temp;

// 	temp = general->env_lst;
// 	while (temp)
// 	{
// 		if (ft_strcmp(temp->key, tmp->key) == 0)
// 		{
// 			free(temp->key);
// 			free(temp->value);
// 			free(temp);
// 			return (NULL);
// 		}
// 		temp = temp->next;
// 	}
// 	return (NULL);
// }
