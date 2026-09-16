function hasValues(letterArr, word)
{
    for (let i = 0; i < arr.length; i++) {
        let letter = word[i];
        if (letter && !letterArr.includes(letter)) return false;
    }
    return true;
}

function anagram(arr)
{
    let result = [];
    let forbiddenIndexes = [];
    for (let i = 0; i < arr.length; i++) {
        if (forbiddenIndexes.includes(i)) continue;
        let letterArr = arr[i].split("");
        let preResult = [];
        for (let j = i + 1; j < arr.length; j++) {
            if (arr[i].length !== arr[j].length) continue;
            if (!hasValues(letterArr, arr[j])) continue;
            forbiddenIndexes.push(j);
            if (!preResult.includes(arr[i])) preResult.push(arr[i]);
            if (!preResult.includes(arr[j])) preResult.push(arr[j]);
        }
        if (preResult.length > 0) result.push(preResult.sort());
    }
    return result.sort();
}

let arr = ["стол", "слот", "такси", "яблоко", "осёл", "lol", "лост", "oll", "искат"];
console.log(anagram(arr));