//
// Created by Russell Joyce on 12/05/2020.
//

#ifndef PICOC_STATS_H
#define PICOC_STATS_H

#include "interpreter.h"

#define NO_RUN_MODES 7
#define NO_TOKENS 98

extern const char *RunModeNames[NO_RUN_MODES];

struct LexTokenStat {
    const char* name;
    int count[NO_RUN_MODES];
};

extern struct LexTokenStat LexTokenStats[NO_TOKENS];

void stats_log_statement(enum LexToken token, struct ParseState *parser);
void stats_log_expression(enum LexToken token, struct ParseState *parser);
void stats_print_tokens(int all);

#endif //PICOC_STATS_H
