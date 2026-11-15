d=1,*[0]*7
[*$<][1].chars.map{i=:atcoder=~/#{_1}/;d[i+1]+=d[i]if i}
p d[7]%=10**9+7
