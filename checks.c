/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/21 14:05:52 by elen_t13         ###   ########.fr       */
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

int check_cut_quotes(t_shell *general, const char *input, int *i, int start)
{
	char *dup;

	dup = NULL;
	while (input[*(i)])
	{
		if (input[*(i)] == '\"')
			general->db_quote = !general->db_quote;
		else if (input[*(i)] == '\'')
			general->sg_quote = !general->sg_quote;
		else if (input[(*i)] == '$' && general->db_quote)
		{
			dup = open_dollar(general, input, i, start);
			// don't forget to free dup in the function below
			printf("dup = %s\n", dup);
			// can you write here the function that will replace the dup value
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
	// printf("aaaa %d - %d\n", general->db_quote, general->sg_quote);
	if (general->db_quote || general->sg_quote)
		return (printf("Error: Unclosed quotes found in input.\n"), -1);
	return (0);
}

// handle this function later
char *expand_var(const char *input)
{
	int i = 0, j = 0;
	int len = strlen(input);
	char *expanded = malloc(len + 1); // Allocate memory for the expanded string
	if (!expanded)
	{
		perror("malloc failed");
		return NULL;
	}

	while (i < len)
	{
		// If it's a '$' and we're inside double quotes
		if (input[i] == '$')
		{
			i++; // Move past the '$'
			int var_start = i;

			// Find the end of the variable name (until space, another $, or end of string)
			while (i < len && (input[i] != ' ' && input[i] != '$' && input[i] != '"' && input[i] != '\''))
			{
				i++;
			}

			int var_len = i - var_start;
			char *var_name = strndup(input + var_start, var_len); // Extract the variable name

			// Get the value of the variable (could be an environment variable lookup, etc.)
			char *var_value = get_env_var(var_name);
			if (var_value)
			{
				// Copy the value of the variable into expanded
				strcpy(expanded + j, var_value);
				j += strlen(var_value);
			}
			else
			{
				// If the variable is not found, copy the "$" as is
				expanded[j++] = '$';
				strcpy(expanded + j, var_name);
				j += var_len;
			}

			free(var_name); // Don't forget to free the variable name
		}
		else
		{
			// Copy the character as is when it's not a '$'
			expanded[j++] = input[i++];
		}
	}

	expanded[j] = '\0'; // Null-terminate the expanded string
	return expanded;
}
