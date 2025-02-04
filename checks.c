/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <el.tamazyan03@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/02/04 14:22:39 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sgmnt_cpy(char *input, int *i)
{
	int		j;
	int		length;
	char	*result;

	length = 0;
	if (input[*i] == '?' || input[*i] == '$' || input[*i] == '0')
		return(ft_strdup(&input[*i]));
	else
	{
		while (input[*i + length] && input[*i + length] != ' '
			&& input[*i + length] != '"' && input[*i + length] != '$'
			&& input[*i + length] != '\'')
			length++;
	}
	result = (char *)malloc((length + 1) * sizeof(char));
	j = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '$'
		&& input[*i] != '\"' && input[*i] != '\'' && j < length)
	{
		result[j++] = input[*i];
		(*i)++;
	}
	result[j] = '\0';
	return (result);
}

char	*open_dollar(t_shell *general, char *input, int *i)
{
	if (input[*i])
	{
		(*i)++;
		if (input[*i] == '?' && input[*i + 1])
			general->doll_lst->value = ft_itoa(get_exit_status());
		general->doll_lst->u_key = sgmnt_cpy(input, i);
		if (!general->doll_lst->u_key[0])
			general->doll_lst->value = ft_strdup("$");
		else
			general->doll_lst->value = check_env_var(general->env_lst, general->doll_lst->u_key);
		if (!general->doll_lst->value)
		{
			general->doll_lst->value = (char *)malloc(sizeof(char) * 1);
			check_malloc(general, general->doll_lst->value);
			general->doll_lst->value[0] = '\0';
		}
	}
	printf("aaaa: %s\n", general->doll_lst->value);
	printf("aaaa: %s\n", general->doll_lst->u_key);
	
	return (general->doll_lst->value);
}

int	check_inp_quotes(t_shell *general, char *input, int i, int start)
{
	general->sg_quote = 0;
	general->db_quote = 0;
	i = 0;
	(void)general;
	(void)start;
	// printf("input[i] = %c\n", input[i]);
	while (input[i])
	{
		printf("input[i] = %c\n", input[i]);
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
