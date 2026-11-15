eval"N,K="+gets.split*?,
F=[l=-1]*26
S=gets
$><<(1..K).map{|k|c=0;S[l=F.map!{|i|i+=1 while i<=l||i<N&&S[i].ord-97!=c;c+=1;i}.find{_1+K-k<N}]}*''
