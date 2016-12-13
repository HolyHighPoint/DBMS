/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         HSQL_STYPE
#define YYLTYPE         HSQL_LTYPE
/* Substitute the variable and function names.  */
#define yyparse         hsql_parse
#define yylex           hsql_lex
#define yyerror         hsql_error
#define yydebug         hsql_debug
#define yynerrs         hsql_nerrs


/* Copy the first part of user declarations.  */
#line 1 "bison_parser.y" /* yacc.c:339  */

/**
 * bison_parser.y
 * defines bison_parser.h
 * outputs bison_parser.c
 *
 * Grammar File Spec: http://dinosaur.compilertools.net/bison/bison_6.html
 *
 */
/*********************************
 ** Section 1: C Declarations
 *********************************/

#include "parser/bison_parser.h"
#include "parser/flex_lexer.h"

#include <stdio.h>

using namespace hsql;

int yyerror(YYLTYPE *llocp, SQLParserResult **result, yyscan_t scanner, const char *msg)
{

    SQLParserResult *list = new SQLParserResult();
    list->isValid = false;
    list->errorMsg = strdup(msg);
    list->errorLine = llocp->first_line;
    list->errorColumn = llocp->first_column;

    *result = list;
    return 0;
}




#line 110 "bison_parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison_parser.h".  */
#ifndef YY_HSQL_BISON_PARSER_H_INCLUDED
# define YY_HSQL_BISON_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef HSQL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define HSQL_DEBUG 1
#  else
#   define HSQL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define HSQL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined HSQL_DEBUG */
#if HSQL_DEBUG
extern int hsql_debug;
#endif
/* "%code requires" blocks.  */
#line 42 "bison_parser.y" /* yacc.c:355  */

// %code requires block

#include "../sql/statements.h"
#include "../SQLParserResult.h"
#include "parser_typedef.h"

// Auto update column and line number
#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
        yylloc->total_column++; \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

#line 171 "bison_parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef HSQL_TOKENTYPE
# define HSQL_TOKENTYPE
enum hsql_tokentype
{
    SQL_IDENTIFIER = 258,
    SQL_STRING = 259,
    SQL_FLOATVAL = 260,
    SQL_INTVAL = 261,
    SQL_NOTEQUALS = 262,
    SQL_LESSEQ = 263,
    SQL_GREATEREQ = 264,
    SQL_DEALLOCATE = 265,
    SQL_PARAMETERS = 266,
    SQL_INTERSECT = 267,
    SQL_TEMPORARY = 268,
    SQL_TIMESTAMP = 269,
    SQL_DISTINCT = 270,
    SQL_NVARCHAR = 271,
    SQL_RESTRICT = 272,
    SQL_TRUNCATE = 273,
    SQL_ANALYZE = 274,
    SQL_BETWEEN = 275,
    SQL_CASCADE = 276,
    SQL_COLUMNS = 277,
    SQL_CONTROL = 278,
    SQL_DEFAULT = 279,
    SQL_EXECUTE = 280,
    SQL_EXPLAIN = 281,
    SQL_HISTORY = 282,
    SQL_INTEGER = 283,
    SQL_NATURAL = 284,
    SQL_PREPARE = 285,
    SQL_PRIMARY = 286,
    SQL_SCHEMAS = 287,
    SQL_SPATIAL = 288,
    SQL_VIRTUAL = 289,
    SQL_BEFORE = 290,
    SQL_COLUMN = 291,
    SQL_CREATE = 292,
    SQL_DELETE = 293,
    SQL_DIRECT = 294,
    SQL_DOUBLE = 295,
    SQL_ESCAPE = 296,
    SQL_EXCEPT = 297,
    SQL_EXISTS = 298,
    SQL_GLOBAL = 299,
    SQL_HAVING = 300,
    SQL_IMPORT = 301,
    SQL_INSERT = 302,
    SQL_ISNULL = 303,
    SQL_OFFSET = 304,
    SQL_RENAME = 305,
    SQL_SCHEMA = 306,
    SQL_SELECT = 307,
    SQL_SORTED = 308,
    SQL_TABLES = 309,
    SQL_UNIQUE = 310,
    SQL_UNLOAD = 311,
    SQL_UPDATE = 312,
    SQL_VALUES = 313,
    SQL_AFTER = 314,
    SQL_ALTER = 315,
    SQL_CROSS = 316,
    SQL_DELTA = 317,
    SQL_GROUP = 318,
    SQL_INDEX = 319,
    SQL_INNER = 320,
    SQL_LIMIT = 321,
    SQL_LOCAL = 322,
    SQL_MERGE = 323,
    SQL_MINUS = 324,
    SQL_ORDER = 325,
    SQL_OUTER = 326,
    SQL_RIGHT = 327,
    SQL_TABLE = 328,
    SQL_UNION = 329,
    SQL_USING = 330,
    SQL_WHERE = 331,
    SQL_CALL = 332,
    SQL_DATE = 333,
    SQL_DESC = 334,
    SQL_DROP = 335,
    SQL_FILE = 336,
    SQL_FROM = 337,
    SQL_FULL = 338,
    SQL_HASH = 339,
    SQL_HINT = 340,
    SQL_INTO = 341,
    SQL_JOIN = 342,
    SQL_LEFT = 343,
    SQL_LIKE = 344,
    SQL_LOAD = 345,
    SQL_NULL = 346,
    SQL_PART = 347,
    SQL_PLAN = 348,
    SQL_SHOW = 349,
    SQL_TEXT = 350,
    SQL_TIME = 351,
    SQL_VIEW = 352,
    SQL_WITH = 353,
    SQL_ADD = 354,
    SQL_ALL = 355,
    SQL_AND = 356,
    SQL_ASC = 357,
    SQL_CSV = 358,
    SQL_FOR = 359,
    SQL_INT = 360,
    SQL_KEY = 361,
    SQL_NOT = 362,
    SQL_OFF = 363,
    SQL_SET = 364,
    SQL_TBL = 365,
    SQL_TOP = 366,
    SQL_AS = 367,
    SQL_BY = 368,
    SQL_IF = 369,
    SQL_IN = 370,
    SQL_IS = 371,
    SQL_OF = 372,
    SQL_ON = 373,
    SQL_OR = 374,
    SQL_TO = 375,
    SQL_DATABASE = 376,
    SQL_DATABASES = 377,
    SQL_CHAR = 378,
    SQL_VARCHAR = 379,
    SQL_TINYINT = 380,
    SQL_USE = 381,
    SQL_EQUALS = 382,
    SQL_LESS = 383,
    SQL_GREATER = 384,
    SQL_NOTNULL = 385,
    SQL_UMINUS = 386
};
#endif

/* Value type.  */
#if ! defined HSQL_STYPE && ! defined HSQL_STYPE_IS_DECLARED
typedef union HSQL_STYPE HSQL_STYPE;
union HSQL_STYPE
{
#line 101 "bison_parser.y" /* yacc.c:355  */

    double fval;
    int64_t ival;
    char *sval;
    uintmax_t uval;
    bool bval;

    hsql::SQLStatement *statement;
    hsql::SelectStatement  *select_stmt;
    hsql::ImportStatement  *import_stmt;
    hsql::CreateStatement  *create_stmt;
    hsql::InsertStatement  *insert_stmt;
    hsql::DeleteStatement  *delete_stmt;
    hsql::UpdateStatement  *update_stmt;
    hsql::DropStatement    *drop_stmt;
    hsql::ShowStatement    *show_stmt;
    hsql::DescStatement    *desc_stmt;
    hsql::UseStatement     *use_stmt;
    hsql::PrepareStatement *prep_stmt;
    hsql::ExecuteStatement *exec_stmt;

    hsql::TableRef *table;
    hsql::Expr *expr;
    hsql::OrderDescription *order;
    hsql::OrderType order_type;
    hsql::LimitDescription *limit;
    hsql::ColumnDefinition *column_t;
    hsql::GroupByDescription *group_t;
    hsql::UpdateClause *update_t;

    hsql::SQLParserResult *stmt_list;

    std::vector<char *> *str_vec;
    std::vector<hsql::TableRef *> *table_vec;
    std::vector<hsql::ColumnDefinition *> *column_vec;
    std::vector<hsql::UpdateClause *> *update_vec;
    std::vector<hsql::Expr *> *expr_vec;
    std::vector<std::vector<hsql::Expr *>*> *expr_vec_vec;

#line 355 "bison_parser.cpp" /* yacc.c:355  */
};
# define HSQL_STYPE_IS_TRIVIAL 1
# define HSQL_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined HSQL_LTYPE && ! defined HSQL_LTYPE_IS_DECLARED
typedef struct HSQL_LTYPE HSQL_LTYPE;
struct HSQL_LTYPE
{
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};
# define HSQL_LTYPE_IS_DECLARED 1
# define HSQL_LTYPE_IS_TRIVIAL 1
#endif



