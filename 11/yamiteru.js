const isLeap = (year) => {
  return year % 1000 === 0
    ? year % 400 === 0
    : year % 4 === 0;
};

module.exports = isLeap;
