K=eval *$<
p (1..1e4).sum{|a|K%a<1?(a..(d=K/a)**0.5).count{|b|d%b<1&&b<=d/b}:0}