int hsql_parse (hsql::SQLParserResult **result, yyscan_t scanner);

#endif /* !YY_HSQL_BISON_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 383 "bison_parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
/* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
/* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
/* The OS might guarantee only one guard page at the bottom of the stack,
   and a page size can be as small as 4096 bytes.  So we cannot safely
   invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
   to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL \
             && defined HSQL_STYPE_IS_TRIVIAL && HSQL_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
    yytype_int16 yyss_alloc;
    YYSTYPE yyvs_alloc;
    YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  60
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   463

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  152
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  305

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   386

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
    0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,   138,     2,     2,
    143,   144,   136,   134,   150,   135,   145,   137,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,   147,   146,
    129,   127,   130,   151,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,   141,     2,   142,   139,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,   148,     2,   149,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
    5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
    65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
    75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
    95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
    105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
    115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
    125,   126,   128,   131,   132,   133,   140
};

#if HSQL_DEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
    0,   238,   238,   245,   246,   250,   255,   260,   261,   262,
    263,   264,   265,   266,   267,   268,   269,   270,   271,   279,
    284,   292,   296,   308,   316,   320,   330,   336,   342,   347,
    356,   357,   361,   362,   366,   369,   372,   379,   380,   384,
    385,   386,   390,   394,   395,   405,   409,   413,   417,   430,
    438,   450,   456,   466,   467,   477,   486,   487,   491,   503,
    504,   508,   509,   513,   518,   530,   531,   532,   536,   547,
    548,   552,   557,   562,   563,   567,   572,   576,   577,   580,
    581,   585,   586,   587,   592,   593,   594,   601,   602,   606,
    607,   611,   612,   616,   623,   624,   625,   626,   627,   631,
    632,   633,   637,   638,   642,   643,   644,   645,   646,   647,
    648,   649,   650,   651,   652,   657,   658,   659,   660,   661,
    662,   666,   670,   671,   675,   676,   677,   681,   686,   687,
    691,   695,   700,   711,   712,   722,   723,   729,   734,   735,
    740,   750,   758,   759,   763,   766,   767,   771,   772,   780,
    792,   793,   794,   795,   796,   802,   808,   812,   821,   822,
    827,   828,   837,   840,   846,   852
};
#endif

#if HSQL_DEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
    "$end", "error", "$undefined", "IDENTIFIER", "STRING", "FLOATVAL",
    "INTVAL", "NOTEQUALS", "LESSEQ", "GREATEREQ", "DEALLOCATE", "PARAMETERS",
    "INTERSECT", "TEMPORARY", "TIMESTAMP", "DISTINCT", "NVARCHAR",
    "RESTRICT", "TRUNCATE", "ANALYZE", "BETWEEN", "CASCADE", "COLUMNS",
    "CONTROL", "DEFAULT", "EXECUTE", "EXPLAIN", "HISTORY", "INTEGER",
    "NATURAL", "PREPARE", "PRIMARY", "SCHEMAS", "SPATIAL", "VIRTUAL",
    "BEFORE", "COLUMN", "CREATE", "DELETE", "DIRECT", "DOUBLE", "ESCAPE",
    "EXCEPT", "EXISTS", "GLOBAL", "HAVING", "IMPORT", "INSERT", "ISNULL",
    "OFFSET", "RENAME", "SCHEMA", "SELECT", "SORTED", "TABLES", "UNIQUE",
    "UNLOAD", "UPDATE", "VALUES", "AFTER", "ALTER", "CROSS", "DELTA",
    "GROUP", "INDEX", "INNER", "LIMIT", "LOCAL", "MERGE", "MINUS", "ORDER",
    "OUTER", "RIGHT", "TABLE", "UNION", "USING", "WHERE", "CALL", "DATE",
    "DESC", "DROP", "FILE", "FROM", "FULL", "HASH", "HINT", "INTO", "JOIN",
    "LEFT", "LIKE", "LOAD", "NULL", "PART", "PLAN", "SHOW", "TEXT", "TIME",
    "VIEW", "WITH", "ADD", "ALL", "AND", "ASC", "CSV", "FOR", "INT", "KEY",
    "NOT", "OFF", "SET", "TBL", "TOP", "AS", "BY", "IF", "IN", "IS", "OF",
    "ON", "OR", "TO", "DATABASE", "DATABASES", "CHAR", "VARCHAR", "TINYINT",
    "USE", "'='", "EQUALS", "'<'", "'>'", "LESS", "GREATER", "NOTNULL",
    "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "UMINUS", "'['", "']'", "'('",
    "')'", "'.'", "';'", "':'", "'{'", "'}'", "','", "'?'", "$accept",
    "input", "statement_list", "statement", "preparable_statement",
    "prepare_statement", "execute_statement", "import_statement",
    "import_file_type", "file_path", "create_statement", "opt_not_exists",
    "column_def_commalist", "column_def", "column_type", "column_vartype",
    "column_primary", "opt_not_null", "drop_statement", "delete_statement",
    "truncate_statement", "insert_statement", "opt_column_list",
    "update_statement", "update_clause_commalist", "update_clause",
    "select_statement", "select_with_paren", "select_no_paren",
    "set_operator", "select_clause", "opt_distinct", "select_list",
    "from_clause", "opt_where", "opt_group", "opt_having", "opt_order",
    "opt_order_type", "opt_limit", "expr_list", "literal_list",
    "literal_list_list", "expr_alias", "expr", "scalar_expr", "unary_expr",
    "binary_expr", "comp_expr", "function_expr", "column_name", "literal",
    "string_literal", "num_literal", "int_literal", "star_expr",
    "placeholder_expr", "table_ref", "table_ref_atomic",
    "table_ref_commalist", "table_ref_name", "table_ref_name_no_alias",
    "table_name", "database_name", "alias", "opt_alias", "join_clause",
    "opt_join_type", "join_table", "join_condition", "opt_semicolon",
    "ident_commalist", "show_statement", "desc_statement", "use_statement", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
    0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
    265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
    275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
    285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
    295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
    305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
    315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
    325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
    335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
    345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
    355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
    365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
    375,   376,   377,   378,   379,   380,   381,    61,   382,    60,
    62,   383,   384,   385,    43,    45,    42,    47,    37,    94,
    386,    91,    93,    40,    41,    46,    59,    58,   123,   125,
    44,    63
};
# endif

#define YYPACT_NINF -243

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-243)))

#define YYTABLE_NINF -157

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-157)))

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    197,     3,    44,    61,    82,   -24,     6,    20,    35,    71,
    44,    44,   -18,   -30,    -6,   -29,   122,   -23,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,    19,  -243,  -243,  -243,   123,   -15,  -243,     1,
    -85,    18,    18,    18,    44,    38,    44,  -243,     0,    36,
    -243,  -243,    44,    44,   143,  -243,  -243,   143,    28,    31,
    -243,   197,  -243,  -243,  -243,    79,  -243,    96,   118,  -243,
    190,    11,   232,   197,    89,    44,    44,   143,   121,  -243,
    120,    59,  -111,  -243,  -243,  -243,     0,     0,  -243,     0,
    -243,   124,    54,  -243,   102,  -243,  -243,  -243,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,  -243,   202,    65,  -243,
    -243,  -243,  -243,  -243,  -243,  -243,     0,   140,   206,  -243,
    -243,   -54,  -243,  -243,   -23,   170,    73,   -56,  -243,     0,
    -243,   213,   215,    43,    71,   220,   292,    17,    30,     4,
    121,     0,  -243,     0,     0,     0,     0,     0,   141,   230,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -243,  -243,   119,   -51,  -243,   242,   217,   118,   198,  -243,
    11,    99,  -243,   248,   142,    25,   259,   167,  -243,  -243,
    -11,   112,  -243,     0,  -243,  -243,   -29,  -243,   106,    41,
    15,  -243,   -36,   195,  -243,   324,   305,   305,   324,   292,
    0,  -243,   273,   324,   305,   305,    17,    17,   125,   125,
    125,  -243,    11,   202,  -243,   115,  -243,  -243,  -243,  -243,
    206,  -243,  -243,   116,   180,    -7,   156,    27,  -243,   128,
    44,  -243,   260,    11,   133,    51,   129,     4,  -243,  -243,
    -243,  -243,  -243,   178,   159,  -243,   324,  -243,  -243,  -243,
    -243,  -243,   213,  -243,  -243,  -243,  -243,  -243,   168,   131,
    -243,  -243,    25,   282,  -243,  -243,    29,   144,  -243,    15,
    -243,   136,     7,     0,  -243,   199,  -243,   206,  -243,   148,
    -243,    11,   111,     4,   -29,  -243,   175,   -26,  -243,   150,
    -243,    50,  -243,   151,     0,     0,  -243,   168,  -243,    15,
    259,  -243,   259,  -243,  -243
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
    0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
    0,     0,     0,     0,     0,     0,     0,   159,     3,     6,
    5,    18,     8,     9,    14,    11,    12,    10,    13,     7,
    59,    60,    80,    15,    16,    17,     0,   142,    50,    21,
    0,    31,    31,    31,     0,     0,     0,    69,     0,     0,
    141,   164,     0,     0,     0,   162,   163,     0,     0,     0,
    1,   158,     2,    66,    67,     0,    65,     0,    86,    47,
    0,     0,     0,     0,     0,     0,     0,     0,    74,    24,
    0,    54,   122,   127,   128,   130,     0,     0,   131,     0,
    132,     0,    71,    87,   148,    95,    96,    97,   104,    98,
    99,   101,   124,   125,   129,   100,   126,     0,     0,    45,
    144,    46,   165,    62,    61,     4,     0,    80,     0,    63,
    143,     0,    89,    19,   159,     0,     0,     0,    28,     0,
    49,     0,     0,     0,    70,     0,   103,   102,     0,     0,
    74,     0,   146,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    147,    93,     0,    74,    56,     0,    83,    86,    84,    22,
    0,     0,    30,     0,     0,     0,    73,     0,    25,   160,
    0,     0,    52,     0,   123,    94,     0,    72,   133,   135,
    148,   137,   154,    76,    88,   116,   119,   120,   113,   111,
    0,   145,   112,   115,   117,   118,   106,   105,   108,   107,
    109,   110,     0,     0,    55,     0,    82,    81,    79,    64,
    0,    90,    20,     0,     0,     0,     0,     0,    32,     0,
    0,    53,     0,     0,    51,     0,     0,     0,   140,   150,
    151,   153,   152,     0,     0,    68,   114,    58,    57,    48,
    85,    29,     0,    37,    39,    41,    40,    38,    44,     0,
    42,    27,     0,     0,    23,   161,     0,     0,   121,     0,
    138,   134,     0,     0,    26,     0,    34,     0,    33,     0,
    91,     0,   136,     0,     0,   156,     0,    78,    43,     0,
    36,     0,   139,     0,     0,     0,    75,    44,    92,     0,
    157,   149,    77,    35,   155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -243,  -243,   224,   227,   226,  -243,  -243,  -243,  -243,    52,
    -243,    24,  -243,    40,  -243,  -243,  -243,     8,  -243,  -243,
    -243,  -243,  -243,  -243,  -243,    90,  -164,   293,     5,  -243,
    240,   176,  -243,  -243,  -110,  -243,  -243,   192,  -243,   149,
    42,  -190,  -243,   179,   -75,  -243,  -243,  -243,  -243,  -243,
    -243,   -70,  -118,  -243,  -116,  -243,  -243,  -243,  -189,  -243,
    45,  -243,    -2,   -12,  -242,   132,  -243,  -243,    49,  -243,
    201,  -243,  -243,  -243,  -243
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
    -1,    16,    17,    18,    19,    20,    21,    22,    80,   177,
    23,    75,   227,   228,   258,   259,   229,   276,    24,    25,
    26,    27,   133,    28,   163,   164,    29,    30,    31,    67,
    32,    48,    91,   140,   130,   245,   296,    68,   218,   119,
    92,   121,   234,    93,    94,    95,    96,    97,    98,    99,
    100,   101,   102,   103,   104,   105,   106,   187,   188,   271,
    189,    49,   190,   111,   160,   161,   191,   243,   192,   301,
    62,   180,    33,    34,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
    38,   122,   168,    82,    83,    84,    85,    37,    50,    51,
    37,   136,   137,   178,   138,    83,    84,    85,   142,   295,
    59,   253,   236,     9,    55,   129,   174,   282,   225,   239,
    193,    63,   134,    36,   135,   240,   241,   143,   144,   145,
    41,   166,    78,   266,    81,   112,    52,    37,   270,    42,
    108,   109,   242,   214,   176,    53,   226,   304,   143,   144,
    145,    64,    72,    73,    39,   128,    76,    77,   195,   196,
    197,   198,   199,   126,   127,   202,   203,   204,   205,   206,
    207,   208,   209,   210,   211,    40,    47,   175,    44,    65,
    169,   291,    56,    66,   292,     9,   170,    43,   254,   213,
    221,   181,    45,    54,   250,   142,  -156,    86,   235,   143,
    144,   145,  -156,  -156,    15,    57,   255,   256,   257,   146,
    293,    46,    60,    61,   141,   246,    69,   149,  -156,  -156,
    70,   147,    74,   231,   178,    87,    88,   148,   182,   232,
    146,    79,   247,    89,    71,   107,   110,   186,     9,   150,
    284,    90,   147,   156,   157,   158,   159,   151,   148,   152,
    153,   289,    90,   122,   154,   155,   156,   157,   158,   159,
    150,   261,   113,   280,   185,   114,  -155,   262,   151,   170,
    152,   153,  -155,  -155,   118,   154,   155,   156,   157,   158,
    159,   146,   116,   120,   298,   268,   125,   129,  -155,  -155,
    170,   131,   132,   147,   141,   162,   139,     1,   165,   148,
    65,   122,    85,   172,   149,     2,   173,    83,   179,   300,
    302,   150,     3,   184,   143,   144,   145,     4,   264,   151,
    200,   152,   153,   201,     5,     6,   154,   155,   156,   157,
    158,   159,     1,     7,     8,   215,   212,   220,   222,     9,
    2,   223,   224,   230,    10,   233,   237,     3,   244,   249,
    251,   252,   260,   265,   159,   272,   143,   144,   145,     5,
    6,   263,   273,   269,   277,   275,    11,    12,     7,     8,
    143,   144,   145,   267,     9,   279,   283,   281,   115,    10,
    288,    13,   290,   294,   297,   299,   216,   124,   123,   143,
    144,   145,   278,   248,   274,   303,   146,   117,    58,   167,
    183,    11,    12,  -157,  -157,   287,   219,   285,   147,   217,
    194,   286,   238,    14,   148,   171,    13,     0,     0,     0,
    0,   143,   144,   145,     0,     0,   150,     0,     0,     0,
    15,     0,     0,     0,   151,     0,   152,   153,   146,     0,
    0,   154,   155,   156,   157,   158,   159,     0,    14,     0,
    147,     0,   146,     0,     0,     0,   148,     0,     0,     0,
    0,     0,     0,     0,   147,    15,     0,     0,   150,     0,
    148,   146,     0,     0,     0,     0,   151,     0,   152,   153,
    0,     0,     0,   154,   155,   156,   157,   158,   159,   148,
    151,     0,   152,   153,     0,     0,     0,   154,   155,   156,
    157,   158,   159,   146,     0,     0,     0,     0,     0,   151,
    0,   152,   153,     0,     0,     0,   154,   155,   156,   157,
    158,   159,     0,     0,  -157,  -157,     0,     0,     0,   154,
    155,   156,   157,   158,   159,     0,     0,     0,     0,     0,
    0,   151,     0,   152,   153,     0,     0,     0,   154,   155,
    156,   157,   158,   159
};

static const yytype_int16 yycheck[] =
{
    2,    71,   118,     3,     4,     5,     6,     3,    10,    11,
    3,    86,    87,   131,    89,     4,     5,     6,     3,    45,
    15,    28,   186,    52,    54,    76,    82,   269,     3,    65,
    140,    12,   143,    30,   145,    71,    72,     7,     8,     9,
    64,   116,    44,   233,    46,    57,    64,     3,   237,    73,
    52,    53,    88,   163,   129,    73,    31,   299,     7,     8,
    9,    42,   147,   148,     3,    77,    42,    43,   143,   144,
    145,   146,   147,    75,    76,   150,   151,   152,   153,   154,
    155,   156,   157,   158,   159,     3,    15,   143,    82,    70,
    144,   281,   122,    74,   283,    52,   150,   121,   105,   150,
    170,    58,    82,   121,   220,     3,    65,   107,   183,     7,
    8,     9,    71,    72,   143,   121,   123,   124,   125,    89,
    284,    86,     0,   146,   150,   200,     3,   112,    87,    88,
    145,   101,   114,   144,   252,   135,   136,   107,   133,   150,
    89,   103,   212,   143,   143,   109,     3,   143,    52,   119,
    143,   151,   101,   136,   137,   138,   139,   127,   107,   129,
    130,   277,   151,   233,   134,   135,   136,   137,   138,   139,
    119,   144,   144,   144,   144,   144,    65,   150,   127,   150,
    129,   130,    71,    72,    66,   134,   135,   136,   137,   138,
    139,    89,   113,     3,   144,   144,   107,    76,    87,    88,
    150,    81,   143,   101,   150,     3,    82,    10,   143,   107,
    70,   281,     6,    43,   112,    18,   143,     4,     3,   294,
    295,   119,    25,     3,     7,     8,     9,    30,   230,   127,
    89,   129,   130,     3,    37,    38,   134,   135,   136,   137,
    138,   139,    10,    46,    47,     3,   127,    49,   149,    52,
    18,     3,   110,    86,    57,   143,   150,    25,    63,   144,
    144,    81,   106,     3,   139,    87,     7,     8,     9,    37,
    38,   143,   113,   144,   143,   107,    79,    80,    46,    47,
    7,     8,     9,   150,    52,     3,   150,   143,    61,    57,
    91,    94,   144,   118,   144,   144,    79,    73,    72,     7,
    8,     9,   262,   213,   252,   297,    89,    67,    15,   117,
    134,    79,    80,     8,     9,   273,   167,   272,   101,   102,
    141,   272,   190,   126,   107,   124,    94,    -1,    -1,    -1,
    -1,     7,     8,     9,    -1,    -1,   119,    -1,    -1,    -1,
    143,    -1,    -1,    -1,   127,    -1,   129,   130,    89,    -1,
    -1,   134,   135,   136,   137,   138,   139,    -1,   126,    -1,
    101,    -1,    89,    -1,    -1,    -1,   107,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   101,   143,    -1,    -1,   119,    -1,
    107,    89,    -1,    -1,    -1,    -1,   127,    -1,   129,   130,
    -1,    -1,    -1,   134,   135,   136,   137,   138,   139,   107,
    127,    -1,   129,   130,    -1,    -1,    -1,   134,   135,   136,
    137,   138,   139,    89,    -1,    -1,    -1,    -1,    -1,   127,
    -1,   129,   130,    -1,    -1,    -1,   134,   135,   136,   137,
    138,   139,    -1,    -1,   129,   130,    -1,    -1,    -1,   134,
    135,   136,   137,   138,   139,    -1,    -1,    -1,    -1,    -1,
    -1,   127,    -1,   129,   130,    -1,    -1,    -1,   134,   135,
    136,   137,   138,   139
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
    0,    10,    18,    25,    30,    37,    38,    46,    47,    52,
    57,    79,    80,    94,   126,   143,   153,   154,   155,   156,
    157,   158,   159,   162,   170,   171,   172,   173,   175,   178,
    179,   180,   182,   224,   225,   226,    30,     3,   214,     3,
    3,    64,    73,   121,    82,    82,    86,    15,   183,   213,
    214,   214,    64,    73,   121,    54,   122,   121,   179,   180,
    0,   146,   222,    12,    42,    70,    74,   181,   189,     3,
    145,   143,   147,   148,   114,   163,   163,   163,   214,   103,
    160,   214,     3,     4,     5,     6,   107,   135,   136,   143,
    151,   184,   192,   195,   196,   197,   198,   199,   200,   201,
    202,   203,   204,   205,   206,   207,   208,   109,   214,   214,
    3,   215,   215,   144,   144,   155,   113,   182,    66,   191,
    3,   193,   203,   156,   154,   107,   214,   214,   215,    76,
    186,    81,   143,   174,   143,   145,   196,   196,   196,    82,
    185,   150,     3,     7,     8,     9,    89,   101,   107,   112,
    119,   127,   129,   130,   134,   135,   136,   137,   138,   139,
    216,   217,     3,   176,   177,   143,   196,   189,   206,   144,
    150,   222,    43,   143,    82,   143,   196,   161,   204,     3,
    223,    58,   180,   183,     3,   144,   143,   209,   210,   212,
    214,   218,   220,   186,   195,   196,   196,   196,   196,   196,
    89,     3,   196,   196,   196,   196,   196,   196,   196,   196,
    196,   196,   127,   150,   186,     3,    79,   102,   190,   191,
    49,   203,   149,     3,   110,     3,    31,   164,   165,   168,
    86,   144,   150,   143,   194,   196,   178,   150,   217,    65,
    71,    72,    88,   219,    63,   187,   196,   203,   177,   144,
    206,   144,    81,    28,   105,   123,   124,   125,   166,   167,
    106,   144,   150,   143,   214,     3,   193,   150,   144,   144,
    210,   211,    87,   113,   161,   107,   169,   143,   165,     3,
    144,   143,   216,   150,   143,   212,   220,   192,    91,   206,
    144,   193,   210,   178,   118,    45,   188,   144,   144,   144,
    196,   221,   196,   169,   216
};

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
    0,   152,   153,   154,   154,   155,   155,   156,   156,   156,
    156,   156,   156,   156,   156,   156,   156,   156,   156,   157,
    157,   158,   158,   159,   160,   161,   162,   162,   162,   162,
    163,   163,   164,   164,   165,   165,   165,   166,   166,   167,
    167,   167,   168,   169,   169,   170,   170,   170,   170,   171,
    172,   173,   173,   174,   174,   175,   176,   176,   177,   178,
    178,   179,   179,   180,   180,   181,   181,   181,   182,   183,
    183,   184,   185,   186,   186,   187,   187,   188,   188,   189,
    189,   190,   190,   190,   191,   191,   191,   192,   192,   193,
    193,   194,   194,   195,   196,   196,   196,   196,   196,   197,
    197,   197,   198,   198,   199,   199,   199,   199,   199,   199,
    199,   199,   199,   199,   199,   200,   200,   200,   200,   200,
    200,   201,   202,   202,   203,   203,   203,   204,   205,   205,
    206,   207,   208,   209,   209,   210,   210,   210,   211,   211,
    212,   213,   214,   214,   215,   216,   216,   217,   217,   218,
    219,   219,   219,   219,   219,   220,   220,   221,   222,   222,
    223,   223,   224,   224,   225,   226
};

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
    0,     2,     2,     1,     3,     1,     1,     1,     1,     1,
    1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
    6,     2,     5,     7,     1,     1,     8,     7,     4,     7,
    3,     0,     1,     3,     3,     6,     4,     1,     1,     1,
    1,     1,     2,     2,     0,     3,     3,     3,     6,     4,
    2,     6,     5,     3,     0,     5,     1,     3,     3,     1,
    1,     3,     3,     3,     5,     1,     1,     1,     6,     1,
    0,     1,     2,     2,     0,     4,     0,     2,     0,     4,
    0,     1,     1,     0,     2,     4,     0,     1,     3,     1,
    3,     3,     5,     2,     3,     1,     1,     1,     1,     1,
    1,     1,     2,     2,     1,     3,     3,     3,     3,     3,
    3,     3,     3,     3,     4,     3,     3,     3,     3,     3,
    3,     5,     1,     3,     1,     1,     1,     1,     1,     1,
    1,     1,     1,     1,     3,     1,     4,     1,     1,     3,
    2,     1,     1,     3,     1,     2,     1,     1,     0,     6,
    1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
    1,     3,     2,     2,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, result, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if HSQL_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const *const yylocp)
{
    unsigned res = 0;
    int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;

    if (0 <= yylocp->first_line)
    {
        res += YYFPRINTF (yyo, "%d", yylocp->first_line);

        if (0 <= yylocp->first_column)
            res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }

    if (0 <= yylocp->last_line)
    {
        if (yylocp->first_line < yylocp->last_line)
        {
            res += YYFPRINTF (yyo, "-%d", yylocp->last_line);

            if (0 <= end_col)
                res += YYFPRINTF (yyo, ".%d", end_col);
        }
        else if (0 <= end_col && yylocp->first_column < end_col)
            res += YYFPRINTF (yyo, "-%d", end_col);
    }

    return res;
}

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const *const yyvaluep, YYLTYPE const *const yylocationp, hsql::SQLParserResult **result, yyscan_t scanner)
{
    FILE *yyo = yyoutput;
    YYUSE (yyo);
    YYUSE (yylocationp);
    YYUSE (result);
    YYUSE (scanner);

    if (!yyvaluep)
        return;

# ifdef YYPRINT

    if (yytype < YYNTOKENS)
        YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);

# endif
    YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const *const yyvaluep, YYLTYPE const *const yylocationp, hsql::SQLParserResult **result, yyscan_t scanner)
{
    YYFPRINTF (yyoutput, "%s %s (",
               yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

    YY_LOCATION_PRINT (yyoutput, *yylocationp);
    YYFPRINTF (yyoutput, ": ");
    yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result, scanner);
    YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
    YYFPRINTF (stderr, "Stack now");

    for (; yybottom <= yytop; yybottom++)
    {
        int yybot = *yybottom;
        YYFPRINTF (stderr, " %d", yybot);
    }

    YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, hsql::SQLParserResult **result, yyscan_t scanner)
{
    unsigned long int yylno = yyrline[yyrule];
    int yynrhs = yyr2[yyrule];
    int yyi;
    YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
               yyrule - 1, yylno);

    /* The symbols being reduced.  */
    for (yyi = 0; yyi < yynrhs; yyi++)
    {
        YYFPRINTF (stderr, "   $%d = ", yyi + 1);
        yy_symbol_print (stderr,
                         yystos[yyssp[yyi + 1 - yynrhs]],
                         &(yyvsp[(yyi + 1) - (yynrhs)])
                         , &(yylsp[(yyi + 1) - (yynrhs)])                       , result, scanner);
        YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !HSQL_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !HSQL_DEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
    YYSIZE_T yylen;

    for (yylen = 0; yystr[yylen]; yylen++)
        continue;

    return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
    char *yyd = yydest;
    const char *yys = yysrc;

    while ((*yyd++ = *yys++) != '\0')
        continue;

    return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
    if (*yystr == '"')
    {
        YYSIZE_T yyn = 0;
        char const *yyp = yystr;

        for (;;)
            switch (*++yyp)
            {
                case '\'':
                case ',':
                    goto do_not_strip_quotes;

                case '\\':
                    if (*++yyp != '\\')
                        goto do_not_strip_quotes;

                    /* Fall through.  */
                default:
                    if (yyres)
                        yyres[yyn] = *yyp;

                    yyn++;
                    break;

                case '"':
                    if (yyres)
                        yyres[yyn] = '\0';

                    return yyn;
            }

do_not_strip_quotes:
        ;
    }

    if (! yyres)
        return yystrlen (yystr);

    return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
    YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
    YYSIZE_T yysize = yysize0;
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    /* Internationalized format string. */
    const char *yyformat = YY_NULLPTR;
    /* Arguments of yyformat. */
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
    /* Number of reported tokens (one for the "unexpected", one per
       "expected"). */
    int yycount = 0;

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yychar) is if
         this state is a consistent state with a default action.  Thus,
         detecting the absence of a lookahead is sufficient to determine
         that there is no unexpected or expected token to report.  In that
         case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is a
         consistent state with a default action.  There might have been a
         previous inconsistent state, consistent state with a non-default
         action, or user semantic action that manipulated yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (yytoken != YYEMPTY)
    {
        int yyn = yypact[*yyssp];
        yyarg[yycount++] = yytname[yytoken];

        if (!yypact_value_is_default (yyn))
        {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = YYLAST - yyn + 1;
            int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
            int yyx;

            for (yyx = yyxbegin; yyx < yyxend; ++yyx)
                if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                        && !yytable_value_is_error (yytable[yyx + yyn]))
                {
                    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                        yycount = 1;
                        yysize = yysize0;
                        break;
                    }

                    yyarg[yycount++] = yytname[yyx];
                    {
                        YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);

                        if (! (yysize <= yysize1
                                && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                            return 2;

                        yysize = yysize1;
                    }
                }
        }
    }

    switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
            YYCASE_(0, YY_("syntax error"));
            YYCASE_(1, YY_("syntax error, unexpected %s"));
            YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
            YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
            YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
            YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

    {
        YYSIZE_T yysize1 = yysize + yystrlen (yyformat);

        if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
            return 2;

        yysize = yysize1;
    }

    if (*yymsg_alloc < yysize)
    {
        *yymsg_alloc = 2 * yysize;

        if (! (yysize <= *yymsg_alloc
                && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
            *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;

        return 1;
    }

    /* Avoid sprintf, as that infringes on the user's name space.
       Don't have undefined behavior even if the translation
       produced a string with the wrong number of "%s"s.  */
    {
        char *yyp = *yymsg;
        int yyi = 0;

        while ((*yyp = *yyformat) != '\0')
            if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
                yyp += yytnamerr (yyp, yyarg[yyi++]);
                yyformat += 2;
            }
            else
            {
                yyp++;
                yyformat++;
            }
    }
    return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, hsql::SQLParserResult **result, yyscan_t scanner)
{
    YYUSE (yyvaluep);
    YYUSE (yylocationp);
    YYUSE (result);
    YYUSE (scanner);

    if (!yymsg)
        yymsg = "Deleting";

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    YYUSE (yytype);
    YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (hsql::SQLParserResult **result, yyscan_t scanner)
{
    /* The lookahead symbol.  */
    int yychar;


    /* The semantic value of the lookahead symbol.  */
    /* Default value used for initialization, for pacifying older GCCs
       or non-GCC compilers.  */
    YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
    YYSTYPE yylval YY_INITIAL_VALUE ( = yyval_default);

    /* Location data for the lookahead symbol.  */
    static YYLTYPE yyloc_default
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL
        = { 1, 1, 1, 1 }
# endif
          ;
    YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

    int yyn;
    int yyresult;
    /* Lookahead token as an internal (translated) token number.  */
    int yytoken = 0;
    /* The variables used to return semantic value and location from the
       action routines.  */
    YYSTYPE yyval;
    YYLTYPE yyloc;

#if YYERROR_VERBOSE
    /* Buffer for error messages, and its allocated size.  */
    char yymsgbuf[128];
    char *yymsg = yymsgbuf;
    YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

    /* The number of symbols on the RHS of the reduced rule.
       Keep to zero when no symbol should be popped.  */
    int yylen = 0;

    yyssp = yyss = yyssa;
    yyvsp = yyvs = yyvsa;
    yylsp = yyls = yylsa;
    yystacksize = YYINITDEPTH;

    YYDPRINTF ((stderr, "Starting parse\n"));

    yystate = 0;
    yyerrstatus = 0;
    yynerrs = 0;
    yychar = YYEMPTY; /* Cause a token to be read.  */

    /* User initialization code.  */
#line 79 "bison_parser.y" /* yacc.c:1429  */
    {
        // Initialize
        yylloc.first_column = 0;
        yylloc.last_column = 0;
        yylloc.first_line = 0;
        yylloc.last_line = 0;
        yylloc.total_column = 0;
        yylloc.placeholder_id = 0;
    }

#line 1687 "bison_parser.cpp" /* yacc.c:1429  */
    yylsp[0] = yylloc;
    goto yysetstate;

    /*------------------------------------------------------------.
    | yynewstate -- Push a new state, which is found in yystate.  |
    `------------------------------------------------------------*/
yynewstate:
    /* In all cases, when you get here, the value and location stacks
       have just been pushed.  So pushing a state here evens the stacks.  */
    yyssp++;

yysetstate:
    *yyssp = yystate;

    if (yyss + yystacksize - 1 <= yyssp)
    {
        /* Get the current used size of the three stacks, in elements.  */
        YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
        {
            /* Give user a chance to reallocate the stack.  Use copies of
               these so that the &'s don't force the real ones into
               memory.  */
            YYSTYPE *yyvs1 = yyvs;
            yytype_int16 *yyss1 = yyss;
            YYLTYPE *yyls1 = yyls;

            /* Each stack pointer address is followed by the size of the
               data in use in that stack, in bytes.  This used to be a
               conditional around just the two extra args, but that might
               be undefined if yyoverflow is a macro.  */
            yyoverflow (YY_("memory exhausted"),
                        &yyss1, yysize * sizeof (*yyssp),
                        &yyvs1, yysize * sizeof (*yyvsp),
                        &yyls1, yysize * sizeof (*yylsp),
                        &yystacksize);

            yyls = yyls1;
            yyss = yyss1;
            yyvs = yyvs1;
        }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
        goto yyexhaustedlab;
# else

        /* Extend the stack our own way.  */
        if (YYMAXDEPTH <= yystacksize)
            goto yyexhaustedlab;

        yystacksize *= 2;

        if (YYMAXDEPTH < yystacksize)
            yystacksize = YYMAXDEPTH;

        {
            yytype_int16 *yyss1 = yyss;
            union yyalloc *yyptr =
                        (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));

            if (! yyptr)
                goto yyexhaustedlab;

            YYSTACK_RELOCATE (yyss_alloc, yyss);
            YYSTACK_RELOCATE (yyvs_alloc, yyvs);
            YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE

            if (yyss1 != yyssa)
                YYSTACK_FREE (yyss1);
        }
# endif
#endif /* no yyoverflow */

        yyssp = yyss + yysize - 1;
        yyvsp = yyvs + yysize - 1;
        yylsp = yyls + yysize - 1;

        YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                    (unsigned long int) yystacksize));

        if (yyss + yystacksize - 1 <= yyssp)
            YYABORT;
    }

    YYDPRINTF ((stderr, "Entering state %d\n", yystate));

    if (yystate == YYFINAL)
        YYACCEPT;

    goto yybackup;

    /*-----------.
    | yybackup.  |
    `-----------*/
