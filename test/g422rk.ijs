NB. /:@/: y -------------------------------------------------------------

rk=: 3 : '/:/:y'

f=: 4 : 0
 assert. (/:@/:   -: rk  ) xx=: x{~ (  1e4,y) ?@$ #x
 assert. (/:@/:"2 -: rk"2) xx=: x{~ (5 1e4,y) ?@$ #x
 1
)

0 1 f"1 0 i.10
a.  f"1 0 i.10

(/:@/:   -: rk  ) x=: u:   1e4 ?@$ 65536
(/:@/:"1 -: rk"1) x=: u: 5 1e4 ?@$ 65536

(/:@/:   -: rk  ) x=: 10&u:   1e4 ?@$ 1048576
(/:@/:"1 -: rk"1) x=: 10&u: 5 1e4 ?@$ 1048576

g=: 3 : 0
 assert. (/:@/:   -: rk  ) xx=:   1e4 ?@$ y
 assert. (/:@/:"1 -: rk"1) xx=: 3 1e4 ?@$ y
 1
)

g"0 ] 10^i.10
g"0 ] 10^IF64#11 12 13 18

(/:@/:   -: rk  ) x=:        1e3 5 ?@$ 0
(/:@/:   -: rk  ) x=: <"0 ]  1e3 5 ?@$ 1e4
(/:@/:   -: rk  ) x=: y{~    1e3 5 ?@$ #y=: 'abc';1 2 3;7.5;;:'bush kerry nader'

(/:@/:"2 -: rk"2) x=:      3 1e3 5 ?@$ 0
(/:@/:"2 -: rk"2) x=: <"0 ]3 1e3 5 ?@$ 1e4
(/:@/:"2 -: rk"2) x=: y{~  3 1e3 5 ?@$ #y=: 'abc';1 2 3;7.5;;:'bush kerry nader'

(/:@/:"0 -: rk"0) x=:     3 12 ?@$ 2
(/:@/:"0 -: rk"0) x=: a.{~3 12 ?@$ #a.
(/:@/:"0 -: rk"0) x=:     3 12 ?@$ 2e9
(/:@/:"0 -: rk"0) x=:     3 12 ?@$ 0
(/:@/:"0 -: rk"0) x=: u:  3 12 ?@$ 65536
(/:@/:"0 -: rk"0) x=: 10&u:  3 12 ?@$ 1048576
(/:@/:"0 -: rk"0) x=: y{~ 3 12 ?@$ #y=: 'abc';1 2 3;7.5;;:'bush kerry nader'

x=: 1e4 ?@$ 1e4
y=: 1e4 ?@$ 5000
(/:x/:y) -: x /:@/: y

x=: (5 1e4 ?@$ 2) * 5 1e4 ?@$ 1000
(/:@/:"1 x) -: /:@/:"1 $.x

(i.0    ) -: /:@/:     0 1e9 2e9 99 $ 0
(i.0 2e9) -: /:@/:"1 ] 0 2e9        $ 0
(i.0 2e9) -: /:@/:"2 ] 0 2e9 17     $ 0

(3 4 17$i.17) -: /:@/:"2 ] 3 4 17 0 $ 0
(3 4 17$i.17) -: rk   "2 ] 3 4 17 0 $ 0

(/:@/: -: /:@/:@x:)"1 ] 17 31 ?@$ 1000

'limit error' -: /:@/:"2 etx 0 $~ (IF64$2e9),1e9 11 17 0


4!:55 ;:'f g rk x xx y'

