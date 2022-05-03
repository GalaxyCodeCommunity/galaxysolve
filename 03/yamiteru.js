// ### Benchmark results

// Regex x 10,066,555 ops/sec
// isHexColor x 25,876,438 ops/sec

// Regex = function(c) { return /^#[0-9A-F]{6}$/i.test(c); }
// Credit to Juuaann74



// ### Implementation

function isHexColor(c) {
  // We want color to be only string
  if (typeof c === "string") {
    // We don't care about #
    const s = c[0] === "#" ? c.slice(1) : c;
    // Cache the length of the string
    const l = s.length;

    // Check if length is between <3, 6>
    if (l > 2 && l < 7) {
      // Convert string to hexadecimal number
      const n = Number(`0x${s}`);
      // Check if number is not NaN
      return n === n;
    }
  }

  // Otherwise return false
  return false;
}



// ### Tests

const hexes = [
  "#73668a",
  "3b68b5",
  "#fff",
  "000",
  "#a",
  "#03b68b5",
  "hello",
  134,
  true
];

for(const hex of hexes) {
    console.log(hex, isHexColor(hex));
}

// #73668a true
// 3b68b5 true
// #fff true
// 000 true
// #a false
// #03b68b5 false
// hello false
// 134 false
// true false
