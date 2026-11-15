require"ac-library-rb/dsu"
gets
d=AcLibraryRb::DSU.new(3e5)
p$<.map{_1.split.map &:to_i}.sort_by{_3}.sum{d[_1]==d[_2]?0:_3+0*d.unite(_1,_2)}
