// ### Implementation

function reverseArray(a: number[]) {
    const l = a.length;
    const m = l - 1;
    const r = [];

    for(let i = 0; i < l; ++i) {
        r[i] = a[m - i];
    }

    return r;
}



// ### Test

// console.log(reverseArray([1, 2, 3]));

// [ 3, 2, 1 ]



// ### Export

export default reverseArray;
