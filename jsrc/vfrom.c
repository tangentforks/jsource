/* Copyright 1990-2007, Jsoftware Inc.  All rights reserved.               */
/* Licensed use only. Any other use is in violation of copyright.          */
/*                                                                         */
/* Verbs: From & Associates. See Hui, Some Uses of { and }, APL87.         */

#include "j.h"


F1(jtcatalog){PROLOG(0072);A b,*wv,x,z,*zv;C*bu,*bv,**pv;I*cv,i,j,k,m=1,n,p,*qv,r=0,*s,t=0,*u;
 F1RANK(1,jtcatalog,0);
 if(!(AN(w)&&AT(w)&BOX+SBOX))R box(w);
 n=AN(w); wv=AAV(w); RELBASEASGN(w,w);
 DO(n, x=WVR(i); if(AN(x)){p=AT(x); t=t?t:p; ASSERT(HOMO(t,p),EVDOMAIN); RE(t=maxtype(t,p));});
 RE(t=maxtype(B01,t)); k=bp(t);
 GA(b,t,n,1,0);      bv=CAV(b);
 GATV(x,INT,n,1,0);    qv=AV(x);
 GATV(x,BOX,n,1,0);    pv=(C**)AV(x);
 RZ(x=apv(n,0L,0L)); cv=AV(x);
 DO(n, x=WVR(i); if(TYPESNE(t,AT(x)))RZ(x=cvt(t,x)); r+=AR(x); qv[i]=p=AN(x); RE(m=mult(m,p)); pv[i]=CAV(x););
 GATV(z,BOX,m,r,0);    zv=AAV(z); s=AS(z); 
 DO(n, x=WVR(i); u=AS(x); DO(AR(x),*s++=*u++;););
 for(i=0;i<m;i++){
  bu=bv-k;
  DO(n, MC(bu+=k,pv[i]+k*cv[i],k););
  DO(n, j=n-1-i; if(qv[j]>++cv[j])break; cv[j]=0;);
  RZ(*zv++=ca(b));
 }
 EPILOG(z);
}

#define SETJ(jexp)    {j=(jexp); if(0<=j)ASSERT(j<p,EVINDEX) else{j+=p; ASSERT(0<=j,EVINDEX);}}

#define IFROMLOOP(T)        \
 {T   * RESTRICT v=(T*)wv,* RESTRICT x=(T*)zv;  \
  if(1==an){v+=j;   DO(m,                                    *x++=*v;       v+=p; );}  \
  else              DO(m, DO(an, SETJ(av[i]);                *x++=v[j];);   v+=p; );   \
 }
#define IFROMLOOP2(T,qexp)  \
 {T* RESTRICT u,* RESTRICT v=(T*)wv,* RESTRICT x=(T*)zv;  \
  q=(qexp); pq=p*q;         \
  if(1==an){v+=j*q; DO(m,                     u=v;     DO(q, *x++=*u++;);   v+=pq;);}  \
  else              DO(m, DO(an, SETJ(av[i]); u=v+j*q; DO(q, *x++=*u++;);); v+=pq;);   \
 }

