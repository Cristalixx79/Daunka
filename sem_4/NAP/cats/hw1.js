function diff(arr1, arr2)
{
    let result = [];
    for (const item in arr1) {
        const element = arr1[item];
        if (!arr2.includes(element))
        {
            result.push(element);
        }
    }
    return result;
}

let arr1 = [1, 2, 3];
let arr2 = [2, 3, 4];

console.log(diff(arr1, arr2));