yybackup:

    /* Do appropriate processing given the current state.  Read a
       lookahead token if we need one and don't already have one.  */

    /* First try to decide what to do without reference to lookahead token.  */
    yyn = yypact[yystate];

    if (yypact_value_is_default (yyn))
        goto yydefault;

    /* Not known => get a lookahead token if don't already have one.  */

    /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
    if (yychar == YYEMPTY)
    {
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex (&yylval, &yylloc, scanner);
    }

    if (yychar <= YYEOF)
    {
        yychar = yytoken = YYEOF;
        YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
    else
    {
        yytoken = YYTRANSLATE (yychar);
        YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;

    if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
        goto yydefault;

    yyn = yytable[yyn];

    if (yyn <= 0)
    {
        if (yytable_value_is_error (yyn))
            goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
    }

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus)
        yyerrstatus--;

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the shifted token.  */
    yychar = YYEMPTY;

    yystate = yyn;
    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    *++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END
    *++yylsp = yylloc;
    goto yynewstate;


    /*-----------------------------------------------------------.
    | yydefault -- do the default action for the current state.  |
    `-----------------------------------------------------------*/
yydefault:
    yyn = yydefact[yystate];

    if (yyn == 0)
        goto yyerrlab;

    goto yyreduce;


    /*-----------------------------.
    | yyreduce -- Do a reduction.  |
    `-----------------------------*/
yyreduce:
    /* yyn is the number of a rule to reduce with.  */
    yylen = yyr2[yyn];

    /* If YYLEN is nonzero, implement the default value of the action:
       '$$ = $1'.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  Assigning to YYVAL
       unconditionally makes the parser a bit smaller, and it avoids a
       GCC warning that YYVAL may be used uninitialized.  */
    yyval = yyvsp[1 - yylen];

    /* Default location.  */
    YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
    YY_REDUCE_PRINT (yyn);

    switch (yyn)
    {
        case 2:
#line 238 "bison_parser.y" /* yacc.c:1646  */
            {
                *result = (yyvsp[-1].stmt_list);
            }

#line 1878 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 3:
#line 245 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.stmt_list) = new SQLParserResult((yyvsp[0].statement));
            }

#line 1884 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 4:
#line 246 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[-2].stmt_list)->addStatement((yyvsp[0].statement));
                (yyval.stmt_list) = (yyvsp[-2].stmt_list);
            }

