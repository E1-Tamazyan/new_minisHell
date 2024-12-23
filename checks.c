/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/23 15:39:45 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************
// 4 function

int check_cmd(char **env, t_shell *general)
{
	// int		index;
	// int		j;
	t_token *tmp;

	tmp = general->tok_lst;
	(void)env;
	while (tmp)
	{
		if (ft_strcmp((const char *)tmp->context, "env") == 0)
			return (export_builtin(general, tmp->context), 0);
		else if (ft_strcmp((const char *)tmp->context, "export") == 0)
			return (export_builtin(general, tmp->context), 0); // 1 error
		else if (ft_strcmp((const char *)tmp->context, "pwd") == 0)
			return (pwd_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "cd") == 0)
			return (cd_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "unset") == 0)
			return (unset_builtin(general), 0);
		// else if (ft_strcmp((const char *)tmp->context, "echo") == 0)
		// 	return (echo_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "exit") == 0)
			return (exit_builtin(general), 0);
		tmp = tmp->next;
	}
	return (0);
}

char *sgmnt_cpy(char *input, int *i)
{
	char *result;
	int j;
	int length;

	length = 0;
	while (input[*i + length] && input[*i + length] != ' ' && input[*i + length] != '$' && input[*i + length] != '"')
		length++;
	result = (char *)malloc((length + 1) * sizeof(char));
	j = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '$' && input[*i] != '"')
	{
		result[j++] = input[*i];
		
		(*i)++;
	}
	result[j] = '\0';
	// check leak here
	return (result);
}

char *open_dollar(t_shell *general, char *input, int *i, int start)
{
	(void)start;
	if (input[*i] && input[*i] == '$')
	{
		(*i)++;
		general->doll_lst->u_key = sgmnt_cpy(input, i);
		general->doll_lst->value = check_env_var(general->env_lst, general->doll_lst->u_key);
	}
	return (general->doll_lst->value);
} // sadf ba"rev $USER jan"

int check_inp_quotes(t_shell *general, char *input, int i, int start)
{
	int flag_sg;
	int flag_db;

	flag_sg = 0;
	flag_db = 0;
	i = start;
	(void)general;
	while (input[i])
	{
		if (input[i] == '\"')
			flag_db = !flag_db;
		else if (input[i] == '\'')
			flag_sg = !flag_sg;
		i++;
	}
	if (flag_db || flag_sg)
		return (printf("Error: Unclosed quotes found in input.\n"), -1);
	return (0);
}

// change to double pointer input, change the value of intire input
//  that will be seen from parent function,
// with replacing just opened $USER. Remeber this case (m$: e"ch"o abc"etamazy$USER" ab)


// save the previous logic
// 
// char *countcpy_len(char *input, int start, int l, t_shell *general)
// {
// 	int		i;
// 	char	*copy;
// 	int		len;
// 	int		val_len;
	
// 	len = 0;
// 	i = start;
// 	while (input[start] && input[start] != '$')
// 	{
// 		start++;
// 		len++;
// 	}
// 	val_len = 0;
// 	while (general->doll_lst->value[val_len])
// 		val_len++;
// 	// *length += spec_len(input, l);
// 	copy = (char *)malloc(sizeof(char) * (val_len + len + 1));
// 	check_malloc(copy);
// 	ft_strcpy(copy, input, i, len);
// 	ft_strcpy_2(copy, general->doll_lst->value, len, val_len);
// 	copy[val_len + len] = '\0';
// 	return (copy);
// } 
// sdfsd dfs"sdfs $USER jan"
// handle this function later
// read about smart pointers and its types
