/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaboya <algaboya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:55:53 by algaboya          #+#    #+#             */
/*   Updated: 2025/02/02 03:03:31 by algaboya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_init(t_shell *g, t_cmd_lst **cmd, t_token *tok)
{
	(void)g;
	(void)cmd;
	if ((*cmd)->heredoc == NULL)
	{
		(*cmd)->heredoc = ft_strdup(tok->context);
		check_malloc(g, (*cmd)->heredoc);
	}
	return (0);
}

void	execute_heredoc(t_shell *g, t_cmd_lst *cmd)
{
	char	*input;

	(void)g;
	cmd -> std_in = open("temple.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (cmd -> std_in < 0)
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
		write(cmd -> std_in, input, ft_strlen(input));
		write(cmd -> std_in, "\n", 1);
		free(input);
	}
	close(cmd -> std_in);
	open_infile(g, "temple.txt");
}

void	handle_redirection(t_shell *g, t_ttype type)
{
	if (g->curr_tok->next)
	{
		g->curr_tok = g->curr_tok->next;
		if (type == REDIR_OUT)
			handle_out_redirection(g);
		else if (type == REDIR_APPEND)
			handle_append_redirection(g);
		else if (type == REDIR_IN)
			handle_in_redirection(g);
		else if (type == REDIR_HEREDOC)
			handle_heredoc_redirection(g);
		g->curr_tok = g->curr_tok->next;
	}
}

void	check_redir(char *redir)
{
	if (redir)
		free_set_null(redir);
}
