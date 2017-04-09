1:@:(echo^:ECHOFILENAME) './gsp2.ijs'
NB. ^ -------------------------------------------------------------------

(scheck ^ $.x), (^ -: ^&.$.) x=:     _10+?    405$2
(scheck ^ $.x), (^ -: ^&.$.) x=:     _10+?  3 4 5$21
(scheck ^ $.x), (^ -: ^&.$.) x=:   o._10+?  3 4 5$21
(scheck ^ $.x), (^ -: ^&.$.) x=:j./o._10+?2 3 4 5$21

1 -: 3 $. ^ $. 0 1 0
1 -: 3 $. ^ $. 2 3 4
1 -: 3 $. ^ $. 2 3.4
1 -: 3 $. ^ $. 2 3j4

f=: 4 : '(p^q) -: ((2;x)$.p) ^ (2;y)$.q'

p=: ?4 3 5 2$2
q=: ?4 3 5 2$2
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c

p=: ?4 3 5 2$4
q=: ?4 3 5 2$4
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c

p=: o.?3 5 2$4
q=: o.?3 5 2$4
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c

p=: j./?2 3 5 2$4
q=: j./?2 3 5 2$4
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c


NB. ^. ------------------------------------------------------------------

(scheck ^. $.x), (^. -: ^.&.$.) x=:     _10+?    405$2
(scheck ^. $.x), (^. -: ^.&.$.) x=:     _10+?  3 4 5$21
(scheck ^. $.x), (^. -: ^.&.$.) x=:   o._10+?  3 4 5$21
(scheck ^. $.x), (^. -: ^.&.$.) x=:j./o._10+?2 3 4 5$21

__ -: 3 $. ^. $. 0 1 0
__ -: 3 $. ^. $. 2 3 4
__ -: 3 $. ^. $. 2 3.4
__ -: 3 $. ^. $. 2 3j4

f=: 4 : '(p^.q) -: ((2;x)$.p) ^. (2;y)$.q'

p=: ?3 5 2$2
q=: ?3 5 2$2
c=: ; (i.1+r) <"1@comb&.>r=:#$p
(<'NaN error') = f etx &.>/~c


NB. $ -------------------------------------------------------------------

d=: ?3 4 5 2$4
c=: ; (i.1+r) <"1@comb&.>r=:#$d

f=: 4 : 0
 a=: 5,(-x){.$d
 s=: a ($,)"(1,x) (2;y)$.d
 *./ (scheck s), s-: a ($,)"(1,x) d
)

(i.>:r) f&>/ c

f=: 4 : 0
 a=: 2
 s=: a ($,)"(1,x) (2;y)$.d
 *./ (scheck s), s-: a ($,)"(1,x) d
)

(i.>:r) f&>/ c

f=: 4 : 0
 a=: 1+?>.1.5*(>.1.2*x){.($d),r$2
 s=: (2;y)$.d
 t=: a ($,)"(1,x) s
 b=. t -: a ($,)"(1,x) d
 if. 0=#$t do. b else. *./ (scheck t), b end.
)

(i.>:r) f&>/ c

f=: 4 : 0
 b=. ('' ($,)"(1,x) d) -: t=. '' ($,)"(1,x) (2;y)$.d
 if. 4096=type t do. b=. b*. scheck t end.
)

(i.>:r) f&>/ c [ d=: (?3 4 5$2) * ?3 4 5 2$4
(i.>:r) f&>/ c [ d=: 0*d

'length error' -: '' ($,) etx $. i.2 3 0


NB. | -------------------------------------------------------------------

(scheck | $.x), (| -: |&.$.) x=:     _10+?    405$2
(scheck | $.x), (| -: |&.$.) x=:     _10+?  3 4 5$21
(scheck | $.x), (| -: |&.$.) x=:   o._10+?  3 4 5$21
(scheck | $.x), (| -: |&.$.) x=:j./o._10+?2 3 4 5$21

(scheck | $.x), (| -: |&.$.) x=: (_10+?60$21),<.-2^31

0 -: 3 $. | $. 0 1 0
0 -: 3 $. | $. 2 3 4
0 -: 3 $. | $. 2 3.4
0 -: 3 $. | $. 2 3j4

f=: 4 : '(p|q) -: ((2;x)$.p) | (2;y)$.q'

p=: ?6 5 2$2
q=: ?6 5 2$2
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c

p=: ?6 5 2$4
q=: ?6 5 2$4
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c

p=: o.?3 5 2$4
q=: o.?3 5 2$4
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c

p=: j./?2 3 5 2$4
q=: j./?2 3 5 2$4
c=: ; (i.1+r) <"1@comb&.>r=:#$p
f&>/~c


NB. |: ------------------------------------------------------------------

x=: ?7 6 5 4 3 2$3

f=: 3 : 0 " 0
 r=: #$x
 c=: (1+?r)?r
 p=: ?~r
 (p|:x) -: p|:(2;c)$.x
)

f"0 i.4 10


4!:55 ;:'a c d f g i p q r s t x y'


