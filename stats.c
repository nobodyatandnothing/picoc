//
// Created by Russell Joyce on 12/05/2020.
//

#include "stats.h"

#define NO_RUN_MODES 7
#define NO_TOKENS 102
#define NO_TYPES 13

struct LexTokenStat {
    const char* name;
    int count[NO_RUN_MODES];
};

struct TypeStat {
    const char* name;
    int assignments;
};

const char *RunModeNames[NO_RUN_MODES] = {
        "RunModeRun",
        "RunModeSkip",
        "RunModeReturn",
        "RunModeCaseSearch",
        "RunModeBreak",
        "RunModeContinue",
        "RunModeGoto"
};

struct LexTokenStat LexTokenStats[NO_TOKENS] = {
        {"TokenNone", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenComma", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenAddAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenSubtractAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenMultiplyAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenDivideAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenModulusAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenShiftLeftAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenShiftRightAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenArithmeticAndAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenArithmeticOrAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenArithmeticExorAssign", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenQuestionMark", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenColon", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenLogicalOr", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenLogicalAnd", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenArithmeticOr", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenArithmeticExor", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenAmpersand", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenEqual", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenNotEqual", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenLessThan", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenGreaterThan", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenLessEqual", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenGreaterEqual", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenShiftLeft", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenShiftRight", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenPlus", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenMinus", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenAsterisk", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenSlash", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenModulus", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenIncrement", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenDecrement", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenUnaryNot", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenUnaryExor", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenSizeof", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenCast", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenLeftSquareBracket", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenRightSquareBracket", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenDot", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenArrow", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenOpenBracket", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenCloseBracket", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenIdentifier", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenIntegerConstant", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenFloatConstant", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenDoubleConstant", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenStringConstant", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenCharacterConstant", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenSemicolon", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenEllipsis", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenLeftBrace", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenRightBrace", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenIntType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenCharType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenFloatType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenDoubleType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenVoidType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenEnumType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenLongType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenSignedType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenShortType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenStaticType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenAutoType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenRegisterType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenExternType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenStructType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenUnionType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenUnsignedType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenTypedef", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenContinue", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenDo", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenElse", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenFor", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenGoto", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenIf", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenWhile", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenBreak", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenSwitch", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenCase", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenDefault", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenReturn", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenHashDefine", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenHashInclude", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenHashIf", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenHashIfdef", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenHashIfndef", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenHashElse", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenHashEndif", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenNew", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenDelete", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenOpenMacroBracket", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenEOF", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenEndOfLine", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenEndOfFunction", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenBackSlash", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenVolatileType", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenHashPragma", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenUnderscorePragma", {0, 0, 0, 0, 0, 0, 0}},
        {"TokenConstType", {0, 0, 0, 0, 0, 0, 0}}
};

struct TypeStat TypeStats[NO_TYPES] = {
        {"Char", 0},
        {"UnsignedChar", 0},
        {"Short", 0},
        {"UnsignedShort", 0},
        {"Int", 0},
        {"UnsignedInt", 0},
        {"Long", 0},
        {"UnsignedLong", 0},
        {"LongLong", 0},
        {"UnsignedLongLong", 0},
        {"Float", 0},
        {"Double", 0},
        {"Pointer", 0}
};

unsigned int FunctionParameterCounts[PARAMETER_MAX + 1] = {0};
unsigned int FunctionParameterDynamicCounts[PARAMETER_MAX + 1] = {0};
unsigned int FunctionCallDepth = 0;
unsigned int FunctionCallWatermark = 0;
unsigned int LoopDepth = 0;
unsigned int LoopWatermark = 0;
unsigned int ConditionalDepth = 0;
unsigned int ConditionalWatermark = 0;


void stats_log_statement(enum LexToken token, struct ParseState *parser)
{
    if (parser->pc->CollectStats) {
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Parsing Statement %s (%d) in %s (%d) at %s:%d:%d\n", LexTokenStats[token].name, token,
                    RunModeNames[parser->Mode], parser->Mode, parser->FileName, parser->Line, parser->CharacterPos);
        }
        LexTokenStats[token].count[parser->Mode]++;
    }
}


void stats_log_expression(enum LexToken token, struct ParseState *parser)
{
    if (parser->pc->CollectStats) {
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Parsing Expression %s (%d) in %s (%d) at %s:%d:%d\n", LexTokenStats[token].name, token,
                    RunModeNames[parser->Mode], parser->Mode, parser->FileName, parser->Line, parser->CharacterPos);
        }
        LexTokenStats[token].count[parser->Mode]++;
    }
}