#line 1890 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 5:
#line 250 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[0].prep_stmt)->setPlaceholders(yyloc.placeholder_list);
                yyloc.placeholder_list.clear();
                (yyval.statement) = (yyvsp[0].prep_stmt);
            }

#line 1900 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 7:
#line 260 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].select_stmt);
            }

#line 1906 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 8:
#line 261 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].import_stmt);
            }

#line 1912 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 9:
#line 262 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].create_stmt);
            }

#line 1918 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 10:
#line 263 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].insert_stmt);
            }

#line 1924 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 11:
#line 264 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].delete_stmt);
            }

#line 1930 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 12:
#line 265 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].delete_stmt);
            }

#line 1936 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 13:
#line 266 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].update_stmt);
            }

#line 1942 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 14:
#line 267 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].drop_stmt);
            }

#line 1948 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 15:
#line 268 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].show_stmt);
            }

#line 1954 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 16:
#line 269 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].desc_stmt);
            }

#line 1960 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 17:
#line 270 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].use_stmt);
            }

#line 1966 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 18:
#line 271 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.statement) = (yyvsp[0].exec_stmt);
            }

#line 1972 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 19:
#line 279 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.prep_stmt) = new PrepareStatement();
                (yyval.prep_stmt)->name = (yyvsp[-2].sval);
                (yyval.prep_stmt)->query = new SQLParserResult((yyvsp[0].statement));
            }

