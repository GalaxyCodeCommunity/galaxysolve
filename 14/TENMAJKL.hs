-- see https://github.com/TENMAJKL/morse/blob/master/morse.hs

-- Idea came from summer camp where my friend had morse code that looked like binary tree, so 
-- I decided to write haskell app that solves morse code using recursion

-- Table : https://upload.wikimedia.org/wikipedia/commons/thumb/1/19/Morse-code-tree.svg/1280px-Morse-code-tree.svg.png

data Character = Character {
    value :: Char,
    dot :: Maybe Character,
    line :: Maybe Character 
}

newCharacter :: Character
newCharacter = Character {
    value = ' ',
    dot = Just Character {
        value = 'e',
        dot = Just Character {
            value = 'i',
            dot = Just Character {
                value = 's',
                dot = Just Character {
                    value = 'h',
                    dot = Nothing,
                    line = Nothing
                },
                line = Just Character {
                    value = 'v',
                    dot = Nothing,
                    line = Nothing
                }
            },
            line = Just Character {
                value = 'u',
                dot = Just Character {
                    value = 'f',
                    dot = Nothing,
                    line = Nothing
                },
                line = Nothing  
            }
        },
        line = Just Character {
            value = 'a',
            dot = Just Character {
                value = 'r',
                dot = Just Character {
                    value ='l',
                    dot = Nothing,
                    line = Nothing 
                },
                line = Nothing 
            },
            line = Just Character {
                value = 'w',
                dot = Just Character {
                    value = 'p',
                    dot = Nothing,
                    line = Nothing 
                },
                line = Just Character {
                    value = 'j',
                    dot = Nothing,
                    line = Nothing 
                }
            }
        }
    },
    line = Just Character {
        value = 't',
        dot = Just Character {
            value = 'n',
            dot = Just Character {
                value = 'd',
                dot = Just Character {
                    value = 'b',
                    dot = Nothing,
                    line = Nothing
                },
                line = Just Character {
                    value = 'x',
                    dot = Nothing,
                    line = Nothing
                }
            },
            line = Just Character {
                value = 'k',
                dot = Just Character {
                    value = 'c',
                    dot = Nothing,
                    line = Nothing
                },
                line = Just Character {
                    value = 'y',
                    dot = Nothing,
                    line = Nothing
                }
            }
        },
        line = Just Character {
            value = 'm',
            dot = Just Character {
                value = 'g',
                dot = Just Character {
                    value ='z',
                    dot = Nothing,
                    line = Nothing 
                },
                line = Just Character {
                    value ='q',
                    dot = Nothing,
                    line = Nothing 
                }
            },
            line = Just Character {
                value = 'o',
                dot = Nothing, 
                line = Nothing 
            }
        }
    }
}

solve :: Character -> String -> String
solve morse target = if null target then "" else
    case head target of 
    '.' -> case dot morse of 
        Just x -> solve x (tail target)
        Nothing -> "error"
    '-' -> case line morse of 
        Just x -> solve x (tail target)
        Nothing -> "error"
    '|' -> value morse : solve newCharacter (tail target)
    _ -> "error"

main = print (solve newCharacter ".-|....|---|.---||.|")
