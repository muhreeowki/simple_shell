#include "shell.h"

int main(void)
{
	size_t size = MAX_INPUT_SIZE;
	char *user_input;
	char **paths;
	cmd *head;
	char nl = '\n';
	
	while (1)
	{
		user_input = malloc(sizeof(char) * size);
		if (user_input == NULL)
		{
			perror(NULL);
			return(-1);
		}

		/* get env variabls */
		paths = get_paths();

		/* Prompt */
		write(STDOUT_FILENO, "$ ", 2);

		/* Get user input */
		if(getline(&user_input, &size, stdin) == -1)
		{
			/* exit */
			write(STDOUT_FILENO, &nl, 1);
			/* Create a function to FREE the cmdlist (linked list) and all the commands inside it */
			free(user_input);
			free_cmdlist(head);
			return(0);
		}

		user_input[strcspn(user_input, "\n")] = '\0'; /* Create remove_nl function */

		/* Parser */
		head = parser(user_input, paths);

		if (head == NULL)
		{
			perror("parser");
			continue;
		}

		printf("%s\n", user_input);

		executor(head);

		free(user_input);
		free_cmdlist(head);
	}

	return (0);
}


/**
 * free_listint - frees a linked list
 *
 * @head: pointer to the head of the linked list
 *
 * Return: nothing.
 */
void free_cmdlist(cmd *head)
{
	cmd *ptr = head;
	cmd *next;

	if (head == NULL)
		return;

	while (ptr)
	{
		next = ptr->next;
		free(ptr->arguments);
		free(ptr);
		ptr = next;
	}
}
