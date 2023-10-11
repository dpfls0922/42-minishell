#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*readline(const char *prompt);

#endif