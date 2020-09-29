//
// Created by Russell Joyce on 12/05/2020.
//

#include "stats.h"
#include "interpreter.h"

#define NUM_RUN_MODES 7
#define NUM_TOKENS 107
#define NUM_TYPES 13
#define NUM_BASE_TYPES 22
#define NUM_OPERATORS 45
#define NUM_EXPRESSION_TYPES 4

struct LexTokenStat {
    const char* name;
    int count[NUM_RUN_MODES];
};

struct TypeStat {
    const char* name;
    int assignments;
};

const char *RunModeNames[NUM_RUN_MODES] = {
        "RunModeRun",
        "RunModeSkip",
        "RunModeReturn",
        "RunModeCaseSearch",
        "RunModeBreak",
        "RunModeContinue",
        "RunModeGoto"
};

struct LexTokenStat LexTokenStats[NUM_TOKENS] = {
        {"TokenNone"},
        {"TokenComma"},
        {"TokenAssign"},
        {"TokenAddAssign"},
        {"TokenSubtractAssign"},
        {"TokenMultiplyAssign"},
        {"TokenDivideAssign"},
        {"TokenModulusAssign"},
        {"TokenShiftLeftAssign"},
        {"TokenShiftRightAssign"},
        {"TokenArithmeticAndAssign"},
        {"TokenArithmeticOrAssign"},
        {"TokenArithmeticExorAssign"},
        {"TokenQuestionMark"},
        {"TokenColon"},
        {"TokenLogicalOr"},
        {"TokenLogicalAnd"},
        {"TokenArithmeticOr"},
        {"TokenArithmeticExor"},
        {"TokenAmpersand"},
        {"TokenEqual"},
        {"TokenNotEqual"},
        {"TokenLessThan"},
        {"TokenGreaterThan"},
        {"TokenLessEqual"},
        {"TokenGreaterEqual"},
        {"TokenShiftLeft"},
        {"TokenShiftRight"},
        {"TokenPlus"},
        {"TokenMinus"},
        {"TokenAsterisk"},
        {"TokenSlash"},
        {"TokenModulus"},
        {"TokenIncrement"},
        {"TokenDecrement"},
        {"TokenUnaryNot"},
        {"TokenUnaryExor"},
        {"TokenSizeof"},
        {"TokenCast"},
        {"TokenLeftSquareBracket"},
        {"TokenRightSquareBracket"},
        {"TokenDot"},
        {"TokenArrow"},
        {"TokenOpenBracket"},
        {"TokenCloseBracket"},
        {"TokenIdentifier"},
        {"TokenIntegerConstant"},
        {"TokenUnsignedIntegerConstant"},
        {"TokenLongIntegerConstant"},
        {"TokenUnsignedLongIntegerConstant"},
        {"TokenLongLongIntegerConstant"},
        {"TokenUnsignedLongLongIntegerConstant"},
        {"TokenFloatConstant"},
        {"TokenDoubleConstant"},
        {"TokenStringConstant"},
        {"TokenCharacterConstant"},
        {"TokenSemicolon"},
        {"TokenEllipsis"},
        {"TokenLeftBrace"},
        {"TokenRightBrace"},
        {"TokenIntType"},
        {"TokenCharType"},
        {"TokenFloatType"},
        {"TokenDoubleType"},
        {"TokenVoidType"},
        {"TokenEnumType"},
        {"TokenLongType"},
        {"TokenSignedType"},
        {"TokenShortType"},
        {"TokenStaticType"},
        {"TokenAutoType"},
        {"TokenRegisterType"},
        {"TokenExternType"},
        {"TokenStructType"},
        {"TokenUnionType"},
        {"TokenUnsignedType"},
        {"TokenTypedef"},
        {"TokenContinue"},
        {"TokenDo"},
        {"TokenElse"},
        {"TokenFor"},
        {"TokenGoto"},
        {"TokenIf"},
        {"TokenWhile"},
        {"TokenBreak"},
        {"TokenSwitch"},
        {"TokenCase"},
        {"TokenDefault"},
        {"TokenReturn"},
        {"TokenHashDefine"},
        {"TokenHashInclude"},
        {"TokenHashIf"},
        {"TokenHashIfdef"},
        {"TokenHashIfndef"},
        {"TokenHashElse"},
        {"TokenHashEndif"},
        {"TokenNew"},
        {"TokenDelete"},
        {"TokenOpenMacroBracket"},
        {"TokenEOF"},
        {"TokenEndOfLine"},
        {"TokenEndOfFunction"},
        {"TokenBackSlash"},
        {"TokenVolatileType"},
        {"TokenHashPragma"},
        {"TokenUnderscorePragma"},
        {"TokenConstType"}
};

