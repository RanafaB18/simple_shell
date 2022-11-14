#include "main.h"

/**
* slice - divides string
* @str: string to slice
* @result: where to store sliced string
* @start: where to start slicing from
* @end: where to slice to
* Return: void
*/
void slice(const char *str, char *result, size_t start, size_t end)
{
	strncpy(result, str + start, end - start);
}
/**
  * findIndexOfEqual - finds index of "=" in environment variable
  * @env: environment variable
  * Return: index of "="
  */
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
/**
  * isName - checks if "name" is what the user is looking for
  * @env: environment variable
  * @name: name of the environment variable the user is looking for
  * Return: index of the value in the environment key if successful, -1 if not
  */
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
/**
  * getValue - gets the value of an environment variable
  * @env: environment variable
  * @indexOfValue: index of value in environment variable
  * Return: value of environment variable if successful, NULL if not
  */
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
/**
  * _getenv - get value of environment variable name
  * @name: name of environment variable key
  * Return: value of environment key, NULL if not successful
  */
char *_getenv(const char *name)
{
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
