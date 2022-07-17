db = {
    1: {
        "en": {1: "dog", 2: "dogs"},
        "cs": {1: "pes", 2: "psi", 5: "psů"}
    },
    2: {
        "en": {1: "cat", 2: "cats"},
        "cs": {1: "kočka", 2: "kočky", 5: "koček"}
    },
    3: {
        "en": {1: "human", 2: "humans"},
        "cs": {1: "člověk", 2: "lidi", 5: "lidí"}
    }
}

words = {
    "dog": 1,
    "dogs": 1,
    "cat": 2,
    "cats": 2,
    "human": 3,
    "humans": 3
}

def translate(word: str, lang: str, count: int = 1):
    try:
        w = db[words[word]][lang]
        i = min(w.keys(), key=lambda x: (abs(x - count), x))
        return w[i]
    except KeyError:
        return word


print(translate("dog", "cs"))        # pes
print(translate("cat", "cs", 2))     # kočky
print(translate("human", "en", 10))  # humans
