const numbers = [1,3,50,10]; // here you can input a numbers to test

function checker(arr) {

    for (let i = 0; i < arr.length; i++) {

        if (arr[i] % 2 === 0) {
        } else {
            console.log(arr[i]); // print a prime numbers
        }
        
    }

}

checker(numbers); // calling the function to test prime numbers
