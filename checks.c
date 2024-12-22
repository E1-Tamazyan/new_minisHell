/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/22 16:26:06 by elen_t13         ###   ########.fr       */
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

char *sgmnt_cpy(const char *input, int *i)
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

char *open_dollar(t_shell *general, const char *input, int *i, int start)
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

int check_inp_quotes(t_shell *general, const char *input, int i, int start)
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
int check_cut_quotes(t_shell *general, const char *input, int *i, int start)
{
	char *dup;

	dup = NULL;
	if (check_inp_quotes(general, input, *i, start) == -1)
		return (-1);
	while (input[*(i)])
	{
		if (input[*(i)] == '\"')
			general->db_quote = !general->db_quote;
		else if (input[*(i)] == '\'')
			general->sg_quote = !general->sg_quote;
		else if (input[(*i)] == '$' && general->db_quote)
		{
			dup = open_dollar(general, input, i, start);
			// correct thisss i think it not gonna work $USER$USER
			input = expand_var(input, general, start);
			printf("______dup = %s\n", dup);
			(*i)--;
		}
		else if ((input[*(i)] == ' ' || input[*(i)] == '|' || input[*(i)] == '>' || input[*(i)] == '<') && !general->db_quote && !general->sg_quote)
		{
			if (input[*(i)] == ' ')
				return (add_token_list(&general->tok_lst, my_substr(input, start, ((*i) - start)), 0), 0);
			*i = init_op_token(input, *i, &general->tok_lst);
		}
		(*i)++;
	}
	return (0);
}

char *expand_var(const char *input, t_shell *general, int start)
{
	int		len;
	char	*expanded;

	len = 0;
	expanded = countcpy_len(input, start, len, general);
	printf("expanded = %s, %d\n", expanded, len);
	// special_len = spec_len(input, len);
	// len = ft_strlen();
	return (expanded);
}
int	spec_len(const char *input, int start)
{
	int	i;

	i = 0;
	while (input[start] && input[start] != '\"')
	{
		start++;
		i++;
	}
	return (i);
}
char *countcpy_len(const char *input, int start, int l, t_shell *general)
{
	int		i;
	char	*copy;
	int		len;
	int		val_len;

	len = 0;
	i = start;
	while (input[start] && input[start] != '$')
	{
		start++;
		len++;
	}
	l = len + ft_strlen(general->doll_lst->u_key);
	val_len = 0;
	while (general->doll_lst->value[val_len])
		val_len++;
	copy = (char *)malloc(sizeof(char) * (val_len + len + spec_len(input, l) + 1));
	check_malloc(copy);
	ft_strcpy(copy, input, i, len);
	ft_strcpy_2(copy, general->doll_lst->value, len, val_len);
	copy[val_len + len] = '\0';
	// ft_strcpy_3(copy, input, (val_len + len), (len + l));
	return (copy);
} 

// save the previous logic
// 
// char *countcpy_len(const char *input, int start, int l, t_shell *general)
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

