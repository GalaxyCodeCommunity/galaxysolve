const merge = (first, ...rest) => {
  const arrays = [first, ...rest];
  const length = arrays.length;
  const max = Math.max(...arrays.map((v) => v.length));
  const res = [];

  for(let i = 0; i < max; ++i) {
    for(let j = 0; j < length; j++) {
      const tmp = arrays[j][i];

      if(tmp !== undefined) {
        res.push(tmp);
      }
    }
  }

  return res;
};

module.exports = merge;
