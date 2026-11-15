N=gets.to_i/2;p$<.map{_1.split.map &:to_i}.transpose.sum{_1.max(N).sum-_1.min(N).sum}
