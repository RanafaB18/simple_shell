#include "main.h"

void slice(const char *str, char *result, size_t start, size_t end)
{
	strncpy(result, str + start, end - start);
}

int findIndexOfEqual(char *env)
{
	int i = 0;
	while (env[i] != '\0')
	{
		if (env[i] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int isName(char *env, const char *name)
{
	size_t start = 0;
	int indexOfEqual = findIndexOfEqual(env);
	size_t end = indexOfEqual;
	int indexOfValue = (strlen(env) - (strlen(env) - end)) + 1;
	char *environName;
	if (indexOfEqual == -1)
	{
		return (-1);
	}
	environName = malloc(sizeof(char) * (end + 1));

	slice(env, environName, start, end);
	environName[end] = '\0';
	if (strcmp(environName, name) == 0)
	{
		free(environName);
		return (indexOfValue);
	}
	free(environName);
	return (-1);
}

char *getValue(char *env, int indexOfValue)
{
	char *value;
	int i = indexOfValue;
	int lengthOfEnviron;
	int size;

	if (indexOfValue == -1)
	{
		return (NULL);
	}
	lengthOfEnviron = strlen(env);
	size = lengthOfEnviron - indexOfValue;
	value = malloc(sizeof(char) * (size + 1));
	while (env[i] != '\0')
	{
		value[i - indexOfValue] = env[i];
		i++;
	}
	value[i - indexOfValue] = '\0';
	return (value);
}

char *_getenv(const char *name)
{
	extern char **environ;
	int result;
	char *value;
	int i = 0;

	while (environ[i] != NULL)
	{
		result = isName(environ[i], name);
		if (result == -1)
		{
			value = 0;
			i++;
		}
		else
		{
			value = getValue(environ[i], result);
			break;
		}
	}
	return (value);
}
