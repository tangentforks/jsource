1:@:(echo^:ECHOFILENAME) './gsp110.ijs'
NB. * -------------------------------------------------------------------

f=: 3 : '(*./scheck q) *. (*xx) -: q=. *s=: (2;y)$.xx'

f&> c=: ; (i.1+r) <"1@comb&.>r=:#$xx=:     _10+?    405$2
f&> c=: ; (i.1+r) <"1@comb&.>r=:#$xx=:     _10+?  3 4 5$21
f&> c=: ; (i.1+r) <"1@comb&.>r=:#$xx=:   o._10+?  3 4 5$21
f&> c=: ; (i.1+r) <"1@comb&.>r=:#$xx=:j./o._10+?2 3 4 5$21

f&> c=: ; (i.1+r) <"1@comb&.>r=:#$xx=: (_10+?60$21),<.-2^31

0 -: 3 $. * $. 0 1 0
0 -: 3 $. * $. 2 3 4
0 -: 3 $. * $. 2 3.4
0 -: 3 $. * $. 2 3j4

f=: 4 : '(p*q) -: ((2;x)$.p) * (2;y)$.q'
g=: 3 : '(p*a) -: ((2;y)$.p) * a'

p=: (?7 5$2) * ?7 5 3$10
q=: (?7 5$2) * ?7 5 3$10
a=: ?2
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c
g&>c

p=: (?4 2 5$2) * ?4 2 5 3$4
q=: (?4 2 5$2) * ?4 2 5 3$4
a=: ?2e6
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c
g&>c

p=: (?4 2 5$2) * ?4 2 5 3$4e7
q=: (?4 2 5$2) * ?4 2 5 3$4e7
a=: ?2e6
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c
g&>c

p=: (?4 2 5$2) * o.?4 2 5 3$4
q=: (?4 2 5$2) * o.?4 2 5 3$4
a=: ?2e6
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c
g&>c

p=: (?4 5$2) * j./?2 4 5 3$4
q=: (?4 5$2) * j./?2 4 5 3$4
a=: j./?2e6 2e6
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c
g&>c

f=: 4 : 0
 s=: (2;x)$.xx
 t=: (2;y)$.yy
 q=. s *"2 t
 (q-: xx*"2 yy) *. *./scheck q
)

c=: ; (i.1+r) <"1@comb&.>r=:4
d=: ; (i.1+r) <"1@comb&.>r=:3

xx=: (?5 4 3$2) * ?5 4 3 6$100
yy=: (?5   3$2) * ?5   3 6$100
c f&>/d

xx=: (?5 4 3$2) * ?5 4 3 6$100
yy=: ( 5   3$0) * ?5   3 6$100
c f&>/d

xx=: ( 5 4 3$0) * ?5 4 3 6$100
yy=: (?5   3$2) * ?5   3 6$100
c f&>/d

xx=: ( 5 4 3$0) * ?5 4 3 6$100
yy=: ( 5   3$0) * ?5   3 6$100
c f&>/d

xx=: (?5   3$2) * ?5   3 6$100
yy=: (?5 4 3$2) * ?5 4 3 6$100
d f&>/c

xx=: (?5   3$2) * ?5   3 6$100
yy=: ( 5 4 3$0) * ?5 4 3 6$100
d f&>/c

xx=: ( 5   3$0) * ?5   3 6$100
yy=: (?5 4 3$2) * ?5 4 3 6$100
d f&>/c

xx=: ( 5   3$0) * ?5   3 6$100
yy=: ( 5 4 3$0) * ?5 4 3 6$100
d f&>/c


4!:55 ;:'a c d f g p q r s t xx yy'


