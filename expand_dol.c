/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:13:47 by elen_t13          #+#    #+#             */
/*   Updated: 2024/12/22 19:01:58 by elen_t13         ###   ########.fr       */
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
	// printf("expanded = %s, %d\n", expanded, len);
	// special_len = spec_len(input, len);
	// free(input)
	// input = NULL;
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
	l = len + ft_strlen(general->doll_lst->u_key);
	val_len = 0;
	while (general->doll_lst->value[val_len])
		val_len++;
	copy = (char *)malloc(sizeof(char) * (val_len + len + spec_len(input, l) + 1));
	check_malloc(copy);
	ft_strcpy(copy, input, i, len);
	ft_strcpy_2(copy, general->doll_lst->value, len, val_len);
	ft_strcpy_3(copy, input, (val_len + len), (len + l));
	// printf("%s\n", copy);
	return (copy);
} // echo ba"rev $USER jan" vonc es

int check_cut_quotes(t_shell *general, char **input, int *i, int start)
{
	char *dup = NULL;

	if (check_inp_quotes(general, *input, *i, start) == -1)
		return (-1);
	while ((*input)[*i])
	{
		if ((*input)[*i] == '\"')
			general->db_quote = !general->db_quote;
		else if ((*input)[*i] == '\'')
			general->sg_quote = !general->sg_quote;
		else if ((*input)[*i] == '$' && general->db_quote)
		{
			dup = open_dollar(general, *input, i, start);
			*input = expand_var(input, general, start);
			printf("______dup = %s\n", dup);
			printf("______input = %s\n", *input);
			// printf("______input = %s, ___%c\n", *input, *input[--(*i)]);
			(*i)--;
		}
		else if (((*input)[*i] == ' ' || (*input)[*i] == '|' || (*input)[*i] == '>' || (*input)[*i] == '<') && !general->db_quote && !general->sg_quote)
		{
			if ((*input)[*i] == ' ')
			{
				add_token_list(&general->tok_lst, my_substr(*input, start, (*i - start)), 0);
				return (0);
			}
			*i = init_op_token(*input, *i, &general->tok_lst);
		}

		(*i)++;
	}

	return (0);
}

// just save the previous version
// int check_cut_quotes(t_shell *general, char **input, int *i, int start)
// {
// 	char *dup;

// 	dup = NULL;
// 	if (check_inp_quotes(general, *input, *i, start) == -1)
// 		return (-1);
// 	while (input[*(i)])
// 	{
// 		if (input[*(i)] == '\"')
// 			general->db_quote = !general->db_quote;
// 		else if (input[*(i)] == '\'')
// 			general->sg_quote = !general->sg_quote;
// 		else if (input[(*i)] == '$' && general->db_quote)
// 		{
// 			dup = open_dollar(general, *input, i, start);
// 			// correct thisss i think it not gonna work $USER$USER
// 			// ft_strcpy_3(copy, input, (val_len + len), (len + l));
// 			input = expand_var(input, general, start);
// 			printf("______dup = %s\n", dup);
// 			(*i)--;
// 		}
// 		else if ((input[*(i)] == ' ' || input[*(i)] == '|' || input[*(i)] == '>' || input[*(i)] == '<') && !general->db_quote && !general->sg_quote)
// 		{
// 			if (input[*(i)] == ' ')
// 				return (add_token_list(&general->tok_lst, my_substr(*input, start, ((*i) - start)), 0), 0);
// 			*i = init_op_token(*input, *i, &general->tok_lst);
// 		}
// 		(*i)++;
// 	}
// 	return (0);
// }

// major module python jango