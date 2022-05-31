const O = 32;
const U = [65, 90];
const L = [97, 122];

function inRange(n, [ s, e ]) {
  return n >= s && n <= e;
}

function isUpperCase(n) {
  return inRange(n, U);
}

function isLowerCase(n) {
  return inRange(n, L);
}

function flipAscii(n, m) {
  return String.fromCharCode(n + (O * m));
}

function lowerToUpper(n) {
  return flipAscii(n, -1);
}

function upperToLower(n) {
  return flipAscii(n, +1);
}

function flipCharacter(c) {
  const n = c.charCodeAt(0);

  if(isUpperCase(n)) return upperToLower(n);
  else if(isLowerCase(n)) return lowerToUpper(n);

  return c;
}

function flipCase(s) {
  const l = s.length;

  let r = "";

  for(let i = 0; i < l; ++i) {
    r += flipCharacter(s[i]);
  }

  return r;
}

module.exports = flipCase;
