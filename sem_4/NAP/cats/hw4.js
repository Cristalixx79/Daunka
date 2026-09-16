function getSumAndMultOfArray(arr)
{
    let res = [];
    let summ = 0;
    let mult = 1;
    for (let i = 0; i < arr.length; i++) {
        const element = arr[i];
        
        summ += element;
        mult *= element;
    }
    res.push(summ);
    res.push(mult);
    return res;
}

let arr1 = [1, 2, 3];

let r = getSumAndMultOfArray(arr1)
console.log("Sum: ", r[0], "\tMult: ", r[1]);