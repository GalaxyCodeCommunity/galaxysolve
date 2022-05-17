const log = (body: any)=>{
    console.log(`${body}`);
}

const inRange=(num1: number, num2:number)=>{

    let array: [] = [];
    for (let i = num1; i < num2 + 1; i++) {
        // @ts-ignore
        array.push(i)
    }
    return array;
}
const isRangeReversed=(num: number, num2: number)=>{
    let arrayReversed: [] = [];
    for (let i = num; i > num2 - 1; i--) {
        // @ts-ignore
        arrayReversed.push(i)
    }
    return arrayReversed;
}
log(isRangeReversed(20, 10))