F2(jtifrom){A z;C*wv,*zv;I acr,an,ar,*av,j,k,m,p,pq,q,*s,wcr,wf,wk,wn,wr,*ws,zn;
 F1PREFIP;
 RZ(a&&w);
 // This routine is implemented as if it had infinite rank: if no rank is specified, it operates on the entire
 // a (and w).  This has implications for empty arguments.
 ar=AR(a); acr=jt->rank?jt->rank[0]:ar;
 wr=AR(w); wcr=jt->rank?jt->rank[1]:wr; wf=wr-wcr; jt->rank=0;
 if(ar>acr)R rank2ex(a,w,0L,acr,wcr,acr,wcr,jtifrom);  // split a into cells if needed.  Only 1 level of rank loop is used
 // From here on, execution on a single cell of a (on a matching cell of w, or all w).  The cell of a may have any rank
 an=AN(a); wn=AN(w); ws=AS(w);
 if(!(INT&AT(a)))RZ(a=cvt(INT,a));
 // If a is empty, it needs to simulate execution on a cell of fills.  But that might produce error, if w has no
 // items, where 0 { empty is an index error!  In that case, we set wr to 0, in effect making it an atom (since failing exec on fill-cell produces atomic result)
// if(an==0 && wn==0 && ws[wf]==0)wcr=wr=0;     defer this pending analysis
 // If w is empty, portions of its shape may overflow during calculations, and there is no data to move (we still need to
 // audit for index error, though).  If w is not empty, there is no need to check for such overflow.  So we split the computation here.
 // Either way, we need   zn: #atoms in result   p: #items in a cell of w
 p=wcr?*(ws+wf):1;
 av=AV(a);  // point to the selectors
 I wflag=AFLAG(w);
 if(wn){
  // For virtual results we need: kn: number of atoms in an item of a cell of w;   
  PROD(k, wcr-1, ws+wf+1);  // number of atoms in an item of a cell
  // Also  m: #cells in w 
  PROD(m,wf,ws); zn=k*m;  RE(zn=mult(an,zn));
  if((zn>1)&&!(wf|(wflag&(AFSMM|AFNJA)))){
   // result is more than one atom and does not come from multiple cells.  Perhaps it should be virtual.  See if the indexes are consecutive
   I index0 = av[0]; index0+=(index0>>(BW-1))&p;  // index of first item
   // check the last item before checking the middle.
   I indexn = av[an-1]; indexn+=(indexn>>(BW-1))&p;
   if(indexn==index0+an-1){
     I indexp=index0; DO(an-1, indexn=av[1+i]; indexn+=(indexn>>(BW-1))&p; if(indexn!=indexp+1){indexn=p; break;} indexp=indexn;);
   }else indexn=p;
   if((index0|(p-indexn-1))>=0){  // index0>0 and indexn<=p-1
    // indexes are consecutive and in range.  Make the result virtual.  Rank of w cell must be > 0, since we have >=2 consecutive result atoms
    RZ(z=virtualip(w,index0*k,ar+wr-1));
    // fill in shape and number of atoms.  ar can be anything
    I* as=AS(a); AN(z)=zn; s=AS(z); DO(ar, *s++=as[i];) DO(wr-1, s[i]=ws[i+1];)
    RETF(z);
   }
  }
  // for copying items, we need    k: size in bytes of an item of a cell of w
  k*=bp(AT(w));
 } else {zn=0;}  // No data to move
 // Allocate the result area and fill in the shape
 GA(z,AT(w),zn,ar+wr-(0<wcr),ws);  // result-shape is frame of w followed by shape of a followed by shape of item of cell of w; start with w-shape, which gets the frame
 s=AS(z); ICPY(s+wf,AS(a),ar); if(wcr)ICPY(s+wf+ar,1+wf+ws,wcr-1);
 if(!zn){DO(an, SETJ(av[i])) R z;}  // If no data to move, just audit the indexes and quit
 // from here on we are moving items
 wk=k*p;   // stride between cells of w
 wv=CAV(w); zv=CAV(z); SETJ(*av);
 if(AT(w)&FL+CMPX){if(k==sizeof(D))IFROMLOOP(D) else IFROMLOOP2(D,k/sizeof(D));}
 else switch(k){
  case sizeof(C): IFROMLOOP(C); break; 
  case sizeof(S): IFROMLOOP(S); break;  
#if SY_64
  case sizeof(int):IFROMLOOP(int); break;
#endif
  case sizeof(I): IFROMLOOP(I); break;
  default:
   if     (0==k%sizeof(I))IFROMLOOP2(I,k/sizeof(I))
#if SY_64
   else if(0==k%sizeof(int))IFROMLOOP2(int,k/sizeof(int))
#endif
   else if(0==k%sizeof(S))IFROMLOOP2(S,k/sizeof(S))
   else{S*x,*u;
    q=1+k/sizeof(S);
    if(1==an){wv+=k*j; DO(m,                     x=(S*)zv; u=(S*) wv;      DO(q, *x++=*u++;); zv+=k;   wv+=wk;);}
    else               DO(m, DO(an, SETJ(av[i]); x=(S*)zv; u=(S*)(wv+k*j); DO(q, *x++=*u++;); zv+=k;); wv+=wk;);
  }
 }
 RELOCATE(w,z); RETF(z);  // todo kludge should inherit norel
}    /* a{"r w for numeric a */

