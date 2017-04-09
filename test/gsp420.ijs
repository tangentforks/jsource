1:@:(echo^:ECHOFILENAME) './gsp420.ijs'
NB. / -------------------------------------------------------------------

(=/x  ) -: =/$.x=: ?1000$2
(=/1,x) -: =/$.1,x
(=/0,x) -: =/$.0,x
(=/x+.0=x) -: =/(3;1)$.$.x=:?1000$2

(<./x) -: <./$.x=:        ?1000$2
(<./x) -: <./$.x=:    _10+?1000$21
(<./x) -: <./$.x=: o. _10+?1000$21
(<./x+c*0=x) -: <./ (3;c=:_20+?40)$.$.x=: _10+?1000$21

(>./x) -: >./$.x=:        ?1000$2
(>./x) -: >./$.x=:    _10+?1000$21
(>./x) -: >./$.x=: o. _10+?1000$21
(>./x+c*0=x) -: >./ (3;c=:_20+?40)$.$.x=: _10+?1000$21

(+/x) -: +/$.x=:        ?  1000$2
(+/x) -: +/$.x=:    _10+?  1000$21
(+/x) -: +/$.x=: o. _10+?  1000$21
(+/x) -: +/$.x=: j./_10+?2 1000$21
(+/x) -: +/$.x=: ( _5+?1000$21),<._1+2^31
(+/x) -: +/$.x=: (_15+?1000$21),<.-  2^31
(+/x+c*0=x) -: +/ (3;c=:_20+?40)$.$.x=: _10+?1000$21
(+/   x) -: +/   $.x=: ?2 3 4 5$2e9
(+/"1 x) -: +/"1 $.x=: ?2 3 4 5$2e9
(+/"2 x) -: +/"2 $.x=: ?2 3 4 5$2e9
(+/"3 x) -: +/"3 $.x=: ?2 3 4 5$2e9

(+./x) -: +./$.x=:?1000$2
(+./x+.0=x) -: +./(3;1)$.$.x=:?1000$2

(*/x) -: */$.x=:        ?  7$2
(*/x) -: */$.x=:    _10+?  7$21
(*/x) -: */$.x=: o. _10+?  7$21
(*/x) -: */$.x=: j./_10+?2 7$21
(*/x) -: */$.x=: ( _5+?7$21),<._1+2^31
(*/x) -: */$.x=: (_15+?7$21),<.-  2^31
(*/x+c*0=x) -: */ (3;c=:_20+?40)$.$.x=: _10+?7$21

(*./x) -: *./$.x=:?1000$2
(*./x+.0=x) -: *./(3;1)$.$.x=:?1000$2

(~:/x) -: ~:/$.x=: ?1000$2
(~:/x+.0=x) -: ~:/(3;1)$.$.x=:?1000$2


f=: 1 : (':'; '(scheck t) *. (u/"x d) -: t=: u/"x s=:(2;y)$.d')

(>:i.r) + f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _2+?11 5 4 3 2$5
(>:i.r) * f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  1+?11 5 4 3 2$5
(>:i.r) >.f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _2+?11 5 4 3 2$5
(>:i.r) <.f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _2+?11 5 4 3 2$5
(>:i.r) = f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?11 5 4 3 2$2
(>:i.r) ~:f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?11 5 4 3 2$2
(>:i.r) +.f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?11 5 4 3 2$2
(>:i.r) *.f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?11 5 4 3 2$2

(>:i.r) + f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     11 5 4 3 2$0
(>:i.r) +.f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     11 5 4 3 2$0

0  -: + / 1 $. 20 ; 0 ; 2-2
40 -: + / 1 $. 20 ; 0 ; 2
0  -: * / 1 $.  5 ; 0 ; 2-2
1  -: * / 1 $.  5 ; 0 ; 2-1
32 -: * / 1 $.  5 ; 0 ; 2
17 -: >./ 1 $. 19 ; 0 ; 17
_7 -: <./ 1 $. 19 ; 0 ; _7

1  -: = / 1 $. 20 ; 0 ; 0
0  -: = / 1 $. 19 ; 0 ; 0
1  -: = / 1 $. 20 ; 0 ; 1
1  -: = / 1 $. 19 ; 0 ; 1

0  -: ~:/ 1 $. 20 ; 0 ; 0
0  -: ~:/ 1 $. 19 ; 0 ; 0
0  -: ~:/ 1 $. 20 ; 0 ; 1
1  -: ~:/ 1 $. 19 ; 0 ; 1

0  -: +./ 1 $. 20 ; 0 ; 0
1  -: +./ 1 $. 20 ; 0 ; 1
0  -: *./ 1 $. 20 ; 0 ; 0
1  -: *./ 1 $. 20 ; 0 ; 1

g=: 1 : (':'; '(scheck t) *. (u/"x $.^:_1 s) -: t=: u/"x s=:(3;e)$.(2;y)$.d')

(>:i.r) + g&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _2+?8 6 5 3 2$5 [ e=: 17
(>:i.r) + g&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _2+?8 6 5 3 2$5 [ e=: _7
(>:i.r) * g&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?8 6 5 3 2$5 [ e=: 2
(>:i.r) * g&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?8 6 5 3 2$5 [ e=: _1
(>:i.r) +.g&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?8 6 5 3 2$2 [ e=: 1
(>:i.r) *.g&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?8 6 5 3 2$2 [ e=: 1


NB. f/@, ----------------------------------------------------------------

f=: 1 : 0
 s=: (2;y)$.d 
 x=.u/,d
 (x -: u/@, s) *. (x -: u/@:,s) *. (x -: u/&, s) *. x -: u/&:, s
)

=  f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:      ?7 3 5 11$2
=  f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:      ?7 3 5 12$2
~: f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:      ?7 3 5 11$2
~: f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:      ?7 3 5 12$2
+. f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:      ?7 3 5 11$2
+. f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:      ?7 3 5 12$2
*. f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:      ?7 3 5 11$2
*. f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:      ?7 3 5 12$2
<. f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _1e9+?7 3 5 11$2e9
>. f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _1e9+?7 3 5 12$2e9
+  f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _1e9+?7 3 5 11$2e9
*  f&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    1+?7 3 5 12$10

g=: 1 : 0
 s=:(3;e)$.(2;y)$.d
 x=. u/, $.^:_1 s
 (x -: u/@, s) *. (x -: u/@:,s) *. (x -: u/&, s) *. x -: u/&:, s
)

=  g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 15$2 [ e=: 1
=  g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 16$2 [ e=: 1
~: g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 17$2 [ e=: 1
~: g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 18$2 [ e=: 1
+. g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 15$2 [ e=: 1
+. g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 16$2 [ e=: 1
*. g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 17$2 [ e=: 1
*. g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 18$2 [ e=: 1
+  g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _2+?7 3 5 11$5 [ e=: 17
+  g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=: _2+?7 3 5 12$5 [ e=: _7
*  g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 13$5 [ e=: 2
*  g&> c=: ; (i.1+r) <"1@comb&.>r=:#$d=:    ?7 3 5 14$5 [ e=: _1

(+/@, s) -: +/,s=: $. 1e8*i.3 4
(*/@, s) -: */,s=: $. 100+i.3 4
 

NB. f/ over axis of length 2 --------------------------------------------

f=: 1 : 0
 :
 s=: (2;y)$.d
 assert. ((0{"x d) u (1{"x d)) -: t=: u/"x s
 assert. scheck s
 assert. scheck t
 1
)

(>:i.r) =  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) =  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) =  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) =  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) <  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) <  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) <  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5

(>:i.r) <. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) <. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) <. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5

(>:i.r) <: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) <: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) <: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5

(>:i.r) >  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) >  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) >  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5

(>:i.r) >. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) >. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) >. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5

(>:i.r) >: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) >: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) >: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5

(>:i.r) +  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) +  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) +  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: (_1+?2 2 2 2 2$3)*1e6+2^30
(>:i.r) +  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) +  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) +. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) +. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) +. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) +. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) +: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2

