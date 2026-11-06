require "ac-library-rb/segtree"
N,Q=gets.split.map &:to_i
AcLibraryRb::Segtree.new([s=0]+gets.chop.map{|c|c=='(' ? (s+=1) : (s-=1)})
S=gets.chop
O=(1..N).map{
}