#define BSET(x,y0,y1,y2,y3)     *x++=y0; *x++=y1; *x++=y2; *x++=y3;
#define BSETV(b)                MC(v,wv+b*k,k); v+=k;

#if !SY_64 && SY_WIN32
#define BNNERN(T)   \
 {B*au=av;T*v=(T*)wv,v0,v1,*x=(T*)zv;                                               \
  DO(m, v0=v[0]; v1=v[1]; u=(I*)av; DO(q, switch(*u++){                             \
   case B0000: BSET(x,v0,v0,v0,v0); break;  case B0001: BSET(x,v0,v0,v0,v1); break; \
   case B0010: BSET(x,v0,v0,v1,v0); break;  case B0011: BSET(x,v0,v0,v1,v1); break; \
   case B0100: BSET(x,v0,v1,v0,v0); break;  case B0101: BSET(x,v0,v1,v0,v1); break; \
   case B0110: BSET(x,v0,v1,v1,v0); break;  case B0111: BSET(x,v0,v1,v1,v1); break; \
   case B1000: BSET(x,v1,v0,v0,v0); break;  case B1001: BSET(x,v1,v0,v0,v1); break; \
   case B1010: BSET(x,v1,v0,v1,v0); break;  case B1011: BSET(x,v1,v0,v1,v1); break; \
   case B1100: BSET(x,v1,v1,v0,v0); break;  case B1101: BSET(x,v1,v1,v0,v1); break; \
   case B1110: BSET(x,v1,v1,v1,v0); break;  case B1111: BSET(x,v1,v1,v1,v1); break; \
  });                                                                               \
  b=(B*)u; DO(r, *x++=*b++?v1:v0;); v+=p;);                                         \
 }
#define BNNERM(T,T1)   \
 {B*au=av;T*c,*v=(T*)wv,v0,v1,*x=(T*)zv;T1 vv[16],*y;                                  \
  DO(m, v0=v[0]; v1=v[1]; c=(T*)vv; y=(T1*)x; u=(I*)av;                                \
   BSET(c,v0,v0,v0,v0); BSET(c,v0,v0,v0,v1); BSET(c,v0,v0,v1,v0); BSET(c,v0,v0,v1,v1); \
   BSET(c,v0,v1,v0,v0); BSET(c,v0,v1,v0,v1); BSET(c,v0,v1,v1,v0); BSET(c,v0,v1,v1,v1); \
   BSET(c,v1,v0,v0,v0); BSET(c,v1,v0,v0,v1); BSET(c,v1,v0,v1,v0); BSET(c,v1,v0,v1,v1); \
   BSET(c,v1,v1,v0,v0); BSET(c,v1,v1,v0,v1); BSET(c,v1,v1,v1,v0); BSET(c,v1,v1,v1,v1); \
   DO(q, switch(*u++){                                                                 \
    case B0000: *y++=vv[ 0]; break;  case B0001: *y++=vv[ 1]; break;                   \
    case B0010: *y++=vv[ 2]; break;  case B0011: *y++=vv[ 3]; break;                   \
    case B0100: *y++=vv[ 4]; break;  case B0101: *y++=vv[ 5]; break;                   \
    case B0110: *y++=vv[ 6]; break;  case B0111: *y++=vv[ 7]; break;                   \
    case B1000: *y++=vv[ 8]; break;  case B1001: *y++=vv[ 9]; break;                   \
    case B1010: *y++=vv[10]; break;  case B1011: *y++=vv[11]; break;                   \
    case B1100: *y++=vv[12]; break;  case B1101: *y++=vv[13]; break;                   \
    case B1110: *y++=vv[14]; break;  case B1111: *y++=vv[15]; break;                   \
   });                                                                                 \
   b=(B*)u; x=(T*)y; DO(r, *x++=*b++?v1:v0;); v+=p;);                                  \
 }