#line 1982 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 20:
#line 284 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.prep_stmt) = new PrepareStatement();
                (yyval.prep_stmt)->name = (yyvsp[-4].sval);
                (yyval.prep_stmt)->query = (yyvsp[-2].stmt_list);
            }

#line 1992 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 21:
#line 292 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.exec_stmt) = new ExecuteStatement();
                (yyval.exec_stmt)->name = (yyvsp[0].sval);
            }

#line 2001 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 22:
#line 296 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.exec_stmt) = new ExecuteStatement();
                (yyval.exec_stmt)->name = (yyvsp[-3].sval);
                (yyval.exec_stmt)->parameters = (yyvsp[-1].expr_vec);
            }

#line 2011 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 23:
#line 308 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.import_stmt) = new ImportStatement((ImportStatement::ImportType) (yyvsp[-4].uval));
                (yyval.import_stmt)->filePath = (yyvsp[-2].sval);
                (yyval.import_stmt)->tableName = (yyvsp[0].sval);
            }

#line 2021 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 24:
#line 316 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = ImportStatement::kImportCSV;
            }

#line 2027 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 25:
#line 320 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.sval) = (yyvsp[0].expr)->name;
            }

#line 2033 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 26:
#line 330 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.create_stmt) = new CreateStatement(CreateStatement::kTableFromTbl);
                (yyval.create_stmt)->ifNotExists = (yyvsp[-5].bval);
                (yyval.create_stmt)->tableName = (yyvsp[-4].sval);
                (yyval.create_stmt)->filePath = (yyvsp[0].sval);
            }

