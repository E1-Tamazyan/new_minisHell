/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:10 by elen_t13          #+#    #+#             */
/*   Updated: 2025/01/13 22:07:30 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ************************
// *** CAUTION *** FULL ***
// ************************
// 4 function

int check_cmd(char **env, t_shell *general)
{
	t_token *tmp;

	tmp = general->tok_lst;
	(void)env;
	while (tmp)
	{
		if (ft_strcmp((const char *)tmp->context, "env") == 0)
			return (export_builtin(general, tmp->context), 0);
		else if (ft_strcmp((const char *)tmp->context, "export") == 0)
			return (export_builtin(general, tmp->context), 0); // 1 error
		else if (ft_strcmp((const char *)tmp->context, "pwd") == 0)
			return (pwd_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "cd") == 0)
			return (cd_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "unset") == 0)
			return (unset_builtin(general), 0);
		// else if (ft_strcmp((const char *)tmp->context, "echo") == 0)
		// 	return (echo_builtin(general), 0);
		else if (ft_strcmp((const char *)tmp->context, "exit") == 0)
			return (exit_builtin(general), 0);
		tmp = tmp->next;
	}
	return (0);
}

char* sgmnt_cpy(char* input, int* i)
{
	char	*key;
	int		start;
	int		len;
	int		j;
	
	(*i)++;
	start = *i;
	if (input[*i] == '$' || input[*i] == '?' || input[*i] == '0')
	{
		key = (char*)malloc(3 * sizeof(char));
		if (key == NULL)
			return NULL;
		key[0] = '$';
		key[1] = input[*i];
		key[2] = '\0';
		(*i)++;
		return (key);
	}
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	len = *i - start;
	if (len == 0)
		return NULL;
	key = (char*)malloc((len + 1) * sizeof(char));
	if (key == NULL)
		return NULL;
	j = 0;
	while (j < len)
	{
		key[j] = input[start + j];
		j++;	
	}
	key[len] = '\0';
	return (key);
}

char *get_pid(void)
{
	char	*name;
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid == 0)
		exit(0);
	else
	{
		wait(&status);
		name = ft_itoa((int)pid - 1);
	}
	return (name);
}

int	open_dollar(t_shell *general, char *input, int *i, int start)
{
	(void)start;
	if (input[*i] && input[*i] == '$')
	{
		general->doll_lst->u_key = sgmnt_cpy(input, i);
		printf("*************\n");
		if (general->doll_lst->u_key == NULL)
			general->doll_lst->value = NULL;
		else if (!general->doll_lst->u_key[0])
		{
			general->doll_lst->value = (char *)malloc(sizeof(char) * 2);
			check_malloc(general->doll_lst->value);
			general->doll_lst->value[0] = '$'; 
			general->doll_lst->value[1] = '\0';
		}
		else
			general->doll_lst->value = check_env_var(general->env_lst, general->doll_lst->u_key);
		if (!general->doll_lst->value)
		{
			general->doll_lst->value = (char *)malloc(sizeof(char) * 1);
			check_malloc(general->doll_lst->value);
			general->doll_lst->value[0] = '\0'; 
		}
	}
	return (1);
} // echo ba"rev $USER$USER jan" vonc es

int check_inp_quotes(t_shell *general, char *input, int i, int start)
{
	int flag_sg;
	int flag_db;

	flag_sg = 0;
	flag_db = 0;
	i = start;
	(void)general;
	while (input[i])
	{
		if (input[i] == '\"' && !flag_sg)
			flag_db = !flag_db;
		else if (input[i] == '\'' && !flag_db)
			flag_sg = !flag_sg;
		i++;
	}
	if (flag_db || flag_sg)
		return (printf("Error: Unclosed quotes found in input.\n"), -1);
	return (0);
}
// SIGSEGV
// echo ba"rev $USER' $USERecho ba"rev $USER' $USER 'jan"$USER dff -a | $$

// should make 3 tokens
// echo ba"rev $USER' $USERecho ba"rev
// $USER' $USER 'jan"$USER"
// dff -a | $$

// echo ba"rev $USER' $USERecho ba"rev $USER' $USER 'jan"$USER"