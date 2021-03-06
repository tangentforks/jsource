/* Copyright 1990-2007, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Type Definitions                                                        */

#define U unsigned

#if (SYS & SYS_UNIX)
#define _stdcall      
#endif

#if SY_64
typedef long long          A1;
typedef unsigned long long BT;
typedef long long          I;
typedef long long          SB;
typedef unsigned long long UI;
typedef unsigned long long UIL;   /* for typecast 8 byte double */
typedef long long          IL;

#else
typedef long               A1;
typedef unsigned long      BT;
typedef long               I;
typedef long               SB;
typedef unsigned long      UI;
typedef unsigned long long UIL;
typedef long long          IL;
#endif

typedef char               B;
typedef unsigned char      C;
typedef char*              Ptr;
typedef short              S;
typedef short              C2;
typedef unsigned int       C4;
typedef unsigned char      UC;
typedef unsigned short     US;
typedef unsigned short     U2;
typedef unsigned int       UINT;
typedef int                I4;
typedef unsigned int       UI4;
typedef double             D;
typedef FILE*              F;

typedef long double        LD;

// This is the main structure for J entities
typedef US                 RANKT;
typedef I                  FLAGT;

typedef struct AD AD;
typedef AD *A;

// obsolete typedef struct {I k,flag,m,t,c,n,r,s[1];} AD;  // old version

typedef struct AD {
 union {
  I k;
  A chain;   // used when block is on free chain
 } kchain;
 FLAGT flag;
 union {
  I m;  // For NJA/SMM blocks, size of allocation. 
  A back; // For VIRTUAL blocks, points to backing block
} mback;
 union {
  I t;  // type
  A proxychain;  // used when block is on free chain
 } tproxy;
 I c;  // usecount
 I n;  // # atoms
#if C_LE
 RANKT r;  // rank
 US h;   // reserved for allocator.  Not used for AFNJA memory
#if BW==64
 UI4 fill;   // On 64-bit systems, there will be a padding word here - insert in case compiler doesn't
#endif
#else
#if BW==64
 UI4 fill;   // On 64-bit systems, there will be a padding word here - insert in case compiler doesn't
#endif
 US h;   // reserved for allocator.  Not used for AFNJA memory
 RANKT r;  // rank
#endif
 I s[1];   // shape starts here
} AD;

typedef struct {A a,t;}TA;
typedef A                (*AF)();
typedef UI               (*UF)();
typedef void             (*VF)();
typedef B                (*CMP)();    /* comparison function in sort     */
typedef A                  X;
typedef struct {X n,d;}    Q;
typedef struct {D re,im;}  Z;
typedef union {D d;UINT i[2];UI ui;} DI;

#if (SYS & SYS_PC+SYS_MACINTOSH)        /* for use by the session manager  */
typedef S SI;
#else
typedef I SI;
#endif

/* Fields of type A                                                        */

#define AK(x)           ((x)->kchain.k)        /* offset of ravel wrt x           */
#define AFLAG(x)        ((x)->flag)     /* flag                            */
#define AM(x)           ((x)->mback.m)        /* Max # bytes in ravel            */
#define ABACK(x)        ((x)->mback.back)        /* Max # bytes in ravel            */
#define AT(x)           ((x)->tproxy.t)        /* Type; one of the #define below  */
#define AC(x)           ((x)->c)        /* Reference count.                */
#define AN(x)           ((x)->n)        /* # elements in ravel             */
#define AR(x)           ((x)->r)        /* Rank                            */
// obsolete #define AH              7L              /* # non-shape header words in A   */
#define SMMAH           7L   // number of header words in old-fashioned SMM alloc
#define NORMAH          7L   // number of header words in new system
#define AS(x)           ((x)->s)        // Because s is an array, AS(x) is a pointer to the shape, which is in s.  The shape is stored in the fixed position s.

#if SY_64
#define AKXR(x)         (SZI*(NORMAH+(x)))
#define WP(t,n,r)       (SMMAH+ r   +(1&&t&LAST0)+(((t&NAME?sizeof(NM):0)+(n)*bp(t)+SZI-1)>>LGSZI))  // # I to allocate
// obsolete #define BP(t,n,r)       ((r*SZI  + ((t&LAST0)? (t&NAME)?(AH*SZI+sizeof(NM)+2*SZI-1):(AH*SZI+2*SZI-1) : (AH*SZI+SZI-1)) + (n)*bp(t)) & (-SZI))  // # bytes to allocate
#else
#define AKXR(x)         (SZI*(NORMAH+((x)|1)))
#define WP(t,n,r)       (SMMAH+(r|1)+  (1&&t&LAST0)+(((t&NAME?sizeof(NM):0)+(n)*bp(t)+SZI-1)>>LGSZI))
// obsolete #define BP(t,n,r)       (((r|1)*SZI + ((t&LAST0)? (t&NAME)?(AH*SZI+sizeof(NM)+2*SZI-1):(AH*SZI+2*SZI-1) : (AH*SZI+SZI-1)) + (n)*bp(t)) & (-SZI))  // # bytes to allocate
/* r|1 to make sure array values are double-word aligned */
#endif
#define AKX(x)          AKXR(AR(x))

