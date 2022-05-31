const N = [2, 3, 5, 7];
const L = N.length;

function isPrimeNumber(n) {
  if(n <= 1) return false;

  if(N.indexOf(n) !== -1) return true;

  for(let i = 0; i < L; ++i) {
    if(n % N[i] === 0) return false;
  }

  return true;
}

function getPrimesFromArray(a) {
  const l = a.length;
  const r = [];

  for(let i = 0; i < l; ++i) {
    const n = a[i];
    if(isPrimeNumber(n)) r.push(n);
  }

  return r;
}

module.exports = getPrimesFromArray;
