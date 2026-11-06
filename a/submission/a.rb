require"ac-library-rb/priority_queue"
(N,M),*I=$<.map{_1.split.map &:to_i}
A=I[...N].sort
q=AcLibraryRb::HeapQueue.new
p I[i=N].sort.reverse.sum{q<<A[i-=1][1]while i>0&&A[i-1][0]>=_1;q.empty?&&(p -1;exit);q.pop}
