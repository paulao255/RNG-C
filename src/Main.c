/* Importations: */
#include "C-Utils/cutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* RNG Game version variables: */
#define RNG_GAME_FULL_VERSION     20260127                          /* RNG Game full version variable (2026/01/27).                   */
#define RNG_GAME_MAJOR_VERSION    2026                              /* RNG Game major version variable (2026).                        */
#define RNG_GAME_MINOR_VERSION    1                                 /* RNG Game minor version variable (01).                          */
#define RNG_GAME_PATCH_VERSION    27                                /* RNG Game patch version variable (26).                          */

/* Global variables: */
static long double all_attempts = 0.0L;                             /* All attempts variable.                                         */
static long double wins         = 0.0L;                             /* All wins variable.                                             */
static long double loses        = 0.0L;                             /* All loses variable.                                            */

#define MIN                        0                                /* Minimum value variable.                                        */
#define MAX                       10                                /* Maximum value variable.                                        */

/* Functions prototype: */
static int save_data(const char *path, const char *name);           /* Save game data function.                                       */
static int load_data(const char *path, const char *format);         /* Load game data function.                                       */

/* Main code: */
int main(void)
{
	/* Start seed: */
	srand((unsigned) time(NULL));

	/* Main variables: */
	int loop = 1;                                               /* First loop variable.                                           */
	int number = 0;                                             /* Number to use variable.                                        */
	int random_number[2] = {rand() % (MAX - MIN + 1) + MIN, 0}; /* Random numbers variable (random number and old random number). */
	long double round_attempts = 0.0L;                          /* Attempts variable.                                             */
	char option[8192] = "";                                     /* First option variable.                                         */
	char snumber[8192] = "";                                    /* String number variable.                                        */

	/* Initializations before the game (load): */
	enable_vt_and_utf8();
	load_data("data/statistics.csv", "%Lf,%Lf,%Lf");

	/* Main loop: */
	while(loop == 1)
	{
		clear_terminal();
		puts("=======================================");
		printf("========= RNG Game %.4d-%.2d-%.2d =========\n", RNG_GAME_MAJOR_VERSION, RNG_GAME_MINOR_VERSION, RNG_GAME_PATCH_VERSION);
		puts("=======================================");
		puts("         [ 0 ] Options...");
		puts("         [ 1 ] Play game!");
		fputs("\t   Your answer: ", stdout);
		scanf("%8191s", option);
		clear_terminal();

		if(strcmp(option, "0") == 0)
		{
			++loop;

			while(loop == 2)
			{
				puts("==================================");
				puts("============ Options =============");
				puts("==================================");
				printf("  %s[ 0 ] Return%s\n", BOLD, BASE_TERMINAL);
				printf("  %s[ 1 ] Save%s and %squit...%s\n", GREEN_COLOR, BASE_TERMINAL, RED_COLOR, BASE_TERMINAL);
				printf("  %s[ 2 ] Change the random number%s\n", CYAN_COLOR, BASE_TERMINAL);
				printf("  %s[ 3 ] View statistics%s\n", YELLOW_COLOR, BASE_TERMINAL);
				printf("  %s[ 4 ] Read \"READ-ME\"%s\n", YELLOW_COLOR, BASE_TERMINAL);
				fputs("\t Your answer: ", stdout);
				scanf("%8191s", option);

				if(strcmp(option, "0") == 0)
				{
					--loop;
				}

				else if(strcmp(option, "1") == 0)
				{
					loop = 0;
					save_data("data", "statistics.csv");
					clear_terminal();
				}

				else if(strcmp(option, "2") == 0)
				{
					clear_terminal();
					random_number[1] = random_number[0];
					printf("Now your attempts restart and the random number has changed to a new value! (Old random number: %d)\n", random_number[1]);
					random_number[0] = rand() % (MAX - MIN + 1) + MIN;
					round_attempts = 0.0L;
					petc();
					clear_terminal();
				}

				else if(strcmp(option, "3") == 0)
				{
					clear_terminal();
					printf("Number of all attempts: %0.Lf\n", all_attempts);
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					printf("Number of wins: %0.Lf\n", wins);
					printf("Number of loses: %0.Lf\n", loses);
					petc();
					clear_terminal();
				}

				else if(strcmp(option, "3.14") == 0 || strcmp(option, "3,14") == 0)
				{
					clear_terminal();
					easter_egg_function();
					clear_terminal();
				}

				else if(strcmp(option, "4") == 0)
				{
					clear_terminal();
					rrmf();
					apetc();
					clear_terminal();
				}

				else
				{
					clear_terminal();
				}
			}
		}

		else if(strcmp(option, "1") == 0)
		{
			printf("Type the number that you think it is (%sMin: %d%s, %sMax: %d%s, if you type another number below %d it will be rounded to %d, and the same will hapend to the number above %d...): ", BOLD, MIN, BASE_TERMINAL, BOLD, MAX, BASE_TERMINAL, MIN, MIN, MAX);
			scanf("%8191s", snumber);
			number = atoi(snumber);
			clear_terminal();
			fputs("Soo... ", stdout);

			if(number > MAX)
			{
				number = MAX;

				if(number > random_number[0])
				{
					printf("%s%sYou lose!%s The random number is below %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, MAX);
					
					++all_attempts;
					++round_attempts;
					++loses;
					
					save_data("data", "statistics.csv");
				}

				else if(number == random_number[0])
				{
					printf("%s%sYou win!%s The random number is = %d!\n", BOLD, GREEN_COLOR, BASE_TERMINAL, MAX);
					puts("Now the random number has changed to a new value!");
					
					++all_attempts;
					++round_attempts;
					++wins;
					
					save_data("data", "statistics.csv");
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);
					
					random_number[0] = rand() % (MAX - MIN + 1) + MIN;
					round_attempts = 0.0L;
				}
			}

			else if(number < MIN)
			{
				number = MIN;

				if(number < random_number[0])
				{
					printf("%s%sYou lose!%s The random number is above %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, MIN);

					++all_attempts;
					++round_attempts;
					++loses;

					save_data("data", "statistics.csv");
				}

				else if(number == random_number[0])
				{
					printf("%s%sYou win!%s The random number is = %d!\n", BOLD, GREEN_COLOR, BASE_TERMINAL, MIN);
					puts("Now the random number has changed to a new value!");

					++all_attempts;
					++round_attempts;
					++wins;

					save_data("data", "statistics.csv");
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);

					random_number[0] = rand() % (MAX - MIN + 1) + MIN;
					round_attempts = 0.0L;
				}
			}

			else
			{
				if(number < random_number[0])
				{
					printf("%s%sYou lose!%s The random number is above %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, number);

					++all_attempts;
					++round_attempts, ++loses;

					save_data("data", "statistics.csv");
				}

				else if(number == random_number[0])
				{
					printf("%s%sYou win!%s The random number is = %d!\n", BOLD, GREEN_COLOR, BASE_TERMINAL, number);
					puts("Now the random number has changed to a new value!");

					++all_attempts;
					++round_attempts;
					++wins;

					save_data("data", "statistics.csv");
					printf("Number of attempts in this round: %0.Lf\n", round_attempts);

					random_number[0] = rand() % (MAX - MIN + 1) + MIN;
					round_attempts = 0.0L;
				}

				else if(number > random_number[0])
				{
					printf("%s%sYou lose!%s The random number is below %d!\n", BOLD, RED_COLOR, BASE_TERMINAL, number);

					++all_attempts;
					++round_attempts;
					++loses;

					save_data("data", "statistics.csv");
				}
			}

			petc();
		}
	}

	return 0;
}

/* Save data function: */
static int save_data(const char *path, const char *name)
{
	make_directory(path, 0755);

	char full_path[4096] = "";
	sprintf(full_path, "%s/%s", path, name);
	FILE *statistics = fopen(full_path, "w");

	if(!statistics)
	{
		perror("Error");

		return 1;
	}

	fprintf(statistics, "%Lf,%Lf,%Lf\n", all_attempts, wins, loses);
	fclose(statistics);

	return 0;
}

/* Load data function: */
static int load_data(const char *path, const char *input_format)
{
	FILE *statistics = fopen(path, "r");

	if(!statistics)
	{
		perror("Error");
		save_data("data", "statistics.csv");

		return 1;
	}

	char buffer[8192] = "";

	if(fgets(buffer, sizeof(buffer), statistics) != NULL)
	{
		long double value[3] = {0.0L, 0.0L, 0.0L};
		const int itens = sscanf(buffer, input_format, &value[0], &value[1], &value[2]);

		if(itens == 3)
		{
			all_attempts = value[0];
			wins         = value[1];
			loses        = value[2];
		}

		else
		{
			save_data("data", "statistics.csv");
		}
	}

	else
	{
		save_data("data", "statistics.csv");
	}

	fclose(statistics);

	return 0;
}
