N,K=gets.split.map &:to_i;A=N.times.map{gets.split.map &:to_i}.sort_by{-_2};dp=[0]+[-1e18]*K;A.map{|a,d|K.times{i=K-1-_1;dp[i+1]=[dp[i+1],dp[i]+a-i*d].max}};p dp.max
