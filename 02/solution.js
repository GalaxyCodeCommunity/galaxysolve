const array = ["1","2","3","4"];


function rotate(arr){

    let newArray = [];
    for(let i = 0; i < arr.length; i++){
        newArray.unshift(arr[i]);
    }

    console.log(newArray);

}

rotate(array);
