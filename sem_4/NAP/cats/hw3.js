function sumOfSquares(arr)
{
    let summ = 0;
    for (let i = 0; i < arr.length; i++) {
        const element = arr[i];
        
        summ += (element * element);
    }
    return summ;
}

let arr1 = [1, 2, 3];

console.log(sumOfSquares(arr1));