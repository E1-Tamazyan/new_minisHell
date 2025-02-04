/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <el.tamazyan03@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:35:09 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/03 20:53:25 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_heredoc_syntax(t_shell *general, t_token *head)
{
	while (head)
	{
		if (head->type == 5)
		{
			head = head->next;
			if (head->type == 1 || head->type == 2 \
			|| head->type == 3 || head->type == 4 \
			|| head->type == 5)
			{
				ft_putstr_fd("\nsyntax error unexpected token ", 2);
				ft_putstr_fd(head->context, 2);
				ft_putstr_fd("\n", 2);
				clean_gen_exit(general, 2, 1, 1);
			}
		}
		head = head->next;
	}
}

void	check_heredoc_limit(t_shell *general)
{
	int		count;
	t_token	*head;

	count = 0;
	head = general->tok_lst;
	while (head)
	{
		if (head->type == 5)
			count++;
		head = head->next;
	}
	if (count > 16)
	{
		ft_putstr_fd("minisHell: maximum here-document count exceeded\n", 2);
		clean_gen_exit(general, 2, 1, 1);
	}
	head = general->tok_lst;
	check_heredoc_syntax(general, head);
}