#define AV(x)           ( (I*)((C*)(x)+AK(x)))  /* pointer to ravel        */
#define BAV(x)          (      (C*)(x)+AK(x) )  /* boolean                 */
#define CAV(x)          (      (C*)(x)+AK(x) )  /* character               */
#define UCAV(x)         (     (UC*)(x)+AK(x) )  /* unsigned character      */
#define USAV(x)         ((US*)((C*)(x)+AK(x)))  /* wchar                   */
#define UAV(x)          (     (UC*)(x)+AK(x) )  /* unsigned character      */
#define UIAV(x)         ((UI*)((C*)(x)+AK(x)))  /* unsigned character      */
#define UI4AV(x)        ((UI4*)((C*)(x)+AK(x)))  /* unsigned 32-bit int      */
#define C4AV(x)         ((C4*)((C*)(x)+AK(x)))  /* literal4                */
#define NAV(x)          ((NM*)((C*)(x)+AK(x)))  /* name                    */
#define IAV(x)          AV(x)                   /* integer                 */
#define DAV(x)          ( (D*)((C*)(x)+AK(x)))  /* double                  */
#define ZAV(x)          ( (Z*)((C*)(x)+AK(x)))  /* complex                 */
#define XAV(x)          ( (X*)((C*)(x)+AK(x)))  /* extended                */
#define QAV(x)          ( (Q*)((C*)(x)+AK(x)))  /* rational                */
#define AAV(x)          ( (A*)((C*)(x)+AK(x)))  /* boxed                   */
#define A1AV(x)         ((A1*)((C*)(x)+AK(x)))  /* boxed relative address  */
#define VAV(x)          ( (V*)((C*)(x)+AK(x)))  /* verb, adverb, conj      */
#define PAV(x)          ( (P*)((C*)(x)+AK(x)))  /* sparse                  */
#define SBAV(x)         ((SB*)((C*)(x)+AK(x)))  /* symbol                  */
#define voidAV(x)       ((void*)((C*)(x)+AK(x)))  // unknown

/* Types for AT(x) field of type A                                         */
/* Note: BOOL name conflict with ???; SCHAR name conflict with sqltypes.h  */

// NOTE!! the length of NOUN types must be power-of-2 multiples because of jtamend2

#define B01X 0
#define B01             ((I)1L<<B01X)           /* B  boolean                      */
#define B01SIZE         sizeof(B)       // length of 1 atom
#define LITX 1
#define LIT             ((I)1L<<LITX)           /* C  literal (character)          */
#define LITSIZE sizeof(C)
#define INTX 2
#define INT             ((I)1L<<INTX)           /* I  integer                      */
#define INTSIZE sizeof(I)
#define FLX 3
#define FL              ((I)1L<<FLX)           /* D  double (IEEE floating point) */
#define FLSIZE sizeof(D)
#define CMPXX 4
#define CMPX            ((I)1L<<CMPXX)          /* Z  complex                      */
#define CMPXSIZE sizeof(Z)
#define BOXX 5
#define BOX             ((I)1L<<BOXX)          /* A  boxed                        */
#define BOXSIZE sizeof(A)
#define XNUMX 6
#define XNUM            ((I)1L<<XNUMX)          /* X  extended precision integer   */
#define XNUMSIZE sizeof(X)
#define RATX 7
#define RAT             ((I)1L<<RATX)         /* Q  rational number              */
#define RATSIZE sizeof(Q)
#define BITX 8
#define BIT             ((I)1L<<BITX)         /* BT bit boolean                  */
// No size for BIT, since it is fractional
// Bit 9 unused
#define SB01X 10
#define SB01            ((I)1L<<SB01X)        /* P  sparse boolean               */
#define SB01SIZE sizeof(P)
#define SLITX 11
#define SLIT            ((I)1L<<SLITX)        /* P  sparse literal (character)   */
#define SLITSIZE sizeof(P)
#define SINTX 12
#define SINT            ((I)1L<<SINTX)        /* P  sparse integer               */
#define SINTSIZE sizeof(P)
#define SFLX 13
#define SFL             ((I)1L<<SFLX)        /* P  sparse floating point        */
#define SFLSIZE sizeof(P)
#define SCMPXX 14
#define SCMPX           ((I)1L<<SCMPXX)       /* P  sparse complex               */
#define SCMPXSIZE sizeof(P)
#define SBOXX 15
#define SBOX            ((I)1L<<SBOXX)       /* P  sparse boxed                 */
#define SBOXSIZE sizeof(P)
#define SBTX 16
#define SBT             ((I)1L<<SBTX)       /* SB symbol                       */
#define SBTSIZE sizeof(SB)
#define C2TX 17
#define C2T             ((I)1L<<C2TX)      /* C2 unicode (2-byte characters)  */
#define C2TSIZE sizeof(US)
#define C4TX 18
#define C4T             ((I)1L<<C4TX)         /* C4 unicode (4-byte characters)  */
#define C4TSIZE sizeof(C4)
#define XDX 19
#define XD              ((I)1L<<XDX)   /* DX extended floating point      */
#define XDSIZE sizeof(DX)
#define XZX 20
#define XZ              ((I)1L<<XZX)   /* ZX extended complex             */
#define XZSIZE sizeof(ZX)
#define VERBX 21
#define VERB            ((I)1L<<VERBX)      /* V  verb                         */
#define VERBSIZE sizeof(V)
#define ADVX 22
#define ADV             ((I)1L<<ADVX)      /* V  adverb                       */
#define ADVSIZE sizeof(V)
#define CONJX 23
#define CONJ            ((I)1L<<CONJX)     /* V  conjunction                  */
#define CONJSIZE sizeof(V)
// ASGN see below
#define MARKX 25
#define MARK            ((I)1L<<MARKX)     /* I  end-of-stack marker          */
#define MARKSIZE sizeof(I)
#define NAMEX 26
#define NAME            ((I)1L<<NAMEX)    /* NM name                         */
#define NAMESIZE sizeof(C)
#define SYMBX 27
#define SYMB            ((I)1L<<SYMBX)     /* I  locale (symbol table)        */
#define SYMBSIZE sizeof(I)
#define CONWX 28
#define CONW            ((I)1L<<CONWX)    /* CW control word                 */
#define CONWSIZE sizeof(CW)
#define LPARX 29
#define LPAR            ((I)1L<<LPARX)    /* I  left  parenthesis            */
#define LPARSIZE sizeof(I)
#define RPARX 30
#define RPAR            ((I)1L<<RPARX)   /* I  right parenthesis            */
#define RPARSIZE sizeof(I)
// NOTE maxtype & maybe others require bit 31 to be 0!!
#define ASGNX 24
#define ASGN            ((I)1L<<ASGNX)     /* I  assignment                   */
#define ASGNSIZE sizeof(I)     // only 1 byte, but all non-DIRECT are fullword multiples
// ASGN type can have the following informational bits set along with ASGN
#define ASGNLOCAL       ((I)1L<<SYMBX)     // set for =. (but not when assigning to locative)    aliases with SYMB
#define ASGNTONAME      ((I)1L<<CONWX)     // set when assignment is to name    aliases with CONW
// NOUN types can have the following informational bits set
// obsolete #define NOUNSAFE0       ((I)1L<<SYMBX)     // set when the current block does not need to be protected by EPILOG.  Example is name or constant.   Aliases with SYMB
// obsolete #define NOUNSAFE        ((I)1L<<CONWX)     // set when descendants of the current (necessarily indirect) block do not need to be protected by EPILOG.  Example is 3 {. name.    aliases with CONW
#define NOUNCVTVALIDCT  ((I)1L<<SYMBX)     // Flag for jtcvt: if set, convert only the #atoms given in the parameter   Aliases with SYMB
// NAME type can have the following information flags set
// obsolete #define NAMEIPOK        ((I)1L<<SYMBX)     // set if the value can be marked inplaceable when it is moved onto the stack (if name is reassigned - watch for errors!)   Aliases with SYMB
#define NAMEBYVALUE     ((I)1L<<CONWX)     // set if the name is one of x x. m m. etc that is always passed by value, never by name   Aliases with CONW

