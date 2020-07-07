/* picoc main program - this varies depending on your operating system and
 * how you're using picoc */
/* platform-dependent code for running programs is in this file */
#if defined(UNIX_HOST) || defined(WIN32)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

/* include only picoc.h here - should be able to use it with only the
    external interfaces, no internals from interpreter.h */
#include "picoc.h"
#include "stats.h"


#if defined(UNIX_HOST) || defined(WIN32)
#include "LICENSE.h"

/* Override via STACKSIZE environment variable */
#define PICOC_STACK_SIZE (32*1024*1024)

int main(int argc, char **argv)
{
    int ParamCount = 1;
    int DontRunMain = false;
    int CollectStats = false;
    int StatsType = 0;
    int StackSize = getenv("STACKSIZE") ? atoi(getenv("STACKSIZE")) : PICOC_STACK_SIZE;
    Picoc pc;

    if (argc < 2 || strcmp(argv[ParamCount], "-h") == 0) {
        printf(PICOC_VERSION "  \n"
               "Format:\n\n"
               "> picoc <file1.c>... [- <arg1>...]          : run a program, calls main() as the entry point\n"
               "> picoc -s <file1.c>... [- <arg1>...]       : run a script, runs the program without calling main()\n"
               "> picoc -d[type] <file1.c>... [- <arg1>...] : run a program, outputting debugging stats\n"
               "> picoc -r                                  : output list of run modes, then quit\n"
               "> picoc -t                                  : output list of tokens, then quit\n"
               "> picoc -i                                  : interactive mode, Ctrl+d to exit\n"
               "> picoc -c                                  : copyright info\n"
               "> picoc -h                                  : this help message\n");
        return 0;
    }

    if (strcmp(argv[ParamCount], "-c") == 0) {
        printf("%s\n", (char*)&__LICENSE);
        return 0;
    }

    PicocInitialize(&pc, StackSize);

    if (strcmp(argv[ParamCount], "-s") == 0) {
        DontRunMain = true;
        PicocIncludeAllSystemHeaders(&pc);
        ParamCount++;
    } else if (strncmp(argv[ParamCount], "-r", 2) == 0) {
        stats_print_runmode_list();
        return 0;
    } else if (strncmp(argv[ParamCount], "-t", 2) == 0) {
        stats_print_token_list();
        return 0;
    } else if (strncmp(argv[ParamCount], "-d", 2) == 0) {
        if (strlen(argv[ParamCount]) > 2) {
            StatsType = atoi(&argv[ParamCount][2]);
        }
        CollectStats = true;
        pc.CollectStats = true;
        if (StatsType > 9) {
            pc.PrintStats = true;
            StatsType -= 10;
        } else {
            pc.PrintStats = false;
        }
        ParamCount++;
    }

    if (argc > ParamCount && strcmp(argv[ParamCount], "-i") == 0) {
        PicocIncludeAllSystemHeaders(&pc);
        PicocParseInteractive(&pc);
    } else {
        if (PicocPlatformSetExitPoint(&pc)) {
            PicocCleanup(&pc);
            return pc.PicocExitValue;
        }

        for (; ParamCount < argc && strcmp(argv[ParamCount], "-") != 0; ParamCount++)
            PicocPlatformScanFile(&pc, argv[ParamCount]);

        if (!DontRunMain)
            PicocCallMain(&pc, argc - ParamCount, &argv[ParamCount]);
    }

    PicocCleanup(&pc);

    /* Stats types:
     * 0: Print tokens that have been seen for each run mode
     * 1: Print all tokens for each run mode
     * 2: Print all tokens for each run mode in CSV format (multiple rows, with header row)
     * 3: Print all tokens for RunModeRun only in CSV format (one row, no header row)
     * 4: Print CSV list of function parameter counts
     *
     * Add 10 to each type to also print token information to stderr in real-time as they are parsed.
     */

    if (CollectStats) {
        switch (StatsType) {
            case 0:
                stats_print_tokens(false);
                break;
            case 1:
                stats_print_tokens(true);
                break;
            case 2:
                stats_print_tokens_csv();
                break;
            case 3:
                stats_print_tokens_csv_runmode(RunModeRun);
                break;
            case 4:
                stats_print_function_parameter_counts();
                break;
            default:
                break;
        }
    }

    return pc.PicocExitValue;
}
#endif