#else
#define BNNERN(T)       {T*v=(T*)wv,*x=(T*)zv; DO(m, b=av; DO(an, *x++=*(v+*b++);); v+=p;);}
#define BNNERM(T,T1)    BNNERN(T)
#endif

#define INNER1B(T)  {T*v=(T*)wv,*x=(T*)zv; v+=*av; DO(m, *x++=*v; v+=p;);}

// a is boolean
static F2(jtbfrom){A z;B*av,*b;C*wv,*zv;I acr,an,ar,k,m,p,q,r,*s,*u=0,wcr,wf,wk,wn,wr,*ws,zn;
 RZ(a&&w);
 ar=AR(a); acr=jt->rank?jt->rank[0]:ar;
 wr=AR(w); wcr=jt->rank?jt->rank[1]:wr; wf=wr-wcr; jt->rank=0;
 if(ar>acr)R rank2ex(a,w,0L,acr,wcr,acr,wcr,jtbfrom);
 an=AN(a); wn=AN(w); ws=AS(w);
 // If a is empty, it needs to simulate execution on a cell of fills.  But that might produce domain error, if w has no
 // items, where 0 { empty is an index error!  In that case, we set wr to 0, in effect making it an atom (since failing exec on fill-cell produces atomic result)
// if(an==0 && wn==0 && ws[wf]==0)wcr=wr=0;
 p=wcr?*(ws+wf):1; q=an>>LGSZI; r=an&(SZI-1);
 ASSERT(2<=p||1==p&&all0(a)||!p&&!an,EVINDEX);
 // We always need zn, the number of result atoms
 if(wn){
  // If there is data to move, we also need m: #cells of w   k: #bytes in an items of a cell of w   wk: #bytes in a cell of w
  PROD(m,wf,ws); PROD(k, wcr-1, ws+wf+1); zn=k*m; k*=bp(AT(w)); wk=k*p; RE(zn=mult(an,zn));
 }else{zn=0;}
 GA(z,AT(w),zn,ar+wr-(0<wcr),ws);
 s=AS(z); ICPY(s+wf,AS(a),ar); if(wcr)ICPY(s+wf+ar,1+wf+ws,wcr-1);
 if(!zn)R z;  // If no data to move, just return the shape
 av=BAV(a); wv=CAV(w); zv=CAV(z);
 switch(k+k+(1==an)){
  case   2*sizeof(I): BNNERN(I);   break;
  case   2*sizeof(C): BNNERM(C,I); break; 
  case 1+2*sizeof(C): INNER1B(C);  break;
  case 1+2*sizeof(S): INNER1B(S);  break;
#if SY_64
  case 1+2*sizeof(int): INNER1B(int);  break;
#endif
  case 1+2*sizeof(I): INNER1B(I);  break;
  default:
   if(1==an){wv+=k**av; DO(m, MC(zv,wv,k); zv+=k; wv+=wk;);}
#if !SY_64 && SY_WIN32
   else{A x;C*v,*xv,*xv00,*xv01,*xv02,*xv03,*xv04,*xv05,*xv06,*xv07,*xv08,*xv09,*xv10,*xv11,
         *xv12,*xv13,*xv14,*xv15;I i,j,k4=k*4;
    GATV(x,LIT,16*k4,1,0); xv=CAV(x);
    xv00=xv;       xv01=xv+   k4; xv02=xv+ 2*k4; xv03=xv+ 3*k4;
    xv04=xv+ 4*k4; xv05=xv+ 5*k4; xv06=xv+ 6*k4; xv07=xv+ 7*k4;
    xv08=xv+ 8*k4; xv09=xv+ 9*k4; xv10=xv+10*k4; xv11=xv+11*k4;
    xv12=xv+12*k4; xv13=xv+13*k4; xv14=xv+14*k4; xv15=xv+15*k4;
    for(i=0;i<m;++i){
     u=(I*)av; v=xv;
     BSETV(0); BSETV(0); BSETV(0); BSETV(0);   BSETV(0); BSETV(0); BSETV(0); BSETV(1);
     BSETV(0); BSETV(0); BSETV(1); BSETV(0);   BSETV(0); BSETV(0); BSETV(1); BSETV(1);
     BSETV(0); BSETV(1); BSETV(0); BSETV(0);   BSETV(0); BSETV(1); BSETV(0); BSETV(1);
     BSETV(0); BSETV(1); BSETV(1); BSETV(0);   BSETV(0); BSETV(1); BSETV(1); BSETV(1);
     BSETV(1); BSETV(0); BSETV(0); BSETV(0);   BSETV(1); BSETV(0); BSETV(0); BSETV(1);
     BSETV(1); BSETV(0); BSETV(1); BSETV(0);   BSETV(1); BSETV(0); BSETV(1); BSETV(1);
     BSETV(1); BSETV(1); BSETV(0); BSETV(0);   BSETV(1); BSETV(1); BSETV(0); BSETV(1);
     BSETV(1); BSETV(1); BSETV(1); BSETV(0);   BSETV(1); BSETV(1); BSETV(1); BSETV(1);
     for(j=0;j<q;++j,zv+=k4)switch(*u++){
      case B0000: MC(zv,xv00,k4); break;   case B0001: MC(zv,xv01,k4); break;
      case B0010: MC(zv,xv02,k4); break;   case B0011: MC(zv,xv03,k4); break;  
      case B0100: MC(zv,xv04,k4); break;   case B0101: MC(zv,xv05,k4); break;
      case B0110: MC(zv,xv06,k4); break;   case B0111: MC(zv,xv07,k4); break;
      case B1000: MC(zv,xv08,k4); break;   case B1001: MC(zv,xv09,k4); break;
      case B1010: MC(zv,xv10,k4); break;   case B1011: MC(zv,xv11,k4); break;
      case B1100: MC(zv,xv12,k4); break;   case B1101: MC(zv,xv13,k4); break;
      case B1110: MC(zv,xv14,k4); break;   case B1111: MC(zv,xv15,k4); break;
     }
     b=(B*)u; DO(r, MC(zv,wv+k**b++,k); zv+=k;); wv+=wk;
   }}
#else
   else DO(m, b=av; DO(an, MC(zv,wv+k**b++,k); zv+=k;); wv+=wk;);
#endif
 }
 RELOCATE(w,z); RETF(z);  // todo kludge should inherit norel
}    /* a{"r w for boolean a */