// Planned coding to save bits in type
// Uses bits 24-27 eg
// MARK is represented by type of all 0
// Other types are in bits 24-27:
// CONJ   0001
// ADV    0101
// VERB   1101
// ASGN   xy10    x=ASGNLOCAL y=ASGNTONAME
// CONW   0100    must be allocated by GAF, & not be copied, unless ca() is modified to use length not type
// SYMB   1100
// NAME   100v    v=NAMEBYVALUE
// RPAR   0011    must be allocated by GAF, & not be copied, unless ca() is modified to use length not type
// LPAR   1011    must be allocated by GAF, & not be copied, unless ca() is modified to use length not type
// obsolete // 1000 and 0100 are used as flag bits for NOUNSAFE

#define ANY             -1L
#define SPARSE          (SB01+SINT+SFL+SCMPX+SLIT+SBOX)
#define NUMERIC         (B01+BIT+INT+FL+CMPX+XNUM+RAT+XD+XZ+SB01+SINT+SFL+SCMPX)
#define DIRECT          (LIT+C2T+C4T+B01+BIT+INT+FL+CMPX+SBT)
#define JCHAR           (LIT+C2T+C4T+SLIT)
#define NOUN            (NUMERIC+JCHAR+BOX+SBOX+SBT)
#define DENSE           (NOUN&~SPARSE)
#define FUNC            (VERB+ADV+CONJ)
#define RHS             (NOUN+FUNC)
#define IS1BYTE         (B01+LIT)
#define LAST0           (B01+LIT+C2T+C4T+NAME)
// Don't call traverse unless one of these bits is set
#define TRAVERSIBLE     (XD|RAT|XNUM|BOX|VERB|ADV|CONJ|SB01|SINT|SFL|SCMPX|SLIT|SBOX)
// Allow recursive usecount in one of these types
#define RECURSIBLE      (BOX|VERB|ADV|CONJ)