(>:i.r) *  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) *  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) *  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: (_1+?2 2 2 2 2$2)*1e7
(>:i.r) *  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) *  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) *. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) *. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) *. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) *. f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) *: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2

(>:i.r) -  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) -  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) -  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: (_1+?2 2 2 2 2$3)*1e6+2^30
(>:i.r) -  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) -  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) %  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) %  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) %  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=: (_1+?2 2 2 2 2$3)*1e6+2^30
(>:i.r) %  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) %  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) ^  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) ^  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) ^  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) ^  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) ~: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) ~: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) ~: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) ~: f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) |  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) |  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) |  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) |  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5

(>:i.r) !  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:     ?2 2 2 2 2$2
(>:i.r) !  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:  _2+?2 2 2 2 2$5
(>:i.r) !  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:o._2+?2 2 2 2 2$5
(>:i.r) !  f&>/ c=: ; (i.1+r) <"1@comb&.>r=:#$d=:r._2+?2 2 2 2 2$5


NB. ,/ ------------------------------------------------------------------

f=: 4 : '(scheck t) -: (,/"x d) -: t=: ,/"x s=:(2;y)$.d'

d=: (?11 5$2) * ?11 5 2 7$5
c=: ; (i.1+r) <"1@comb&.>r=:#$d

] b=: (1+i.r) f&>/ c

'limit error' -: ,/ etx $. 0$~>IF64{1e5 1e6 0;1e10 2e9 0


4!:55 ;:'b c d e f g r s t x'