A jtfrombu(J jt,A a,A w,I wf){A p,q,z;B b=0;I ar,*as,h,m,r,*u,*v,wcr,wr,*ws;
 ar=AR(a); as=AS(a); h=as[ar-1];
 wr=AR(w); ws=AS(w); wcr=wr-wf;
 DO(ar, if(!as[i]){b=1; break;});
 DO(wr, if(!ws[i]){b=1; break;});
 if(b){
  GA(z,AT(w),0,wf+(wcr-h)+(ar-1),0); u=AS(z);
  v=ws;      DO(wf,    *u++=*v++;);
  v=as;      DO(ar-1,  *u++=*v++;);
  v=ws+wf+h; DO(wcr-h, *u++=*v++;);
  R z;
 } 
 GATV(p,INT,h,1,0); v=AV(p)+h; u=ws+wf+h; m=1; DO(h, *--v=m; m*=*--u;);
 r=wr+1-h;
 if(r==wr)
  z=irs2(pdt(a,p),w,VFLAGNONE, RMAX,wcr+1-h,jtifrom);
 else if(ARELATIVE(w)){
  GATV(q,INT,r,1,0); 
  v=AV(q); ICPY(v,ws,wf); *(v+wf)=m; ICPY(v+wf+1,ws+wf+h,wcr-h); RZ(q=reshape(q,w));
  z=irs2(pdt(a,p),q,VFLAGNONE, RMAX,wcr+1-h,jtifrom);
 }else{
  RZ(q=gah(r,w)); v=AS(q); ICPY(v,ws,wf); *(v+wf)=m; ICPY(v+wf+1,ws+wf+h,wcr-h);  /* q is reshape(.,w) */
  z=irs2(pdt(a,p),q,VFLAGNONE, RMAX,wcr+1-h,jtifrom);
 }
 RETF(z);
}    /* (<"1 a){"r w, dense w, integer array a */