// NOUNSAFE flag
// obsolete #define SAFE(x)         ((x)|(NOUNSAFE|NOUNSAFE0))    // type, current block and descendants safe from tstack
// obsolete #define SAFED(x)        ((x)|NOUNSAFE)    // type, descendants safe from tstack
// obsolete #define SAFE0(x)        ((x)|NOUNSAFE0)    // type, current block safe from tstack
// obsolete #define UNSAFE(x)       ((x)&~(NOUNSAFE|NOUNSAFE0))   // type, not safe from tstack
// obsolete #define UNSAFED(x)      ((x)&~(NOUNSAFE))   // type, descendants not safe from tstack
// obsolete #define UNSAFE0(x)      ((x)&~(NOUNSAFE0))   // type, not safe from tstack
// scaf expunge all the following
#define SAFE(x)         (x)    // type, current block and descendants safe from tstack
#define SAFED(x)        (x)    // type, descendants safe from tstack
#define SAFE0(x)        (x)    // type, current block safe from tstack
#define UNSAFE(x)       (x)   // type, not safe from tstack
#define UNSAFED(x)      (x)   // type, descendants not safe from tstack
#define UNSAFE0(x)      (x)   // type, not safe from tstack

// obsolete #define TYPESEQ(x,y)    (0==UNSAFE((x)^(y)))  // types are equal, ignoring NOUNSAFE bits
// obsolete #define TYPESNE(x,y)    (0!=UNSAFE((x)^(y)))  // types are equal, ignoring NOUNSAFE bits
// obsolete #define TYPESLT(x,y)    (UNSAFE(x)<UNSAFE(y))  // type x < type y
// obsolete #define TYPESGT(x,y)    (UNSAFE(x)>UNSAFE(y)) // type x > type y
#define TYPESEQ(x,y)    ((x)==(y))  // types are equal, ignoring NOUNSAFE bits
#define TYPESXOR(x,y)    ((x)^(y))  // types are not equal, ignoring NOUNSAFE bits, using full-word logical
#define TYPESNE(x,y)    ((x)!=(y))  // types are equal, ignoring NOUNSAFE bits
#define TYPESLT(x,y)    ((x)<(y))  // type x < type y
#define TYPESGT(x,y)    ((x)>(y)) // type x > type y

// Utility: keep the lowest 1 only
#define LOWESTBIT(x)    ((x)&-(x))

#define HOMO(s,t)       (TYPESEQ((s),(t)) || (s)&NUMERIC&&(t)&NUMERIC || (s)&JCHAR&&(t)&JCHAR)
#define STYPE(t)        (((t)&(B01|LIT|INT|FL|CMPX|BOX))<<(SB01X-B01X))
#define DTYPE(t)        (((t)&(SB01|SLIT|SINT|SFL|SCMPX|SBOX))>>(SB01X-B01X))

// Flags in the count field of type A
#define ACINPLACE       (I)(((UI)-1>>1)^(UI)-1)  // set when this block CAN be used in inplace operations.  Always the sign bit.
#define ACPERMANENT     ((I)((UI)ACINPLACE>>1))  // next-to-top bit, set in blocks that should never modify the AC field
#define ACUSECOUNT      (I)1  // lower bits used for usecount
#define ACIPNO(a)       (AC(a)&=~ACINPLACE)
#define ACIPYES(a)      (AC(a)|=ACINPLACE)
#define ACIPISOK(a)     (AC(a)<0)  // OK to modify if INPLACE set - set only when usecount=1
#define ACUC(a)         (AC(a)&(~ACINPLACE))  // just the usecount portion
#define ACUC1           (ACUSECOUNT*1) // <= this is usecount==1; > is UC>1
// obsolete #define ACINCRBY(a,w)   (AC(a)=(AC(a)+(w))&~ACINPLACE)  // add w to usecount; always clear INPLACE at that time
#define ACINCR(a)       if(!ACISPERM(AC(a)))(AC(a)=(AC(a)+1)&~ACINPLACE)
#define ACX(a)          {AC(a)=ACPERMANENT;}
#define ACISPERM(c)     (((c)+(c))<0)  // is PERMANENT bit set?
#define ASGNINPLACE(w)  (ACIPISOK(w) || jt->assignsym&&jt->assignsym->val==w&&(AC(w)<=1&&notonupperstack(w)))  // OK to inplace ordinary operation
#define ASGNINPLACENJA(w)  (ASGNINPLACE(w)||(AFNJA&AFLAG(w)&&AC(w)==2))   // OK to inplace, for ops that have special support for NJA blocks

/* Values for AFLAG(x) field of type A                                     */
// the flags defined here must be mutually exclusive with TRAVERSIBLE

#define AFRO            (I)1            /* read only; can't change data    */
#define AFNJA           (I)2            /* non-J alloc; i.e. mem mapped    */
#define AFSMM           (I)4            /* SMM managed                     */
#define AFRELX          3
#define AFREL           (I)(1<<AFRELX)            // uses relative addressing.
#define AFNOSMRELX      4
#define AFNOSMREL       (I)(1<<AFNOSMRELX)   // this block and its descendants contain NO relative addressing/SMM (set only in boxed nouns)
// Note: in s.c we rely on AFNOSMREL's being adjacent to BOX!!  In cr.c we rely on its being exactly what it is (it matches a hole in STATExxx)
// The values of BOX, ADV, CONJ, and VERB may also appear in AFLAG, where they must match the value in AT(), and indicate that the usecount for the block is recursive, i. e. that
// the usecount for this block, except for the first, has NOT been propagated to its descendants, and thus that it must be propagated only when this
// block is actually freed
#define AFNVRX          8
#define AFNVR           (1<<AFNVRX)  // This value is on the parser's execution stack, and must not be freed until it is removed
#define AFNVRUNFREEDX   18
#define AFNVRUNFREED    (1<<AFNVRUNFREEDX)  // This value does NOT need to be freed by the parser, even though it was stacked
#define AFVIRTUALX      17      // matches C2TX
#define AFVIRTUAL       (1<<AFVIRTUALX)  // this block is a VIRTUAL block: a subsequence of another block.  The data pointer points to the actual data, and the
                                 // m field points to the start of the block containing the actual data.  A VIRTUAL block cannot be incorporated into another block, and it
                                 // cannot be assigned, unless it is 'realized' by creating another block and copying the data.  We realize whenever we call ra() on the block,
                                 // except during the EPILOG, where we don't realize the block unless the real block is about to be freed.
