N,M,S,T = gets.split.map(&:to_i)
E = Array.new(N+1){[]}
M.times{
	a,b = gets.split.map(&:to_i)
	E[a]<<b
}
E.each(&:sort!)

D = [nil]*(N+1)
D[S] = d = 0
Q0 = [S]
Q1 = []
until Q1.empty? && Q0.empty?

	while a = Q0.shift
#warn "at #{a}"
		if b = E[a][0]
			if ! D[b]
				D[b] = d
#warn "+0 #{a} to #{b}"
				Q0<<b
			end
			Q1<<a
		end
	end

	d += 1
	while a = Q1.shift
#warn "at #{a}"
		E[a].each{|b|
			if ! D[b]
				D[b] = d
#warn "+1 #{a} to #{b}"
				Q0<<b
			end
		}
	end
end
#warn D.inspect

p(D[T]||-1)

