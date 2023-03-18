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
    #include<stdio.h>
    #include"tree.h"
    #include"lex.yy.c"
    #define YYSTYPE node*
    int yylex(void);
    void yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    #define RED "\033[0;32;31m"
    #define NONE "\033[m"
    #define YELLOW "\033[1;33m"
    extern int bisonsim;
    extern node* root;
    extern int haserror;

#line 89 "./syntax.tab.c"

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
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_Program = 33,                   /* Program  */
  YYSYMBOL_ExtDefList = 34,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 35,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 36,                /* ExtDecList  */
  YYSYMBOL_Specifier = 37,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 38,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 39,                    /* OptTag  */
  YYSYMBOL_Tag = 40,                       /* Tag  */
  YYSYMBOL_VarDec = 41,                    /* VarDec  */
  YYSYMBOL_FunDec = 42,                    /* FunDec  */
  YYSYMBOL_VarList = 43,                   /* VarList  */
  YYSYMBOL_ParamDec = 44,                  /* ParamDec  */
  YYSYMBOL_CompSt = 45,                    /* CompSt  */
  YYSYMBOL_StmtList = 46,                  /* StmtList  */
  YYSYMBOL_Stmt = 47,                      /* Stmt  */
  YYSYMBOL_DefList = 48,                   /* DefList  */
  YYSYMBOL_Def = 49,                       /* Def  */
  YYSYMBOL_DecList = 50,                   /* DecList  */
  YYSYMBOL_Dec = 51,                       /* Dec  */
  YYSYMBOL_Exp = 52,                       /* Exp  */
  YYSYMBOL_Args = 53                       /* Args  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   255

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
<<<<<<< HEAD
       0,    53,    53,    59,    61,    63,    65,    67,    69,    71,
      73,    78,    80,    83,    85,    89,    91,    93,    98,   100,
     104,   106,   108,   110,   112,   115,   120,   122,   124,   126,
     128,   130,   132,   134,   136,   138,   140,   144,   146,   148,
     150,   152,   154,   157,   159,   164,   166,   168,   170,   172,
     174,   176,   178,   180,   182,   184,   186,   188,   190,   192,
     194,   196,   198,   202,   204
=======
<<<<<<< HEAD
<<<<<<< HEAD
       0,    56,    56,    58,    59,    61,    62,    63,    64,    66,
      67,    71,    72,    74,    75,    76,    78,    79,    81,    85,
      86,    87,    89,    90,    91,    93,    94,    96,   100,   101,
     103,   104,   106,   107,   108,   109,   110,   111,   112,   116,
     117,   119,   120,   122,   123,   125,   126,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   150,   151
=======
       0,    52,    52,    54,    55,    57,    58,    59,    60,    62,
      63,    67,    68,    70,    71,    74,    75,    77,    81,    82,
      85,    86,    87,    89,    90,    92,    96,    97,    99,   100,
     102,   103,   104,   105,   106,   107,   108,   112,   113,   115,
     116,   118,   119,   121,   122,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   146,   147
>>>>>>> 6167a60366b5123f99de96992d6be4d8a38646cd
=======
       0,    57,    57,    59,    60,    62,    63,    64,    65,    66,
      69,    70,    74,    75,    77,    78,    81,    82,    84,    88,
      89,    92,    93,    94,    97,    98,   100,   104,   108,   109,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   128,   129,   131,   132,   133,   134,   135,   136,
     137,   138,   141,   142,   145,   146,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   170,   171
>>>>>>> dev
>>>>>>> 9364a9d3b001473071d411492dc97d6c794e746e
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
  "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-39)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,     5,   -58,     2,    17,   -58,    23,   114,   -58,   -58,
      33,    35,   -58,   -58,   -58,    18,    43,   -58,    45,    -2,
      13,    15,   -58,    32,   -58,    59,    87,    81,    42,   -58,
      98,    59,    89,    42,   -58,    59,   101,   115,   -58,   -58,
     116,   -58,    69,   -58,     1,   117,   129,   -58,   -58,   130,
     -58,   -12,   -58,    31,   -58,   -58,   118,   107,   107,   107,
     107,   131,   134,   -58,   128,    69,   119,   107,   -58,    59,
     -58,   -58,    97,   232,    28,   177,   133,   107,   107,   -58,
     -58,   -58,   107,   107,   107,   107,   107,   107,   107,   107,
     160,   107,   219,   -58,   -58,   148,   146,   -58,   -58,   191,
     205,   219,   226,   232,   232,    28,    28,    66,    66,   -58,
     162,   107,   -58,    80,    80,   -58,   -58,   139,   -58,    80,
     -58
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    16,     0,     2,     0,     0,    12,     8,
      17,     0,    14,     1,     3,     0,    18,     6,     0,     9,
       0,     0,    22,     0,     5,     0,     0,     0,     0,     7,
       0,     0,     0,     0,    21,     0,     0,    24,    18,    10,
       0,    27,     0,    40,    43,     0,    41,    13,    37,    25,
      20,     0,    19,     0,    61,    62,    60,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,    39,     0,
      23,    36,     0,    54,    55,     0,     0,     0,     0,    26,
      28,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,    42,    57,    64,     0,    53,    32,     0,
       0,    45,    48,    49,    50,    51,    52,    46,    47,    59,
       0,     0,    56,     0,     0,    58,    63,    33,    35,     0,
      34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -58,   -58,   173,   -58,   143,    12,   -58,   -58,   -58,   -27,
     -58,   144,   -58,   161,   145,   136,    61,   -58,   111,   -58,
     -57,    71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    18,    31,     8,    11,    12,    19,
      20,    36,    37,    63,    64,    65,    32,    33,    45,    46,
      66,    96
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      73,    74,    75,    76,    44,    25,     2,    10,    49,    67,
      92,     9,     7,     3,    27,    95,    30,    13,     7,    26,
      99,   100,    26,    -4,     1,   101,   102,   103,   104,   105,
     106,   107,   108,     2,   110,    35,    28,    71,    22,   -38,
       3,     2,    44,    30,    90,   -38,   -38,   -38,     3,    91,
       2,    24,    34,   -38,    95,    41,   -15,     3,    21,   -38,
       2,   -38,    23,    35,    38,   -38,   -38,     3,   -38,   -38,
      53,   -38,    54,    55,    56,    83,    84,    85,    86,    87,
      57,    53,    90,    54,    55,    56,    58,    91,    59,    42,
      40,    57,    28,   -29,    48,    60,    61,    58,    62,    59,
      54,    55,    56,    28,    43,    41,    60,    61,    57,    62,
      54,    55,    56,    47,    58,    15,    59,    94,    57,    16,
      17,    50,    51,    68,    58,    81,    59,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    69,    72,    52,    98,
      91,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      77,    26,    79,    78,    91,   111,    82,    83,    84,    85,
      86,    87,    88,    89,    90,   109,   112,   119,    39,    91,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    14,
      93,    29,   116,    91,   115,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     0,    70,     0,    97,    91,    82,
      83,    84,    85,    86,    87,    88,    89,    90,     0,     0,
      80,   113,    91,    82,    83,    84,    85,    86,    87,    88,
      89,    90,     0,     0,     0,   114,    91,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    84,    85,    86,    87,
      91,     0,    90,     0,    86,    87,     0,    91,    90,   117,
     118,     0,     0,    91,     0,   120
};

static const yytype_int8 yycheck[] =
{
      57,    58,    59,    60,    31,     7,    18,     5,    35,     8,
      67,     6,     0,    25,     1,    72,     1,     0,     6,    21,
      77,    78,    21,     0,     1,    82,    83,    84,    85,    86,
      87,    88,    89,    18,    91,    23,    23,     6,    20,    24,
      25,    18,    69,     1,    16,     3,     4,     5,    25,    21,
      18,     6,    20,    11,   111,    24,    23,    25,    23,    17,
      18,    19,    19,    51,     5,    23,    24,    25,    26,    27,
       1,    29,     3,     4,     5,     9,    10,    11,    12,    13,
      11,     1,    16,     3,     4,     5,    17,    21,    19,    28,
       3,    11,    23,    24,    33,    26,    27,    17,    29,    19,
       3,     4,     5,    23,     6,    24,    26,    27,    11,    29,
       3,     4,     5,    24,    17,     1,    19,    20,    11,     5,
       6,    20,     7,     6,    17,     6,    19,     8,     9,    10,
      11,    12,    13,    14,    15,    16,     7,    19,    22,     6,
      21,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      19,    21,    24,    19,    21,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     5,    20,    28,    25,    21,
       8,     9,    10,    11,    12,    13,    14,    15,    16,     6,
      69,    20,   111,    21,    22,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    51,    -1,    20,    21,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      65,    20,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    20,    21,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    10,    11,    12,    13,
      21,    -1,    16,    -1,    12,    13,    -1,    21,    16,   113,
     114,    -1,    -1,    21,    -1,   119
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    18,    25,    33,    34,    35,    37,    38,     6,
       5,    39,    40,     0,    34,     1,     5,     6,    36,    41,
      42,    23,    20,    19,     6,     7,    21,     1,    23,    45,
       1,    37,    48,    49,    20,    37,    43,    44,     5,    36,
       3,    24,    48,     6,    41,    50,    51,    24,    48,    41,
      20,     7,    22,     1,     3,     4,     5,    11,    17,    19,
      26,    27,    29,    45,    46,    47,    52,     8,     6,     7,
      43,     6,    19,    52,    52,    52,    52,    19,    19,    24,
      46,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    21,    52,    50,    20,    52,    53,    20,     6,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,     5,
      52,     7,    20,    20,    20,    22,    53,    47,    47,    28,
      47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    36,
      36,    37,    37,    38,    38,    39,    39,    40,    41,    41,
      42,    42,    42,    43,    43,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    47,    47,    47,    48,    48,    49,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    53,    53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     1,     4,
       4,     3,     2,     3,     1,     2,     4,     2,     2,     0,
       2,     1,     3,     5,     7,     5,     2,     2,     0,     3,
       2,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     3,     1
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
<<<<<<< HEAD
#line 53 "./syntax.y"
                    {
    if(!bisonsim)  {printf(YELLOW"     Program:ExtDefList (%d)\n"NONE,(yyloc).first_line);}
    yyval=add_nonterminal("Program", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);
    root=yyval;
}
#line 1352 "./syntax.tab.c"
=======
<<<<<<< HEAD
<<<<<<< HEAD
#line 56 "./syntax.y"
=======
#line 57 "./syntax.y"
>>>>>>> dev
                    {if(!bisonsim)  {printf(YELLOW"     Program:1\n"NONE);}}
#line 1359 "./syntax.tab.c"
>>>>>>> 9364a9d3b001473071d411492dc97d6c794e746e
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 59 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     ExtDefList:ExtDef ExtDefList (%d)\n"NONE,(yyloc).first_line);}  
        yyval=add_nonterminal("ExtDefList", (yyloc).first_line, NOTTOKEN,2,yyvsp[-1],yyvsp[0]);}
#line 1359 "./syntax.tab.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 61 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     ExtDefList:empty (%d)\n"NONE,(yyloc).first_line);}   yyval=NULL;}
#line 1365 "./syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 63 "./syntax.y"
                                    {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier ExtDecList SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDef", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1372 "./syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 65 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDef", (yyloc).first_line, NOTTOKEN,2,yyvsp[-1],yyvsp[0]);}
#line 1379 "./syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 67 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     ExtDef:Specifier FunDec CompSt (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDeft", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1386 "./syntax.tab.c"
    break;

  case 8: /* ExtDef: error SEMI  */
