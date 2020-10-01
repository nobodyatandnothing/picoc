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
#define EXPRESSION_CHAIN_STACK_SIZE 100

struct LexTokenStat {
    const char* name;
    int count[NUM_RUN_MODES];
};

struct TypeStat {
    const char* name;
    int assignments;
};

struct FileCoordinate {
    char* FileName;
    int Line;
    int Column;
};

struct Expression {
    enum ExpressionType Type;
    enum LexToken Op;
    enum BaseType TopType;
    enum BaseType BottomType;
};

struct ExpressionChainNode {
    struct Expression Expression;
    struct ExpressionChainNode *Next;
};

struct ExpressionChainListNode {
    struct ExpressionChainNode *ExpressionChainHead;
    struct FileCoordinate Coordinate;
    struct ExpressionChainListNode *Next;
};

union ExpressionHash {
    uint32_t Hash;
    struct {
        uint8_t Type;
        uint8_t Op;
        uint8_t TopType;
        uint8_t BottomType;
    } Components;
};

struct ExpressionChainItem {
    union ExpressionHash Hash;
    unsigned int LeafCount;
    unsigned int BranchCount;
    unsigned int BranchListSize;
    struct ExpressionChainItem *Branches;
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


void stats_print_expression(enum ExpressionType Type, enum LexToken Op, enum BaseType TopType, enum BaseType BottomType);
void stats_traverse_expressions_tree(struct ExpressionChainItem *Node);


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
struct ExpressionChainListNode *ExpressionChainListHead = NULL;
struct ExpressionChainListNode *ExpressionChainListTail = NULL;
struct ExpressionChainNode *CurrentExpression = NULL;
struct ExpressionChainItem ExpressionChainsRoot = {{0}};
struct ExpressionChainItem *ExpressionChainTreePosition = NULL;
union ExpressionHash ExpressionChainStack[EXPRESSION_CHAIN_STACK_SIZE];
int ExpressionChainStackTop = 0;
int TotalExpressions = 0;
int TotalExpressionChains = 0;


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

        ExpressionChainTreePosition = &ExpressionChainsRoot;
        ExpressionChainTreePosition->LeafCount++;
        TotalExpressionChains++;

        /* temporarily move the parser to the next token to get more accurate file coordinates */
        struct ParseState PreState;
        ParserCopy(&PreState, Parser);
        LexGetToken(Parser, NULL, true);

        if (Parser->pc->CollectFullExpressions) {
            if (ExpressionChainListHead == NULL) {
                ExpressionChainListHead = malloc(sizeof(struct ExpressionChainListNode));
                if (ExpressionChainListHead == NULL) {
                    fprintf(stderr, "Error allocating memory for expression chain stats\n");
                    exit(1);
                }
                ExpressionChainListTail = ExpressionChainListHead;
            } else {
                struct ExpressionChainListNode *NewNode = malloc(sizeof(struct ExpressionChainListNode));
                if (NewNode == NULL) {
                    fprintf(stderr, "Error allocating memory for expression chain stats\n");
                    exit(1);
                }
                ExpressionChainListTail->Next = NewNode;
                ExpressionChainListTail = NewNode;
            }
            ExpressionChainListTail->ExpressionChainHead = NULL;
            ExpressionChainListTail->Next = NULL;
            CurrentExpression = NULL;
            ExpressionChainListTail->Coordinate.FileName = strdup(Parser->FileName);
            ExpressionChainListTail->Coordinate.Line = Parser->Line;
            ExpressionChainListTail->Coordinate.Column = Parser->CharacterPos;
        }

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
        TotalExpressions++;

