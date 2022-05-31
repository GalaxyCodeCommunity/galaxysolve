function range(a, b) {
  const r = [];
  const x = a > b;

  let i = a - (x ? -1: 1);

  const p = x
    ? () => --i >= b
    : () => ++i <= b;

  while(p()) {
    r.push(i);
  }

  return r;
}

module.exports = range;
