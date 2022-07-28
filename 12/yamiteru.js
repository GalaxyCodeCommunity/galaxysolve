const WORDS = {
  dog: {
    cs: [
      [[0, 0], "psů"],
      [[1, 1], "pes"],
      [[2, 4], "psi"],
      [[5, Infinity], "psů"]
    ],
    en: [
      [[0, 0], "dogs"],
      [[1, 1], "dog"],
      [[2, Infinity], "dogs"],
    ]
  },
  cat: {
    cs: [
      [[0, 0], "koček"],
      [[1, 1], "kočka"],
      [[2, 4], "kočky"],
      [[5, Infinity], "koček"]
    ],
    en: [
      [[0, 0], "cats"],
      [[1, 1], "cat"],
      [[2, Infinity], "cats"],
    ]
  },
  human: {
    cs: [
      [[0, 0], "lidí"],
      [[1, 1], "člověk"],
      [[2, 4], "lidi"],
      [[5, Infinity], "lidí"]
    ],
    en: [
      [[0, 0], "humans"],
      [[1, 1], "human"],
      [[2, Infinity], "humans"],
    ]
  }
};

const CACHE = {};

const translateWithoutCache = (word, lang, count) => {
  const ctx = WORDS?.[word]?.[lang];

  if(ctx === undefined) return word;

  for(const [[min, max], res] of ctx) {
    if((min === max && count === min) || (count >= min && count <= max)) {
      return res;
    }
  }

  return word;
};

const translate = (word, lang, count = 1) => {
  const key = `${word}-${lang}-${count}`;

  if(key in CACHE) {
    return CACHE[key];
  } else {
    return (CACHE[key] = translateWithoutCache(word, lang, count));
  }
};

// console.log([
//   ["dog", "cs"],
//   ["cat", "cs", 2],
//   ["human", "en", 10]
// ].map(([word, lang, count = 1]) =>
//   translate(word, lang, count)
// ));

module.exports = translate;
