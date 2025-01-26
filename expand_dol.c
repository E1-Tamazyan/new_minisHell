/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:13:47 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/23 14:53:16 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// *********************
// ****CAUTION FULL*****
// *********************
// 4 function

void	expand_var(char **input, t_shell *general, int *start, int *i)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = *input;
	*input = countcpy_len(input[0], *start, &len, general);
	*start = 0;
	free(tmp);
	*i = len - 1;
	return ;
}
int spec_len(char *input, int start)
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
char *countcpy_len(char *input, int start, int *l, t_shell *general)
{
	char	*copy;
	int		i;
	int		len;
	int		val_len;

	len = 0;
	i = start;
	while (input[start] && input[start] != '$' && (start++))
		len++;
	if (input[start] && input[start] == '$' && (input[start + 1] && (input[++start] == '$' || input[start] == '?' || input[start] == '0')))
		len++;
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
	while (input[0][*i])
	{
		if (!general->sg_quote && input[0][*i] == '\"')
			general->db_quote = !general->db_quote;
		else if (!general->db_quote && input[0][*i] == '\'')
			general->sg_quote = !general->sg_quote;
		else if (input[0][*i] == '$' && !general->sg_quote)
		{
			// segfault $? $$ $0 again, new one, dunno why look later
			// echo ba"rev $USER' $USERecho ba"rev $USER' $USER 'jan"$USER"
			open_dollar(general, input[0], i, start);
			expand_var(input, general, &start, i);
		}
		else if ((input[0][*i] == ' ' || input[0][*i] == '|' || input[0][*i] == '>' || input[0][*i] == '<') && !general->db_quote && !general->sg_quote)
			return (add_token_list(&general->tok_lst, my_substr(*input, start, (*i - start)), 0), 0);
		if (input[0][(*i)])
			(*i)++;
	}
	add_token_list(&general->tok_lst, my_substr(*input, start, (*i - start)), 0);
	return (0);
} // echo ba"rev $USER jan" vonc es

// check leaks
// valgrind --leak-check=full ./your_program
//  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell