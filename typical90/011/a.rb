o=[0]
$<.map{_1.split.map &:to_i}.sort.map{|d,c,s|c&&o=(0..d).map{|i|[o[i]||b=o[-1],i<c ?0:(o[i-c]||b)+s].max}}
p o[-1]
