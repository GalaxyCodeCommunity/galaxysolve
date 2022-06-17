let pole = [1, 2, 3, 4, 5, 6];

let dlzkaDoSwapu = () =>{ if (pole.length < 6 ) { pole.length = pole.length * pole.length } return pole.length};

function swap(pole, dlzka) {
    for(let i = 1; i < dlzka; i += 2) {
        let docasnaVec = pole[ i - 1 ];
        pole[ i - 1 ] = pole[i];
        pole[i] = docasnaVec
    };
    return pole
}
console.log(swap(pole, dlzkaDoSwapu()));

/*
* Returned -> ** [ 2, 1, 4, 3, 6, 5 ] **
*/