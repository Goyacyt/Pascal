/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./syntax.y"

    #define YYDEBUG 1
    #include"tree.h"
    #include"lex.yy.c"
    int yylex(void);
    void yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    extern int bisonsim;
    extern node* root;
    extern int haserror;
    extern int error_line;
    extern int errorsim;

#line 86 "./syntax.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntax.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_SEMI = 6,                       /* SEMI  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_ASSIGNOP = 8,                   /* ASSIGNOP  */
  YYSYMBOL_RELOP = 9,                      /* RELOP  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_MINUS = 11,                     /* MINUS  */
  YYSYMBOL_STAR = 12,                      /* STAR  */
  YYSYMBOL_DIV = 13,                       /* DIV  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_DOT = 16,                       /* DOT  */
  YYSYMBOL_NOT = 17,                       /* NOT  */
  YYSYMBOL_TYPE = 18,                      /* TYPE  */
  YYSYMBOL_LP = 19,                        /* LP  */
  YYSYMBOL_RP = 20,                        /* RP  */
  YYSYMBOL_LB = 21,                        /* LB  */
  YYSYMBOL_RB = 22,                        /* RB  */
  YYSYMBOL_LC = 23,                        /* LC  */
  YYSYMBOL_RC = 24,                        /* RC  */
  YYSYMBOL_STRUCT = 25,                    /* STRUCT  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_IF = 27,                        /* IF  */
  YYSYMBOL_ELSE = 28,                      /* ELSE  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_NEG = 30,                       /* NEG  */
  YYSYMBOL_LOWER_THAN_ELSE = 31,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_righterror = 32,                /* righterror  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_Program = 34,                   /* Program  */
  YYSYMBOL_ExtDefList = 35,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 36,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 37,                /* ExtDecList  */
  YYSYMBOL_Specifier = 38,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 39,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 40,                    /* OptTag  */
  YYSYMBOL_Tag = 41,                       /* Tag  */
  YYSYMBOL_VarDec = 42,                    /* VarDec  */
  YYSYMBOL_FunDec = 43,                    /* FunDec  */
  YYSYMBOL_VarList = 44,                   /* VarList  */
  YYSYMBOL_ParamDec = 45,                  /* ParamDec  */
  YYSYMBOL_CompSt = 46,                    /* CompSt  */
  YYSYMBOL_StmtList = 47,                  /* StmtList  */
  YYSYMBOL_Stmt = 48,                      /* Stmt  */
  YYSYMBOL_DefList = 49,                   /* DefList  */
  YYSYMBOL_Def = 50,                       /* Def  */
  YYSYMBOL_DecList = 51,                   /* DecList  */
  YYSYMBOL_Dec = 52,                       /* Dec  */
  YYSYMBOL_Exp = 53,                       /* Exp  */
  YYSYMBOL_Args = 54                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   324

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    49,    49,    55,    57,    59,    61,    63,    65,    67,
      68,    69,    70,    71,    73,    75,    80,    82,    85,    87,
      91,    93,    95,   100,   102,   106,   108,   112,   114,   117,
     122,   126,   128,   130,   132,   134,   136,   138,   140,   151,
     152,   156,   158,   160,   162,   163,   164,   166,   168,   171,
     173,   178,   180,   182,   184,   186,   188,   190,   192,   194,
     196,   198,   200,   202,   204,   206,   208,   210,   212,   214,
     215,   216,   217,   218,   222,   224
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "SEMI", "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV",
  "AND", "OR", "DOT", "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC",
  "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "NEG", "LOWER_THAN_ELSE",
  "righterror", "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList",
  "Specifier", "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec",
  "VarList", "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def",
  "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-42)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      42,   119,   -42,    18,    24,   -42,    42,   134,   -42,   -42,
      10,   -42,   -42,    15,    33,   -42,   -42,   -42,    -1,    44,
     -42,    60,     9,    64,    43,   109,    54,    10,    71,   -42,
     -42,   299,   -42,    77,    85,   -42,   -42,   -42,    91,   -42,
      -4,    63,    92,    89,   -42,   -42,    83,   163,   180,   185,
     189,    88,    90,   -42,    97,    54,   201,   -42,    98,   -42,
      77,   104,   121,   -42,   112,   -42,   189,   -42,   -42,    77,
     -42,   -42,   158,   -42,    58,   -42,    58,   123,   137,   215,
     189,   189,   -42,   -42,   -42,   189,   189,   189,   189,   189,
     189,   189,   189,   149,   189,   -42,   135,   -42,    -6,   -42,
     287,   -42,   140,   -42,   230,   145,   -42,   -42,   -42,   -42,
     259,   273,   287,   120,   302,   302,    58,    58,   300,   300,
     -42,   244,   -42,   -42,   189,   -42,   100,   100,   -42,   -42,
     127,   -42,   100,   -42
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,    21,     0,     2,     0,     0,    17,     9,
       0,    10,    11,    22,     0,    19,     1,     3,     0,    23,
       6,     0,    14,     0,     0,     0,     0,     0,     0,    12,
      13,     0,     5,     0,     0,     8,     7,    45,     0,    23,
      49,     0,    47,     0,    67,    68,    66,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,    41,     0,    26,
       0,     0,    28,    15,     0,    44,     0,    46,    43,     0,
      40,    39,     0,    71,    60,    72,    61,     0,     0,     0,
       0,     0,    30,    31,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,    29,    25,     0,    24,
      50,    48,     0,    63,    75,     0,    69,    70,    59,    35,
       0,     0,    51,    54,    55,    56,    57,    58,    52,    53,
      65,     0,    27,    73,     0,    62,     0,     0,    64,    74,
      36,    38,     0,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -42,   -42,   164,   170,   139,     0,   -42,   -42,   -42,    -7,
     -42,    75,   -42,     2,   124,   -41,    48,   152,   118,   -42,
     -40,    74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    21,    25,     8,    14,    15,    22,
      23,    61,    62,    53,    54,    55,    26,    27,    41,    42,
      56,   105
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,     7,    71,    12,    66,    29,     7,    74,    76,    78,
      79,    24,     2,   -42,   -42,   -42,    33,    34,    40,     3,
      30,   -42,    10,    13,    16,    36,   100,   -42,     2,   -42,
      34,    60,   104,   -42,   -42,     3,   -42,   -42,   -20,   -42,
     110,   111,    -4,     1,    24,   112,   113,   114,   115,   116,
     117,   118,   119,    96,   121,    43,    28,    44,    45,    46,
       2,     2,    40,    31,    67,    47,    32,     3,     3,    68,
      35,    48,    24,    49,    93,    57,    58,    10,   -32,    94,
      50,    51,    39,    52,   104,   130,   131,    10,    64,     2,
      43,   133,    44,    45,    46,   -42,     3,    65,    60,    69,
      47,    43,    72,    44,    45,    46,    48,    80,    49,    81,
      38,    47,    10,    70,    39,    50,    51,    48,    52,    49,
       1,    82,    95,    10,    97,     9,    50,    51,    98,    52,
      87,    88,    89,    90,    99,    18,    93,     2,   107,    19,
      20,    94,    10,   106,     3,    85,    86,    87,    88,    89,
      90,    91,    92,    93,   120,   132,    34,   108,    94,   102,
     123,    44,    45,    46,    73,   125,    44,    45,    46,    47,
      17,    11,    63,   122,    47,    48,    37,    49,   103,    83,
      48,    75,    49,    44,    45,    46,    77,   101,    44,    45,
      46,    47,    44,    45,    46,     0,    47,    48,   129,    49,
      47,     0,    48,     0,    49,     0,    48,    84,    49,    85,
      86,    87,    88,    89,    90,    91,    92,    93,     0,     0,
       0,   109,    94,    85,    86,    87,    88,    89,    90,    91,
      92,    93,     0,     0,     0,     0,    94,   124,    85,    86,
      87,    88,    89,    90,    91,    92,    93,     0,     0,     0,
       0,    94,    85,    86,    87,    88,    89,    90,    91,    92,
      93,     0,     0,     0,     0,    94,   128,    85,    86,    87,
      88,    89,    90,    91,    92,    93,     0,     0,     0,   126,
      94,    85,    86,    87,    88,    89,    90,    91,    92,    93,
       0,     0,     0,   127,    94,    85,    86,    87,    88,    89,
      90,    91,    92,    93,     0,     0,     0,     0,    94,    86,
      87,    88,    89,    90,    89,    90,    93,     2,    93,    59,
       0,    94,     0,    94,     3
};