B jtaindex(J jt,A a,A w,I wf,A*ind){A*av,q,z;I an,ar,c,j,k,t,*u,*v,*ws;
 RZ(a&&w);
 an=AN(a); *ind=0;
 if(!an)R 0;
 ws=wf+AS(w); ar=AR(a); av=AAV(a); RELBASEASGN(a,a); q=AVR(0); c=AN(q);
 if(!c)R 0;
 ASSERT(c<=AR(w)-wf,EVLENGTH);
 GATV(z,INT,an*c,1+ar,AS(a)); *(ar+AS(z))=c; v=AV(z);
 for(j=0;j<an;++j){
  q=AVR(j); t=AT(q);
  if(t&BOX)R 0;
  if(!(t&INT))RZ(q=cvt(INT,q));
  if(!(c==AN(q)&&1>=AR(q)))R 0; 
  u=AV(q);
  DO(c, k=u[i]; if(0>k)k+=ws[i]; ASSERT(0<=k&&k<ws[i],EVINDEX); *v++=k;);
 }
 *ind=z;
 R 1;
}    /* <"1 a to a where a is an integer index array */

static B jtaindex1(J jt,A a,A w,I wf,A*ind){A z;I c,k,n,t,*v,*ws;
 RZ(a&&w);
 n=AN(a); t=AT(a); *ind=0; if(AR(a)==0)R 0;  // revert to normal code for atomic a
 ws=wf+AS(w); c=*(AS(a)+AR(a)-1);   // c = length of 1-cell
 if(!n||!c||t&BOX)R 0;  // revert to normal code for empty or boxed a
 ASSERT(c<=AR(w)-wf,EVLENGTH);
 RZ(z=t&INT?ca(a):cvt(INT,a)); v=AV(z);
 DO(n/c, DO(c, k=*v; if(0>k)*v=k+=ws[i]; ASSERT(0<=k&&k<ws[i],EVINDEX); ++v;););  // convert indexes to nonnegative & check for in-range
 *ind=z;
 R 1;
}    /* verify that <"1 a is valid for (<"1 a){w */

