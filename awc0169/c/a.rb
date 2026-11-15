require"ac-library-rb/dsu"
(N,M,Q),*I=$<.map{_1.split.map &:to_i}
C=((J=I[0...M]).map{_1[0]}+J.map{_2}+(K=I[M..]).map{_3}).sort.uniq
Z=->u{C.bsearch_index{_1>=u}}
e=J.map{_1.map{|u|Z[u]}}
K.map{|j,i,v|e[i-1][j-1]=Z[v];d=AcLibraryRb::DSU.new C.size;puts e.transpose.map(&:sort).transpose.each{d.merge(_1,_2)}.map{d.size(_1[0])%2}*' '}
