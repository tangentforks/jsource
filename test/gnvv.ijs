1:@:(echo^:ECHOFILENAME) './gnvv.ijs'
NB. N V0 V1 -------------------------------------------------------------

lr=: 1 : '5!:5 <''u'''

'5 >. #'     -: (5 >.#) lr
'(i.8) , 8:' -: ((i.8) , 8:) lr


NB. N V0 V1 inverses ----------------------------------------------------

testx=: 2 : '(x b._1) -: 5!:5<''y''' 

(3 * ])                    testx ((%3) * ] )
([: +: 3 * ])              testx ((%3) * -:)
(3 * 4 + 5  *  6 + 7 * ] ) testx (      (%7) * _6 + (%5) *  _4 + (%3) * ])
(3 * 4 + [: *: 6 + 7 * ] ) testx (      (%7) * _6 + [:   %: _4 + (%3) * ])
(3 * 4 + [: *: 6 + 7 * +:) testx ([: -: (%7) * _6 + [:   %: _4 + (%3) * ])


4!:55 ;:'lr testx'


