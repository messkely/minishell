/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:21:43 by messkely          #+#    #+#             */
/*   Updated: 2024/06/10 20:17:30 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(int fd)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
		return (1);
	ft_putendl_fd(path, fd);
	return (0);
}