#line 2044 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 27:
#line 336 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
                (yyval.create_stmt)->ifNotExists = (yyvsp[-4].bval);
                (yyval.create_stmt)->tableName = (yyvsp[-3].sval);
                (yyval.create_stmt)->columns = (yyvsp[-1].column_vec);
            }

#line 2055 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 28:
#line 342 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.create_stmt) = new CreateStatement(CreateStatement::kDatabase);
                (yyval.create_stmt)->ifNotExists = (yyvsp[-1].bval);
                (yyval.create_stmt)->tableName = (yyvsp[0].sval);
            }

#line 2065 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 29:
#line 347 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.create_stmt) = new CreateStatement(CreateStatement::kIndex);
                (yyval.create_stmt)->ifNotExists = (yyvsp[-4].bval);
                (yyval.create_stmt)->tableName = (yyvsp[-3].sval);
                (yyval.create_stmt)->indexName = (yyvsp[-1].sval);
            }

#line 2076 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 30:
#line 356 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.bval) = true;
            }

#line 2082 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 31:
#line 357 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.bval) = false;
            }

#line 2088 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 32:
#line 361 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.column_vec) = new std::vector<ColumnDefinition *>();
                (yyval.column_vec)->push_back((yyvsp[0].column_t));
            }

#line 2094 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 33:
#line 362 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[-2].column_vec)->push_back((yyvsp[0].column_t));
                (yyval.column_vec) = (yyvsp[-2].column_vec);
            }

#line 2100 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 34:
#line 366 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.column_t) = new ColumnDefinition((yyvsp[-2].sval), (ColumnDefinition::DataType) (yyvsp[-1].uval), (yyvsp[0].bval));
            }

#line 2108 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 35:
#line 369 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.column_t) = new ColumnDefinition((yyvsp[-5].sval), (ColumnDefinition::DataType) (yyvsp[-4].uval), (yyvsp[0].bval), (yyvsp[-2].expr)->ival);
            }

#line 2116 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 36:
#line 372 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.column_t) = new ColumnDefinition((yyvsp[-1].sval), (ColumnDefinition::DataType) (yyvsp[-3].uval), false);
            }

#line 2124 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 37:
#line 379 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = ColumnDefinition::INTEGER;
            }

#line 2130 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 38:
#line 380 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = ColumnDefinition::TINYINT;
            }

#line 2136 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 39:
#line 384 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = ColumnDefinition::INT;
            }

#line 2142 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 40:
#line 385 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = ColumnDefinition::VARCHAR;
            }

#line 2148 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 41:
#line 386 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = ColumnDefinition::CHAR;
            }

#line 2154 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 42:
#line 390 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = ColumnDefinition::PRIMARY;
            }

#line 2160 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 43:
#line 394 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.bval) = true;
            }

#line 2166 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 44:
#line 395 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.bval) = false;
            }

#line 2172 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 45:
#line 405 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.drop_stmt) = new DropStatement(DropStatement::kTable);
                (yyval.drop_stmt)->name = (yyvsp[0].sval);
            }

#line 2181 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 46:
#line 409 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.drop_stmt) = new DropStatement(DropStatement::kDatabase);
                (yyval.drop_stmt)->name = (yyvsp[0].sval);
            }

#line 2190 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 47:
#line 413 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.drop_stmt) = new DropStatement(DropStatement::kPreparedStatement);
                (yyval.drop_stmt)->name = (yyvsp[0].sval);
            }

#line 2199 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 48:
#line 417 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.drop_stmt) = new DropStatement(DropStatement::kIndex);
                (yyval.drop_stmt)->name = (yyvsp[-3].sval);
                (yyval.drop_stmt)->index = (yyvsp[-1].sval);
            }

#line 2209 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 49:
#line 430 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.delete_stmt) = new DeleteStatement();
                (yyval.delete_stmt)->tableName = (yyvsp[-1].sval);
                (yyval.delete_stmt)->expr = (yyvsp[0].expr);
            }

#line 2219 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 50:
#line 438 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.delete_stmt) = new DeleteStatement();
                (yyval.delete_stmt)->tableName = (yyvsp[0].sval);
            }

#line 2228 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 51:
#line 450 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertValues);
                (yyval.insert_stmt)->tableName = (yyvsp[-3].sval);
                (yyval.insert_stmt)->columns = (yyvsp[-2].str_vec);
                (yyval.insert_stmt)->values = (yyvsp[0].expr_vec_vec);
            }