static const yytype_int16 yycheck[] =
{
       0,     1,    43,     1,     8,     6,     6,    47,    48,    49,
      50,     1,    18,     3,     4,     5,     7,    21,    25,    25,
      18,    11,    23,     5,     0,    23,    66,    17,    18,    19,
      21,    31,    72,    23,    24,    25,    26,    27,    23,    29,
      80,    81,     0,     1,     1,    85,    86,    87,    88,    89,
      90,    91,    92,    60,    94,     1,    23,     3,     4,     5,
      18,    18,    69,    19,     1,    11,     6,    25,    25,     6,
       6,    17,     1,    19,    16,    27,    28,    23,    24,    21,
      26,    27,     5,    29,   124,   126,   127,    23,     3,    18,
       1,   132,     3,     4,     5,    24,    25,     6,    98,     7,
      11,     1,    19,     3,     4,     5,    17,    19,    19,    19,
       1,    11,    23,    24,     5,    26,    27,    17,    29,    19,
       1,    24,    24,    23,    20,     6,    26,    27,     7,    29,
      10,    11,    12,    13,    22,     1,    16,    18,     1,     5,
       6,    21,    23,    20,    25,     8,     9,    10,    11,    12,
      13,    14,    15,    16,     5,    28,    21,    20,    21,     1,
      20,     3,     4,     5,     1,    20,     3,     4,     5,    11,
       6,     1,    33,    98,    11,    17,    24,    19,    20,    55,
      17,     1,    19,     3,     4,     5,     1,    69,     3,     4,
       5,    11,     3,     4,     5,    -1,    11,    17,   124,    19,
      11,    -1,    17,    -1,    19,    -1,    17,     6,    19,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,     6,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    21,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    21,    22,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    20,
      21,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    20,    21,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,     9,
      10,    11,    12,    13,    12,    13,    16,    18,    16,    20,
      -1,    21,    -1,    21,    25
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    18,    25,    34,    35,    36,    38,    39,     6,
      23,    36,    46,     5,    40,    41,     0,    35,     1,     5,
       6,    37,    42,    43,     1,    38,    49,    50,    23,     6,
      46,    19,     6,     7,    21,     6,    46,    50,     1,     5,
      42,    51,    52,     1,     3,     4,     5,    11,    17,    19,
      26,    27,    29,    46,    47,    48,    53,    49,    49,    20,
      38,    44,    45,    37,     3,     6,     8,     1,     6,     7,
      24,    48,    19,     1,    53,     1,    53,     1,    53,    53,
      19,    19,    24,    47,     6,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    21,    24,    42,    20,     7,    22,
      53,    51,     1,    20,    53,    54,    20,     1,    20,     6,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
       5,    53,    44,    20,     7,    20,    20,    20,    22,    54,
      48,    48,    28,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    37,    37,    38,    38,    39,    39,
      40,    40,    41,    42,    42,    43,    43,    44,    44,    45,
      46,    47,    47,    48,    48,    48,    48,    48,    48,    48,
      48,    49,    49,    50,    50,    50,    50,    51,    51,    52,
      52,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       2,     2,     3,     3,     1,     3,     1,     1,     5,     2,
       1,     0,     1,     1,     4,     4,     3,     3,     1,     2,
       4,     2,     0,     2,     1,     3,     5,     7,     5,     2,
       2,     2,     0,     3,     3,     2,     3,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     4,     3,     1,     1,     1,     3,
       3,     2,     2,     4,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 49 "./syntax.y"
                    {
    if(!bisonsim)  {printf(YELLOW"     Program:ExtDefList (%d)\n"NONE,(yyloc).first_line);}
    yyval=add_nonterminal("Program", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);
    root=yyval;
}
#line 1370 "./syntax.tab.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 55 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     ExtDefList:ExtDef ExtDefList (%d)\n"NONE,(yyloc).first_line);}  
        yyval=add_nonterminal("ExtDefList", (yyloc).first_line, NOTTOKEN,2,yyvsp[-1],yyvsp[0]);}
