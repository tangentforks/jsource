/* Copyright 1990-2006, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Adverbs: Utilities                                                      */

#include "j.h"


static I jtfdepger(J jt,A w){A*wv;I d=0,k; 
 wv=AAV(w); RELBASEASGN(w,w); 
 DO(AN(w), k=fdep(fx(WVR(i))); d=MAX(d,k);); 
 R d;
}

I jtfdep(J jt,A w){A f,g;I d=0,k;V*v;
 RZ(w);
 v=VAV(w);
 if(v->fdep)R v->fdep;  // for speed, use previous value if it has been calculated
 if(f=v->f) d=VERB&AT(f)?fdep(f):NOUN&AT(f)&&VGERL&v->flag?fdepger(f):0;
 if(g=v->g){k=VERB&AT(g)?fdep(g):NOUN&AT(g)&&VGERR&v->flag?fdepger(g):0; d=MAX(d,k);}
 if(CFORK==v->id){k=fdep(v->h); d=MAX(d,k);}
 if(!jt->jerr)v->fdep=(UI4)(1+d);  //Save computed value for next time, but not if error; that would lose the error next time
 R 1+d;
}    /* function depth:  1 + max depth of components */

F1(jtfdepadv){RZ(w); ASSERT(VERB&AT(w),EVDOMAIN); R sc(fdep(w));}

// jtdf1 and jtdf2 can be called with or without inplace flags since they don't use jt but merely pass it through
DF1(jtdf1){RZ(self); R CALL1(VAV(self)->f1,  w,self);}
DF2(jtdf2){RZ(self); R CALL2(VAV(self)->f2,a,w,self);}

DF1(jtdfs1){F1PREFIP;A s=jt->sf,z; RZ(self); z=CALL1IP(VAV(self)->f1,  w,jt->sf=self); jt->sf=s; RETF(z);}
DF2(jtdfs2){F2PREFIP;
A s=jt->sf,z; 
RZ(self); 
z=CALL2IP(VAV(self)->f2,a,w,jt->sf=self); jt->sf=s; 
RETF(z);}    
     /* for monads and dyads that can possibly involve $: */

A jtdfss1(J jt, A w, A self, A self0)     {RZ(self); R CALL1(VAV(self)->f1,  w,self0);}
A jtdfss2(J jt, A a, A w, A self, A self0){RZ(self); R CALL2(VAV(self)->f2,a,w,self0);}
     // used to treat self as an argument.  Used with routines that don't really use self

F1(jtself1){A z;I d=fdep(jt->sf); FDEPINC(d); z=df1(  w,jt->sf); FDEPDEC(d); RETF(z);}
F2(jtself2){A z;I d=fdep(jt->sf); FDEPINC(d); z=df2(a,w,jt->sf); FDEPDEC(d); RETF(z);}

A jtac1(J jt,AF f){R fdef(0,0,VERB, f,0L, 0L,0L,0L, VFLAGNONE, RMAX,RMAX,RMAX);}
A jtac2(J jt,AF f){R fdef(0,0,VERB, 0L,f, 0L,0L,0L, VFLAGNONE, RMAX,RMAX,RMAX);}

F1(jtdomainerr1){ASSERT(0,EVDOMAIN);}
F2(jtdomainerr2){ASSERT(0,EVDOMAIN);}

// create a block for a function (verb/adv/conj).  The meanings of all fields depend on the function executed in f1/f2
// if there has been a previous error this function returns 0
A jtfdef(J jt,I flag2,C id,I t,AF f1,AF f2,A fs,A gs,A hs,I flag,I m,I l,I r){A z;V*v;
 RE(0);
 GA(z,t,1,0,0); v=VAV(z);
 if(fs)INCORP(fs); if(gs)INCORP(gs); if(hs)INCORP(hs);   // indicate fgh are about to be incorporated
 v->f1    =f1?f1:jtdomainerr1;  /* monad C function */
 v->f2    =f2?f2:jtdomainerr2;  /* dyad  C function */
 v->f     =fs;                  /* monad            */
 v->g     =gs;                  /* dyad             */      
 v->h     =hs;                  /* fork right tine or other auxiliary stuff */
 v->flag  =(UI4)flag;
 v->mr    =(RANKT)m;                   /* monadic rank     */
 v->lr    =(RANKT)l;                   /* left    rank     */
 v->rr    =(RANKT)r;                   /* right   rank     */
 v->fdep  =0;                   /* function depth   */
 v->id    =(C)id;                  /* spelling         */
 v->flag2 = (UI4)flag2;         // more flags
 R z;
}

B nameless(A w){A f,g,h;C id;V*v;
 if(!w||NOUN&AT(w))R 1;
 v=VAV(w);
 id=v->id; f=v->f; g=v->g; h=v->h;
 R !(id==CTILDE&&NAME&AT(f)) && nameless(f) && nameless(g) && (id==CFORK?nameless(h):1);
}

B jtprimitive(J jt,A w){A x=w;V*v;
 RZ(w);
 v=VAV(w);
 if(CTILDE==v->id&&NOUN&AT(v->f))RZ(x=fix(w));
 R!VAV(x)->f;
}    /* 1 iff w is a primitive */


// w is a conj, f C n
// Return 1 if f is of the form <@:g  (or <@g when g has infinite rank)
B jtboxatop(J jt,A w){RZ(w); R 1&boxat(VAV(w)->f,RMAX,RMAX,RMAX);}

// x is a verb
// Return if verb is of the form <@:g  (or <@g when g has rank >= input rank)
// bit 0 for monad case, bit 1 for dyad
I boxat(A x, I m, I l, I r){C c;V*v;
 if(!x)R 0;
 v=VAV(x); c=v->id;   // x->f, v->value, c=id of f
 if(!COMPOSE(c))R 0;  // Return if not @ @: & &:
 if(CBOX==ID(v->f)) {  // if u is <...
   if(c==CATCO) R 3; if(c==CAMPCO) R 1;  // @: is always good, and &: for monad
   I res = 0;
   if(v->g&&VERB&AT(v->g)){
    res |= VAV(v->g)->mr>=m;    // monad ok if rank big enough  for either @ or &
    res |= (c==CAT)&&VAV(v->g)->lr>=l&&VAV(v->g)->rr>=r?2:0;  // dyad for @ only, if rank big enough
   }
   R res;
 }
 R 0; 
}    /* 1 iff "last" function in w is <@f */

// w is a verb
// Result has bit 0 set if the verb is [ or ...@[, bit 1 set if ] or ...@]   (or @:)
// The set bit indicates that argument WILL NOT be examined when w is executed
I atoplr(A w){
 if(!w)R 0;
 V *v=VAV(w);     // v->verb info, c=id of w
 C id = v->id;if(v->id==CAT||v->id==CATCO)id = VAV(v->g)->id;
 switch(id){
  case CLEFT: R JTINPLACEW;   // ...@[  ok to inplace W
  case CRIGHT: R JTINPLACEA;   // ...@]  ok to inplace A
 }
 R 0;   // both args in use
}