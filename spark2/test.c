#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	char	*buf;

	buf = getcwd(0, 4096);
	printf("pwd: %s\n", buf);
	chdir(argv[1]);
	// free(buf);
	buf = getcwd(0, 4096);
	printf("pwd: %s\n", buf);
}
