//
// Created by Russell Joyce on 12/05/2020.
//

#include "stats.h"

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
        {"TokenFPConstant", {0, 0, 0, 0, 0, 0, 0}},
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
        {"TokenBackSlash", {0, 0, 0, 0, 0, 0, 0}}
};


void stats_log_statement(enum LexToken token, struct ParseState *parser) {
    fprintf(stderr, "Parsing Statement %s (%d) in %s (%d) at %s:%d:%d\n", LexTokenStats[token].name, token, RunModeNames[parser->Mode], parser->Mode, parser->FileName, parser->Line, parser->CharacterPos);
    LexTokenStats[token].count[parser->Mode]++;
}


void stats_log_expression(enum LexToken token, struct ParseState *parser) {
    fprintf(stderr, "Parsing Expression %s (%d) in %s (%d) at %s:%d:%d\n", LexTokenStats[token].name, token, RunModeNames[parser->Mode], parser->Mode, parser->FileName, parser->Line, parser->CharacterPos);
    LexTokenStats[token].count[parser->Mode]++;
}


void stats_print_tokens(int all) {
    fprintf(stderr, "\n*********\nToken stats:\n");
    for (int i = 0; i < NO_RUN_MODES; i++) {
        fprintf(stderr, "***\n");
        fprintf(stderr, "%s\n", RunModeNames[i]);
        for (int j = 0; j < NO_TOKENS; j++) {
            if (all || LexTokenStats[j].count[i] > 0) {
                fprintf(stderr, "%5d %s\n", LexTokenStats[j].count[i],
                        LexTokenStats[j].name);
            }
        }
    }
    fprintf(stderr, "*********\n");
}
