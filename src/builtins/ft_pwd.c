/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:21:43 by messkely          #+#    #+#             */
/*   Updated: 2024/07/02 16:46:33 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
		return (1);
	printf("%s\n", path);
	return (0);
}

int main(int argc, char **argv) {
    int fd = 1;

    if (ft_pwd(fd) != 0) {
        perror("ft_pwd failed");
        return (1);
    }

    return (0);
}
