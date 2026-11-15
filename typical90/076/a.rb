puts (B=[s=0]+([*$<][1].split*2).map{s+=_1.to_i}).any?{|b|B.bsearch{s/20r-_1+b}}?:Yes: :No
