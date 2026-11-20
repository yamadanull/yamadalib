puts N=rand(2..5)
puts M=rand(2..5)
puts Q=1
puts A=N.times.map{rand(0..3)}*' '
M.times{
  u=rand(1..N-1)
  v=rand(u+1..N)
  w=rand(0..3)
  puts [u,v,w]*' '
}
Q.times{
  u=rand(1..N-1)
  v=rand(u+1..N)
  puts [u,v]*' '
}
