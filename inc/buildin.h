/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujimak <mfujimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:43:48 by mfujimak          #+#    #+#             */
/*   Updated: 2023/12/07 13:00:12 by mfujimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	buildin_cmd(t_command_exec	*cmd_exec);
int	buildin_cd(t_command_exec	*cmd_exec);
int	buildin_echo(t_command_exec	*cmd_exec);
int	buildin_env(t_command_exec	*cmd_exec);
int	buildin_exit(t_command_exec	*cmd_exec);
int	buildin_export(t_command_exec	*cmd_exec);
int	buildin_pwd(t_command_exec	*cmd_exec);
int	buildin_unset(t_command_exec	*cmd_exec);
int	buildin_checker(char *filename);
