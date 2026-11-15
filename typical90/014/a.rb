p$<.map{_1.split.map(&:to_i).sort}.drop(1).transpose.sum{(_1-_2).abs}
