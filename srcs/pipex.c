/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabid <mabid@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 13:46:48 by morikumo          #+#    #+#             */
/*   Updated: 2022/06/14 21:33:13 by mabid            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief Processus enfant qui s'exécute à l'intérieur d'un fork, 
 * prend le filein, place l'output à l'intérieur
 * d'un pipe, puis ferme la fonction avec close
 * 
 * @param argv 
 * @param envp 
 * @param fd 
 */
void	child_process(char **argv, char **envp, int *fd)
{
	int		filein;

	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	filein = open(argv[1], O_RDONLY, 0666);
	if (filein == -1)
	{
		perror(argv[1]);
		exit(-1);
	}
	dup2(filein, STDIN_FILENO);
	close(filein);
	execute(argv[2], envp);
}

/**
 * @brief Processus parent qui récupère les données du canal,
 *  modifie la sortie pour le fileout et aussi fermer avec la fonction close
 * 
 * @param argv 
 * @param envp 
 * @param fd 
 */
void	child_process2(char **argv, char **envp, int *fd)
{
	int		fileout;

	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fileout == -1)
	{
		perror(argv[4]);
		exit(-1);
	}
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	execute(argv[3], envp);
}

/**
 * @brief Deuxieme processus a faire dans le main mais est fait a part pour 
 * les ligne...
 * 
 * @param argv 
 * @param envp 
 * @param fd 
 */
void	child_process3(char **argv, char **envp, int *fd)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		error();
	else if (pid2 == 0)
		child_process2(argv, envp, fd);
}

/**
 * @brief Fonction principale qui exécute le processus enfant et parent 
 * ou affiche une erreur message si les arguments sont erronés 
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		else
			child_process3(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		close(fd[1]);
		close(fd[0]);
	}
	else
		ft_putstr_fd("Error\nEx:./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
	return (0);
}
