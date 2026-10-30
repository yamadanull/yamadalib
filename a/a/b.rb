gets;S=[s=0]+gets.split.map{s+=_1.to_i};s=0;U=S.map{s+=_1};f=->x{i=((8*x+1)**0.5-1).to_i/2;U[i]+S[x-i*-~i/2]};$<.map{l,r=_1.split.map &:to_i;p f[r]-f[l-1]}
