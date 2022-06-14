/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 13:46:53 by morikumo          #+#    #+#             */
/*   Updated: 2022/06/14 20:03:01 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_verif(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	return (0);
}

char	*ft_free(char **paths)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/**
 * @brief Va chercher la commande dans l'environement  
	et tester chaque chemin par le access, et renvoie le bon chemin
 * 
 * @param cmd 
 * @param envp 
 * @return char* 
 */
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (ft_verif(cmd));
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i++])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	ft_free(paths);
	return (NULL);
}
		//i++;

/**
 * @brief Fonction qui prend la commande et l'envoie à find_path
 avant de l'exécuter.
 * 
 * @param argv 
 * @param envp 
 */
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		command_not_found(argv, "command not found");
	}
	if (execve(path, cmd, envp) == -1)
		error();
}
