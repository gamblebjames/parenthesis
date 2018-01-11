/*****************************************************************************
	Author: Ben Gamble
	Creation Date: 01/05/2018
	Last Modified: 01/06/2018
	Last Modified By: Ben Gamble
	Description: Ensure every opening parenthesis has a closing parenthesis.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char	*get_input();
bool	check_string(char *buf);

int main(
	int argc, 
	char **argv)
{
	
	char *buf;
	bool check;

	buf = get_input();
	printf("Your string: %s",buf);
	// printf("Your string is %ld bytes.\n",strlen(buf));

	check = check_string(buf);
	if(check == 1)
		printf("All parentheses are closed.\n");
	else
		printf("A parenthesis is not closed.\n");

	free(buf);

	return 0;
}

/*	Get a string input from the user.	*/
char *get_input() 
{
	char	*buf;
	int		too_long = 0;
	
	if((buf = (char *)malloc(100)) == NULL) {
		perror("Failed to allocate memory");
		exit(-1);
	}

	while(1) {
		printf("Enter a string under 100 characters:\n");
		if(fgets(buf,100,stdin) == NULL) {
			perror("Failed to read string from stdin");
			exit(-1);
		}
		else {
			// Determine if the input is too long
			if(!strchr(buf,'\n')) {
				scanf("%*[^\n]"); // Scan and discard up to \n
				scanf("%*c");     // Discard the \n
				printf("Keep your string under 100 characters.\n");
			}
			else 
				break;
		}
	}

	return buf;
}

/*	Look for the number of parenthesis in the entire string and store their
	index values in their respective arrays.							     */
bool check_string(
	char *buf)
{
	int		begin_paren = 0, end_paren = 0;
	int		*begin_index, *end_index;
	int		len = strlen(buf);
	bool	check = true;

	if((begin_index = (int *)malloc(sizeof(int))) == NULL) {
		perror("Failed to allocate memory");
		exit(-1);
	}
	if((end_index = (int *)malloc(sizeof(int))) == NULL) {
		perror("Failed to allocate memory");
		exit(-1);
	}

	for(int i = 0 ; i < len; i++) {
		if(buf[i] == '(') {
			if(begin_paren != 0) {
				// Possibly more efficient to malloc 100*sizeof(int) instead
				// of realloc since string size is limited to 100 bytes	
				if(realloc(begin_index,sizeof(int)) == NULL)
					perror("Failed to reallocate memory");
			}
			begin_index[begin_paren++] = i;
		} 
		else if(buf[i] == ')') {
			if(end_paren != 0) {
				if(realloc(end_index,sizeof(int)) == NULL)
					perror("Failed to reallocate memory");
			}
			end_index[end_paren++] = i;
		}
	}

	if(begin_paren != end_paren)
		check = false;
	for(int i = 0; i < begin_paren; i++) {
		if(end_index[i] < begin_index[i])
			check = false;
	}

	free(begin_index);
	free(end_index);

	return check;
}

/*	Test cases:
	()
	(()
	)()
	())
	()(
	()()
	(())
	())(		*/