#line 2239 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 52:
#line 456 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertSelect);
                (yyval.insert_stmt)->tableName = (yyvsp[-2].sval);
                (yyval.insert_stmt)->columns = (yyvsp[-1].str_vec);
                (yyval.insert_stmt)->select = (yyvsp[0].select_stmt);
            }

#line 2250 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 53:
#line 466 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.str_vec) = (yyvsp[-1].str_vec);
            }

#line 2256 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 54:
#line 467 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.str_vec) = NULL;
            }

#line 2262 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 55:
#line 477 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.update_stmt) = new UpdateStatement();
                (yyval.update_stmt)->table = (yyvsp[-3].table);
                (yyval.update_stmt)->updates = (yyvsp[-1].update_vec);
                (yyval.update_stmt)->where = (yyvsp[0].expr);
            }

#line 2273 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 56:
#line 486 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.update_vec) = new std::vector<UpdateClause *>();
                (yyval.update_vec)->push_back((yyvsp[0].update_t));
            }

#line 2279 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 57:
#line 487 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[-2].update_vec)->push_back((yyvsp[0].update_t));
                (yyval.update_vec) = (yyvsp[-2].update_vec);
            }

#line 2285 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 58:
#line 491 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.update_t) = new UpdateClause();
                (yyval.update_t)->column = (yyvsp[-2].sval);
                (yyval.update_t)->value = (yyvsp[0].expr);
            }

#line 2295 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 61:
#line 508 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.select_stmt) = (yyvsp[-1].select_stmt);
            }

#line 2301 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 62:
#line 509 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.select_stmt) = (yyvsp[-1].select_stmt);
            }

#line 2307 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 63:
#line 513 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.select_stmt) = (yyvsp[-2].select_stmt);
                (yyval.select_stmt)->order = (yyvsp[-1].order);
                (yyval.select_stmt)->limit = (yyvsp[0].limit);
            }

#line 2317 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 64:
#line 518 "bison_parser.y" /* yacc.c:1646  */
            {
                // TODO: allow multiple unions (through linked list)
                // TODO: capture type of set_operator
                // TODO: might overwrite order and limit of first select here
                (yyval.select_stmt) = (yyvsp[-4].select_stmt);
                (yyval.select_stmt)->unionSelect = (yyvsp[-2].select_stmt);
                (yyval.select_stmt)->order = (yyvsp[-1].order);
                (yyval.select_stmt)->limit = (yyvsp[0].limit);
            }

#line 2331 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 68:
#line 536 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.select_stmt) = new SelectStatement();
                (yyval.select_stmt)->selectDistinct = (yyvsp[-4].bval);
                (yyval.select_stmt)->selectList = (yyvsp[-3].expr_vec);
                (yyval.select_stmt)->fromTable = (yyvsp[-2].table);
                (yyval.select_stmt)->whereClause = (yyvsp[-1].expr);
                (yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
            }

#line 2344 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 69:
#line 547 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.bval) = true;
            }

#line 2350 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 70:
#line 548 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.bval) = false;
            }

#line 2356 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 72:
#line 557 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.table) = (yyvsp[0].table);
            }

#line 2362 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 73:
#line 562 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = (yyvsp[0].expr);
            }

#line 2368 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 74:
#line 563 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = NULL;
            }

#line 2374 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 75:
#line 567 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.group_t) = new GroupByDescription();
                (yyval.group_t)->columns = (yyvsp[-1].expr_vec);
                (yyval.group_t)->having = (yyvsp[0].expr);
            }

#line 2384 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 76:
#line 572 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.group_t) = NULL;
            }

#line 2390 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 77:
#line 576 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = (yyvsp[0].expr);
            }

#line 2396 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 78:
#line 577 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = NULL;
            }

#line 2402 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 79:
#line 580 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.order) = new OrderDescription((yyvsp[0].order_type), (yyvsp[-1].expr));
            }

#line 2408 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 80:
#line 581 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.order) = NULL;
            }

#line 2414 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 81:
#line 585 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.order_type) = kOrderAsc;
            }

#line 2420 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 82:
#line 586 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.order_type) = kOrderDesc;
            }

#line 2426 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 83:
#line 587 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.order_type) = kOrderAsc;
            }

#line 2432 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 84:
#line 592 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.limit) = new LimitDescription((yyvsp[0].expr)->ival, kNoOffset);
                delete (yyvsp[0].expr);
            }

#line 2438 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 85:
#line 593 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.limit) = new LimitDescription((yyvsp[-2].expr)->ival, (yyvsp[0].expr)->ival);
                delete (yyvsp[-2].expr);
                delete (yyvsp[0].expr);
            }

#line 2444 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 86:
#line 594 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.limit) = NULL;
            }

#line 2450 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 87:
#line 601 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr_vec) = new std::vector<Expr *>();
                (yyval.expr_vec)->push_back((yyvsp[0].expr));
            }

#line 2456 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 88:
#line 602 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr));
                (yyval.expr_vec) = (yyvsp[-2].expr_vec);
            }

#line 2462 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 89:
#line 606 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr_vec) = new std::vector<Expr *>();
                (yyval.expr_vec)->push_back((yyvsp[0].expr));
            }

#line 2468 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 90:
#line 607 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr));
                (yyval.expr_vec) = (yyvsp[-2].expr_vec);
            }

#line 2474 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 91:
#line 611 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr_vec_vec) = new std::vector<std::vector<Expr *>*>();
                (yyval.expr_vec_vec)->push_back((yyvsp[-1].expr_vec));
            }

#line 2480 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 92:
#line 612 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[-4].expr_vec_vec)->push_back((yyvsp[-1].expr_vec));
                (yyval.expr_vec_vec) = (yyvsp[-4].expr_vec_vec);
            }

#line 2486 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 93:
#line 616 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = (yyvsp[-1].expr);
                (yyval.expr)->alias = (yyvsp[0].sval);
            }

#line 2495 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 94:
#line 623 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = (yyvsp[-1].expr);
            }

#line 2501 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 102:
#line 637 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpUnary(Expr::UMINUS, (yyvsp[0].expr));
            }

#line 2507 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 103:
#line 638 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpUnary(Expr::NOT, (yyvsp[0].expr));
            }

#line 2513 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 105:
#line 643 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '-', (yyvsp[0].expr));
            }

#line 2519 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 106:
#line 644 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '+', (yyvsp[0].expr));
            }

#line 2525 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 107:
#line 645 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '/', (yyvsp[0].expr));
            }

#line 2531 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 108:
#line 646 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '*', (yyvsp[0].expr));
            }

#line 2537 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 109:
#line 647 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '%', (yyvsp[0].expr));
            }

#line 2543 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 110:
#line 648 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '^', (yyvsp[0].expr));
            }

#line 2549 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 111:
#line 649 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::AND, (yyvsp[0].expr));
            }

#line 2555 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 112:
#line 650 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::OR, (yyvsp[0].expr));
            }

#line 2561 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 113:
#line 651 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LIKE, (yyvsp[0].expr));
            }

#line 2567 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 114:
#line 652 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), Expr::NOT_LIKE, (yyvsp[0].expr));
            }

#line 2573 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 115:
#line 657 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '=', (yyvsp[0].expr));
            }

#line 2579 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 116:
#line 658 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::NOT_EQUALS, (yyvsp[0].expr));
            }

#line 2585 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 117:
#line 659 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '<', (yyvsp[0].expr));
            }

#line 2591 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 118:
#line 660 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '>', (yyvsp[0].expr));
            }

#line 2597 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 119:
#line 661 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LESS_EQ, (yyvsp[0].expr));
            }

#line 2603 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 120:
#line 662 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::GREATER_EQ, (yyvsp[0].expr));
            }

#line 2609 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 121:
#line 666 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeFunctionRef((yyvsp[-4].sval), (yyvsp[-1].expr), (yyvsp[-2].bval));
            }

#line 2615 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 122:
#line 670 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeColumnRef((yyvsp[0].sval));
            }

#line 2621 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 123:
#line 671 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeColumnRef((yyvsp[-2].sval), (yyvsp[0].sval));
            }

#line 2627 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 127:
#line 681 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeLiteral((yyvsp[0].sval));
            }

#line 2633 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 128:
#line 686 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeLiteral((yyvsp[0].fval));
            }

#line 2639 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 130:
#line 691 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makeLiteral((yyvsp[0].ival));
            }

#line 2645 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 131:
#line 695 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = new Expr(kExprStar);
            }

#line 2651 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 132:
#line 700 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.expr) = Expr::makePlaceholder(yylloc.total_column);
                yyloc.placeholder_list.push_back((yyval.expr));
            }

#line 2660 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 134:
#line 712 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[0].table_vec)->push_back((yyvsp[-2].table));
                auto tbl = new TableRef(kTableCrossProduct);
                tbl->list = (yyvsp[0].table_vec);
                (yyval.table) = tbl;
            }

