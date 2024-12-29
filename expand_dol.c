/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:13:47 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/29 17:40:58 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// *********************
// ****CAUTION FULL*****
// *********************
// 4 function

void	expand_var(char **input, t_shell *general, int *start, int *i)
{
	int	len;

	len = 0;
	*input = countcpy_len(*input, *start, &len, general);
	*start = 0;
	*i = len;
	return ;
}
int spec_len(char *input, int start)
{
	int i;

	i = 0;
	while (input[start])
	{
		start++;
		i++;
	}
	return (i);
}
char *countcpy_len(char *input, int start, int *l, t_shell *general)
{
	int i;
	char *copy;
	int len;
	int val_len;

	len = 0;
	i = start;
	while (input[start] && input[start] != '$')
	{
		start++;
		len++;
	}
	*l = len + ft_strlen(general->doll_lst->u_key);
	val_len = ft_strlen(general->doll_lst->value);	
	copy = (char *)malloc(sizeof(char) * (val_len + len + spec_len(input, *l) + 1));
	check_malloc(copy);
	ft_strcpy(copy, input, i, len);
	ft_strcpy_2(copy, general->doll_lst->value, len, val_len);
	ft_strcpy_3(copy, input, (val_len + len), (*l + i + 1));
	*l = val_len + len;
	return (copy);
} // echo ba"rev $USER jan" vonc es

int	check_cut_quotes(t_shell *general, char **input, int *i, int start)
{
	if (check_inp_quotes(general, *input, *i, start) == -1)
		return (-1);
	while ((*input)[*i])
	{
		if (!general->sg_quote && (*input)[*i] == '\"')
			general->db_quote = !general->db_quote;
		else if (!general->db_quote && (*input)[*i] == '\'')
			general->sg_quote = !general->sg_quote;
		else if ((*input)[*i] == '$' && !general->sg_quote)
		{
			printf("aaaaaaaaaaaaaaaaaaaaaaa\n");
			open_dollar(general, *input, i, start);
			expand_var(input, general, &start, i);
			(--*i);
		}
		else if (((*input)[*i] == ' ' || (*input)[*i] == '|' || (*input)[*i] == '>' || (*input)[*i] == '<' || (*input)[*i] == '$') && !general->db_quote && !general->sg_quote)
			return (add_token_list(&general->tok_lst, my_substr(*input, start, (*i - start)), 0), 0);
		(*i)++;
	}
	add_token_list(&general->tok_lst, my_substr(*input, start, (*i - start)), 0);
	return (0);
} // echo ba"rev $USER jan" vonc es