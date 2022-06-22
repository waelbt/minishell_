/**--H E A D E R  H E R E!**/
/**--H E A D E R  H E R E!**/
/**--H E A D E R  H E R E!**/
/**--H E A D E R  H E R E!**/
/**--H E A D E R  H E R E!**/


#include "../include/minishell.h"

void	cd(char *path)
{
	if (chdir(path) < 0)
		perror("Error");
}