struct TypeStat TypeStats[NUM_TYPES] = {
        {"Char"},
        {"UnsignedChar"},
        {"Short"},
        {"UnsignedShort"},
        {"Int"},
        {"UnsignedInt"},
        {"Long"},
        {"UnsignedLong"},
        {"LongLong"},
        {"UnsignedLongLong"},
        {"Float"},
        {"Double"},
        {"Pointer"}
};

const char *BaseTypeNames[NUM_BASE_TYPES] = {
        "Void",
        "Int",
        "Short",
        "Char",
        "Long",
        "LongLong",
        "UnsignedInt",
        "UnsignedShort",
        "UnsignedChar",
        "UnsignedLong",
        "UnsignedLongLong",
        "Float",
        "Double",
        "Function",
        "Macro",
        "Pointer",
        "Array",
        "Struct",
        "Union",
        "Enum",
        "GotoLabel",
        "_Type"
};

const char *OperatorSymbols[NUM_OPERATORS] = {
        "none",
        ",",
        "=",
        "+=",
        "-=",
        "*=",
        "/=" ,
        "%=" ,
        "<<=",
        ">>=" ,
        "&=" ,
        "|=",
        "^=" ,
        "?",
        ":" ,
        "||",
        "&&",
        "|",
        "^",
        "&",
        "==",
        "!=",
        "<",
        ">",
        "<=",
        ">=",
        "<<",
        ">>",
        "+",
        "-",
        "*",
        "/",
        "%",
        "++",
        "--",
        "!",
        "~",
        "sizeof",
        "cast",
        "[",
        "]",
        ".",
        "->",
        "(",
        ")"
};



unsigned int FunctionParameterCounts[PARAMETER_MAX + 1] = {0};
unsigned int FunctionParameterDynamicCounts[PARAMETER_MAX + 1] = {0};
unsigned int FunctionCallDepth = 0;
unsigned int FunctionCallWatermark = 0;
unsigned int LoopDepth = 0;
unsigned int LoopWatermark = 0;
unsigned int ConditionalDepth = 0;
unsigned int ConditionalWatermark = 0;
unsigned int ExpressionDepth = 0;
unsigned int ExpressionWatermark = 0;
unsigned int ExpressionCounts[NUM_EXPRESSION_TYPES][NUM_OPERATORS][NUM_BASE_TYPES][NUM_BASE_TYPES] = {{{{0}}}};


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


