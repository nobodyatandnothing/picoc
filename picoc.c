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
    long StatsType = 0;
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
               "> picoc -y                                  : output list of basic types, then quit\n"
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
    } else if (strncmp(argv[ParamCount], "-y", 2) == 0) {
        stats_print_types_list();
        return 0;
    } else if (strncmp(argv[ParamCount], "-d", 2) == 0) {
        if (strlen(argv[ParamCount]) > 2) {
            StatsType = strtol(&argv[ParamCount][2], NULL, 0);
        }
        CollectStats = true;
        pc.CollectStats = true;
        if (StatsType >= 0x1000) {
            pc.PrintMemory = true;
            StatsType -= 0x1000;
        }
        if (StatsType >= 0x100) {
            pc.PrintExpressions = true;
            StatsType -= 0x100;
        }
        if (StatsType >= 0x10) {
            pc.PrintStats = true;
            StatsType -= 0x10;
        }
        if (StatsType == 0xa)
            pc.CollectFullExpressions = true;
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
     * 0x0: Print tokens that have been seen for each run mode
     * 0x1: Print all tokens for each run mode
     * 0x2: Print all tokens for each run mode in CSV format (multiple rows, with header row)
     * 0x3: Print all tokens for RunModeRun only in CSV format (one row, no header row)
     * 0x4: Print CSV list of function definition parameter counts
     * 0x5: Print CSV list of runtime function call parameter counts
     * 0x6: Print maximum measured function call, loop, conditional statement and expression chain depths
     * 0x7: Print number of assignments to each basic variable type
     * 0x8: Print number of assignments to each basic variable type, in CSV format (one row, no header row)
     * 0x9: Print summary of expressions encountered during execution and their counts
     * 0xa: Print full list of expressions encountered during execution
     * 0xb: Print summary information about expression chains
     * 0xc: Print information about stack depths and frame sizes
     * 0xd: Print information about stack depths and frame sizes in CSV format
     * 0xe: Print summary of expressions encountered during execution and their counts, in CSV format
     *
     * Add 0x0010 to each type to also print token information to stderr in real-time as they are parsed.
     * Add 0x0100 to each type to also print expressions information to stderr in real-time as they are executed.
     * Add 0x1000 to each type to also print memory information to stderr in real-time as it is allocated.
     */

    if (CollectStats) {
        switch (StatsType) {
            case 0x00:
                stats_print_tokens(false);
                break;
            case 0x01:
                stats_print_tokens(true);
                break;
            case 0x02:
                stats_print_tokens_csv();
                break;
            case 0x03:
                stats_print_tokens_csv_runmode(RunModeRun);
                break;
            case 0x04:
                stats_print_function_parameter_counts(false);
                break;
            case 0x05:
                stats_print_function_parameter_counts(true);
                break;
            case 0x06:
                stats_print_max_depths();
                break;
            case 0x07:
                stats_print_assignments();
                break;
            case 0x08:
                stats_print_assignments_csv();
                break;
            case 0x09:
                stats_print_expressions_summary();
                break;
            case 0x0a:
                stats_print_expression_chains();
                break;
            case 0x0b:
                stats_print_expression_chains_summary();
                break;
            case 0x0c:
                stats_print_stack_info();
                break;
            case 0x0d:
                stats_print_stack_info_csv();
                break;
            case 0x0e:
                stats_print_expressions_summary_csv();
                break;
            default:
                break;
        }
    }

    return pc.PicocExitValue;
}
#endif
