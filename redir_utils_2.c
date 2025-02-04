/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:42:40 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 03:01:32 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_out_redirection(t_shell *g)
{
	check_redir(g->curr_cmd->red_out);
	g->curr_cmd->red_out = ft_strdup(g->curr_tok->context);
	g->curr_cmd->std_out = open_redir_out(g, g->curr_cmd->red_out, 0);
}

void	handle_append_redirection(t_shell *g)
{
	check_redir(g->curr_cmd->red_append);
	g->curr_cmd->red_append = ft_strdup(g->curr_tok->context);
	g->curr_cmd->std_out = open_redir_out(g, g->curr_cmd->red_append, 1);
}

void	handle_in_redirection(t_shell *g)
{
	check_redir(g->curr_cmd->red_in);
	g->curr_cmd->red_in = ft_strdup(g->curr_tok->context);
	g->curr_cmd->std_in = open_infile(g, g->curr_cmd->red_in);
}

void	handle_heredoc_redirection(t_shell *g)
{
	check_redir(g->curr_cmd->heredoc);
	g->curr_cmd->heredoc = ft_strdup(g->curr_tok->context);
	execute_heredoc(g, g->curr_cmd);
}
