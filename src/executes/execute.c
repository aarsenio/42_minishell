/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:20:26 by nuno              #+#    #+#             */
/*   Updated: 2023/03/06 10:50:55 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static static char	*extract_path_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (0);
}

static char	*get_path(char **envp, char **cmds)
{
	int		i;
	char	*cmd_final;
	char	*path;
	char	**path_temp;

	i = 0;
	cmd_final = ft_strjoin("/", cmds[0]);
	path_temp = ft_split(ft_strchr(extract_path_line(envp), '/'), ':');
	while (path_temp[i])
	{
		path = ft_strjoin(path_temp[i], cmd_final);
		if (access(path, F_OK) == 0)
		{
			free(cmd_final);
			free_matrix(path_temp);
			return (path);
		}
		else
			free(path);
		i++;
	}
	free(cmd_final);
	free_matrix(path_temp);
	return (0);
}

static void	call_execve(char *argv_cmd, char **envp)
{
	char	*path;
	char	**cmds;

	cmds = ft_split(argv_cmd, ' ');
	path = get_path(envp, cmds);
	if (execve(path, cmds, envp) < 0)
	{
		free_matrix(cmds);
		free(path);
		end_and_error_message("Error executing command");
	}
}

static void	execute_pipe_infinite_commands(char *argv, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		end_and_error_message("Error creating pipe");
	pid = fork();
	if (pid < 0)
		end_and_error_message("Error forking");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		call_execve(argv, envp);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		wait(NULL);
	}
}

void	execute(int argc, char **argv, char**envp) //modificar argumentos
{
	int	i;
	int	file_fd[2];

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)	//modificar para redirect <<
	{
		i = 2;
		file_fd[1] = open_file(argv[argc - 1], 0);
		here_doc(argc, argv[2]);
	}
	else
	{
		i = 1;
		file_fd[0] = open_file(argv[1], 1);
		file_fd[1] = open_file(argv[argc - 1], 2);
		dup2(file_fd[0], STDIN_FILENO);
	}
	while (i < argc - 3)
		execute_pipe_infinite_commands(argv[++i], envp);
	dup2(file_fd[1], STDOUT_FILENO);
	call_execve(argv[argc - 2], envp);
}
