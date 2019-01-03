#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	//Declare variables
	FILE *inputPointer;		//Pointer to user's input file
	char filename[100];		//Buffer in which to store the file name;
	char currentChar;		//The current character that we are counting
	int totalCount;			//The current total count of character in the file
	int targetCount;		//The count of target letter in the file
	pid_t pid; 				//The fork's pid

	//Print prompt for user before betting their file path from stdin
	printf("Enter the path of the file you would like to be analyzed: \n");
	scanf("%s", filename);

	int i = 65;

	//loop through the alphabet, forking for each letter
	while(i <= 90)
	{
		//Reset variables
		totalCount = 0;
		targetCount = 0;
		//Create a status int fot the parent to watch
		int status;
		int forkValue;
		//Generate fork and check for errors
		pid_t pid;
		pid = fork();

		//create if statment for child process to use
		if(pid == 0)
		{
			//Open the file
			inputPointer = fopen(filename, "r");
			//If no file is opened, return an error
			if(inputPointer == NULL)
			{
				printf("Error when opening file, please try again or check system files");
				exit(1);
			}

			//Get the next character from the file
			currentChar = fgetc(inputPointer);

			//check each character of the file until EOF is reached
			while(currentChar != EOF)
			{
				//Check if it's the character we're looking for, then increment the appropriate counters
				if(currentChar == i || currentChar == (i + 32))
				{
					targetCount++;
					totalCount++;
				}
				else if(currentChar < 33 || currentChar == 127)
				{}
				else
				{
					totalCount++;
				}

				//Get the next character from the file
				currentChar = fgetc(inputPointer);
			}

			fclose(inputPointer);
			//Calculate the statistics for this letter and then print them
			double stat = ((double)targetCount / (double) totalCount) * 100;
			printf("Frequency of %c: ", i);
			printf("%lf%% of characters.\n", stat);
			exit(0);
		}
		//check if there was an error forking the program
		else if(pid < 0)
		{
			perror("error forking, try again or check system files");
			exit(1);
		}
		//run parent process otherwise
		else
		{
			wait(&status);
		}
		i++;

	}
			return 0;
}
