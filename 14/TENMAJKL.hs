-- see https://github.com/TENMAJKL/morse/blob/master/morse.hs

-- Idea came from summer camp where my friend had morse code that looked like binary tree, so 
-- I decided to write haskell app that solves morse code using recursion

-- Table : https://upload.wikimedia.org/wikipedia/commons/thumb/1/19/Morse-code-tree.svg/1280px-Morse-code-tree.svg.png

data Character = Empty | Character {
    value :: Char,
    dot :: Character,
    line :: Character 
}

newCharacter :: Character
newCharacter = Character {
    value = ' ',
    dot = Character {
        value = 'e',
        dot = Character {
            value = 'i',
            dot = Character {
                value = 's',
                dot = Character {
                    value = 'h',
                    dot = Empty,
                    line = Empty
                },
                line = Character {
                    value = 'v',
                    dot = Empty,
                    line = Empty
                }
            },
            line = Character {
                value = 'u',
                dot = Character {
                    value = 'f',
                    dot = Empty,
                    line = Empty
                },
                line = Empty  
            }
        },
        line = Character {
            value = 'a',
            dot = Character {
                value = 'r',
                dot = Character {
                    value ='l',
                    dot = Empty,
                    line = Empty 
                },
                line = Empty 
            },
            line = Character {
                value = 'w',
                dot = Character {
                    value = 'p',
                    dot = Empty,
                    line = Empty 
                },
                line = Character {
                    value = 'j',
                    dot = Empty,
                    line = Empty 
                }
            }
        }
    },
    line = Character {
        value = 't',
        dot = Character {
            value = 'n',
            dot = Character {
                value = 'd',
                dot = Character {
                    value = 'b',
                    dot = Empty,
                    line = Empty
                },
                line = Character {
                    value = 'x',
                    dot = Empty,
                    line = Empty
                }
            },
            line = Character {
                value = 'k',
                dot = Character {
                    value = 'c',
                    dot = Empty,
                    line = Empty
                },
                line = Character {
                    value = 'y',
                    dot = Empty,
                    line = Empty
                }
            }
        },
        line = Character {
            value = 'm',
            dot = Character {
                value = 'g',
                dot = Character {
                    value ='z',
                    dot = Empty,
                    line = Empty 
                },
                line = Character {
                    value ='q',
                    dot = Empty,
                    line = Empty 
                }
            },
            line = Character {
                value = 'o',
                dot = Empty, 
                line = Empty 
            }
        }
    }
}

solve :: Character -> String -> String
solve morse target = if null target then "" else
    case head target of 
    '.' -> case dot morse of 
        x -> solve x (tail target)
    '-' -> case line morse of 
        x -> solve x (tail target)
    '|' -> value morse : solve newCharacter (tail target)
    _ -> "error"

main = print (solve newCharacter ".-|....|---|.---||.|")
