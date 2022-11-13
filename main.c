#include "main.h"

int main(__attribute__((unused)) int argc,__attribute__((unused)) char **argv)
{
	char *userInput;
	int flag = 1;
	while (flag == 1)
	{
		printf("#cisfun$ ");
		userInput = getInput();
		if (userInput == NULL)
		{
			free(userInput);
			flag = 0;
		}
		else
		{
			runCommand(userInput);
		}
		free(userInput);
	}
	return (0);
}