static A jtafrom2(J jt,A p,A q,A w,I r){A z;C*wv,*zv;I d,e,j,k,m,n,pn,pr,* RESTRICT pv,
  qn,qr,* RESTRICT qv,* RESTRICT s,wf,wk,wr,* RESTRICT ws,zn;
 wr=AR(w); ws=AS(w); wf=wr-r; wk=bp(AT(w));
 pn=AN(p); pr=AR(p); pv=AV(p);
 qn=AN(q); qr=AR(q); qv=AV(q);
 if(AN(w)){
  // Set zn=#atoms of result  d=#atoms in a _2-cell of cell of w
  // e=length of axis corresponding to q  n=#_2-cells in a cell of w   m=#cells of w (frame*size of 2-cell*(# _2-cells = pn*qn))
  PROD(m,wf,ws); PROD(d,r-2,ws+wf+2); e=ws[1+wf]; n=e*ws[wf]; RE(zn=mult(pn,mult(qn,d*m)));
 }else{zn=0;}
 GA(z,AT(w),zn,wf+pr+qr+r-2,ws);
 s=AS(z)+wf; ICPY(s,AS(p),pr); 
 s+=pr;      ICPY(s,AS(q),qr);
 s+=qr;      ICPY(s,ws+wf+2,r-2);
 if(!zn)R z;  // If no data to move, exit with empty.  Rank is right
 wv=CAV(w); zv=CAV(z); 
 switch(k=d*wk){   // k=*bytes in a _2-cell of a cell of w
  default:        {C* RESTRICT v=wv,* RESTRICT x=zv-k;n=k*n;   // n=#bytes in a cell of w
   DO(m, DO(pn, j=e*pv[i]; DO(qn, MC(x+=k,v+k*(j+qv[i]),k);)); v+=n;); R z;}
#define INNER2(T) {T* RESTRICT v=(T*)wv,* RESTRICT x=(T*)zv;   \
   DO(m, DO(pn, j=e*pv[i]; DO(qn, *x++=v[j+qv[i]];         )); v+=n;); R z;}  // n=#_2-cells in a cell of w
  case sizeof(C): INNER2(C);
  case sizeof(S): INNER2(S);
#if SY_64
  case sizeof(int): INNER2(int);
#endif
  case sizeof(I): INNER2(I);
#if !SY_64 && SY_WIN32
  case sizeof(D): INNER2(D);
#endif
}}   /* (<p;q){"r w  for positive integer arrays p,q */

static A jtafi(J jt,I n,A w){A x;
 if(!(AN(w)&&BOX&AT(w)))R pind(n,w);
 ASSERT(!AR(w),EVINDEX);
 x=AAV0(w);
 R AN(x)?less(IX(n),pind(n,x)):ace; 
}

static F2(jtafrom){PROLOG(0073);A c,ind,p=0,q,*v,x,y=w;B b=1,bb=1;I acr,ar,i=0,j,k,m,n,pr,r,*s,t,wcr,wf,wr;
 RZ(a&&w);
 ar=AR(a); acr=  jt->rank?jt->rank[0]:ar;
 wr=AR(w); wcr=r=jt->rank?jt->rank[1]:wr; wf=wr-wcr; jt->rank=0;
 if(ar){
  if(ar==acr&&wr==wcr){RE(aindex(a,w,wf,&ind)); if(ind)R frombu(ind,w,wf);}
  R wr==wcr?rank2ex(a,w,0L,0L,wcr,0L,wcr,jtafrom):
      df2(rank1ex(a,0L,acr,jtbox),rank1ex(w,0L,wcr,jtbox),amp(ds(CLBRACE),ds(COPE)));
 }
 c=AAV0(a); t=AT(c); n=IC(c); v=AAV(c); RELBASEASGNB(c,c);  // B prob not reqd 
 k=bp(AT(w)); s=AS(w)+wr-r;
 ASSERT(1>=AR(c),EVRANK);
 ASSERT(n<=r,EVLENGTH);
 if(n&&!(t&BOX)){RE(aindex(a,w,wf,&ind)); if(ind)R frombu(ind,w,wf);}
 if(r==wr)for(i=m=pr=0;i<n;++i){
  p=afi(s[i],AADR(cd,v[i]));
  if(!(p&&1==AN(p)&&INT&AT(p)))break;
  pr+=AR(p); 
  m+=*AV(p)*prod(r-i-1,1+i+s);
 }
 if(i){I*ys;
  RZ(y=gah(pr+r-i,w)); ys=AS(y); DO(pr, *ys++=1;); ICPY(ys,s+i,r-i);
  /* obsolete AM(y)= */AN(y)=prod(AR(y),AS(y));
  AK(y)=k*m+CAV(w)-(C*)y;
 }
 for(;i<n;i+=2){
  j=1+i; if(!p)p=afi(s[i],AADR(cd,v[i])); q=j<n?afi(s[j],AADR(cd,v[j])):ace; if(!(p&&q))break;
  if(p!=ace&&q!=ace){b=0; y=afrom2(p,q,y,r-i);}
  else if(p!=ace)   {b=0; y=irs2(p,y,0L,AR(p),r-i,jtifrom);}
  else if(q!=ace)   {b=0; y=irs2(q,y,0L,AR(q),r-j,jtifrom);}
  p=0;
 }  // todo kludge should remove b and ca() which seems to be used only if out=in
 RE(y); if(b){RZ(y=ca(x=y)); RELOCATE(x,y);} EPILOG(y);    // todo kludge should inherit norel
}    /* a{"r w for boxed index a */

