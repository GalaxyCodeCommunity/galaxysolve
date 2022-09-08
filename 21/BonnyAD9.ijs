bitsToNum=:{~&0@:>@:((<@:(({~&0@:>@:] + >@:[ * ^~&2@:{~&1@:>@:]) , +&1@:{~&1@:>@:]))/)@:,&(< 0 0)@:(;/)
numToBits=:(|~&2 , $:@:<.@:%&2)^:(>&1)
rngState=:64 $ numToBits <. */ 6!:0 '' NB. seed is based on current time
rngNext=:(6 b. (|.!.0)~&11)@:(6 b. (|.!.0)~&_7)@:(6 b. (|.!.0)~&13)

rngNextNum =: 3 : 0
rngState=:rngNext rngState
(bitsToNum (32 {. rngState)) + bitsToNum (32 }. rngState)
)

(echo@:|~&100@:rngNextNum)"0 i.100
