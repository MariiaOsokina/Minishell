/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:22:24 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/12 23:04:14 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdio.h>
/*error examples:

chmod 222 ./test
msg - bash: ./test: Permission denied
exit status -126



/ls
msg -  /ls: No such file or directory
exit status -  127

/lklklk/ll
bash: /lklklk/ll: No such file or directory
exit status -  127


./uyu
bash: ./uyu: No such file or directory
exit status -  127

cat test1.c
cat: test1.c: No such file or directory
exit status - 1

cat ls/test.c
msg -  : ls/test.c: No such file or directory
exit status: 1


jkjkjkjkk
msg - jkjkjkjkk: command not found
exit status - 127

cat: test1.c
Command 'cat:' not found, did you mean:
  command 'catm' from deb mescc-tools (1.3-2)
  command 'cat' from deb coreutils (8.32-4.1ubuntu1.2)
Try: sudo apt install <deb name>
exit status - 127

lds
Command 'lds' not found, did you mean:
  command 'lsd' from snap lsd (0.16.0)
  command 'ls' from deb coreutils (8.32-4.1ubuntu1.2)
  command 'ldb' from deb rocksdb-tools (6.11.4-3)
  command 'lvs' from deb lvm2 (2.03.11-2.1ubuntu4)
  command 'sds' from deb simh (3.8.1-6.1)
  command 'ldd' from deb libc-bin (2.35-0ubuntu3.8)
  command 'ld' from deb binutils (2.38-4ubuntu2.6)
  command 'lrs' from deb lrslib (0.71a-1)
  command 'les' from deb atm-tools (1:2.5.1-4build2)
See 'snap info <snapname>' for additional versions.
exit status - 127

ls llll
message - ls: cannot access 'llll': No such file or directory
exit status- 2
ls 00 000
ls: cannot access '00': No such file or directory
ls: cannot access '000': No such file or directory
exit status- 2


wc 989898
wc: 989898: No such file or directory
exit status- 1

rm
rm: missing operand
Try 'rm --help' for more information.
exit status - 1


> $file
bash: $file: ambiguous redirect
exit status - 1

cat -2222
cat: invalid option -- '2'
Try 'cat --help' for more information.
exit status - 1


cat 90 909
cat: 90: No such file or directory
cat: 909: No such file or directory
exit status - 1


cd jkjkjkjk
bash: cd: jkjkjkjk: No such file or directory
exit status - 1


cd .. 89
bash: cd: too many arguments
exit status - 1


*/





//function prints the error message in the terminal and returns the exit number(int)

void	ft_err_msg(t_err_msg msg, char *cause)
{
	// if (err.msg == ERRMSG_CMD_NOT_FOUND)
	// 	return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
	//ft_putstr_fd(": command not found\n", 2), err.no);
	if (msg == ERRMSG_NO_SUCH_FILE)
		printf("minishell: %s: No such file or directory\n", cause);
	else if (msg == ERRMSG_PERM_DENIED)
		printf("minishell: %s: Permission denied\n", cause);
	// else if (err.msg == ERRMSG_AMBIGUOUS)
	// 	return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(err.cause, 2),
	// 		ft_putstr_fd(": ambiguous redirect\n", 2), err.no);
	// else if (err.msg == ERRMSG_TOO_MANY_ARGS)
	// 	return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
	// 		err.no);
	// else if (err.msg == ERRMSG_NUMERIC_REQUI)
	// 	return (ft_putstr_fd("minishell: exit: ", 2),
	// 		ft_putstr_fd(err.cause, 2),
	// 		ft_putstr_fd(": numeric argument required\n", 2), err.no);
	return ;
}




