#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

void pass_gen(int N, char *sitename)
{
	int i = 0;
	int j = 0;
	int randomizer = 0;
	int k = 0;

	srand((unsigned int)(time(NULL)));

	char numbers[] = "0123456789";
	char letter[] = "abcdefghijklmnopqrstuvwxyz";
	char LETTER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char symbols[] = "!@#$^&*?";
	char password[N + 1];


	for (i = 0; i < N; i++)
	{
		if (randomizer == 1)
		{
			password[i] = numbers[rand() % 10];
			randomizer = rand() % 4;
			printf("%c", password[i]);

		}
		else if (randomizer == 2)
		{
			password[i] = letter[rand() % 26];
			randomizer = rand() % 4;
			printf("%c", password[i]);
		}
		else if (randomizer == 3)
		{
			password[i] = LETTER[rand() % 26];
			randomizer = rand() % 4;
			printf("%c", password[i]);
		}
		else
		{
			password[i] = symbols[rand() % 8];
			randomizer = rand() % 4;
			printf("%c", password[i]);
		}

	}

	printf("\n");
	password[N] = '\0';

	FILE *fp;
	char filepath[] = "/etc/mypasswords/passman.txt";

	if (access(filepath, F_OK) == -1)
	{
		fp = fopen(filepath, "w");
		fclose(fp);
	}

	fp = fopen(filepath, "r");

	if (fp == NULL)
	{
		printf("Unable to access password file\n");
		return;
	}
	char line[100];
	int found = 0;

	while (fgets(line, 100, fp) != NULL)
	{
		if (strstr(line, sitename) != NULL)
		{
			printf("That site name already exists.\n");
			found = 1;
			break;
		}
	}
	fclose(fp);

	if(!found)
	{
		fp = fopen(filepath, "a");

		if (fp == NULL)
		{
			printf("Can't write to file\n");
			return;
		}

		fprintf(fp, "%s: %s\n", sitename, password);

		fclose(fp);
	}
}

void read_pass(char *sitename)
{
	FILE *fp;
	char line[100];
	int found = 0;
	char filepath[] = "/etc/mypasswords/passman.txt";

	fp = fopen(filepath, "r");
	if (fp == NULL)
	{
		printf("Unable to access file\n");
	}
	else
	{
		while (fgets(line, 100, fp) != NULL)
		{
			if (strncmp(line, sitename, strlen(sitename)) == 0 && line[strlen(sitename)] == ':')
			{
				printf("%s", line);
				found = 1;
				break;
			}
		}

		if (!found)
		{
			printf("Password not found\n");
		}
		fclose(fp);
	}
}

void delete_pass(char *sitename)
{
	FILE *fp;
	FILE *temp;
	char line[100];
	int found = 0;
	char ans;
	char filepath[] = "/etc/mypasswords/passman.txt";
	char tempfile[] = "/etc/mypasswords/temppassman.txt";

	fp = fopen(filepath, "r");

	if (fp == NULL)
	{
		printf("Unable to open password file\n");
		return;
	}

	temp = fopen(tempfile, "w");
	{
		if (temp == NULL)
		{
			printf("Unable to make temp file\n");
			fclose(fp);
		}
	}

	while (fgets(line, 100, fp) != NULL)
	{
		if(strncmp(line, sitename, strlen(sitename)) == 0 && line[strlen(sitename)] == ':')
		{
			found = 1;
		}
		else
		{
			fputs(line, temp);
		}
	}
	fclose(fp);
	fclose(temp);

	if(remove(filepath) != 0)
	{
		printf("Unable to delete password file\n");
	}

	if (rename(tempfile, filepath)!= 0)
	{
		printf("Unable to rename temporary file\n");
	}

	if (found)
	{
		printf("%s Password deleted successfully\n", sitename);
	}
	else
	{
		printf("Password doesn't exist\n");
	}
}

int main(int argc, char *argv[])
{
	int N;
	int i = 0;

	if (argc < 3 || argc > 4)
	{
		printf("Usage:\nWriting: passman w sitename passwordlength\nReading: passman r sitename\nDeleting: passman x sitename\n");
		return (1);
	}
	else
	{

	if (strcmp(argv[1], "w") == 0)
	{
		if (argc == 4)
		{
			for (; argv[3][i] != '\0'; i++)
			{
				if (!isdigit(argv[3][i]))
				{
					printf("Usage: w sitename length\n");
					return (1);
				}
				else
				{
					break;
				}
			}
			N = atoi(argv[3]);
			pass_gen(N, argv[2]);
		}
		else
		{
			printf("Usage: w username length\n");
			return (1);
		}
	}

	if (strcmp(argv[1], "r") == 0)
	{
		if (argc == 3)
		{
			read_pass(argv[2]);
		}
		else
		{
			printf("Usage: r sitename\n");
		}
	}
	if (strcmp(argv[1], "x") == 0)
	{
		if (argc == 3)
		{
			delete_pass(argv[2]);
		}
		else
		{
			printf("Usage: x sitename\n");
		}
	}
	}
	return (0);
}
