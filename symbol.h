/*  
关键字：            
    const           1
    var             2
    procedure       3
    if              4
    call            5
    begin           6
    end             7
    ood             8
    if              9
    then            10
    call            11
    do              12
    while           13
    read            14
    write           15
一些语法分析需要用到的符号
    {               16
    }               17
    (               18
    )               19
    ;               20
    ,               21
运算符:
    +               22
    -               23
    *               24
    /               25
    >               26
    <               27
    >=              28
    <=              29
    =               30
    :=              31
    #               32
一些没有意义的字符：
    space
标识符：
    <标识符> ---> <字母> {<字母>|<数字>}*
*/

/* 符号 */
char syms[][11] = {
    "const",
    "var",
    "procedure",
    "if",
    "call",
    "begin",    
    "end",
    "ood",
    "then",
    "do",
    "while",
    "read",
    "write",
    "{",
    "}",
    "(",
    ")",
    ";",
    ",",
    "+",
    "-",
    "*",
    "/",
    ">",
    "<",
    ">=",
    "<=",
    "=",
    ":=",
    "#",
    "identifier",
    "number"
};

/* 非终态 */
#define UNSTOP 0

/* 终态 */
#define CONST_SYM 1
#define VAR_SYM 2
#define PROCEDURE_SYM 3
#define IF_SYM 4
#define CALL_SYM 5
#define BEGIN_SYM 6
#define END_SYM 7
#define OOD_SYM 8
#define THEN_SYM 9
#define DO_SYM 10
#define WHILE_SYM 11
#define READ_SYM 12
#define WRITE_SYM 13

#define LEFT_BRACE_SYM 14
#define RIGHT_BRACE_SYM 15
#define LEFT_PARENTHESIS_SYM 16
#define RIGHT_PARENTHESIS_SYM 17
#define SEMICOLON_SYM 18
#define COMMA_SYM 19
#define ADD_SYM 20
#define MINUS_SYM 21
#define MUL_SYM 22
#define DIVIDE_SYM 23
#define GREATER_SYM 24
#define LESS_SYM 25
#define GREATE_EQUAL_SYM 26
#define LESS_EQUAL_SYM 27
#define EQUAL_SYM 28
#define ASSIGN_SYM 29
#define HASHTAG_SYM 30

#define IDENTIFIER 31
#define NUMBER 32

