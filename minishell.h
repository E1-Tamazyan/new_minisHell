/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etamazya <etamazya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:42:32 by etamazya          #+#    #+#             */
/*   Updated: 2025/01/26 21:22:39 by etamazya         ###   ########.fr       */
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
#include <fcntl.h>

typedef enum s_ttype
{
	WORD = 0,			// commands and arguments
	PIPE = 1,			// '|'
	REDIR_IN = 2,		// '<'
	REDIR_OUT = 3,	 	// '>'
	APPEND_OUT = 4,		// '>>'
	REDIR_HEREDOC = 5,	// '<<'
}			t_ttype;

typedef struct		s_token
{
	char			*context;
	t_ttype			type; // remove this
	struct s_token	*next;
}					t_token;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				is_print;
	struct s_env	*next;
}					t_env;

typedef struct			s_cmd_lst
{
	char				*cmd;
	char				**args;
	struct s_cmd_lst	*next;
	char				*heredoc;
	char				*red_in;
	char				*red_out;
	char				*red_append;
	int					std_in; // fd
	int					std_out; // fd
}						t_cmd_lst;

typedef struct		s_dollar
{
	char			*u_key;
	char			*value;
	// int				dollar_sign; // 1 = sgl_quote, 2 = dbl quote
	struct s_dollar	*next;

}	t_dollar;

typedef struct	s_shell
{
	t_token		*tok_lst;
	t_env		*env_lst;
	t_cmd_lst	*cmd_lst;
	t_dollar	*doll_lst;
	t_env		*sorted_env_lst;
	t_token		*curr_tok;
	t_cmd_lst	*curr_cmd;
	int			sg_quote;
	int			db_quote;
	int			pipe_count;
	int			tok_count;
	char		*name;
	int			shlvl;		// check
	char		pwd; // check
	char		*oldpwd; // check
}			t_shell;

// Elena's
t_token		*ft_lst_delone(t_token **lst, t_token *node);
void		list_add_back_cmd(t_cmd_lst **lst, t_cmd_lst *new);
int			heredoc_init(t_shell *g, t_cmd_lst **cmd, t_token *tok);
int			open_redir_2(t_shell *g);
int			open_redir(t_shell *g);
int			redirs_management(t_shell *g);
void		fill_commands(t_shell *general);
int			check_fill_commands(t_shell *g, int i, int j);
void		check_heredoc_syntax(t_token *head);
t_cmd_lst	*initialize_new_cmd();

// just separated
char	*get_pid(void);
char	*ft_itoa(int n); 
void	expand_var(char **input, t_shell *general, int *start, int *i);
char	*countcpy_len(char *input, int start, int *l, t_shell *general);
int		spec_len(char *input, int start);
int		check_inp_quotes(t_shell *general, char *input, int i, int start);
t_env	*add_env_dol(t_shell *general, char *context, char *value);
t_env	*spec_lstnew(char *context, char *value, int printable);
void	check_heredoc_limit(t_shell *general);

// ***_____main_functions_____***
void	init_general(t_shell *general);
int		init_input(char *input, t_shell *gen, char **env);
t_env	*init_env_nodes(char **env);
int	count_commands(t_token *token);


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
t_env	*ft_lstnew(char *context, int printable);
void	ft_lstadd_back(t_env *lst, t_env *node);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *str);
char	*my_substr(const char *s, unsigned int start, int len);
int		ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	ft_strcpy(char *s1, const char *s2, int start, int len);
void	ft_strcpy_2(char *s1, const char *s2, int start, int len);
void	ft_strcpy_3(char *s1, const char *s2, int start_s1, int start_s2);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *str, int c, size_t n);

// int		ft_strcpy();
int		ft_isalnum(int arg);
// t_token	*remove_extra_quotes(t_shell *general);
t_token *remove_extra_quotes(t_shell *general);

// ***_____tokenization_____***
short	init_tokens_cmds(char *input, t_shell *general, int i);
int		init_op_token(char *input, int *i, t_token **token_list);
void	add_token_list(t_token **list, char *content, t_ttype type);
t_token	*create_token(char *content, t_ttype type);

// ** additional
void	printStrings(char **strings);
void	clean_list(t_token **list);
void	clean_env_list(t_env **list);
short	del_t_node(t_token *lst);
int		check_cut_quotes(t_shell *general, char **input,  int *i, int start);


// **************
int		open_dollar(t_shell *general, char *input, int *i, int start);
char	*sgmnt_cpy(char *input, int *i);


// Alla's
void	free_cmd_lst(t_cmd_lst *cmd_lst);
// builtins
int		export_valid(t_token *token_list);
int		pwd_builtin(t_shell *general);
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
void	print_cmd(t_cmd_lst	*cmd_lst);
int		create_cmd_lst(t_shell *g);
int		count_tokens(t_token *token_lst);

// archive
char	*ft_substr(char const *s, unsigned int start, int len);
void	check_malloc(void *str);


#endif