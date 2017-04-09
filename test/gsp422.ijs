1:@:(echo^:ECHOFILENAME) './gsp422.ijs'
NB. /: monad ------------------------------------------------------------

f=: 4 : 0
 assert. (/:   x) -: /:   y
 assert. (/:"1 x) -: /:"1 y
 assert. (/:"2 x) -: /:"2 y
 for_i. i.#y do. assert. (/: i{x) -: /: i{y end.
 1
)

x f y [ x=: $. y=: ((?10$2), 0, 1, 0 ,: 10$1 0 0) * ? 5 10 3$2
x f y [ x=: (2;0)$.y
x f y [ x=: $. y=: ((?10$2), 0, 1, 0 ,: 10$1 0 0) *     _2  +?   5 10 3$5
x f y [ x=: (2;0)$.y
x f y [ x=: $. y=: ((?10$2), 0, 1, 0 ,: 10$1 0 0) * o.  _2  +?   5 10 3$5
x f y [ x=: (2;0)$.y
x f y [ x=: $. y=: ((?10$2), 0, 1, 0 ,: 10$1 0 0) * j./ _2  +? 2 5 10 3$5
x f y [ x=: (2;0)$.y

x f y [ x=: $. y=: ((?10$2), 0, 1, 0 ,: 10$0 0 1) * ? 5 10 3$2
x f y [ x=: (2;0)$.y
x f y [ x=: $. y=: ((?10$2), 0, 1, 0 ,: 10$0 0 1) *     _2e5+?   5 10 3$5e5
x f y [ x=: (2;0)$.y
x f y [ x=: $. y=: ((?10$2), 0, 1, 0 ,: 10$0 0 1) * o.  _2e5+?   5 10 3$5e5
x f y [ x=: (2;0)$.y
x f y [ x=: $. y=: ((?10$2), 0, 1, 0 ,: 10$0 0 1) * j./ _2e5+? 2 5 10 3$5e5
x f y [ x=: (2;0)$.y

f=: 4 : '(/:"x xx) -: /:"x s=: (2;y)$.xx'
c=: ; (i.1+r) <"1@comb&.>r=:4 

(1+i.r) f&>/ c [ xx=:         ?  7 11 13 17$2
(1+i.r) f&>/ c [ xx=:    _2  +?  7 11 13 17$5
(1+i.r) f&>/ c [ xx=: o. _2  +?  7 11 13 17$5
(1+i.r) f&>/ c [ xx=: j./_2  +?2 7 11 13 17$5

(1+i.r) f&>/ c [ xx=:    _2e5+?  7 11 13 17$2e5
(1+i.r) f&>/ c [ xx=: o. _2e5+?  7 11 13 17$5e5
(1+i.r) f&>/ c [ xx=: j./_2e5+?2 7 11 13 17$5e5

(1+i.r) f&>/ c [ xx=:            7 11 13 17$0


NB. /: dyad -------------------------------------------------------------

f=: 4 : 0
 assert. (a/:y) -: a/:(2;x)$.y
 1
)

n=: 100
y=: (?(n,2)$2) * ?(n,2 3)$1000 
c=: ; (i.1+r) <"1@comb&.>r=: #$y

c f&> <y [ a=:   ?(n,4)$1000
c f&> <y [ a=: $.?(n,4)$1000

y=: (?(n,2)$2) * o.?(n,2 3)$1000 
c f&> <y [ a=:   ?(n,4)$1000
c f&> <y [ a=: $.?(n,4)$1000

y=: (?(n,2)$2) * ?(n,2 3)$2 
c f&> <y [ a=:   ?(n,4)$1000
c f&> <y [ a=: $.?(n,4)$1000


4!:55 ;:'a c f n r s x xx y'

