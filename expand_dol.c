/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <el.tamazyan03@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:13:47 by elen_t13          #+#    #+#             */
/*   Updated: 2025/02/04 14:21:17 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var(char **input, t_shell *general, int *start, int *i)
{
	int	len;

	len = 0;
	*input = countcpy_len(*input, *start, &len, general);
	if (!(*input))
		check_malloc(general, *input);
	*start = 0;
	*i = len;
	(--(*i));
	return ;
}

int	spec_len(char *input, int start)
{
	int	i;

	i = 0;
	while (input[start])
	{
		start++;
		i++;
	}
	return (i);
}

char	*countcpy_len(char *input, int start, int *l, t_shell *general)
{
	int		i;
	char	*copy;
	int		context_len;
	int		value_len;

	context_len = 0;
	i = start;
	while (input[start] && input[start] != '$')
	{
		start++;
		context_len++;
	}
	*l = context_len + ft_strlen(general->doll_lst->u_key);
	value_len = ft_strlen(general->doll_lst->value);
	copy = (char *)malloc(sizeof(char) * (value_len + \
		context_len + spec_len(input, *l) + 1));
	check_malloc(general, copy);
	ft_strcpy(copy, input, i, context_len);
	ft_strcpy_2(copy, general->doll_lst->value, context_len, value_len);
	ft_strcpy_3(copy, input, (value_len + context_len), (*l + i + 1));
	return (copy);
}



int	check_cut_quotes(t_shell *g, char **input, int *i, int start)
{
	printf("kkk\n");

	while (input[0] && input[0][*i] && (input[0][*i] != ' ' && !g->sg_quote && !g->db_quote))
	{
		// printf("uuu: [%c]\n", input[0][*i]);
		if (!g->sg_quote && input[0][*i] == '\"')
		{
			g->db_quote = !g->db_quote;
			// printf("aaa\n");	
		}
		else if (!g->db_quote && input[0][*i] == '\'')
		{
			g->sg_quote = !g->sg_quote;
			// printf("bbbbb\n");
		}
		else if (input[0][*i] == '$' && !g->sg_quote)
		{
			if (open_dollar(g, *input, i) != NULL)
			{
				// printf("hiiii\n0");
				expand_var(input, g, &start, i);
			}
		}
		else if ((input[0][*i] == ' ' || input[0][*i] == '|'
			|| input[0][*i] == '>' || input[0][*i] == '<')
				&& !g->db_quote && !g->sg_quote)
			return (add_token_list(&g->tok_lst,
					my_substr(*input, start, (*i - start)), 0), 0);
		if (input[0] && input[0][(*i)])
			(*i)++;
	}
	add_token_list(&g->tok_lst, my_substr(*input, start,
			(*i - start)), 0);
	return (0);
}