// obsolete // INDIRECT means that the data for the block is actually in the value of another block.  Such a block is handled just like any other except
// obsolete // that it must be inplaced with care, and if it is assigned to a name it must be realized, i. e. the values must be copied to a new block.
// obsolete // We achieve this by realizing whenever ra() - but not ra0() - is called for the block
// obsolete #define AFINDIRECT      (VINPLACEOK1|VINPLACEOK2)  // set both bits
#define AFAUDITUCX      32   // this & above is used for auditing the stack (you must run stack audits on a 64-bit system)
#define AFAUDITUC       ((I)1<<AFAUDITUCX)    // this field is used for auditing the tstack, holds the number of deletes implied on the stack for the block

// convert relative address to absolute.  k must have been assigned by RELORIGIN*.  k may well be 0 for non-relatives, and that's OK, no relocation is done
#define AABS(rel,k)     ((I)(rel)+(I)(k))
#define AREL(abs,k)     ((I)(abs)-(I)(k))   /* relative address from absolute address */
#define ARELATIVEB(w)   ((AFLAG(w)&AFNJA+AFSMM+AFREL)!=0)  // test if we know w is boxed - may be used in branches or computation
// obsolete #define ARELATIVE(w)    (ARELATIVEB(w)&&AT(w)&BOX)   // test if we don't, branchless and returning the value in bit BOXX
#define ARELATIVES(w)   ((AT(w)|(~BOX))+(AFLAG(w)&(AFNJA+AFSMM+AFREL)))  // test for relative, leave in sign bit (sign is 0 if RELATIVE)
                               // the test uses the fact that AF* is less than BOX
#define ARELATIVESB(w)   ((AFLAG(w)&(AFNJA+AFSMM+AFREL))-1)  // test for relative, leave in sign bit (sign is 0 if RELATIVE) - if known boxed
#define ARELATIVE(w)    (ARELATIVES(w) >= 0)   // test if we don't, branchless
#define AORWRELATIVE(a,w) ((ARELATIVES(a)&ARELATIVES(w))>=0)  // true if EITHER has sign 0
#define AORWRELATIVEB(a,w) (((AFLAG(a)|AFLAG(w))&AFNJA+AFSMM+AFREL)!=0)  // same test, but this time known to be boxed.  branches or computation
#define AADR(w,z)       (A)((I)(w)+(I)(z))   // was ((w)?(A)((I)(w)+(I)(z)):(z))
// get the base to add to relative refs.  It's the origin of this block unless this block is virtual: then the origin of the backing block
// here the block is known (or assumed) to be relative and boxed.  asgn is an I name we declare and use for assignment.  Result is I
// obsolete #define RELORIGIN(asgn,w)    ((I)(AFLAG(w)&AFVIRTUAL?ABACK(w):w))
#define RELORIGIN(asgn,w)    I asgn; asgn=(I)ABACK(w); asgn=(AFLAG(w)&AFVIRTUAL?asgn:(I)w);
// here we know the block is boxed, but its relative status is unknown
// obsolete #define RELORIGINB(w)   (RELORIGIN(w) & (AFLAG(w)&AFNJA+AFSMM+AFREL?~0:0))
#define RELORIGINB(asgn,w)    I asgn; asgn=(I)ABACK(w); asgn=(AFLAG(w)&AFVIRTUAL?asgn:(I)w); asgn=(AFLAG(w)&AFNJA+AFSMM+AFREL?asgn:0);
// here the block is unknown
// obsolete #define RELORIGINBR(w)  (ARELATIVE(w)?RELORIGIN(w):0)
#define RELORIGINBR(asgn,w)   I asgn; asgn=(I)ABACK(w); asgn=(AFLAG(w)&AFVIRTUAL?asgn:(I)w); asgn=(ARELATIVE(w)?asgn:0);
// use this to indicate the relocation factor for a non-virtual, non-relative block (usually a destination that has been allocated recently)
#define RELORIGINDEST(w) ((I)(w))

