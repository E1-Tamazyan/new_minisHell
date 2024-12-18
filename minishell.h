/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elen_t13 <elen_t13@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2024/12/18 17:54:47 by elen_t13         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# define SUCCESS_EXIT 0
# define FAILURE_EXIT 1
# define EXPORT 1
# define ENV 0
// # include <std.h> // exit(),
#include <stdio.h>			   // readline(), perror()
#include <stdlib.h>			   // exit(),
#include <unistd.h>			   // fork(), access(),
#include <readline/readline.h> // rl_clear_history(), rl_on_new_line(), rl_replace_line(), rl_redisplay(),
#include <readline/history.h>  // rl_clear_history(), add_history(),
#include <sys/wait.h>		   // wait(), waitpid(), wait3(),
#include <sys/resource.h>	   // (struct rusage *rusage),
#include <signal.h>			   //signal(),
#include <limits.h>

typedef enum s_ttype
{
	WORD = 0,			 // commands and arguments
	PIPE = 1,			 // '|'
	REDIR_IN = 2,		 // '<'
	REDIR_OUT = 3,	 	// '>'
	REDIR_APPEND = 4,	 // '>>'
	REDIR_HEREDOC = 5, // '<<'
}			t_ttype;

typedef struct s_token
{
	char			*context;
	t_ttype			type;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

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
	char			*u_key;
	char			*value;
	// int				dollar_sign; // 1 = sgl_quote, 2 = dbl quote
	struct s_dollar	*next;

}	t_dollar;

typedef struct s_shell
{
	t_token		*tok_lst;
	t_env		*env_lst;
	t_cmd_lst	*cmd_lst;
	t_dollar	*doll_lst;
	t_env		*sorted_env_lst;
	int			shlvl;		     // check
	int			sg_quote;
	int			db_quote;
	// char		pwd; // check
	// char		*oldpwd; // check
}			t_shell;

// ***_____main_functions_____***
void	init_general(t_shell *general);
int		init_input(char *input, t_shell *gen, char **env);
int		check_cmd(char **env, t_shell *general);
t_env	*init_env_nodes(char **env);

// ***____env_sorting_____***
char	**sort_env(char **env);
void	quick_sort(char **arr, int low, int high);
int		partition(char **arr, int low, int high);
void	swap(char **a, char **b);

// ***_____utils_____***
void	print_env(t_env *new, int flag);
void	print_tokens(t_token *head);
int		put_key(t_env *node, char *src);
void	put_value(t_env *node, char *src, int pos);
int		sgmnt_len(const char *str, int pos);
char	*check_env_var(t_env *env_lst, const char *context);
int		create_env(char **env, t_shell *general);

// ***_____lib utils_____***
void	ft_strlcpy(char *dest, const char *src, int size, int pos, char limiter);
t_env	*ft_lstnew(char *context);
void	ft_lstadd_back(t_env *lst, t_env *node);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *str);
char	*my_substr(const char *s, unsigned int start, int len);
int		ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_isalnum(int arg);

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
// int		check_cut_quotes(const char *input, int start, int i, t_shell *general);
// int check_cut_quotes(const char *input, int start, int i, t_shell *general);
int	check_cut_quotes(t_shell *general, const char *input,  int *i, int start);


// **************
// int		check_dollar_sign(char *input, int i, t_shell *general);
char	*open_dollar(t_shell *general, const char *input, int *i, int start);
char *sgmnt_cpy(const char *input, int *i);


// Alla's
void	create_print_cmd(t_shell *general);
void	free_cmd_lst(t_cmd_lst *cmd_lst);
// builtins
// void	builin(t_token *token_list);
int		export_valid(t_token *token_list);
int		pwd_builtin(t_shell *general);
int		echo_builtin(t_shell *general);
int		cd_builtin(t_shell *general);
int		export_builtin(t_shell *general, char *command);
void	error_message(char *var);
void	free_ptr(void *ptr);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
t_env	**add_env_lst_var(t_token cur_node, t_shell *general, int i);
t_env	**add_env_no_var(char *context, t_shell *general);
int		count_lst_len(t_env *env_lst);
char	*str_join(char const *s1, char const *s2); //ft_strjoin => str_join
char	**list_to_array(t_env *env);
size_t	my_strlcpy(char *dst, const char *src, size_t dstsize);
void	free_array(char **arr);
t_env	*my_lstnew(char *key, char *value);
int		print_export(char *new);
t_env	*bubble_sort_lst(t_env *lst);
void	swap_node(t_env	*a, t_env *b);
int		change_home(t_shell *general);
char	*get_value(t_shell *general, char *keyik);
int		change_env_value(t_env *lst, char *keyik, char *valik);
int		change_prev_dir(t_shell *general);
int		change_dir(t_shell *general, char *dir);
int		unset_builtin(t_shell *general);
int		unset_exp_var(t_shell *general, char *new);
int		delete_exp_node(t_env **lst, t_env *nodik);
void	free_node(t_env *node);
int		exit_builtin(t_shell *general);
int		is_valid(char **args, int count);
long	ft_atol(char *str);
int		count_args(char **args);

// archive
char	*ft_substr(char const *s, unsigned int start, int len);
void	check_malloc(void *str);

#endif