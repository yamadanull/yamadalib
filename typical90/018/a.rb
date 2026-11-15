include Math
eval"T,L,X,Y,Q,*I="+`dd`.split*?,
I.map{p atan2((1-cos(r=_1*2*PI/T))*L/2,hypot(X,Y+L/2*sin(r)))*180/PI}
