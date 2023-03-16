#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

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
	fp = fopen("pass.txt", "a");

	if (fp == NULL)
	{
		printf("Can't open file");
		return;
	}

	fprintf(fp, "%s: %s\n", sitename, password);

	fclose(fp);
}


int main(int argc, char *argv[])
{
	int N;
	int i = 0;

	if (strcmp(argv[1], "w") == 0 && argc == 4)
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
	

	return (0);
}
