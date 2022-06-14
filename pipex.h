/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 13:46:59 by morikumo          #+#    #+#             */
/*   Updated: 2022/06/14 15:45:33 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "./libft/libft.h"

/*      UTILS       */
void	error(void);
char	*find_path(char *cmd, char **envp);
void	execute(char *argv, char **envp);
void	command_not_found(char *name, char *err);

/*      PIPEX       */
void	child_process(char **argv, char **envp, int *fd);
void	child_process2(char **argv, char **envp, int *fd);
void	child_process3(char **argv, char **envp, int *fd);

#endif