// set up the relative base-offset ad,id... lett is a,i... as a reminder that the suffix must be d.  w is the block.  The result is germane
// only if boxed, but we don't test for boxing here
// obsolete #define RELBASEASGN(lett,w) {lett##d = RELORIGIN(w); lett##d = (AFLAG(w)&(AFNJA+AFSMM+AFREL))?lett##d:0;}
#define RELBASEASGN(lett,w) RELORIGINB(lett##d,w)
// same, but include the test for boxing
// obsolete #define RELBASEASGNB(lett,w) {lett##d = RELORIGIN(w); lett##d = (AT(w)&BOX)?lett##d:0; lett##d = (AFLAG(w)&(AFNJA+AFSMM+AFREL))?lett##d:0;}
#define RELBASEASGNB(lett,w) RELORIGINBR(lett##d,w)
#define AVR(i)          AADR(ad,av[i])
#define IVR(i)          AADR(id,iv[i])
#define WVR(i)          AADR(wd,wv[i])
#define YVR(i)          AADR(yd,yv[i])
// obsolete #define AAV0(w)         (ARELATIVE(w)?(A)(*AV(w)+(I)(w)):*AAV(w))
#define AAV0(w) ((A)((C*)*AAV(w) + (AFLAG(w)&AFNJA+AFSMM+AFREL?(I)(AFLAG(w)&AFVIRTUAL?ABACK(w):w):0)))  // fetch first box of w, which must be boxed
// if w is relative, relocate the contents of z from w to z.  We must have moved the contents of w into output block z without relocating, and now we are fixing it up
// z must be known to be relative and nonvirtual.  This has no result.  z is never disturbed.
// obsolete #define RELOCATE(w,z)   (ARELATIVE(w)?relocate((I)(w)-(I)(z),(z)):(z))
#define RELOCATE(w,z)   if(ARELATIVE(w)){RELORIGIN(wrel,w); relocate(wrel-(I)(z),(z));}
// copy from to to for n boxes, relocating each by offset.  from and to are A* exprs
#define RELOCOPY(to,from,n,offset) DO(n, to[i]=(A)((I)from[i]+offset);)
// same, but use an incrementing pointer for to
#define RELOCOPYT(to,from,n,offset) DO(n, *to++ =(A)((I)from[i]+offset);)
// same, but use an incrementing pointer for from
#define RELOCOPYF(to,from,n,offset) DO(n, to[i]=(A)((I)*from++ +offset);)
// same, but use an incrementing pointer for to and from
#define RELOCOPYTF(to,from,n,offset) DQ(n, *to++ =(A)((I)*from++ +offset);)

typedef struct {I i;US n,go,source;C type;C canend;} CW;

/* control word (always has corresponding token string)                             */
/* type   - as specified in w.h                                            */
/* go     - line number to go to                                           */
/* source - source line number                                             */
/* i      - beginning index of token string                                */
/* n      - length          of token string                                */
// canend - Indicates that the most-recent B-block result can (1) or can't (2) become the result of the running definition.  0 means we don't know yet.


#define DCPARSE  1      /* sentence for parser                                          */
#define DCSCRIPT 2      /* script              -- line()                                */
#define DCCALL   3      /* verb/adv/conj call  -- dbunquote()                           */
#define DCJUNK   4      /* stack entry is obsolete                                      */

typedef struct DS{      /* 1 2 3                                                        */
 struct DS*dclnk;       /* x x x  link to next stack entry                              */
 A dca;                 /*     x  fn/op name                                            */
 A dcf;                 /*     x  fn/op                                                 */
 A dcx;                 /*     x  left argument                                         */
 A dcy;                 /* x x x  &tokens; text       ; right argument                  */
 A dcloc;               /*     x  local symb table (0 if not explicit)                  */
 A dcc;                 /*     x  control matrix   (0 if not explicit)                  */
 I dci;                 /* x x x  index ; next index  ; ptr to line #                   */
 I dcj;                 /* x x x  error#; prev index  ; error #                         */
 I dcn;                 /* x x x  #tokens; line #     ; ptr to symb entry               */
 I dcm;                 /*   x x        ; script index; # of non-locale part of name    */
 I dcstop;              /*     x  the last stop in this function                        */
 C dctype;              /* x x x  type of entry (see #define DC*)                       */
 B dcsusp;              /* x   x  1 iff begins a debug suspension                       */
 C dcss;                /*     x  single step code                                      */
} DST;

typedef DST* DC;


typedef struct {I e,p;X x;} DX;
                                /* for the p field in DX */
#define DXIPREC         ((I)-1) /* infinite precision    */
#define DXINF           ((I)-2) /* _  infinity           */
#define DXMINF          ((I)-3) /* __ negative infinity  */

/* extended floating point                                                 */
/* e - exponent                                                            */
/* p - precision & other codes                                             */
/*        +ve   # of significant digits                                    */
/*        _1    infinite precision (with trailing 0s)                      */
/*        _2    infinity _                                                 */
/*        _3    negative infinity __                                       */
/* x - mantissa                                                            */
/*        least significant digit first                                    */
/*        decimal point after last digit                                   */

#define SYMLINFO 0  // index of LINFO entry
#define SYMLINFOSIZE 1     // Number of symbol-table entries that DO NOT contain symbol chains, but instead are LINFO entries

typedef struct {A name,val;I flag,sn,next,prev;} L;

/* symbol pool entry                           LINFO entry                 */
/* name - name on LHS of assignment         or locale name                 */
/* val  - value                             or locale search path          */
/* flag - various flags                                                    */
/* sn   - script index                                                     */
/* next - index of successor   in hash list or 0                           */
/* prev - index of predecessor in hash list or address of hash entry       */

#define LCH             (I)1            /* changed since last exec of 4!:5 */
#define LHEAD           (I)2            /* head pointer (no predecessor)   */
#define LINFO           (I)4            /* locale info                     */
#define LPERMANENT      (I)8            // This is a permanent entry in a local symbol table; don't delete, just leave val=0