void stats_log_expression_token_parse(enum LexToken token, struct ParseState *parser)
{
    if (parser->pc->CollectStats) {
        if (parser->pc->PrintStats) {
            fprintf(stderr, "Parsing Expression Token %s (%d) in %s (%d) at %s:%d:%d\n", LexTokenStats[token].name, token,
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


void stats_log_expression_parse(struct ParseState *Parser)
{
    if (Parser->pc->CollectStats && (Parser->Mode == RunModeRun) && (strcmp(Parser->FileName, "startup") != 0)) {

        ExpressionDepth = 0;

        /* temporarily move the parser to the next token to get more accurate file coordinates */
        struct ParseState PreState;
        ParserCopy(&PreState, Parser);
        LexGetToken(Parser, NULL, true);

        if (Parser->pc->PrintExpressions) {
            fprintf(stderr, "\n---\nParsing expression at %s:%d:%d\n", Parser->FileName, Parser->Line, Parser->CharacterPos);
        }

        ParserCopy(Parser, &PreState);
    }
}


void stats_log_expression_stack_collapse(struct ParseState *parser)
{
    if (parser->pc->CollectStats && (parser->Mode == RunModeRun) && (strcmp(parser->FileName, "startup") != 0)) {
        if (parser->pc->PrintExpressions) {
//            fprintf(stderr, "Collapsing expression stack at %s:%d:%d\n", parser->FileName, parser->Line, parser->CharacterPos);
        }
    }
}


void stats_log_expression_evaluation(struct ParseState *parser, enum ExpressionType Type, enum LexToken Op, struct Value *BottomValue, struct Value *TopValue)
{
    if (parser->pc->CollectStats && (parser->Mode == RunModeRun) && (strcmp(parser->FileName, "startup") != 0)) {
        enum BaseType TopType = TopValue ? TopValue->Typ->Base : 0;
        enum BaseType BottomType = BottomValue ? BottomValue->Typ->Base : 0;

        ExpressionDepth++;
        if (ExpressionDepth > ExpressionWatermark) {
            ExpressionWatermark = ExpressionDepth;
        }

        if (Type == ExpressionInfix && Op == TokenLeftSquareBracket && BottomValue && BottomType == TypeArray) {
            BottomType = BottomValue->Typ->FromType->Base;
        }

        ExpressionCounts[Type][Op][TopType][BottomType]++;

        if (parser->pc->PrintExpressions) {
            const char *TopTypeName = TopValue ? BaseTypeNames[TopType] : "";
            const char *BottomTypeName = BottomValue ? BaseTypeNames[BottomType] : "";
            const char *OpSymbol = OperatorSymbols[Op];

            switch (Type) {
            case ExpressionInfix:
                if (Op == TokenAssign) {
                    fprintf(stderr, "Evaluating assign expression at %s:%d:%d   var<%s> = %s\n", parser->FileName,
                            parser->Line, parser->CharacterPos, BottomTypeName, TopTypeName);
                } else if (Op == TokenLeftSquareBracket) {
                    fprintf(stderr, "Evaluating array expression at %s:%d:%d    arr<%s>[%s]\n", parser->FileName,
                            parser->Line, parser->CharacterPos, BottomTypeName, TopTypeName);
                } else {
                    fprintf(stderr, "Evaluating infix expression at %s:%d:%d    %s %s %s\n", parser->FileName,
                            parser->Line, parser->CharacterPos, BottomTypeName, OpSymbol, TopTypeName);
                }
                break;
            case ExpressionPrefix:
                fprintf(stderr, "Evaluating prefix expression at %s:%d:%d   %s%s\n", parser->FileName, parser->Line, parser->CharacterPos, OpSymbol, TopTypeName);
                break;
            case ExpressionPostfix:
                fprintf(stderr, "Evaluating postfix expression at %s:%d:%d  %s%s\n", parser->FileName, parser->Line, parser->CharacterPos, TopTypeName, OpSymbol);
                break;
            case ExpressionReturn:
                fprintf(stderr, "Evaluating return expression at %s:%d:%d   ret<%s> = %s\n", parser->FileName, parser->Line, parser->CharacterPos, BottomTypeName, TopTypeName);
                break;
            default:
                fprintf(stderr, "Invalid expression type\n");
                break;
            }
        }
    }
}


void stats_print_tokens(int all)
{
    printf("\n*********\nToken stats:\n");
    for (int i = 0; i < NUM_RUN_MODES; i++) {
        printf("***\n");
        printf("%s\n", RunModeNames[i]);
        for (int j = 0; j < NUM_TOKENS; j++) {
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
    for (int j = 0; j < NUM_TOKENS; j++) {
        printf(",%s", LexTokenStats[j].name);
    }
    for (int i = 0; i < NUM_RUN_MODES; i++) {
        printf("\n%s", RunModeNames[i]);
        for (int j = 0; j < NUM_TOKENS; j++) {
            printf(",%d", LexTokenStats[j].count[i]);
        }
    }
    printf("\n");
}


void stats_print_tokens_csv_runmode(enum RunMode runMode)
{
    for (int i = 0; i < NUM_TOKENS - 1; i++) {
        printf("%d,", LexTokenStats[i].count[runMode]);
    }
    printf("%d\n", LexTokenStats[NUM_TOKENS - 1].count[runMode]);
}


void stats_print_runmode_list(void)
{
    for (int i = 0; i < NUM_RUN_MODES - 1; i++) {
        printf("%s,", RunModeNames[i]);
    }
    printf("%s\n", RunModeNames[NUM_RUN_MODES - 1]);
}


void stats_print_token_list(void)
{
    for (int i = 0; i < NUM_TOKENS - 1; i++) {
        printf("%s,", LexTokenStats[i].name);
    }
    printf("%s\n", LexTokenStats[NUM_TOKENS - 1].name);
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
    for (int i = 0; i < NUM_TYPES - 1; i++) {
        printf("%s,", TypeStats[i].name);
    }
    printf("%s\n", TypeStats[NUM_TYPES - 1].name);
}


void stats_print_assignments(void)
{
    for (int i = 0; i < NUM_TYPES; i++) {
        printf("%s: %d\n", TypeStats[i].name, TypeStats[i].assignments);
    }
}


void stats_print_assignments_csv(void)
{
    for (int i = 0; i < NUM_TYPES - 1; i++) {
        printf("%d,", TypeStats[i].assignments);
    }
    printf("%d\n", TypeStats[NUM_TYPES - 1].assignments);
}


void stats_print_expressions(void)
{
    printf("\n");

    for (int Type = 0; Type < NUM_EXPRESSION_TYPES; Type++) {
        for (int Op = 0; Op < NUM_OPERATORS; Op++) {
            for (int TopType = 0; TopType < NUM_BASE_TYPES; TopType++) {
                for (int BottomType = 0; BottomType < NUM_BASE_TYPES; BottomType++) {
                    unsigned int count = ExpressionCounts[Type][Op][TopType][BottomType];
                    if (count > 0) {
                        const char *TopTypeName = BaseTypeNames[TopType];
                        const char *BottomTypeName = BaseTypeNames[BottomType];
                        const char *OpSymbol = OperatorSymbols[Op];

                        switch (Type) {
                            case ExpressionInfix:
                                if (Op == TokenAssign) {
                                    printf("%7d   assign expressions of type   var<%s> = %s\n", count, BottomTypeName, TopTypeName);
                                } else if (Op == TokenLeftSquareBracket) {
                                    printf("%7d    array expressions of type   arr<%s>[%s]\n", count, BottomTypeName, TopTypeName);
                                } else {
                                    printf("%7d    infix expressions of type   %s %s %s\n", count, BottomTypeName, OpSymbol, TopTypeName);
                                }
                                break;
                            case ExpressionPrefix:
                                printf("%7d   prefix expressions of type   %s%s\n", count, OpSymbol, TopTypeName);
                                break;
                            case ExpressionPostfix:
                                printf("%7d  postfix expressions of type   %s%s\n", count, TopTypeName, OpSymbol);
                                break;
                            case ExpressionReturn:
                                printf("%7d   return expressions of type   ret<%s> = %s\n", count, BottomTypeName, TopTypeName);
                                break;
                            default:
                                printf("Warning: Invalid expression type\n");
                                break;
                        }
                    }
                }
            }
        }
    }

    printf("\nMaximum expression depth: %d\n", ExpressionWatermark);
}