void stats_log_function_definition(int parameterCount, struct ParseState *parser)
{
    if (parser->pc->CollectStats) {
        FunctionParameterCounts[parameterCount]++;
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Parsing function definition with %d parameters at %s:%d:%d\n",
                    parameterCount, parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_log_function_entry(struct ParseState *parser, int argCount)
{
    if (parser->pc->CollectStats) {
        FunctionParameterDynamicCounts[argCount]++;
        FunctionCallDepth++;
        if (FunctionCallDepth > FunctionCallWatermark) {
            FunctionCallWatermark = FunctionCallDepth;
        }
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Entering function (current call depth %u, max %u) at %s:%d:%d\n",
                    FunctionCallDepth, FunctionCallWatermark, parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_log_function_exit(struct ParseState *parser)
{
    if (parser->pc->CollectStats) {
        FunctionCallDepth--;
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Leaving function (current call depth %u, max %u) at %s:%d:%d\n",
                    FunctionCallDepth, FunctionCallWatermark, parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_log_loop_entry(struct ParseState *parser)
{
    if (parser->pc->CollectStats) {
        LoopDepth++;
        if (LoopDepth > LoopWatermark) {
            LoopWatermark = LoopDepth;
        }
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Entering loop (current nesting depth %u, max %u) at %s:%d:%d\n",
                    LoopDepth, LoopWatermark, parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_log_loop_exit(struct ParseState *parser)
{
    if (parser->pc->CollectStats) {
        LoopDepth--;
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Leaving loop (current nesting depth %u, max %u) at %s:%d:%d\n",
                    LoopDepth, LoopWatermark, parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_log_conditional_entry(struct ParseState *parser, int condition)
{
    if (parser->pc->CollectStats && condition) {
        ConditionalDepth++;
        if (ConditionalDepth > ConditionalWatermark) {
            ConditionalWatermark = ConditionalDepth;
        }
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Entering conditional (current nesting depth %u, max %u) at %s:%d:%d\n",
                    ConditionalDepth, ConditionalWatermark, parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_log_conditional_exit(struct ParseState *parser, int condition)
{
    if (parser->pc->CollectStats && condition) {
        ConditionalDepth--;
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Leaving conditional (current nesting depth %u, max %u) at %s:%d:%d\n",
                    ConditionalDepth, ConditionalWatermark, parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_log_assignment(struct ParseState *parser, int type) {
    if (parser->pc->CollectStats && (strcmp(parser->FileName, "startup") != 0)) {
        TypeStats[type].assignments++;
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Assignment of type %s at %s:%d:%d\n",
                    TypeStats[type].name, parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_print_tokens(int all)
{
    printf("\n*********\nToken stats:\n");
    for (int i = 0; i < NO_RUN_MODES; i++) {
        printf("***\n");
        printf("%s\n", RunModeNames[i]);
        for (int j = 0; j < NO_TOKENS; j++) {
            if (all || LexTokenStats[j].count[i] > 0) {
                printf("%5d %s\n", LexTokenStats[j].count[i], LexTokenStats[j].name);
            }
        }
    }
    printf("*********\n");
}


void stats_print_tokens_csv()
{
    printf("RunMode");
    for (int j = 0; j < NO_TOKENS; j++) {
        printf(",%s", LexTokenStats[j].name);
    }
    for (int i = 0; i < NO_RUN_MODES; i++) {
        printf("\n%s", RunModeNames[i]);
        for (int j = 0; j < NO_TOKENS; j++) {
            printf(",%d", LexTokenStats[j].count[i]);
        }
    }
    printf("\n");
}


void stats_print_tokens_csv_runmode(enum RunMode runMode)
{
    for (int i = 0; i < NO_TOKENS - 1; i++) {
        printf("%d,", LexTokenStats[i].count[runMode]);
    }
    printf("%d\n", LexTokenStats[NO_TOKENS - 1].count[runMode]);
}


void stats_print_runmode_list(void)
{
    for (int i = 0; i < NO_RUN_MODES - 1; i++) {
        printf("%s,", RunModeNames[i]);
    }
    printf("%s\n", RunModeNames[NO_RUN_MODES - 1]);
}


void stats_print_token_list(void)
{
    for (int i = 0; i < NO_TOKENS - 1; i++) {
        printf("%s,", LexTokenStats[i].name);
    }
    printf("%s\n", LexTokenStats[NO_TOKENS - 1].name);
}


void stats_print_function_parameter_counts(bool dynamic)
{
    for (int i = 0; i < PARAMETER_MAX; i++) {
        if (dynamic)
            printf("%u,", FunctionParameterDynamicCounts[i]);
        else
            printf("%u,", FunctionParameterCounts[i]);
    }
    if (dynamic)
        printf("%u\n", FunctionParameterDynamicCounts[PARAMETER_MAX]);
    else
        printf("%u\n", FunctionParameterCounts[PARAMETER_MAX]);
}


void stats_print_watermarks(void)
{
    printf("%u,%u,%u\n", FunctionCallWatermark, LoopWatermark, ConditionalWatermark);
}


void stats_print_types_list(void)
{
    for (int i = 0; i < NO_TYPES - 1; i++) {
        printf("%s,", TypeStats[i].name);
    }
    printf("%s\n", TypeStats[NO_TYPES - 1].name);
}


void stats_print_assignments(void)
{
    for (int i = 0; i < NO_TYPES; i++) {
        printf("%s: %d\n", TypeStats[i].name, TypeStats[i].assignments);
    }
}


void stats_print_assignments_csv(void)
{
    for (int i = 0; i < NO_TYPES - 1; i++) {
        printf("%d,", TypeStats[i].assignments);
    }
    printf("%d\n", TypeStats[NO_TYPES - 1].assignments);
}
