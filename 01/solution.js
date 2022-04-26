let num = 16;

function divider(input) {

    for (var i = 1; i < input + 1; i++) {
        if (del(3, i) && del(5, i)) {
            console.log(i + " - fizzbuzz");
        } else if (del(3, i)) {
            console.log(i + " - fizz");
        } else if (del(5, i)) {
            console.log(i + " - buzz");
        } else {
            console.log(i);
        }
    }



}

function del(del,del2){

    if (del2 % del == 0) {
        return true;
    } else {
        return false;
    }

}

divider(num);



// Inspired by Majkel Code
