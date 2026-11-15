(N,),A,*I=$<.map{_1.split.map &:to_i};c=1;I.map{|t,x,y|t<2?(A[x-=c],A[y-=c]=A[y],A[x]):t<3?c=c%N+1:p(A[x-c])}
