#include "main.h"
/**
 * dequote- remove quotes from command argument
 * @line: command string
 * Return: dequoted string
 */
char *dequote(char *line)
{
	int lineLength = _strlen(line);
	int j = 0;
	int i;

	for (i = 0; i < lineLength; i++)
		if (line[i] != '"' && line[i] != '\\')
			line[j++] = line[i];
		else if (line[i + 1] == '"' && line[i] == '\\')
			line[j++] = '"';
		else if (line[i + 1] != '"' && line[i] == '\\')
			line[j++] = '\\';
	if (j > 0)
		line[j] = 0;

	return (line);
}
/**
 * freeStuff- free some arrays
 * @array: 2D array
 * @arrayLength: array length
 * @commandArray: 2D array
 * @commandLength: array length
 * @path: path
 * @argv: 2D array
 * @envp: 2D array
 * Return: void
 */
void freeStuff(char **array, int arrayLength, char **commandArray,
		int commandLength, char *path, char **argv, char **envp)
{
	freeMemory(array, arrayLength);
	freeMemory(commandArray, commandLength);
	free(path);
	free(argv);
	free(envp);

}
void parse(int arrayLength, char *newCommand, char **commandArray,
char **envp, char **array, char **argv)
{
	int i;

	for (i = 0; i < arrayLength; i++)
	{
		newCommand = array[i];
		strcat(newCommand, argv[0]);
		if (access(newCommand, F_OK) == 0)
		{
			execve(newCommand, commandArray, envp);
			break;
		}
	}
}
/**
 * runCommand- execute command
 * @command: command
 * Return: 1 if successful
 */
int runCommand(char *command)
{
	char **argv = malloc(sizeof(char *) * 2);
	char *path = _getenv("PATH"), *delim = ":", *newCommand = NULL;
	int arrayLength = countWords(path, delim);
	char **envp = malloc(sizeof(char *) * 2), **array, **commandArray;
	int j, status, commandLength = countWords(command, " ");
	pid_t child;

	argv[0] = command;
	argv[1] = NULL;
	envp[0] = path;
	envp[1] = NULL;
	commandArray = calloc(commandLength + 1, sizeof(char *));
	allocateMemory(commandArray, command, " ", commandLength, 0);
	for (j = 0; j < commandLength; j++)
		if (commandArray[j][0] == '\"')
			commandArray[j] = dequote(commandArray[j]);
	commandArray[commandLength] = NULL;
	array = calloc(arrayLength, sizeof(char *));
	allocateMemory(array, path, delim, arrayLength, 1);
	child = fork();
	if (child == -1)
		perror("./shell1 ");
	if (child == 0)
	{
		if (strcmp(command, "exit") == 0)
			exit(1);
		if (command[0] == '/')
			execve(command, commandArray, envp);
		else
			parse(arrayLength, newCommand, commandArray, envp, array, argv);
		perror("./shell2");
	}
	if (waitpid(child, &status, 0) == -1)
		exit(-1);
	if (!WIFEXITED(status))
		exit(-1);
	if (WEXITSTATUS(status) == 1)
		exit(1);
	freeStuff(array, arrayLength, commandArray, commandLength, path, argv, envp);
	return (1);
}
