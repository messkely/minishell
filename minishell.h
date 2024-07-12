/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:11 by messkely          #+#    #+#             */
/*   Updated: 2024/07/12 16:02:11 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_smplcmd
{
	char				**argv;
	char				**reds;
	struct s_smplcmd	*next;
}	t_smplcmd;

int			check_syntax(char *input);
void		ft_handle_signals(void);
void		ch_handle_signals(void);
int			exit_status(int exit_status);
void		c_handle_signals(void);
void		ft_error(char *s, char c);

char		*rm_escape_char(char *s);
char		**process_token(char *s, char token);

t_smplcmd	*ft_lstnew(char *content, char **arr, t_smplcmd **pmp);
void		ft_add_back(t_smplcmd **head, t_smplcmd *new);
char		**rm_red_args(char **args, int n, t_smplcmd *pmp);
int			ft_arglen(char **args);
char		*add_space_in_red(char *s);
void		toggle_quotes(char c, int *single_quote, int *double_quote);

void		ft_broom(char **arr);
void		free_list(t_smplcmd **cmdlst);

char		*ft_strtrim(char *s1, char *set);
int			ft_isspace(char c);
int			ft_strlen(char *str);
char		*ft_strndup(char *s, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *str);
int			ft_arglen(char **args);

#endif