typedef struct{A og,g;I ptr,flag;B sw0;} LS;

/* og:   old value of global                                               */
/* g:    global at this level                                              */
/* ptr:  index in pv/nv if numbered locale                                 */
/*       pointer to stloc entry if named locale                            */
/* flag: 1 if named    locale marked for destruction                       */
/*       2 if numbered locale marked for destruction                       */
/* sw0:  old value of stswitched                                           */


typedef struct{UI hash;I4 bucket;I4 bucketx;UC m;C flag,s[1];} NM;

/* hash: hash for  non-locale part of name                                 */
// bucket: (for local simple names) the index of the hash chain for this symbol when viewed as a local
//   0 if chain index not known
// bucketx: (for local simple names, only if bucket!=0) the number of chain entries to discard before
//   starting name search.  If negative, use one's complement and do not bother with name search - symbol-table entry
//   is guaranteed to be at that position  
// m:    length of non-locale part of name note 255-byte limit!
// sn:   symbol table number on last reference  no longer used
// e:    symbol pool entry   on last reference  no longer used
/* s:    string part of full name (1 to ?? characters, including locale of assignment if given)           */

#define NMLOC           1       /* direct   locale abc_lm_                 */
#define NMILOC          2       /* indirect locale abc__de__fgh ...        */
#define NMDOT           4       /* one of the names m. n. u. v. x. y.      */


typedef struct {I a,e,i,x;} P;

/* value fields of sparse array types                                      */
/* fields are offsets from beginning of the P struct                       */
/* a: sparse axes                                                          */
/* e: sparse element                                                       */
/* i: index matrix, columns correspond to a                                */
/* x: value cells corresponding to rows of i                               */

#define SPA(p,a)        ((A)((p)->a+(C*)(p)))  // a is one of aeix; result is A pointer for that component
// obsolete #define SPB(p,a,x)      {(p)->a=(C*)(x)-(C*)(p); RZ((p)->a+(C*)(p));}  // store x into component (a); return if x is 0.  a is one of aeix
// obsolete #define SPB(p,a,x)      {A ZWo = (x); if(ZWo){INCORP(ZWo)} (p)->a=(C*)ZWo-(C*)(p); RZ(ZWo);}  // store x into component (a); return if x is 0.  a is one of aeix
#define SPBV(p,a,v,x)      {RZ(v = (x)); INCORP(v); (p)->a=(C*)v-(C*)(p);}  // store x into component (a); return if x is 0.  a is one of aeix.  Result in v
#define SPB(p,ZWa,x)      {A ZWo = (x); SPBV((p),ZWa,ZWo,(x))}  // store x into component (a); return if x is 0.  a is one of aeix

// Header for hashtables used in i.
// This sits at the beginning of the allocated block, holding info about the stored values
typedef struct {
 I datasize;   // number of bytes in the data area
 I hashelelgsize;  // lg(size of a hashed element)
 UI currentlo;   // the lowest position in the hashtable of the current allocation.
 UI currenthi;   // the highest position+1 of the current allocation.
 UI currentindexofst;   // the value in the hashtable that the minimum value in the input will map to
 UI currentindexend;    // the highest value that can possibly be written, +1
 UI previousindexend;  // All positions from 0 to currenthi are known to be less than currentindexend.
             // Positions from currenthi to the end are known to be less than previousindexend.
 UI invalidlo;   // the start of the area that does not have constrained values because it was used for a bit table (as an index into hashtable, rounded up to multiple of I for endian reasons)
 UI invalidhi;   // the end+1 of the area used for a bit table  (as an index into hash table, rounded up to multiple of I)
 I datamin;  // (for small-range use) minimum value in the data
 UI datarange;  // (for small-range use) range+1 of the data
 // 11 words here; 7 words of header (we allocate no shape); 2 words of memory-allocation header; so this block is 20 words after the
 // memory allocation, and thus is on the same 256-bit boundary as the allocation.
 union {   // We index into the data with varying strides, depending on the range of the data
  UC UC[1];  // cannot have union of 
  US US[1];
  UI4 UI4[1];
  UI UI[1];
 } data;
} IH;
#define IHAV(x)         ((IH*)((C*)(x)+AK(x)))  //  how to refer to the header area

// Return value from condrange
typedef struct {
 I min;  // smallest value found
 I range;  // max+1-min, or 0 if range exceeds max given
} CR;

/* performance monitoring stuff */

typedef struct{
 A name;                /* verb/adverb/conjunction name                    */
 A loc;                 /* locale name                                     */
 I lc;                  /* line number (-1 for entry; -2 for exit)         */
 I s;                   /* space                                           */
 I t[2];                /* time                                            */
 C val;                 /* valence: 1 or 2                                 */
 C unused[3];           /* padding                                         */
} PM;

#define PMCOL  6        /* # of fields in PM                               */

typedef struct{
 I n;                   /* maximum number of records                       */
 I i;                   /* index of next record to be written              */
 I s;                   /* initial bytesmax value                          */
 B rec;                 /* what to record (0 entry & exit; 1 all)          */
 B trunc;               /* what to do on overflow (0 wrap; 1 truncate)     */
 B wrapped;             /* 1 iff wrapping has happened                     */
 C unused[1];           /* padding                                         */
} PM0;


