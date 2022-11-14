#include "main.h"
/**
* _strlen- get the length of a string
* @str: string
* Return: length of string
*/
int _strlen(char *str)
{
	int count = 0;

	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}
/**
  * countWords- count the number of words sepearated by delim
  * @str: string
  * @delim: delimiter to separate words by
  * Return: number of words seperated by delim
  */
int countWords(char *str, char *delim)
{
	int stringLength = _strlen(str) + 1;
	char *cpy = malloc(sizeof(char) * stringLength);
	char *token;
	int count = 0;

	memcpy(cpy, str, stringLength);
	token = strtok(cpy, delim);
	while (token != NULL)
	{
		token = strtok(NULL, delim);
		count++;
	}
	free(cpy);
	return (count);
}
/**
  * allocateMemory- create a 2D array with appropriate space allocated
  * @array: 2D array
  * @str: string
  * @delim: delimiter
  * @length: length of array
  * @addToEnd: if 0, , do not add '/' to elements in array. if 1, add
  * Return: void
  */
void allocateMemory(char **array, char *str, char *delim,
int length, int addToEnd)
{
	int index = 0;
	char *token;
	int tokenLength;

	token = strtok(str, delim);
	while (token != NULL && index < length)
	{
		tokenLength = _strlen(token);
		if (addToEnd == 1)
		{
			array[index] = calloc(tokenLength * 2, sizeof(char));
		}
		else
		{
			array[index] = calloc(tokenLength + 1, sizeof(char));
		}
		strcpy(array[index], token);
		if (addToEnd == 1)
		{
			array[index][tokenLength] = '/';
		}
		token = strtok(NULL, delim);
		index++;
	}
}
/**
  * freeMemory- free memory allocated
  * @array: 2D array
  * @arrayLength: length of array
  * Return: void
  */
void freeMemory(char **array, int arrayLength)
{
	int i;

	for (i = 0; i < arrayLength; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}
/**
  * getInput- get input from the user
  * Return: input from the user
  */
char *getInput()
{
	char *buffer = NULL;
	size_t nbytes = 0;
	ssize_t chars;

	chars = getline(&buffer, &nbytes, stdin);
	if (chars == -1)
	{
		return (NULL);
	}
	if (buffer[chars - 1] == '\n')
	{
		buffer[chars - 1] = '\0';
		--chars;
	}
	return (buffer);
}