#line 1377 "./syntax.tab.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 57 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     ExtDefList:empty (%d)\n"NONE,(yyloc).first_line);}   yyval=NULL;}
#line 1383 "./syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 59 "./syntax.y"
                                    {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier ExtDecList SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDef", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1390 "./syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 61 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDef", (yyloc).first_line, NOTTOKEN,2,yyvsp[-1],yyvsp[0]);}
#line 1397 "./syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 63 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier FunDec CompSt (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDef", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1404 "./syntax.tab.c"
    break;

  case 8: /* ExtDef: Specifier FunDec SEMI  */
#line 65 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier FunDec SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDef", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1411 "./syntax.tab.c"
    break;

  case 9: /* ExtDef: error SEMI  */
#line 67 "./syntax.y"
                 {if (!errorsim) {printf("Wrong ExtDef:error SEMI\n");}yyerrok;}
#line 1417 "./syntax.tab.c"
    break;

  case 10: /* ExtDef: error ExtDef  */
#line 68 "./syntax.y"
                    {if (!errorsim) {printf("Wrong ExtDef: error ExtDef\n");}yyerrok;}
#line 1423 "./syntax.tab.c"
    break;

  case 11: /* ExtDef: error CompSt  */
#line 69 "./syntax.y"
                     {if (!errorsim) {printf("Wrong ExtDef: error CompSt \n");}yyerrok;}
#line 1429 "./syntax.tab.c"
    break;

  case 12: /* ExtDef: Specifier error SEMI  */
#line 70 "./syntax.y"
                            {if (!errorsim) {printf("Wrong ExtDef: Specifier error SEMI\n");}yyerrok;}
#line 1435 "./syntax.tab.c"
    break;

  case 13: /* ExtDef: Specifier error CompSt  */
#line 71 "./syntax.y"
                              {if (!errorsim) {printf("Wrong ExtDef: Specifier error CompSt\n");}yyerrok;}
#line 1441 "./syntax.tab.c"
    break;

  case 14: /* ExtDecList: VarDec  */
#line 73 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     ExtDecList:VarDec (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDecList", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1448 "./syntax.tab.c"
    break;

  case 15: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 75 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     ExtDecList:VarDec COMMA ExtDecList (%d)\n"NONE,(yyloc).first_line);}
         yyval=add_nonterminal("ExtDefList", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1455 "./syntax.tab.c"
    break;

  case 16: /* Specifier: TYPE  */
#line 80 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Specifier:TYPE (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Specifier", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1462 "./syntax.tab.c"
    break;

  case 17: /* Specifier: StructSpecifier  */
#line 82 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Specifier:StructSpecifier (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Specifier", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1469 "./syntax.tab.c"
    break;

  case 18: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 85 "./syntax.y"
                                                {if(!bisonsim)  {printf(YELLOW"     StructSpecifier:STRUCT OptTag LC DefList RC (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("StructSpecifier", (yyloc).first_line, NOTTOKEN, 5,yyvsp[-4],yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1476 "./syntax.tab.c"
    break;

  case 19: /* StructSpecifier: STRUCT Tag  */
#line 87 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     StructSpecifier:STRUCT Tag (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("StructSpecifier", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1483 "./syntax.tab.c"
    break;

  case 20: /* OptTag: ID  */
#line 91 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     OptTag:ID (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("OptTag", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1490 "./syntax.tab.c"
    break;

  case 21: /* OptTag: %empty  */
#line 93 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     OptTag:empty (%d)\n"NONE,(yyloc).first_line);} yyval=NULL;}
#line 1496 "./syntax.tab.c"
    break;

  case 22: /* Tag: ID  */
#line 95 "./syntax.y"
        {if(!bisonsim)  {printf(YELLOW"     Tag:ID (%d)\n"NONE,(yyloc).first_line);}
    yyval=add_nonterminal("Tag", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1503 "./syntax.tab.c"
    break;

  case 23: /* VarDec: ID  */
#line 100 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     VarDec:ID (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("VarDec", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1510 "./syntax.tab.c"
    break;

  case 24: /* VarDec: VarDec LB INT RB  */
#line 102 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     VarDec:VarDec LB INT RB (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("VarDec", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1517 "./syntax.tab.c"
    break;

  case 25: /* FunDec: ID LP VarList RP  */
#line 106 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     FunDec:ID LP VarList RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("FunDec", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1524 "./syntax.tab.c"
    break;

  case 26: /* FunDec: ID LP RP  */
#line 108 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     FunDec:ID LP RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("FunDec", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1531 "./syntax.tab.c"
    break;

  case 27: /* VarList: ParamDec COMMA VarList  */
#line 112 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     VarList:ParamDec COMMA VarList (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("VarList", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1538 "./syntax.tab.c"
    break;

  case 28: /* VarList: ParamDec  */
#line 114 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     VarList:ParamDec (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("VarList", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1545 "./syntax.tab.c"
    break;

  case 29: /* ParamDec: Specifier VarDec  */
#line 117 "./syntax.y"
                           {if(!bisonsim)  {printf(YELLOW"     ParamDec:Specifier VarDec (%d)\n"NONE,(yyloc).first_line);}
    yyval=add_nonterminal("ParamDec", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1552 "./syntax.tab.c"
    break;

  case 30: /* CompSt: LC DefList StmtList RC  */
#line 122 "./syntax.y"
                                        {if(!bisonsim)  {printf(YELLOW"     CompSt:LC DefList StmtList RC (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("CompSt", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1559 "./syntax.tab.c"
    break;

  case 31: /* StmtList: Stmt StmtList  */
#line 126 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     StmtList:Stmt StmtList (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("StmtList", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1566 "./syntax.tab.c"
    break;

  case 32: /* StmtList: %empty  */
#line 128 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     StmtList:empty (%d)\n"NONE,(yyloc).first_line);}    yyval=NULL;}
#line 1572 "./syntax.tab.c"
    break;

  case 33: /* Stmt: Exp SEMI  */
#line 130 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Stmt:Exp SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1579 "./syntax.tab.c"
    break;

  case 34: /* Stmt: CompSt  */
#line 132 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Stmt:CompSt (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1586 "./syntax.tab.c"
    break;

  case 35: /* Stmt: RETURN Exp SEMI  */
#line 134 "./syntax.y"
                         {if(!bisonsim)  {printf(YELLOW"     Stmt:RETURN Exp SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1593 "./syntax.tab.c"
    break;

  case 36: /* Stmt: IF LP Exp RP Stmt  */
#line 136 "./syntax.y"
                                              {if(!bisonsim)  {printf(YELLOW"     Stmt:IF LP Exp RP Stmt LOWER_THAN_ELSE (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 5,yyvsp[-4],yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1600 "./syntax.tab.c"
    break;

  case 37: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 138 "./syntax.y"
                                    {if(!bisonsim)  {printf(YELLOW"     Stmt:IF LP Exp RP Stmt ELSE Stmt (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 7,yyvsp[-6],yyvsp[-5],yyvsp[-4],yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1607 "./syntax.tab.c"
    break;

  case 38: /* Stmt: WHILE LP Exp RP Stmt  */
#line 140 "./syntax.y"
                                      {if(!bisonsim)  {printf(YELLOW"     Stmt:6WHILE LP Exp RP Stmt (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 5,yyvsp[-4],yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1614 "./syntax.tab.c"
    break;

  case 39: /* Stmt: error Stmt  */
#line 151 "./syntax.y"
                 {if (!errorsim) {printf("Wrong Stmt: error Stmt\n");}yyerrok;}
#line 1620 "./syntax.tab.c"
    break;

  case 40: /* Stmt: error RC  */
#line 152 "./syntax.y"
               {if (!errorsim) {printf("Wrong Stmt: error\n");}yyerrok;}
#line 1626 "./syntax.tab.c"
    break;

  case 41: /* DefList: Def DefList  */
#line 156 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     DefList:Def DefList (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("DefList", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1633 "./syntax.tab.c"
    break;

  case 42: /* DefList: %empty  */
#line 158 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     DefList:empty (%d)\n"NONE,(yyloc).first_line);} yyval=NULL;}
#line 1639 "./syntax.tab.c"
    break;

  case 43: /* Def: Specifier DecList SEMI  */
#line 160 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     Def:Specifier DecList SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Def", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1646 "./syntax.tab.c"
    break;

  case 44: /* Def: Specifier error SEMI  */
#line 162 "./syntax.y"
                          {if (!errorsim) {printf("Wrong Def:Specifier error SEMI\n");}yyerrok;}
#line 1652 "./syntax.tab.c"
    break;

  case 45: /* Def: error Def  */
#line 163 "./syntax.y"
                {if (!errorsim) {printf("Wrong Def:error Def\n");}yyerrok;}
#line 1658 "./syntax.tab.c"
    break;

  case 46: /* Def: Specifier DecList error  */
#line 164 "./syntax.y"
                                {if (!errorsim) {printf("Wrong Def:error Specifier DecList\n");}yyerrok;}
#line 1664 "./syntax.tab.c"
    break;

  case 47: /* DecList: Dec  */
#line 166 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     DecList:Dec (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("DecList", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1671 "./syntax.tab.c"
    break;

  case 48: /* DecList: Dec COMMA DecList  */
#line 168 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     DecList:Dec COMMA DecList (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("DecList", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1678 "./syntax.tab.c"
    break;

  case 49: /* Dec: VarDec  */
#line 171 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Dec:VarDec (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Dec", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1685 "./syntax.tab.c"
    break;

  case 50: /* Dec: VarDec ASSIGNOP Exp  */
#line 173 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     Dec:VarDec ASSIGNOP Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Dec", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1692 "./syntax.tab.c"
    break;

  case 51: /* Exp: Exp ASSIGNOP Exp  */
#line 178 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:Exp ASSIGNOP Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1699 "./syntax.tab.c"
    break;

  case 52: /* Exp: Exp AND Exp  */
#line 180 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:Exp AND Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1706 "./syntax.tab.c"
    break;

  case 53: /* Exp: Exp OR Exp  */
#line 182 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp OR Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1713 "./syntax.tab.c"
    break;

  case 54: /* Exp: Exp RELOP Exp  */
#line 184 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:Exp RELOP Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1720 "./syntax.tab.c"
    break;

  case 55: /* Exp: Exp PLUS Exp  */
#line 186 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp PLUS Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1727 "./syntax.tab.c"
    break;

  case 56: /* Exp: Exp MINUS Exp  */
#line 188 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp MINUS Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1734 "./syntax.tab.c"
    break;

  case 57: /* Exp: Exp STAR Exp  */
#line 190 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp STAR Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1741 "./syntax.tab.c"
    break;

  case 58: /* Exp: Exp DIV Exp  */
#line 192 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp DIV Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1748 "./syntax.tab.c"
    break;

  case 59: /* Exp: LP Exp RP  */
#line 194 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:LP Exp RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1755 "./syntax.tab.c"
    break;

  case 60: /* Exp: MINUS Exp  */
#line 196 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     Exp:MINUS Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1762 "./syntax.tab.c"
    break;

  case 61: /* Exp: NOT Exp  */
#line 198 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:NOT Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1769 "./syntax.tab.c"
    break;

  case 62: /* Exp: ID LP Args RP  */
#line 200 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:ID LP Args RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1776 "./syntax.tab.c"
    break;

  case 63: /* Exp: ID LP RP  */
#line 202 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:ID LP RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1783 "./syntax.tab.c"
    break;

  case 64: /* Exp: Exp LB Exp RB  */
#line 204 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp LB Exp RB (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1790 "./syntax.tab.c"
    break;

  case 65: /* Exp: Exp DOT ID  */
#line 206 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:Exp DOT ID (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1797 "./syntax.tab.c"
    break;

  case 66: /* Exp: ID  */
#line 208 "./syntax.y"
        {if(!bisonsim)  {printf(YELLOW"     Exp:ID (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1804 "./syntax.tab.c"
    break;

  case 67: /* Exp: INT  */
#line 210 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Exp:INT (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1811 "./syntax.tab.c"
    break;

  case 68: /* Exp: FLOAT  */
#line 212 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Exp:FLOAT (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1818 "./syntax.tab.c"
    break;

  case 69: /* Exp: LP error RP  */
#line 214 "./syntax.y"
                  {if (!errorsim) {printf("Wrong Exp:LP error RP\n");}yyerrok;}
#line 1824 "./syntax.tab.c"
    break;

  case 70: /* Exp: LP Exp error  */
#line 215 "./syntax.y"
                    {if (!errorsim) {printf("Wrong Exp:LP Exp error\n");}yyerrok;}
#line 1830 "./syntax.tab.c"
    break;

  case 71: /* Exp: MINUS error  */
#line 216 "./syntax.y"
                             {if (!errorsim) {printf("Wrong Exp:MINUS error prec NEG\n");}yyerrok;}
#line 1836 "./syntax.tab.c"
    break;

  case 72: /* Exp: NOT error  */
#line 217 "./syntax.y"
                  {if (!errorsim) {printf("Wrong Exp:NOT error \n");}yyerrok;}
#line 1842 "./syntax.tab.c"
    break;

  case 73: /* Exp: ID LP error RP  */
#line 218 "./syntax.y"
                      {if (!errorsim) {printf("Wrong Exp:ID LP error RP\n");}yyerrok;}
#line 1848 "./syntax.tab.c"
    break;

  case 74: /* Args: Exp COMMA Args  */
#line 222 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Args:Exp COMMA Args (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Args", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1855 "./syntax.tab.c"
    break;

  case 75: /* Args: Exp  */
#line 224 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Args:Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1862 "./syntax.tab.c"
    break;


#line 1866 "./syntax.tab.c"

      default: break;
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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 227 "./syntax.y"


void yyerror(const char *s) {
    if (yylineno!=error_line){
        printf ("Error type B at Line %d: in position(%d-%d), \'%s\' %s \n", yylineno,yylloc.first_column,yylloc.last_column,yytext,s);
        error_line=yylineno;
    }
    haserror=1;
}