const fmap = (x, a, b, c, d) => {
  return (d - c) * ((x - a) / (b - a)) + c;
};

module.export = fmap;
