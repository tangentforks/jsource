1:@:(echo^:ECHOFILENAME) './g311.ijs'
NB. :. ------------------------------------------------------------------

f =. + :. -
g =. - :. +
(f b. _1) -: 5!:5 <'g'

'domain error' -: ex '3 4 :. ''+'''
'domain error' -: ex '3 4 :. +'
'domain error' -: ex '*   :. ''+/'''


4!:55 ;:'f g'