F2(jtfrom){I at;A z;
 F2PREFIP;
 RZ(a&&w);
 at=AT(a);
 switch((at&SPARSE?2:0)+(AT(w)&SPARSE?1:0)){
  case 0: z=at&BOX?afrom(a,w)  :at&B01&&AN(a)!=1?bfrom(a,w):jtifrom(jtinplace,a,w); break;  // make 0{ and 1{ allow virtual result
  case 1: z=at&BOX?frombs(a,w) :                  fromis(a,w); break;
  case 2: z=fromsd(a,w); break;
  default: z=fromss(a,w); break;
 }
 RZ(z); INHERITNOREL(z,w); RETF(z);
}   /* a{"r w main control */

F2(jtsfrom){A ind;
 RE(aindex1(a,w,0L,&ind));
 R !ind?from(irs1(a,0L,1L,jtbox),w):SPARSE&AT(w)?frombsn(ind,w,0L):frombu(ind,w,0L);
}    /* (<"1 a){w */

static F2(jtmapx){
 RZ(a&&w);
 if(!(BOX&AT(w)))R ope(a);
 R every2(box0(every2(a,box0(catalog(every(shape(w),0L,jtiota))),0L,jtover)),w,0L,jtmapx);
}

F1(jtmap){R mapx(ace,w);}

// extract the single box a from w and open it.  Don't mark it no-inplace.
static F2(jtquicksel){I index;
 RE(index=i0(a));  // extract the index
 if(index<0)index += AN(w); ASSERT(0<=index && index < AN(w),EVINDEX);   // remap negative index, check range
 R AAV(w)[index];  // select the box
}

F2(jtfetch){A*av, z;I n;
 F2RANK(1,RMAX,jtfetch,0);
 if(!(BOX&AT(a))){
  // look for the common special case scalar { boxed vector.  This path doesn't run EPILOG
  if(!AR(a) && AR(w)==1 && AT(w)&BOX && !ARELATIVEB(w)){
   RZ(z=jtquicksel(jt,a,w));
   if(!ACIPISOK(w))ACIPNO(z); RETF(z);   // Mark the box as non-inplaceable if the w argument is not inplaceable
  }
  RZ(a=box(a));  // if not special case, box any unboxed a
 }
 n=AN(a); av=AAV(a); RELBASEASGN(a,a);
 if(!n)R w; z=w;
 DO(n, A next=AVR(i); if(!AR(next) && !(AT(next)&BOX) && AR(z)==1 && AT(z)&BOX && !ARELATIVEB(z)){RZ(z=jtquicksel(jt,next,z))}
      else{RZ(z=afrom(box(next),z)); if(i<n-1)ASSERT(!AR(z),EVRANK); if(!AR(z)&&AT(z)&BOX)RZ(z=ope(z));}
   );
 if(!ACIPISOK(w))ACIPNO(z); RETF(z);   // Mark the box as non-inplaceable if the w argument is not inplaceable
}

