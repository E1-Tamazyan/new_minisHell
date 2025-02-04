/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:57:54 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 00:05:21 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_word(t_shell *g, int *j)
{
	g->curr_cmd->args[*j] = ft_strdup(g->curr_tok->context);
	(*j)++;
	g->curr_tok = g->curr_tok->next;
}

static int	args_count(t_token *tmp)
{
	int		count;

	count = 0;
	while (tmp && (tmp -> type != PIPE))
	{
		if (is_redir(tmp -> type))
		{
			if (tmp -> next)
				tmp = tmp -> next;
			else
				break ;
			if (tmp -> next)
				tmp = tmp -> next;
			else
				break ;
		}
		else
		{
			count++;
			tmp = tmp -> next;
		}
	}
	return (count);
}

int	check_fill_commands(t_shell *g)
{
	int	j;

	j = 0;
	while (g -> curr_cmd && g->curr_tok)
	{
		j = 0;
		fill_commands(g);
		g->curr_cmd->args = malloc(sizeof(char *)
				* (args_count(g->curr_tok) + 1));
		g->curr_cmd->args[args_count(g->curr_tok)] = NULL;
		while (g->curr_tok && g->curr_tok->type != PIPE)
		{
			if (g->curr_tok->next && is_redir(g->curr_tok -> type))
				handle_redirection(g, g->curr_tok->type);
			else if (g->curr_tok && g->curr_tok->type == WORD)
				handle_word(g, &j);
		}
		if (g->curr_tok)
			g->curr_tok = g->curr_tok -> next;
		g->curr_cmd = g->curr_cmd -> next;
	}
	return (EXIT_SUCCESS);
}

int	create_cmd_lst(t_shell *g)
{
	t_cmd_lst	*new;
	int			i;

	g->pipe_count = count_commands(g->tok_lst) - 1;
	i = 0;
	g->cmd_lst = initialize_new_cmd();
	while (i < g->pipe_count)
	{
		new = initialize_new_cmd();
		check_malloc(g, g->cmd_lst);
		list_add_back_cmd(&g->cmd_lst, new);
		i++;
	}
	g->curr_cmd = g->cmd_lst;
	g->curr_tok = g->tok_lst;
	if (!g->curr_tok)
		return (EXIT_SUCCESS);
	return (check_fill_commands(g));
}

// static void handle_redirection(t_shell *g, t_ttype type)
// {
// 	if (g->curr_tok->next)
// 	{
// 		g->curr_tok = g->curr_tok->next;
// 		if (type == REDIR_OUT || type == REDIR_APPEND)
// 		{
// 			check_redir(g->curr_cmd->red_out);
// 			g->curr_cmd->red_out = ft_strdup(g->curr_tok->context);
// 			g->curr_cmd -> std_out = open_redir_out(g,
	// 		g->curr_cmd -> red_out, 0);
// 		}
// 		else if (type == REDIR_IN)
// 		{
// 			check_redir(g->curr_cmd->red_in);
// 			g->curr_cmd->red_in = ft_strdup(g->curr_tok->context);
// 			g->curr_cmd -> std_in = open_infile(g, g->curr_cmd -> red_in);

// 		}
// 		else if (type == REDIR_APPEND)
// 		{
// 			check_redir(g->curr_cmd->red_append);
// 			g->curr_cmd->red_append = ft_strdup(g->curr_tok->context);
// 			g->curr_cmd -> std_out = open_redir_out(g,
			// g->curr_cmd -> red_append, 1);
// 		}
// 		else if (type == REDIR_HEREDOC)
// 		{
// 			check_redir(g->curr_cmd->heredoc);
// 			g->curr_cmd->heredoc = ft_strdup(g->curr_tok->context);
// 			execute_heredoc(g, g->curr_cmd);
// 		}
// 		g->curr_tok = g->curr_tok->next;
// 	}
// }
