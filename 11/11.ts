const log = console.log; const isLeap = (year: number) => { if((0 == year % 4) && (0 != year % 100) || (0 == year % 400)) { return log(true) } else {return log(false)} }
isLeap(2016)
isLeap(2017)
