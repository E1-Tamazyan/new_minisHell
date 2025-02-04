/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/02/05 01:11:05 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__check_valid(char c, int *s_i)
{
	if (!(*s_i))
	{
		(*s_i)++;
		return (c != '\0' && (ft_isalpha(c) || c == '_'));
	}
	return (c != '\0' && (ft_isalnum(c) || c == '_'));
}

char	*sgmnt_cpy(char *input, int *i, int *s_i)
{
	int		j;
	int		length;
	char	*result;

	length = 0;
	if (input[*i] == '?' || input[*i] == '$' || input[*i] == '0')
		return (ft_strdup(&input[*i]));
	else
	{
		while (__check_valid(input[*i + length], s_i))
			length++;
	}
	result = (char *)malloc((length + 1) * sizeof(char));
	j = 0;
	while (j < length)
	{
		result[j++] = input[*i];
		(*i)++;
	}
	result[j] = '\0';
	return (result);
}

char	*open_dollar(t_shell *gen, char *input, int *i, int *s_i)
{
	if (input[*i] && input[*i] == '$')
	{
		if (input[*i + 1] && input[*i + 1] != ' '
			&& input[*i + 1] != '"' && input[*i + 1] != '$'
			&& input[*i + 1] != '\'')
			(*i)++;
		if (input[*i] == ' ')
			return (++(*i), NULL);
		if (input[*i] == '?')
		{
			gen->doll_lst->value = ft_itoa(get_exit_status());
			gen->doll_lst->u_key = ft_strdup("?");
			return (gen->doll_lst->value);
		}
		gen->doll_lst->u_key = sgmnt_cpy(input, i, s_i);
		if (!gen->doll_lst->u_key[0])
			gen->doll_lst->value = ft_strdup("$");
		else if (input[*i] != '?')
			gen->doll_lst->value = check_env_var(gen->env_lst, \
			gen->doll_lst->u_key);
		if (!gen->doll_lst->value)
			return (free(gen->doll_lst->u_key), NULL);
	}
	return (gen->doll_lst->value);
}

int	check_inp_quotes(t_shell *general, char *input, int i)
{
	general->sg_quote = 0;
	general->db_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' && !general->sg_quote)
			general->db_quote = !general->db_quote;
		else if (input[i] == '\'' && !general->db_quote)
			general->sg_quote = !general->sg_quote;
		i++;
	}
	if (general->db_quote || general->sg_quote)
		return (printf("Error: Unclosed quotes found in input.\n"), -1);
	return (0);
}