        if (ExpressionChainTreePosition) {
            union ExpressionHash Hash = {.Components = {Type, Op, TopType, BottomType}};

            /* reduce count of current leaf because it will be added to the new leaf instead */
            ExpressionChainTreePosition->LeafCount--;
            TotalExpressionChains--;

            /* if the node has no branches, initialise its branch array */
            if (ExpressionChainTreePosition->Branches == NULL) {
                ExpressionChainTreePosition->Branches = malloc(sizeof(struct ExpressionChainItem) * 2);
                if (ExpressionChainTreePosition->Branches == NULL) {
                    fprintf(stderr, "Error allocating memory for expression chain branches\n");
                    exit(1);
                }
                ExpressionChainTreePosition->BranchListSize = 2;
            }

            /* search for an existing branch with the current expression hash */
            struct ExpressionChainItem *MatchedBranch = NULL;
            for (int i = 0; i < ExpressionChainTreePosition->BranchCount; i++) {
                if (ExpressionChainTreePosition->Branches[i].Hash.Hash == Hash.Hash) {
                    MatchedBranch = &ExpressionChainTreePosition->Branches[i];
                    /* increment the leaf count of the matched (or new) branch */
                    MatchedBranch->LeafCount++;
                    TotalExpressionChains++;
                    break;
                }
            }

            /* if there's not a matching branch, create a new branch for this hash */
            if (MatchedBranch == NULL) {
                /* create more branch storage on this node if it's needed */
                if (ExpressionChainTreePosition->BranchCount == ExpressionChainTreePosition->BranchListSize) {
                    ExpressionChainTreePosition->BranchListSize *= 2;
                    ExpressionChainTreePosition->Branches = realloc(ExpressionChainTreePosition->Branches,
                                                                    sizeof(struct ExpressionChainItem) *
                                                                    ExpressionChainTreePosition->BranchListSize);
                    if (ExpressionChainTreePosition->Branches == NULL) {
                        fprintf(stderr, "Error reallocating memory for %d expression chain branches\n",
                                ExpressionChainTreePosition->BranchListSize);
                        exit(1);
                    }
                }

                /* set up the new branch for the current expression */
                MatchedBranch = &ExpressionChainTreePosition->Branches[ExpressionChainTreePosition->BranchCount];
                MatchedBranch->Hash = Hash;
                MatchedBranch->LeafCount = 1;
                TotalExpressionChains++;
                MatchedBranch->BranchCount = 0;
                MatchedBranch->BranchListSize = 0;
                MatchedBranch->Branches = NULL;
                ExpressionChainTreePosition->BranchCount++;
            }

            /* set the new position in the tree to be the matched (or new) branch */
            ExpressionChainTreePosition = MatchedBranch;
        }

