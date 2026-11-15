_,A,B,C=$<.map{|a|a.split.map{_1.to_i%46}.tally}
p A.sum{|i,c|B.sum{c*_2*C[(-i-_1)%46]||=0}}
