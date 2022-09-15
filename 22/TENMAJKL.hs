data Tree = 
    Some Int Tree Tree 
    | None
    deriving (Show)

invert :: Tree -> Tree
invert None = None
invert (Some value left right) = Some value (invert right) (invert left)

sample :: Tree
sample = Some 
    10 
    (Some 20 
        (Some 30 None None) 
        (Some 40 None 
            (Some 50 None None)
        )
    )
    (Some 60
        (Some 70 None 
            (Some 80 
                (Some 90 None None) None
            )
        )
        None
    )

main = do {
    print (invert sample)
}
