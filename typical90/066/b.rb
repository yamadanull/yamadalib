I=$<.map{_1.split.map &:to_i}
p (2..I.size).sum{|i|a,b=I[i-1];I[i..].sum{|l,r|(a..b).sum{[0,[_1,r+1].min-l].max}/(r-l+1.0)}/(b-a+1)}
