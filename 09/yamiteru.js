const swap = (v) => {
  const l = v.length;
  const o = l % 2 !== 0;
  const m = l - o;
  const x = [];

  for(let i = 0; i < m; i+=2) {
    x.push(v[i+1], v[i]);
  }

  if(o) {
    x.push(v[l-1]);
  }

  return x;
};

module.exports = swap;
