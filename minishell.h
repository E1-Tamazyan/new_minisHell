/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2024/12/09 14:29:04 by etamazya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// # include <std.h> // exit(),
#include <stdio.h>			   // readline(), perror()
#include <stdlib.h>			   // exit(),
#include <unistd.h>			   // fork(), access(),
#include <readline/readline.h> // rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(),
#include <readline/history.h>  // rl_clear_history(), add_history(),
#include <sys/wait.h>		   // wait(), waitpid(), wait3(),
#include <sys/resource.h>	   // (struct rusage *rusage),
#include <signal.h>			   //signal(),

typedef enum s_ttype
{
	WORD = 0,			 // commands and arguments
	PIPE = 1,			 // '|'
	REDIR_IN = 2,		 // '<'
	REDIR_OUT = 3,	 	// '>'
	REDIR_APPEND = 4,	 // '>>'
	REDIR_HEREDOC = 5, // '<<'
	// ENV_VAR = 6,		 // ENV
	// QUOTES = 7,		 // "" ''
	// T_SGL_QUOTES = 7, // ''
	// T_DBL_QUOTES = 8, // ""
} t_ttype;

typedef struct s_token
{
	char *context;
	t_ttype type;
	struct s_token *next;
} t_token;

//**************************************
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_cmd_lst
{
	char				*cmd;
	char				**args;
	struct s_cmd_lst	*next;
	// int		std_in; // fd
	// int		std_out; // fd
	//Gaya's vers.
	// char	*pipe;
	// char	*redir_in;
	// char	*redir_out;
	// char	*append_in;
	// char	*append_out;
}			t_cmd_lst;

typedef struct s_dollar
{
	char *u_key;
	char *value;
	int	dollar_sign; // 1 = sgl_quote, 2 = dbl quote
	struct s_dollar	*next;

}	t_dollar;

typedef struct s_shell
{
	t_token		*tok_lst;
	t_env		*env_lst;
	t_cmd_lst	*cmd_lst;
	t_dollar	*doll_lst;
	t_env		*sorted_env_lst; // for export, to not change the original env_lst above
	int			shlvl;		     // check
	int			args_count;
	// char		pwd; // check
	// char		*oldpwd; // check
	
} t_shell;

// ### NOW WORKING ###

//**************************************

// ***_____main_functions_____***
int init_input(char *input, t_shell *gen, char **env);
int check_cmd(char **env, t_shell *general);
t_env *init_env_nodes(char **env);

// ***____env_sorting_____***
char **sort_env(char **env);
void quick_sort(char **arr, int low, int high);
int partition(char **arr, int low, int high);
void swap(char **a, char **b);

// ***_____utils_____***
void print_env(t_env *lst, int flag);
void print_tokens(t_token *head);
int put_key(t_env *node, char *src);
void put_value(t_env *node, char *src, int pos);
int sgmnt_len(const char *str, int pos);
// void	my_list_iter(t_token *head);
int check_print_dollar(const char *context, t_env *env_lst, int i);
int create_env(char **env, t_shell *general);
t_cmd_lst	*exchange_to_commands(t_token *tok_lst, t_shell *general);

// ***_____lib utils_____***
void ft_strlcpy(char *dest, const char *src, int size, int pos, char limiter);
t_env *ft_lstnew(char *context);
void ft_lstadd_back(t_env **lst, t_env *node);
int ft_strcmp(const char *s1, const char *s2);
int ft_strlen(const char *str);
char *my_substr(const char *s, unsigned int start, int len);
int ft_strchr(const char *s, int c);
char *ft_strdup(const char *s1);
char *ft_strjoin(char *s1, char *s2);

// ***_____tokenization_____***
short	init_tokens(const char *input, t_shell *general, int i);
int		init_op_token(const char *input, int i, t_token **token_list);
void	add_token_list(t_token **list, char *content, t_ttype type);
t_token	*create_token(char *content, t_ttype type);

// ** additional
void	printStrings(char **strings);
void	clean_list(t_token **list);
void	clean_env_list(t_env **list);
short	del_t_node(t_token *lst);
int		check_cut_quotes(const char *input, int start, int i, t_shell *general);

// **************
int	check_dollar_sign(char *input, int i, t_shell *general);
// int	exchange_to_cmd(t_shell *general);
// int	counter_args(t_shell *general);

// Alla's
void lalala(t_shell *general);
void	free_cmd_lst(t_cmd_lst *cmd_lst);
// static t_cmd_lst *create_cmd_lst(t_token *token_lst);
// static int	count_mid_args(t_token *start, t_token *end);
// char	*strdup(const char *__s1);

// archive
char *ft_substr(char const *s, unsigned int start, int len);

#endif