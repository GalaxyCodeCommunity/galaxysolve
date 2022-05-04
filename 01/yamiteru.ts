// ### Constants

const MAX = 20
const ANSWERS = ["", "fizz", "buzz", "fizzbuzz"];



// ### Implementation

// Branchless version of fizzbuzz
// => There is just math and no conditions
function fizzBuzz(max = MAX) {
    for(let i = 1; i <= MAX; ++i) {
        // 1. From boolean to number of division by 5 equal to 0
        // => Returns either 0 or 1
        // 2. Multiply previous step by 2
        // => Returs either 0 or 2
        // 3. From boolean to number of division by by 3 equal to 0
        // => Returns either 0 or 1
        // 4 Adds two previous results together
        // => Returns either 0, 1, 2, or 3
        // 5. Use previous value as index for ANSWERS
        // => Returns either "", "fizz", "buzz" or "fizzbuzz" in this order
        console.log(`${i} ${ANSWERS[(+(i % 5 === 0)) * 2 + (+(i % 3 === 0))]}`);
    }
}



// ### Test

// fizzBuzz(MAX);
//
// 1
// 2
// 3 fizz
// 4
// 5 buzz
// 6 fizz
// 7
// 8
// 9 fizz
// 10 buzz
// 11
// 12 fizz
// 13
// 14
// 15 fizzbuzz
// 16
// 17
// 18 fizz
// 19
// 20 buzz



// ### Export

export default fizzBuzz;
