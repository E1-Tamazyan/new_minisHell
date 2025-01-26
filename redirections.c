/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:20:21 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/26 21:27:01 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// int check_if_redir(t_token *tok)
// {
	
// 	return (0);
// }

int heredoc_init(t_shell *g, t_cmd_lst **cmd, t_token *tok)
{
	(void)g;
	(void)cmd;
	// if(tok)
	// {
		if ((*cmd)->heredoc == NULL)
		{
			(*cmd)->heredoc = ft_strdup(tok->context);
			check_malloc((*cmd)->heredoc);	
		}
	// }
	return (0);
}
static void	execute_heredoc(t_shell *g, t_cmd_lst *cmd)
{
	char *input;
	int fd;
	
	(void)g;
	fd = open("temple.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		printf("./minisHell\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (ft_strcmp(input, cmd->heredoc) == 0)
		{
			free(input);
			break ;
		}
		// if (cmd->type)
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
}

int open_heredoc(t_shell *g, t_token *tok, t_cmd_lst *cmd, int flag)
{
	(void)flag;
	printf("tokk == %s\n", tok->context);
	if (g->cmd_lst->heredoc == NULL)
	{
		if (heredoc_init(g, &cmd, tok) == -1)
			return (-1);
	}
	else if(g->cmd_lst->heredoc != NULL)
	{
		free(g->cmd_lst->heredoc);
		if (heredoc_init(g, &cmd, tok) == -1)
			return (-1);
	}
	execute_heredoc(g, cmd);
	return (0);
}

int open_redir_2(t_shell *g)
{
	if (ft_strcmp(g->curr_tok->context, "<<") == 0)
	{
		printf("tokk == %s\n", g->curr_tok->context);
		g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
		g->curr_cmd->std_in = open_heredoc(g, g->curr_tok, g->curr_cmd, 1);
	 	if (g->curr_cmd->std_out == -1)
			return (EXIT_FAILURE);
	}
	else if (g->curr_tok->context[0] == '<')
	{
		g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
		// g->curr_cmd->std_out = open_redir_out(g, g->curr_tok->context, 0);
	 	if (g->curr_cmd->std_out == -1)
			return (EXIT_FAILURE);
	}
	return(0);
}

int open_redir(t_shell *g)
{
	int status;

	if (ft_strcmp(g->curr_tok->context, ">>") == 0)
	{
		g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
		// g->curr_cmd->std_out = open_redir_out(g, g->curr_tok->context, 1);
	 	if (g->curr_cmd->std_out == -1)
			return (EXIT_FAILURE);
	}
	else if (g->curr_tok->context[0] == '>')
	{
		g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
		// g->curr_cmd->std_out = open_redir_out(g, g->curr_tok->context, 0);
	 	if (g->curr_cmd->std_out == -1)
			return (EXIT_FAILURE);
	}
	else
		status = open_redir_2(g);
	g->curr_tok = ft_lst_delone(&g->tok_lst, g->curr_tok);
	return (0);
}

int redirs_management(t_shell *g)
{
	g->curr_tok = g->tok_lst;
	g->curr_cmd = g->cmd_lst;
	while (g->curr_cmd && g->curr_tok)
	{
		// if (redir_check_pt2(g) == EXIT_FAILURE)
		// 	return (EXIT_FAILURE);
		if(g->curr_tok && (g->curr_tok->type == REDIR_IN || g->curr_tok->type == REDIR_OUT \
		 || g->curr_tok->type == REDIR_HEREDOC) && (!(g->curr_tok->next) || g->curr_tok->next->type == PIPE))
			return (printf("ERORRRRRRR\n"), EXIT_FAILURE); // "minisHell: exit(258) status syntax error near unexpected toke `"
		else if (g->curr_cmd && g->curr_tok \
		&& (g->curr_tok->type == 2 || g->curr_tok->type == 3 || g->curr_tok->type == 4 \
		|| g->curr_tok->type == 5) && (g->curr_tok->next && g->curr_tok->next->type == 0))
		{
			if (open_redir(g) == 1 && g->pipe_count < 1)
				return (EXIT_FAILURE);
		}
		else if (g->curr_tok)
			g->curr_tok = g->curr_tok->next;
		else
			break ;
	}
	return (EXIT_SUCCESS);
}