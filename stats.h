//
// Created by Russell Joyce on 12/05/2020.
//

#ifndef PICOC_STATS_H
#define PICOC_STATS_H

#include "interpreter.h"

#define NO_RUN_MODES 7
#define NO_TOKENS 101

extern const char *RunModeNames[NO_RUN_MODES];

struct LexTokenStat {
    const char* name;
    int count[NO_RUN_MODES];
};

extern struct LexTokenStat LexTokenStats[NO_TOKENS];

void stats_log_statement(enum LexToken token, struct ParseState *parser);
void stats_log_expression(enum LexToken token, struct ParseState *parser);
void stats_log_function(int parameterCount, struct ParseState *parser);
void stats_print_tokens(int all);
void stats_print_tokens_csv(void);
void stats_print_tokens_csv_runmode(enum RunMode runMode);
void stats_print_runmode_list(void);
void stats_print_token_list(void);
void stats_print_function_parameter_counts(void);

#endif //PICOC_STATS_H