        if (parser->pc->CollectFullExpressions) {
            if (ExpressionChainListTail != NULL) {
                struct ExpressionChainNode *NewNode = malloc(sizeof(struct ExpressionChainNode));
                if (NewNode == NULL) {
                    fprintf(stderr, "Error allocating memory for expression chain stats\n");
                    exit(1);
                }
                NewNode->Next = NULL;

                if (ExpressionChainListTail->ExpressionChainHead == NULL) {
                    ExpressionChainListTail->ExpressionChainHead = NewNode;
                } else {
                    CurrentExpression->Next = NewNode;
                }
                CurrentExpression = NewNode;
            }

            CurrentExpression->Expression.Type = Type;
            CurrentExpression->Expression.Op = Op;
            CurrentExpression->Expression.BottomType = BottomType;
            CurrentExpression->Expression.TopType = TopType;
        }

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
    printf("%u,%u,%u,%u\n", FunctionCallWatermark, LoopWatermark, ConditionalWatermark, ExpressionWatermark);
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


void stats_print_expressions_summary(void)
{
    for (int Type = 0; Type < NUM_EXPRESSION_TYPES; Type++) {
        for (int Op = 0; Op < NUM_OPERATORS; Op++) {
            for (int TopType = 0; TopType < NUM_BASE_TYPES; TopType++) {
                for (int BottomType = 0; BottomType < NUM_BASE_TYPES; BottomType++) {
                    unsigned int count = ExpressionCounts[Type][Op][TopType][BottomType];
                    double percentage = (count * 100.0) / TotalExpressions;
                    if (count > 0) {
                        const char *TopTypeName = BaseTypeNames[TopType];
                        const char *BottomTypeName = BaseTypeNames[BottomType];
                        const char *OpSymbol = OperatorSymbols[Op];

                        switch (Type) {
                            case ExpressionInfix:
                                if (Op == TokenAssign) {
                                    printf("%5.1f%% %8d   assign expressions of type   var<%s> = %s\n", percentage, count, BottomTypeName, TopTypeName);
                                } else if (Op == TokenLeftSquareBracket) {
                                    printf("%5.1f%% %8d    array expressions of type   arr<%s>[%s]\n", percentage, count, BottomTypeName, TopTypeName);
                                } else {
                                    printf("%5.1f%% %8d    infix expressions of type   %s %s %s\n", percentage, count, BottomTypeName, OpSymbol, TopTypeName);
                                }
                                break;
                            case ExpressionPrefix:
                                printf("%5.1f%% %8d   prefix expressions of type   %s%s\n", percentage, count, OpSymbol, TopTypeName);
                                break;
                            case ExpressionPostfix:
                                printf("%5.1f%% %8d  postfix expressions of type   %s%s\n", percentage, count, TopTypeName, OpSymbol);
                                break;
                            case ExpressionReturn:
                                printf("%5.1f%% %8d   return expressions of type   ret<%s> = %s\n", percentage, count, BottomTypeName, TopTypeName);
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

    printf("\nTotal expressions: %d\n", TotalExpressions);
    printf("Maximum expression chain depth: %d\n", ExpressionWatermark);
}


void stats_print_expression(enum ExpressionType Type, enum LexToken Op, enum BaseType TopType, enum BaseType BottomType)
{
    const char *TopTypeName = BaseTypeNames[TopType];
    const char *BottomTypeName = BaseTypeNames[BottomType];
    const char *OpSymbol = OperatorSymbols[Op];

    switch (Type) {
        case ExpressionInfix:
            if (Op == TokenAssign) {
                printf("var<%s> = %s", BottomTypeName, TopTypeName);
            } else if (Op == TokenLeftSquareBracket) {
                printf("arr<%s>[%s]", BottomTypeName, TopTypeName);
            } else {
                printf("%s %s %s", BottomTypeName, OpSymbol, TopTypeName);
            }
            break;
        case ExpressionPrefix:
            printf("%s%s", OpSymbol, TopTypeName);
            break;
        case ExpressionPostfix:
            printf("%s%s", TopTypeName, OpSymbol);
            break;
        case ExpressionReturn:
            printf("ret<%s> = %s", BottomTypeName, TopTypeName);
            break;
        default:
            printf("XXXX\n");
            break;
    }
}


void stats_traverse_expressions_tree(struct ExpressionChainItem *Node)
{
    if (ExpressionChainStackTop == EXPRESSION_CHAIN_STACK_SIZE) {
        fprintf(stderr, "Stats printing expression chain stack overflow");
        exit(1);
    }

    union ExpressionHash Hash = Node->Hash;
    ExpressionChainStack[ExpressionChainStackTop++] = Hash;

    /* print out expressions chain stack up to this point, if a chain ended here */
    if (Node->LeafCount > 0) {
        double percentage = (Node->LeafCount * 100.0) / TotalExpressionChains;
        printf("%5.1f%% %8d    ", percentage, Node->LeafCount);
        for (int i = 0; i < ExpressionChainStackTop; i++) {
            stats_print_expression(ExpressionChainStack[i].Components.Type,
                                   ExpressionChainStack[i].Components.Op,
                                   ExpressionChainStack[i].Components.TopType,
                                   ExpressionChainStack[i].Components.BottomType);
            if (i < ExpressionChainStackTop - 1)
                printf("  ->  ");
        }
        printf("\n");
    }

    for (int i = 0; i < Node->BranchCount; i++) {
        stats_traverse_expressions_tree(&Node->Branches[i]);
    }

    ExpressionChainStackTop--;
}


void stats_print_expression_chains_summary(void)
{
    /* depth-first traverse the expressions tree to find the chain counts */
    ExpressionChainStackTop = 0;
    for (int i = 0; i < ExpressionChainsRoot.BranchCount; i++) {
        stats_traverse_expressions_tree(&ExpressionChainsRoot.Branches[i]);
    }

    printf("\nTotal expressions: %d\n", TotalExpressions);
    printf("Total expression chains: %d\n", TotalExpressionChains);
    printf("Maximum expression chain depth: %d\n", ExpressionWatermark);
}


void stats_print_expression_chains(void)
{
    struct ExpressionChainListNode *ExpressionChain = ExpressionChainListHead;

    while (ExpressionChain != NULL) {
        struct ExpressionChainNode *ExpressionNode = ExpressionChain->ExpressionChainHead;

        if (ExpressionNode != NULL) {
            struct FileCoordinate *Coordinate = &ExpressionChain->Coordinate;
            printf("\n%s:%d:%d   ", Coordinate->FileName, Coordinate->Line, Coordinate->Column);
        }

        while (ExpressionNode != NULL) {
            struct Expression *Expression = &ExpressionNode->Expression;

            stats_print_expression(Expression->Type, Expression->Op, Expression->TopType, Expression->BottomType);

            if (ExpressionNode->Next != NULL)
                printf("  ->  ");

            ExpressionNode = ExpressionNode->Next;
        }

        ExpressionChain = ExpressionChain->Next;
    }

    printf("\n");
}
