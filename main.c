#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OUT   0
#define IN    1

#define FALSE 0
#define TRUE  1

#define SIZE  32
#define LEN   512

#define COMMENTS       0
#define IDENTIFICATORS 1
#define COUNT          2

int getInputFromMenu();
void fileToFile();
void fileToConsole();
void consoleToFile();
void consoleToConsole();
void results(FILE *input, FILE *output);
void getFileName(char *arr, int mode);
void counter(char *line, int *data);

int main()
{
	system("chcp 1251");
	while (1)
	{
		system("cls");
		switch (getInputFromMenu())
		{
		case 1:
			fileToFile();
			break;
		case 2:
			fileToConsole();
			break;
		case 3:
			consoleToFile();
			break;
		case 4:
			consoleToConsole();
			break;
		default:
			return 0;
			break;
		}
		system("PAUSE");
	}
}
int getInputFromMenu()
{
	int input;

	printf("�������� ����� �� 0-4\n");
	printf("1. ������ �� ���� � ����� ��� ����\n");
	printf("2. ������ �� ���� � ��������� �� ������\n");
	printf("3. ������ �� ������������ � ����� ��� ����\n");
	printf("4. ������ �� ������������ � ��������� �� ������\n");
	printf("0. ����\n");

	do
	{
		printf("\n�������� �����: ");
		fflush(stdin);
		scanf("%d", &input);
	} while ((input < 0) || (input > 4));

	return input;
}

void fileToFile()
{
	FILE *fileInput = NULL;
	FILE *fileOutput = NULL;
	char fileNameR[SIZE];
	char fileNameW[SIZE];

	getFileName(fileNameR, TRUE);
	fileInput = fopen(fileNameR, "r");
	if (NULL == fileInput)
	{
		perror("\nERROR");
		return;
	}
	getFileName(fileNameW, FALSE);
	fileOutput = fopen(fileNameW, "w");
	if (NULL == fileOutput)
	{
		perror("\nERROR");
		return;
	}

	results(fileInput, fileOutput);

	if (fclose(fileInput) != 0)
	{
		perror("\nERROR");
		return;
	}
	if (fclose(fileOutput) != 0)
	{
		perror("\nERROR");
		return;
	}
}

void fileToConsole()
{
	FILE *fileInput = NULL;
	char fileNameR[SIZE];

	getFileName(fileNameR, TRUE);
	fileInput = fopen(fileNameR, "r");
	if (NULL == fileInput)
	{
		perror("\nERROR");
		return;
	}

	results(fileInput, stdout);

	if (fclose(fileInput) != 0)
	{
		perror("\nERROR");
		return;
	}
}
void consoleToFile()
{
	FILE *fileOutput = NULL;
	char fileNameW[SIZE];

	getFileName(fileNameW, FALSE);
	fileOutput = fopen(fileNameW, "w");
	if (NULL == fileOutput)
	{
		perror("\nERROR");
		return;
	}

	printf("\n�������� ����������:\n");
	results(stdin, fileOutput);

	if (fclose(fileOutput) != 0)
	{
		perror("\nERROR");
		return;
	}
}

void consoleToConsole()
{
	printf("\n�������� ����������:\n");
	results(stdin, stdout);
}

void getFileName(char * arr, int mode)
{
	if (FALSE == mode)
	{
		printf("\n�������� ���� �� ���������: ");
		fflush(stdin);
		scanf("%31s", arr);
	}
	else
	{
		printf("\n�������� ���� �� ������(.c): ");
		fflush(stdin);
		scanf("%31s", arr);

		while (FALSE == ((arr[strlen(arr) - 2] == '.') && (arr[strlen(arr) - 1] == 'c')))
		{
			printf("\nERROR: %s �� �������� �� .c!\n", arr);
			printf("\n�������� �������� ����: ");
			scanf("%s", arr);
		}
	}
}

void results(FILE *input, FILE *output)
{
	int data[COUNT] = { 0 };
	char line[LEN];

	while (fgets(line, LEN, input) != NULL)
	{
		counter(line, data);
	}

	fprintf(output, "\n����� �� ��������� ������� � ����������� �: %d\n", data[COMMENTS]);
	fprintf(output, "����� �� ��������� � ���������������� �: %d\n", data[IDENTIFICATORS]);
}

void counter(char *line, int *data)
{
	static char state = OUT;
	int wordState = OUT;
	char *str = line;
	int counter = 0;
	char word[SIZE] = { 0 };

	while (*str != '\0')
	{
		if ((*str == '/' || *str == '"' || *str == '\'' || *str == '#') && state == OUT)
		{
			state = *str;
		}
		else if (state != OUT)
		{
			switch (state)
			{
			case '/':
				if (*str == '/')
				{
					state = OUT;
					while (*str != '\n')
					{
						str++;
						if (isspace(*str) == FALSE)
						{
							data[COMMENTS]++;
						}
					}
				}
				else if (*str == '*')
				{
					state = *str;
					while ((*str != '\n') && (state != OUT))
					{
						str++;
						if (isspace(*str) == FALSE)
						{
							data[COMMENTS]++;
						}
						if (*str == '*')
						{
							str++;
							if (*str == '/')
							{
								state = OUT;
								str++;
								data[COMMENTS]--;
							}
							else
							{
								str--; //because of cases like /*...**...*/
							}
						}
					}
				}
				else
					state = OUT;
				break;
			case '*':
				while ((*str != '\n') && (state != OUT))
				{
					if (isspace(*str) == FALSE)
					{
						data[COMMENTS]++;
					}
					if (*str == '*')
					{
						str++;
						if (*str == '/')
						{
							state = OUT;
							str++;
							data[COMMENTS]--;
						}
						else
						{
							str--; //because of cases like /*...**...*/
						}
					}
					str++;
				}
				break;
			case '\"':
				while (*str != '\"')
				{
					if (*str == '\\') //because of cases like "...\"..."
					{
						str++;
					}
					str++;
				}
				state = OUT;
				break;
			case '\'':
				while (*str != '\'')
				{
					if (*str == '\\') //because of the case '/''
					{
						str++;
					}
					str++;
				}
				state = OUT;
				break;
			case '#':
				while (*str != '\n')
				{
					str++;
				}
				state = OUT;
				break;
			}
		}
		if (state == OUT)
		{
			if ((isalnum(*str) != FALSE) || (*str == '_')) //The IDENTIFICATOR's name can contain letters, digits and underscore
			{
				if (wordState == OUT)
				{
					wordState = IN;
				}
				word[counter] = *str;
				counter++;
			}
			else
			{
				if (wordState == IN)
				{
					wordState = OUT;
					word[counter] = '\0';
					if (isdigit(word[0]) == FALSE) //The IDENTIFICATOR's name can't start with a digit
					{
						data[IDENTIFICATORS] += counter;
					}
					counter = 0;
					memset(word, 0, sizeof(word));
				}
			}
		}
		str++;
	}
}
