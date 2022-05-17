const log = (body: any)=>{
    console.log(`${body}`);
}
const main = (num1: number, num2:number, reversed: boolean) => {
    if(reversed === false) {
        let array: [] = [];
        for (let i = num1; i < num2 + 1; i++) {
            // @ts-ignore
            array.push(i)
        }
        return array;
    }
    if(reversed === true) {
        let arrayReversed: [] = [];
        for (let i = num1; i > num2 - 1; i--) {
            // @ts-ignore
            arrayReversed.push(i)
        }
        return arrayReversed;
    }
}

log(main(20, 1, true))
