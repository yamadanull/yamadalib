S=$<.map &:chars
p S.count{_1.count(?o)==5}+S.transpose.count{_1.count(?o)==5}+((0..4).all?{S[_1][_1]==?o} ? 1 : 0)+((0..4).all?{S[_1][4-_1]==?o} ? 1 : 0)
