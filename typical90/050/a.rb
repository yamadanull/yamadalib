eval"N,L,*D="+`tr ' ' ,`
s=1
0.upto(N){D<<s+=D[-L]||0}
p s%=10**9+7
