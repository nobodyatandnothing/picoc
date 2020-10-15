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
#define STATS_TYPE_Float 10
#define STATS_TYPE_Double 11
#define STATS_TYPE_Pointer 12

enum ExpressionType {
    ExpressionPrefix,
    ExpressionInfix,
    ExpressionPostfix,
    ExpressionReturn
};

void stats_log_statement(enum LexToken token, struct ParseState *parser);
void stats_log_expression_token_parse(enum LexToken token, struct ParseState *parser);
void stats_log_function_definition(int parameterCount, struct ParseState *parser);
void stats_log_function_entry(struct ParseState *parser, int argCount);
void stats_log_function_exit(struct ParseState *parser);
void stats_log_loop_entry(struct ParseState *parser);
void stats_log_loop_exit(struct ParseState *parser);
void stats_log_conditional_entry(struct ParseState *parser, int condition);
void stats_log_conditional_exit(struct ParseState *parser, int condition);
void stats_log_assignment(struct ParseState *parser, int type);
void stats_log_expression_parse(struct ParseState *Parser);
void stats_log_expression_stack_collapse(struct ParseState *parser);
void stats_log_expression_evaluation(struct ParseState *parser, enum ExpressionType Type, enum LexToken Op, struct Value *BottomValue, struct Value *TopValue);
void stats_log_stack_frame_add(struct ParseState *parser, const char *funcName);
void stats_log_stack_frame_pop(struct ParseState *parser);
void stats_log_stack_allocation(struct ParseState *parser, int Size);
void stats_log_stack_pop(struct ParseState *parser, struct Value *Var);
void stats_log_variable_definition(struct ParseState *parser, char *Ident, struct ValueType *Typ, int IsGlobal);
void stats_print_tokens(int all);
void stats_print_tokens_csv(void);
void stats_print_tokens_csv_runmode(enum RunMode runMode);
void stats_print_runmode_list(void);
void stats_print_token_list(void);
void stats_print_function_parameter_counts(bool dynamic);
void stats_print_max_depths(void);
void stats_print_types_list(void);
void stats_print_assignments(void);
void stats_print_assignments_csv(void);
void stats_print_expressions_summary(void);
void stats_print_expressions_summary_csv(void);
void stats_print_expression_chains_summary(void);
void stats_print_expression_chains(void);
void stats_print_memory_info(void);
void stats_print_memory_info_csv(void);

#endif //PICOC_STATS_H
