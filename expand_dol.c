/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:13:47 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/23 16:30:55 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// *********************
// ****CAUTION FULL*****
// *********************
// 4 function

char *expand_var(char **input, t_shell *general, int start)
{
	int len;
	// int pos;
	char *expanded;

	len = 0;
	expanded = countcpy_len(*input, start, len, general);
	return (expanded);
}
int spec_len(char *input, int start)
{
	int i;

	i = 0;
	// while (input[start] && input[start] != '\"')
	while (input[start])
	{
		start++;
		i++;
	}
	return (i);
}
char *countcpy_len(char *input, int start, int l, t_shell *general)
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
	// printf("dddddd = %d\n", ft_strlen(general->doll_lst->u_key));
	l = len + ft_strlen(general->doll_lst->u_key);
	// printf("dddddd_ = %d\n", l);
	val_len = ft_strlen(general->doll_lst->value);
	copy = (char *)malloc(sizeof(char) * (val_len + len + spec_len(input, l) + 1));
	check_malloc(copy);
	ft_strcpy(copy, input, i, len);
	ft_strcpy_2(copy, general->doll_lst->value, len, val_len);
	// printf("------> l = %c, %c, %d\n", input[len], input[len + 1], (len + ft_strlen(general->doll_lst->u_key)));
	ft_strcpy_3(copy, input, (val_len + len), (l + i + 1));
	// ft_strcpy_3(copy, input, (val_len + len), // the wrong part here);
	return (copy);
} // echo ba"rev $USER jan" vonc es

int check_cut_quotes(t_shell *general, char **input, int *i, int start)
{
	char *dup = NULL;

	if (check_inp_quotes(general, *input, *i, start) == -1)
		return (-1);
	while ((*input)[*i])
	{
		printf("************%c\n", (*input)[*i]);
		if ((*input)[*i] == '\"')
			general->db_quote = !general->db_quote;
		else if ((*input)[*i] == '\'')
			general->sg_quote = !general->sg_quote;
		else if ((*input)[*i] == '$' && general->db_quote)
		{
			dup = open_dollar(general, *input, i, start);
			*input = expand_var(input, general, start);
			printf("______dup = %s, %d\n", dup, *i);
			printf("______input = %s\n", *input);
		}
		else if (((*input)[*i] == ' ' || (*input)[*i] == '|' || (*input)[*i] == '>' || (*input)[*i] == '<') && !general->db_quote && !general->sg_quote)
		{
			if ((*input)[*i] == ' ')
				return (add_token_list(&general->tok_lst, my_substr(*input, start, (*i - start)), 0), 0);
			*i = init_op_token(*input, *i, &general->tok_lst);
		}
		(*i)++;
	}
	return (0);
} // ec ba"rev $USER jan"

// just save the previous version