#line 2671 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 136:
#line 723 "bison_parser.y" /* yacc.c:1646  */
            {
                auto tbl = new TableRef(kTableSelect);
                tbl->select = (yyvsp[-2].select_stmt);
                tbl->alias = (yyvsp[0].sval);
                (yyval.table) = tbl;
            }

#line 2682 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 138:
#line 734 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.table_vec) = new std::vector<TableRef *>();
                (yyval.table_vec)->push_back((yyvsp[0].table));
            }

#line 2688 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 139:
#line 735 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[-2].table_vec)->push_back((yyvsp[0].table));
                (yyval.table_vec) = (yyvsp[-2].table_vec);
            }

#line 2694 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 140:
#line 740 "bison_parser.y" /* yacc.c:1646  */
            {
                auto tbl = new TableRef(kTableName);
                tbl->name = (yyvsp[-1].sval);
                tbl->alias = (yyvsp[0].sval);
                (yyval.table) = tbl;
            }

#line 2705 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 141:
#line 750 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.table) = new TableRef(kTableName);
                (yyval.table)->name = (yyvsp[0].sval);
            }

#line 2714 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 145:
#line 766 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.sval) = (yyvsp[0].sval);
            }

#line 2720 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 148:
#line 772 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.sval) = NULL;
            }

#line 2726 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 149:
#line 781 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.table) = new TableRef(kTableJoin);
                (yyval.table)->join = new JoinDefinition();
                (yyval.table)->join->type = (JoinType) (yyvsp[-4].uval);
                (yyval.table)->join->left = (yyvsp[-5].table);
                (yyval.table)->join->right = (yyvsp[-2].table);
                (yyval.table)->join->condition = (yyvsp[0].expr);
            }

#line 2739 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 150:
#line 792 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = kJoinInner;
            }

#line 2745 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 151:
#line 793 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = kJoinOuter;
            }

#line 2751 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 152:
#line 794 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = kJoinLeft;
            }

#line 2757 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 153:
#line 795 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = kJoinRight;
            }

#line 2763 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 154:
#line 796 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.uval) = kJoinInner;
            }

#line 2769 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 155:
#line 802 "bison_parser.y" /* yacc.c:1646  */
            {
                auto tbl = new TableRef(kTableSelect);
                tbl->select = (yyvsp[-2].select_stmt);
                tbl->alias = (yyvsp[0].sval);
                (yyval.table) = tbl;
            }

#line 2780 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 160:
#line 827 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.str_vec) = new std::vector<char *>();
                (yyval.str_vec)->push_back((yyvsp[0].sval));
            }

#line 2786 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 161:
#line 828 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyvsp[-2].str_vec)->push_back((yyvsp[0].sval));
                (yyval.str_vec) = (yyvsp[-2].str_vec);
            }

#line 2792 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 162:
#line 837 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.show_stmt) = new ShowStatement(ShowStatement::kTable);
            }

#line 2800 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 163:
#line 840 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.show_stmt) = new ShowStatement(ShowStatement::kDatabase);
            }

#line 2808 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 164:
#line 846 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.desc_stmt) = new DescStatement((yyvsp[0].sval));
            }

#line 2816 "bison_parser.cpp" /* yacc.c:1646  */
            break;

        case 165:
#line 852 "bison_parser.y" /* yacc.c:1646  */
            {
                (yyval.use_stmt) = new UseStatement((yyvsp[0].sval));
            }

#line 2824 "bison_parser.cpp" /* yacc.c:1646  */
            break;


#line 2828 "bison_parser.cpp" /* yacc.c:1646  */

        default:
            break;
    }

    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action invokes
       YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
       if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
       incorrect destructor might then be invoked immediately.  In the
       case of YYERROR or YYBACKUP, subsequent parser actions might lead
       to an incorrect destructor call or verbose syntax error message
       before the lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

    YYPOPSTACK (yylen);
    yylen = 0;
    YY_STACK_PRINT (yyss, yyssp);

    *++yyvsp = yyval;
    *++yylsp = yyloc;

    /* Now 'shift' the result of the reduction.  Determine what state
       that goes to, based on the state we popped back to and the rule
       number reduced by.  */

    yyn = yyr1[yyn];

    yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;

    if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
        yystate = yytable[yystate];
    else
        yystate = yydefgoto[yyn - YYNTOKENS];

    goto yynewstate;


    /*--------------------------------------.
    | yyerrlab -- here on detecting error.  |
    `--------------------------------------*/
yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus)
    {
        ++yynerrs;
#if ! YYERROR_VERBOSE
        yyerror (&yylloc, result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
        {
            char const *yymsgp = YY_("syntax error");
            int yysyntax_error_status;
            yysyntax_error_status = YYSYNTAX_ERROR;

            if (yysyntax_error_status == 0)
                yymsgp = yymsg;
            else if (yysyntax_error_status == 1)
            {
                if (yymsg != yymsgbuf)
                    YYSTACK_FREE (yymsg);

                yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);

                if (!yymsg)
                {
                    yymsg = yymsgbuf;
                    yymsg_alloc = sizeof yymsgbuf;
                    yysyntax_error_status = 2;
                }
                else
                {
                    yysyntax_error_status = YYSYNTAX_ERROR;
                    yymsgp = yymsg;
                }
            }

            yyerror (&yylloc, result, scanner, yymsgp);

            if (yysyntax_error_status == 2)
                goto yyexhaustedlab;
        }
# undef YYSYNTAX_ERROR
#endif
    }

    yyerror_range[1] = yylloc;

    if (yyerrstatus == 3)
    {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        if (yychar <= YYEOF)
        {
            /* Return failure if at end of input.  */
            if (yychar == YYEOF)
                YYABORT;
        }
        else
        {
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc, result, scanner);
            yychar = YYEMPTY;
        }
    }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


    /*---------------------------------------------------.
    | yyerrorlab -- error raised explicitly by YYERROR.  |
    `---------------------------------------------------*/
yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (/*CONSTCOND*/ 0)
        goto yyerrorlab;

    yyerror_range[1] = yylsp[1 - yylen];
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    YYPOPSTACK (yylen);
    yylen = 0;
    YY_STACK_PRINT (yyss, yyssp);
    yystate = *yyssp;
    goto yyerrlab1;


    /*-------------------------------------------------------------.
    | yyerrlab1 -- common code for both syntax error and YYERROR.  |
    `-------------------------------------------------------------*/
yyerrlab1:
    yyerrstatus = 3;      /* Each real token shifted decrements this.  */

    for (;;)
    {
        yyn = yypact[yystate];

        if (!yypact_value_is_default (yyn))
        {
            yyn += YYTERROR;

            if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
                yyn = yytable[yyn];

                if (0 < yyn)
                    break;
            }
        }

        /* Pop the current state because it cannot handle the error token.  */
        if (yyssp == yyss)
            YYABORT;

        yyerror_range[1] = *yylsp;
        yydestruct ("Error: popping",
                    yystos[yystate], yyvsp, yylsp, result, scanner);
        YYPOPSTACK (1);
        yystate = *yyssp;
        YY_STACK_PRINT (yyss, yyssp);
    }

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    *++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END

    yyerror_range[2] = yylloc;
    /* Using YYLLOC is tempting, but would change the location of
       the lookahead.  YYLOC is available though.  */
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    *++yylsp = yyloc;

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

    yystate = yyn;
    goto yynewstate;


    /*-------------------------------------.
    | yyacceptlab -- YYACCEPT comes here.  |
    `-------------------------------------*/
yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /*-----------------------------------.
    | yyabortlab -- YYABORT comes here.  |
    `-----------------------------------*/
yyabortlab:
    yyresult = 1;
    goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
    /*-------------------------------------------------.
    | yyexhaustedlab -- memory exhaustion comes here.  |
    `-------------------------------------------------*/
yyexhaustedlab:
    yyerror (&yylloc, result, scanner, YY_("memory exhausted"));
    yyresult = 2;
    /* Fall through.  */
#endif

yyreturn:

    if (yychar != YYEMPTY)
    {
        /* Make sure we have latest lookahead translation.  See comments at
           user semantic actions for why this is necessary.  */
        yytoken = YYTRANSLATE (yychar);
        yydestruct ("Cleanup: discarding lookahead",
                    yytoken, &yylval, &yylloc, result, scanner);
    }

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    YYPOPSTACK (yylen);
    YY_STACK_PRINT (yyss, yyssp);

    while (yyssp != yyss)
    {
        yydestruct ("Cleanup: popping",
                    yystos[*yyssp], yyvsp, yylsp, result, scanner);
        YYPOPSTACK (1);
    }

#ifndef yyoverflow

    if (yyss != yyssa)
        YYSTACK_FREE (yyss);

#endif
#if YYERROR_VERBOSE

    if (yymsg != yymsgbuf)
        YYSTACK_FREE (yymsg);

#endif
    return yyresult;
}
#line 857 "bison_parser.y" /* yacc.c:1906  */

/*********************************
 ** Section 4: Additional C code
 *********************************/

/* empty */