#line 69 "./syntax.y"
                 {printf("Wrong ExtDef\n");yyerrok;}
#line 1392 "./syntax.tab.c"
    break;

  case 9: /* ExtDecList: VarDec  */
#line 71 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     ExtDecList:VarDec (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("ExtDecList", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1399 "./syntax.tab.c"
    break;

  case 10: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 73 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     ExtDecList:VarDec COMMA ExtDecList (%d)\n"NONE,(yyloc).first_line);}
         yyval=add_nonterminal("ExtDefList", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1406 "./syntax.tab.c"
    break;

  case 11: /* Specifier: TYPE  */
#line 78 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Specifier:TYPE (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Specifier", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1413 "./syntax.tab.c"
    break;

  case 12: /* Specifier: StructSpecifier  */
#line 80 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Specifier:StructSpecifier (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Specifier", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1420 "./syntax.tab.c"
    break;

  case 13: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 83 "./syntax.y"
                                                {if(!bisonsim)  {printf(YELLOW"     StructSpecifier:STRUCT OptTag LC DefList RC (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("StructSpecifier", (yyloc).first_line, NOTTOKEN, 5,yyvsp[-4],yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1427 "./syntax.tab.c"
    break;

  case 14: /* StructSpecifier: STRUCT Tag  */
#line 85 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     StructSpecifier:STRUCT Tag (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("StructSpecifier", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1434 "./syntax.tab.c"
    break;

  case 15: /* OptTag: ID  */
#line 89 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     OptTag:ID (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("OptTag", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1441 "./syntax.tab.c"
    break;

  case 16: /* OptTag: %empty  */
#line 91 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     OptTag:empty (%d)\n"NONE,(yyloc).first_line);} yyval=NULL;}
#line 1447 "./syntax.tab.c"
    break;

  case 17: /* Tag: ID  */
#line 93 "./syntax.y"
        {if(!bisonsim)  {printf(YELLOW"     Tag:ID (%d)\n"NONE,(yyloc).first_line);}
    yyval=add_nonterminal("Tag", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1454 "./syntax.tab.c"
    break;

  case 18: /* VarDec: ID  */
#line 98 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     VarDec:ID (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("VarDec", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1461 "./syntax.tab.c"
    break;

<<<<<<< HEAD
  case 19: /* VarDec: VarDec LB INT RB  */
=======
  case 20: /* VarDec: VarDec LB INT RB  */
#line 89 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     VarDec:2\n"NONE);}}
#line 1467 "./syntax.tab.c"
    break;

<<<<<<< HEAD
  case 21: /* VarDec: error RB  */
#line 87 "./syntax.y"
               {printf("Wrong VarDec\n");yyerrok;}
#line 1462 "./syntax.tab.c"
    break;

  case 22: /* FunDec: ID LP VarList RP  */
#line 89 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     FunDec:1\n"NONE);}}
#line 1468 "./syntax.tab.c"
    break;

  case 23: /* FunDec: ID LP RP  */
#line 90 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     FunDec:2\n"NONE);}}
#line 1474 "./syntax.tab.c"
    break;

  case 24: /* FunDec: error RP  */
#line 91 "./syntax.y"
               {printf("Wrong FunDec\n");yyerrok;}
#line 1480 "./syntax.tab.c"
    break;

  case 25: /* VarList: ParamDec COMMA VarList  */
#line 93 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     VarList:1\n"NONE);}}
#line 1486 "./syntax.tab.c"
    break;

  case 26: /* VarList: ParamDec  */
#line 94 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     VarList:2\n"NONE);}}
#line 1492 "./syntax.tab.c"
    break;

  case 27: /* ParamDec: Specifier VarDec  */
#line 96 "./syntax.y"
                           {if(!bisonsim)  {printf(YELLOW"     ParamDec:1\n"NONE);}}
#line 1498 "./syntax.tab.c"
    break;

  case 28: /* CompSt: LC DefList StmtList RC  */
#line 100 "./syntax.y"
                                        {if(!bisonsim)  {printf(YELLOW"     CompSt:1\n"NONE);}}
#line 1504 "./syntax.tab.c"
    break;

  case 29: /* CompSt: error RC  */
#line 101 "./syntax.y"
                {printf("Wrong ComSt\n");yyerrok;}
#line 1510 "./syntax.tab.c"
    break;

  case 30: /* StmtList: Stmt StmtList  */
#line 103 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     StmtList:1\n"NONE);}}
#line 1516 "./syntax.tab.c"
    break;

  case 31: /* StmtList: %empty  */
#line 104 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     StmtList:2\n"NONE);}}
#line 1522 "./syntax.tab.c"
    break;

  case 32: /* Stmt: Exp SEMI  */
#line 106 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Stmt:1\n"NONE);}}
#line 1528 "./syntax.tab.c"
    break;

  case 33: /* Stmt: CompSt  */
#line 107 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Stmt:2\n"NONE);}}
#line 1534 "./syntax.tab.c"
    break;

  case 34: /* Stmt: RETURN Exp SEMI  */
#line 108 "./syntax.y"
                         {if(!bisonsim)  {printf(YELLOW"     Stmt:3"NONE);}}
#line 1540 "./syntax.tab.c"
    break;

  case 35: /* Stmt: IF LP Exp RP Stmt  */
#line 109 "./syntax.y"
                                              {if(!bisonsim)  {printf(YELLOW"     Stmt:4\n"NONE);}}
#line 1546 "./syntax.tab.c"
    break;

  case 36: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 110 "./syntax.y"
                                    {if(!bisonsim)  {printf(YELLOW"     Stmt:5\n"NONE);}}
#line 1552 "./syntax.tab.c"
    break;

  case 37: /* Stmt: WHILE LP Exp RP Stmt  */
#line 111 "./syntax.y"
                                      {if(!bisonsim)  {printf(YELLOW"     Stmt:6\n"NONE);}}
#line 1558 "./syntax.tab.c"
    break;

  case 38: /* Stmt: error SEMI  */
#line 112 "./syntax.y"
                    {printf("Wrong Stmt\n");yyerrok;}
#line 1564 "./syntax.tab.c"
    break;

  case 39: /* DefList: Def DefList  */
#line 116 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     DefList:1\n"NONE);}}
#line 1570 "./syntax.tab.c"
    break;

  case 40: /* DefList: %empty  */
#line 117 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     DefList:2\n"NONE);}}
#line 1576 "./syntax.tab.c"
    break;

  case 41: /* Def: Specifier DecList SEMI  */
#line 119 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     Def:1\n"NONE);}}
#line 1582 "./syntax.tab.c"
    break;

  case 42: /* Def: error SEMI  */
#line 120 "./syntax.y"
                {printf("Wrong Def:semi exist\n");yyerrok;}
#line 1588 "./syntax.tab.c"
    break;

  case 43: /* DecList: Dec  */
#line 122 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     DecList:1\n"NONE);}}
#line 1594 "./syntax.tab.c"
    break;

  case 44: /* DecList: Dec COMMA DecList  */
#line 123 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     DecList:2\n"NONE);}}
#line 1600 "./syntax.tab.c"
    break;

  case 45: /* Dec: VarDec  */
#line 125 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Dec:1\n"NONE);}}
#line 1606 "./syntax.tab.c"
    break;

  case 46: /* Dec: VarDec ASSIGNOP Exp  */
#line 126 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     Dec:2\n"NONE);}}
#line 1612 "./syntax.tab.c"
    break;

  case 47: /* Exp: Exp ASSIGNOP Exp  */
#line 130 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:1\n"NONE);}}
#line 1618 "./syntax.tab.c"
    break;

  case 48: /* Exp: Exp AND Exp  */
#line 131 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:2\n"NONE);}}
#line 1624 "./syntax.tab.c"
    break;

  case 49: /* Exp: Exp OR Exp  */
#line 132 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:3\n"NONE);}}
#line 1630 "./syntax.tab.c"
    break;

  case 50: /* Exp: Exp RELOP Exp  */
#line 133 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:4\n"NONE);}}
#line 1636 "./syntax.tab.c"
    break;

  case 51: /* Exp: Exp PLUS Exp  */
#line 134 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:5\n"NONE);}}
#line 1642 "./syntax.tab.c"
    break;

  case 52: /* Exp: Exp MINUS Exp  */
#line 135 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:6\n"NONE);}}
#line 1648 "./syntax.tab.c"
    break;

  case 53: /* Exp: Exp STAR Exp  */
#line 136 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:7\n"NONE);}}
#line 1654 "./syntax.tab.c"
    break;

  case 54: /* Exp: Exp DIV Exp  */
#line 137 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:8\n"NONE);}}
#line 1660 "./syntax.tab.c"
    break;

  case 55: /* Exp: LP Exp RP  */
#line 138 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:9\n"NONE);}}
#line 1666 "./syntax.tab.c"
    break;

  case 56: /* Exp: MINUS Exp  */
#line 139 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:10\n"NONE);}}
#line 1672 "./syntax.tab.c"
    break;

  case 57: /* Exp: NOT Exp  */
#line 140 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:11\n"NONE);}}
#line 1678 "./syntax.tab.c"
    break;

  case 58: /* Exp: ID LP Args RP  */
#line 141 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:12\n"NONE);}}
#line 1684 "./syntax.tab.c"
    break;

  case 59: /* Exp: ID LP RP  */
#line 142 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:13\n"NONE);}}
#line 1690 "./syntax.tab.c"
    break;

  case 60: /* Exp: Exp LB Exp RB  */
#line 143 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:14\n"NONE);}}
#line 1696 "./syntax.tab.c"
    break;

  case 61: /* Exp: Exp DOT ID  */
#line 144 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:15\n"NONE);}}
#line 1702 "./syntax.tab.c"
    break;

  case 62: /* Exp: ID  */
#line 145 "./syntax.y"
        {if(!bisonsim)  {printf(YELLOW"     Exp:16\n"NONE);}}
#line 1708 "./syntax.tab.c"
    break;

  case 63: /* Exp: INT  */
#line 146 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Exp:17\n"NONE);}}
#line 1714 "./syntax.tab.c"
    break;

  case 64: /* Exp: FLOAT  */
#line 147 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Exp:18\n"NONE);}}
#line 1720 "./syntax.tab.c"
    break;

  case 65: /* Args: Exp COMMA Args  */
#line 150 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Args:1\n"NONE);}}
#line 1726 "./syntax.tab.c"
    break;

  case 66: /* Args: Exp  */
#line 151 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Args:2\n"NONE);}}
#line 1732 "./syntax.tab.c"
    break;


#line 1736 "./syntax.tab.c"
=======
#line 52 "./syntax.y"
                    {}
#line 1340 "./syntax.tab.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 54 "./syntax.y"
                                {}
#line 1346 "./syntax.tab.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 55 "./syntax.y"
                {}
#line 1352 "./syntax.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 57 "./syntax.y"
                                    {}
#line 1358 "./syntax.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 58 "./syntax.y"
                        {}
#line 1364 "./syntax.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 59 "./syntax.y"
                                {}
#line 1370 "./syntax.tab.c"
    break;

  case 8: /* ExtDef: error SEMI  */
#line 60 "./syntax.y"
                 {printf("Wrong ExtDef\n");yyerrok;}
#line 1376 "./syntax.tab.c"
    break;

  case 10: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 63 "./syntax.y"
                                {}
#line 1382 "./syntax.tab.c"
    break;

  case 11: /* Specifier: TYPE  */
#line 67 "./syntax.y"
                    {}
#line 1388 "./syntax.tab.c"
    break;

  case 12: /* Specifier: StructSpecifier  */
#line 68 "./syntax.y"
                        {}
#line 1394 "./syntax.tab.c"
    break;

  case 13: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 70 "./syntax.y"
                                                {}
#line 1400 "./syntax.tab.c"
    break;

  case 14: /* StructSpecifier: STRUCT Tag  */
#line 71 "./syntax.y"
                    {}
#line 1406 "./syntax.tab.c"
    break;

  case 15: /* OptTag: ID  */
#line 74 "./syntax.y"
            {}
#line 1412 "./syntax.tab.c"
    break;

  case 16: /* OptTag: %empty  */
#line 75 "./syntax.y"
                    {}
#line 1418 "./syntax.tab.c"
    break;

  case 17: /* Tag: ID  */
#line 77 "./syntax.y"
        {}
#line 1424 "./syntax.tab.c"
    break;

  case 18: /* VarDec: ID  */
#line 81 "./syntax.y"
            {}
#line 1430 "./syntax.tab.c"
    break;

  case 19: /* VarDec: VarDec LB INT RB  */
#line 82 "./syntax.y"
                        {}
#line 1436 "./syntax.tab.c"
    break;

  case 20: /* FunDec: ID LP VarList RP  */
#line 85 "./syntax.y"
                            {}
#line 1442 "./syntax.tab.c"
    break;

  case 21: /* FunDec: ID LP RP  */
#line 86 "./syntax.y"
                {}
#line 1448 "./syntax.tab.c"
    break;

  case 22: /* FunDec: error RP  */
#line 87 "./syntax.y"
               {printf("Wrong FunDec\n");yyerrok;}
#line 1454 "./syntax.tab.c"
    break;

  case 23: /* VarList: ParamDec COMMA VarList  */
#line 89 "./syntax.y"
                                {}
#line 1460 "./syntax.tab.c"
    break;

  case 24: /* VarList: ParamDec  */
#line 90 "./syntax.y"
                {}
#line 1466 "./syntax.tab.c"
    break;

  case 25: /* ParamDec: Specifier VarDec  */
=======
  case 21: /* FunDec: ID LP VarList RP  */
>>>>>>> dev
#line 92 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     FunDec:1\n"NONE);}}
#line 1473 "./syntax.tab.c"
    break;

  case 22: /* FunDec: ID LP RP  */
#line 93 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     FunDec:2\n"NONE);}}
#line 1479 "./syntax.tab.c"
    break;

  case 23: /* FunDec: error RP  */
#line 94 "./syntax.y"
               {printf("Wrong FunDec\n");yyerrok;}
#line 1485 "./syntax.tab.c"
    break;

  case 24: /* VarList: ParamDec COMMA VarList  */
#line 97 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     VarList:1\n"NONE);}}
#line 1491 "./syntax.tab.c"
    break;

  case 25: /* VarList: ParamDec  */
#line 98 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     VarList:2\n"NONE);}}
#line 1497 "./syntax.tab.c"
    break;

  case 26: /* ParamDec: Specifier VarDec  */
>>>>>>> 9364a9d3b001473071d411492dc97d6c794e746e
#line 100 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     VarDec:VarDec LB INT RB (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("VarDec", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1468 "./syntax.tab.c"
    break;

  case 20: /* FunDec: ID LP VarList RP  */
#line 104 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     FunDec:ID LP VarList RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("FunDec", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1475 "./syntax.tab.c"
    break;

  case 21: /* FunDec: ID LP RP  */
#line 106 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     FunDec:ID LP RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("FunDec", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1482 "./syntax.tab.c"
    break;

  case 22: /* FunDec: error RP  */
#line 108 "./syntax.y"
               {printf("Wrong FunDec\n");yyerrok;}
#line 1488 "./syntax.tab.c"
    break;

  case 23: /* VarList: ParamDec COMMA VarList  */
#line 110 "./syntax.y"
                                {if(!bisonsim)  {printf(YELLOW"     VarList:ParamDec COMMA VarList (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("VarList", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1495 "./syntax.tab.c"
    break;

  case 24: /* VarList: ParamDec  */
#line 112 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     VarList:ParamDec (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("VarList", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1502 "./syntax.tab.c"
    break;

  case 25: /* ParamDec: Specifier VarDec  */
#line 115 "./syntax.y"
                           {if(!bisonsim)  {printf(YELLOW"     ParamDec:Specifier VarDec (%d)\n"NONE,(yyloc).first_line);}
    yyval=add_nonterminal("ParamDec", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1509 "./syntax.tab.c"
    break;

  case 26: /* CompSt: LC DefList StmtList RC  */
#line 120 "./syntax.y"
                                        {if(!bisonsim)  {printf(YELLOW"     CompSt:LC DefList StmtList RC (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("CompSt", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1516 "./syntax.tab.c"
    break;

  case 27: /* CompSt: error RC  */
#line 122 "./syntax.y"
                {printf("Wrong ComSt\n");yyerrok;}
#line 1522 "./syntax.tab.c"
    break;

  case 28: /* StmtList: Stmt StmtList  */
#line 124 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     StmtList:Stmt StmtList (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("StmtList", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1529 "./syntax.tab.c"
    break;

  case 29: /* StmtList: %empty  */
#line 126 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     StmtList:empty (%d)\n"NONE,(yyloc).first_line);}    yyval=NULL;}
#line 1535 "./syntax.tab.c"
    break;

  case 30: /* Stmt: Exp SEMI  */
#line 128 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Stmt:Exp SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1542 "./syntax.tab.c"
    break;

  case 31: /* Stmt: CompSt  */
#line 130 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Stmt:CompSt (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1549 "./syntax.tab.c"
    break;

  case 32: /* Stmt: RETURN Exp SEMI  */
#line 132 "./syntax.y"
                         {if(!bisonsim)  {printf(YELLOW"     Stmt:RETURN Exp SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1556 "./syntax.tab.c"
    break;

  case 33: /* Stmt: IF LP Exp RP Stmt  */
#line 134 "./syntax.y"
                                              {if(!bisonsim)  {printf(YELLOW"     Stmt:IF LP Exp RP Stmt LOWER_THAN_ELSE (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 5,yyvsp[-4],yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1563 "./syntax.tab.c"
    break;

  case 34: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 136 "./syntax.y"
                                    {if(!bisonsim)  {printf(YELLOW"     Stmt:IF LP Exp RP Stmt ELSE Stmt (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 7,yyvsp[-6],yyvsp[-5],yyvsp[-4],yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1570 "./syntax.tab.c"
    break;

  case 35: /* Stmt: WHILE LP Exp RP Stmt  */
#line 138 "./syntax.y"
                                      {if(!bisonsim)  {printf(YELLOW"     Stmt:6WHILE LP Exp RP Stmt (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Stmt", (yyloc).first_line, NOTTOKEN, 5,yyvsp[-4],yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1577 "./syntax.tab.c"
    break;

  case 36: /* Stmt: error SEMI  */
#line 140 "./syntax.y"
                    {printf("Wrong Stmt\n");yyerrok;}
#line 1583 "./syntax.tab.c"
    break;

  case 37: /* DefList: Def DefList  */
#line 144 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     DefList:Def DefList (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("DefList", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1590 "./syntax.tab.c"
    break;

  case 38: /* DefList: %empty  */
#line 146 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     DefList:empty (%d)\n"NONE,(yyloc).first_line);} yyval=NULL;}
#line 1596 "./syntax.tab.c"
    break;

  case 39: /* Def: Specifier DecList SEMI  */
#line 148 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     Def:Specifier DecList SEMI (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Def", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1603 "./syntax.tab.c"
    break;

  case 40: /* Def: error SEMI  */
#line 150 "./syntax.y"
                {printf("Wrong Def:semi exist\n");yyerrok;}
#line 1609 "./syntax.tab.c"
    break;

  case 41: /* DecList: Dec  */
#line 152 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     DecList:Dec (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("DecList", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1616 "./syntax.tab.c"
    break;

  case 42: /* DecList: Dec COMMA DecList  */
#line 154 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     DecList:Dec COMMA DecList (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("DecList", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1623 "./syntax.tab.c"
    break;

  case 43: /* Dec: VarDec  */
#line 157 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Dec:VarDec (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Dec", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1630 "./syntax.tab.c"
    break;

  case 44: /* Dec: VarDec ASSIGNOP Exp  */
#line 159 "./syntax.y"
                            {if(!bisonsim)  {printf(YELLOW"     Dec:VarDec ASSIGNOP Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Dec", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1637 "./syntax.tab.c"
    break;

  case 45: /* Exp: Exp ASSIGNOP Exp  */
#line 164 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:Exp ASSIGNOP Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1644 "./syntax.tab.c"
    break;

  case 46: /* Exp: Exp AND Exp  */
#line 166 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:Exp AND Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1651 "./syntax.tab.c"
    break;

  case 47: /* Exp: Exp OR Exp  */
#line 168 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp OR Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1658 "./syntax.tab.c"
    break;

  case 48: /* Exp: Exp RELOP Exp  */
#line 170 "./syntax.y"
                        {if(!bisonsim)  {printf(YELLOW"     Exp:Exp RELOP Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1665 "./syntax.tab.c"
    break;

  case 49: /* Exp: Exp PLUS Exp  */
#line 172 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp PLUS Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1672 "./syntax.tab.c"
    break;

  case 50: /* Exp: Exp MINUS Exp  */
#line 174 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp MINUS Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1679 "./syntax.tab.c"
    break;

  case 51: /* Exp: Exp STAR Exp  */
#line 176 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp STAR Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1686 "./syntax.tab.c"
    break;

  case 52: /* Exp: Exp DIV Exp  */
#line 178 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp DIV Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1693 "./syntax.tab.c"
    break;

  case 53: /* Exp: LP Exp RP  */
#line 180 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:LP Exp RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1700 "./syntax.tab.c"
    break;

  case 54: /* Exp: MINUS Exp  */
#line 182 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:MINUS Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1707 "./syntax.tab.c"
    break;

  case 55: /* Exp: NOT Exp  */
#line 184 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:NOT Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 2,yyvsp[-1],yyvsp[0]);}
#line 1714 "./syntax.tab.c"
    break;

  case 56: /* Exp: ID LP Args RP  */
#line 186 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:ID LP Args RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1721 "./syntax.tab.c"
    break;

  case 57: /* Exp: ID LP RP  */
#line 188 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:ID LP RP (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1728 "./syntax.tab.c"
    break;

  case 58: /* Exp: Exp LB Exp RB  */
#line 190 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Exp:Exp LB Exp RB (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 4,yyvsp[-3],yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1735 "./syntax.tab.c"
    break;

  case 59: /* Exp: Exp DOT ID  */
#line 192 "./syntax.y"
                {if(!bisonsim)  {printf(YELLOW"     Exp:Exp DOT ID (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1742 "./syntax.tab.c"
    break;

  case 60: /* Exp: ID  */
#line 194 "./syntax.y"
        {if(!bisonsim)  {printf(YELLOW"     Exp:ID (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1749 "./syntax.tab.c"
    break;

  case 61: /* Exp: INT  */
#line 196 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Exp:INT (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1756 "./syntax.tab.c"
    break;

  case 62: /* Exp: FLOAT  */
#line 198 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Exp:FLOAT (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1763 "./syntax.tab.c"
    break;

  case 63: /* Args: Exp COMMA Args  */
#line 202 "./syntax.y"
                    {if(!bisonsim)  {printf(YELLOW"     Args:Exp COMMA Args (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Args", (yyloc).first_line, NOTTOKEN, 3,yyvsp[-2],yyvsp[-1],yyvsp[0]);}
#line 1770 "./syntax.tab.c"
    break;

  case 64: /* Args: Exp  */
#line 204 "./syntax.y"
            {if(!bisonsim)  {printf(YELLOW"     Args:Exp (%d)\n"NONE,(yyloc).first_line);}
        yyval=add_nonterminal("Exp", (yyloc).first_line, NOTTOKEN, 1,yyvsp[0]);}
#line 1777 "./syntax.tab.c"
    break;


<<<<<<< HEAD
#line 1781 "./syntax.tab.c"
=======
<<<<<<< HEAD
#line 1710 "./syntax.tab.c"
>>>>>>> 6167a60366b5123f99de96992d6be4d8a38646cd
=======
#line 1801 "./syntax.tab.c"
>>>>>>> dev
>>>>>>> 9364a9d3b001473071d411492dc97d6c794e746e

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

#line 207 "./syntax.y"


void yyerror(const char *s) {
    printf ("Error type B at Line %d in position(%d-%d), \'%s\'\n", yylineno,yylloc.first_column,yylloc.last_column,yytext);
    haserror=1;
}
