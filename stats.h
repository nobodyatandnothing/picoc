//
// Created by Russell Joyce on 12/05/2020.
//

#ifndef PICOC_STATS_H
#define PICOC_STATS_H

#include "interpreter.h"

#define STATS_TYPE_Char 0
#define STATS_TYPE_UnsignedChar 1
#define STATS_TYPE_Short 2
#define STATS_TYPE_UnsignedShort 3
#define STATS_TYPE_Int 4
#define STATS_TYPE_UnsignedInt 5
#define STATS_TYPE_Long 6
#define STATS_TYPE_UnsignedLong 7
#define STATS_TYPE_LongLong 8
#define STATS_TYPE_UnsignedLongLong 9
#define STATS_TYPE_FP 10
#define STATS_TYPE_Pointer 11

void stats_log_statement(enum LexToken token, struct ParseState *parser);
void stats_log_expression(enum LexToken token, struct ParseState *parser);
void stats_log_function_definition(int parameterCount, struct ParseState *parser);
void stats_log_function_entry(struct ParseState *parser, int argCount);
void stats_log_function_exit(struct ParseState *parser);
void stats_log_loop_entry(struct ParseState *parser);
void stats_log_loop_exit(struct ParseState *parser);
void stats_log_conditional_entry(struct ParseState *parser, int condition);
void stats_log_conditional_exit(struct ParseState *parser, int condition);
void stats_log_assignment(struct ParseState *parser, int type);
void stats_print_tokens(int all);
void stats_print_tokens_csv(void);
void stats_print_tokens_csv_runmode(enum RunMode runMode);
void stats_print_runmode_list(void);
void stats_print_token_list(void);
void stats_print_function_parameter_counts(bool dynamic);
void stats_print_watermarks(void);
void stats_print_types_list(void);
void stats_print_assignments(void);
void stats_print_assignments_csv(void);

#endif //PICOC_STATS_H