/* each unique symbol has a row in jt->sbu                                 */
/* a row is interpreted per SBU                                            */
/* for best results make sizeof(SBU) a multiple of sizeof(I)               */
 
typedef struct{
 I  i;                  /* index into sbs                                  */
 I  n;                  /* length                                          */
 UI h;                  /* hash value                                      */
 I  color;              /* binary tree: color                              */
 I  parent;             /* binary tree: index of parent                    */
 I  left;               /* binary tree: index of left  child               */
 I  right;              /* binary tree: index of right child               */
 I  order;              /* order number                                    */
 I  down;               /* predecessor in ordering                         */
 I  up;                 /* successor   in ordering                         */
 I  flag;               /* bit flags                                       */
} SBU;

#define SBC2  1         /* 1 iff 2-byte character                          */
#define SBC4  2         /* 2 iff 4-byte character                          */



typedef struct {AF f1,f2;A f,g,h;I flag; UI4 fdep; UI4 flag2; RANKT mr,lr,rr; C id;} V;

#define ID(f)           (f&&FUNC&AT(f)?VAV(f)->id:C0)
#define VFLAGNONE 0L
#define VRTNNONE ((A)0)
  
                                        /* type V flag values              */
// bits 0-7 are used in comparison compounds to encode the type of compound, see vcompsc.c
// for other types, they are defined as follows:
#define VFATOPL          JTINPLACEW     // (in forks and v0`v1`v2) f/v0 is x@[, so OK to inplace w arg of h
#define VFATOPR          JTINPLACEA     // (in forks and v0`v1`v2) f/v0 is x@], so OK to inplace a arg of h
// bits 8 and above are available for all functions:
#define VGERL           (I)256          /* gerund left  argument           */
#define VGERR           (I)512          /* gerund right argument           */
#define VTAYFINITE      (I)1024         /* t. finite polynomial            */
#define VIRS1           (I)2048         /* 11 monad has integral rank support */
#define VIRS2           (I)4096         /* 12 dyad  has integral rank support */
#define VFLR            (I)8192         /* function is <.@g                */
#define VCEIL           (I)16384        /* function is >.@g                */
#define VMOD            (I)32768        /* function is m&|@g               */
#define VLOCK           (I)65536        /* function is locked              */
#define VNAMED          (I)131072       /* named explicit defn             */
#define VFIX            (I)262144       /* f. applied                      */
#define VXOPR           (I)524288       /* : defn with u. and x.           */
#define VXOP            (I)1048576      /* : defn derived fn               */
#define VXOPCALL        (I)2097152      /* : defn derived fn call          */
#define VTRY1           (I)4194304      /* monad contains try.             */
#define VTRY2           (I)8388608      /* dyad  contains try.             */
#define VDDOP           (I)16777216     /* 24 derived from a derived operator */
#define VINPLACEOK1     (I)33554432L    // 25 monad can handle in-place args
#define VINPLACEOK2     (I)67108864LL    // 26 dyad can handle in-place args
#define VASGSAFE        ((I)(1L<<27))     // does not alter locale/path
#define VISATOMIC1      ((I)(1L<<28))     // processes each atom individually (logically rank 0, but handles all ranks)

// bits in flag2:
#define VF2RANKONLY1X     0   // set if this verb is u"r, not special-cased (i. e. function points to rank processing).  The rank may be subsumed into a higher rank before we see arguments
#define VF2RANKONLY1     ((I)(1LL<<VF2RANKONLY1X)) 
#define VF2RANKONLY2X     1
#define VF2RANKONLY2     ((I)(1LL<<VF2RANKONLY2X))
#define VF2RANKATOP1X     2   // set if this verb starts out with rank loop and thus can be subsumed into a higher rank loop
#define VF2RANKATOP1     ((I)(1LL<<VF2RANKATOP1X)) 
#define VF2RANKATOP2X     3   // set if this verb starts out with an outer rank loop.  " @ & &. and not special-cased
#define VF2RANKATOP2     ((I)(1LL<<VF2RANKATOP2X))
#define VF2BOXATOP1X      4   // (in u"v)  u was <@f or <&f, and f[12] point to f (i. e. monad)
#define VF2BOXATOP1     ((I)(1LL<<VF2BOXATOP1X))   // (in u"v)  u was <@f or <&f, and f[12] point to f (i. e. monad)
#define VF2BOXATOP2X      5   // (in u"v)  u was <@f or <&f, and f[12] point to f (i. e. monad)
#define VF2BOXATOP2     ((I)(1LL<<VF2BOXATOP2X))   // (in u"v)  u was <@f or <&f, and f[12] point to f (i. e. monad)
#define VF2ISCCAPX        6   // flags (if any) came from ([: g h) rather than f@:g
#define VF2ISCCAP       ((I)(1LL<<VF2ISCCAPX))
#define VF2WILLBEOPENEDX  7   // The result of this verb will be immediately opened (by > or ;)
#define VF2WILLBEOPENED   ((I)(1LL<<VF2WILLBEOPENEDX))




typedef struct {DX re;DX im;} ZX;

/* extended complex                                                        */
/* re - real part                                                          */
/* im - imaginary part                                                     */


// parser stack
typedef struct {
 A a;  // pointer to block
 I t;  // token number for this block
} PSTK;
