window.onload = function () {
    let a = '0'           // Первое число
    let b = ''           // Второе число
    let expressionResult = ''  // Результат вычисления
    let selectedOperation = null  // Выбранная операция
    let operationFinished = false;
    const singleDigitOperations = ['sqrt', 'sign']; // Операции с одним операндом
    const regex = /[1-9]/; // Регулярное выражение для проверки на ноль
    const maxInputSize = 20;
    let negativeFlag = 1;
    let prevNegativeFlag = -1;

    const outputElement = document.getElementById("result")

    const digitButtons = document.querySelectorAll('[id ^= "btn_digit_"]')

    function onDigitButtonClicked(digit) {
        if (operationFinished) {
            a = '0';
            outputElement.innerHTML = 0;
            operationFinished = false;
        }
        if ((a + digit).length > maxInputSize) return;
        if (!selectedOperation) {
            if ((digit != '.') || (digit == '.' && !a.includes(digit))) {
                a += digit;

                if (a.startsWith('0') && !a.includes('.')) {
                    let match = a.match(regex);
                    if (!match) {
                        a = '0';
                    } else {
                        a = match[0];
                    }
                }
            }
            outputElement.innerHTML = a;
        }
        else {
            if (singleDigitOperations.includes(selectedOperation)) {
                return;
            }
            if ((digit != '.') || (digit == '.' && !b.includes(digit))) {
                if ((b + digit).startsWith('.')) {
                    return;
                }
                b += digit;
                outputElement.innerHTML = (a + ' ' + selectedOperation + ' ' + b);
            }
        }
    }

    digitButtons.forEach(button => {
        button.onclick = function () {
            const digitValue = button.innerHTML;
            onDigitButtonClicked(digitValue);
        }
    });

    function getSelectedOperationResult(selectedOperation) {
        let expressionResult = 0;
        switch (selectedOperation) {
            case 'x':
                expressionResult = (+a) * (+b)
                break;
            case '+':
                expressionResult = (+a) + (+b)
                break;
            case '-':
                expressionResult = (+a) - (+b)
                break;
            case '/':
                expressionResult = (+a) / (+b)
                break;
            case 'sqrt':
                expressionResult = Math.sqrt(+a)
            default:
                return null;
        }
        return expressionResult;
    }

    document.getElementById("btn_op_mult").onclick = function () {
        if (a === '') return;
        if (a !== '' && selectedOperation === 'sqrt') {
            a = Math.sqrt(+a);
        }
        if (a !== '' && b !== '') {
            a = getSelectedOperationResult(selectedOperation).toString();
            b = '';
        }
        selectedOperation = 'x';
        outputElement.innerHTML = (a + ' ' + selectedOperation);
        operationFinished = false;
    }
    document.getElementById("btn_op_plus").onclick = function () {
        if (a === '') return;
        if (a !== '' && selectedOperation === 'sqrt') {
            a = Math.sqrt(+a);
        }
        if (a !== '' && b !== '') {
            a = getSelectedOperationResult(selectedOperation).toString();
            b = '';
        }
        selectedOperation = '+';
        outputElement.innerHTML = (a + ' ' + selectedOperation);
        operationFinished = false;
    }
    document.getElementById("btn_op_minus").onclick = function () {
        if (a === '') return;
        if (a !== '' && selectedOperation === 'sqrt') {
            a = Math.sqrt(+a);
        }
        if (a !== '' && b !== '') {
            a = getSelectedOperationResult(selectedOperation).toString();
            b = '';
        }
        selectedOperation = '-';
        outputElement.innerHTML = (a + ' ' + selectedOperation);
        operationFinished = false;
    }
    document.getElementById("btn_op_div").onclick = function () {
        if (a === '') return;
        if (a !== '' && selectedOperation === 'sqrt') {
            a = Math.sqrt(+a);
        }
        if (a !== '' && b !== '') {
            a = getSelectedOperationResult(selectedOperation).toString();
            b = '';
        }
        selectedOperation = '/';
        outputElement.innerHTML = (a + ' ' + selectedOperation);
        operationFinished = false;
    }

    document.getElementById("btn_op_sign").onclick = function () {
        if (a === '') return;
        if (b !== '') {
            outputElement.innerHTML = (a + ' ' + selectedOperation + ' (-' + b + ')');
            a = +a;
            b = -b;
        }
        else if (selectedOperation === 'sqrt') {
            negativeFlag = negativeFlag * (-1);
            outputElement.innerHTML = (`${negativeFlag.toString()[0]}√${a}`);
        }
        else {
            outputElement.innerHTML = -a;
            a = -a;
            //selectedOperation = 'sign';
        }
    }

    document.getElementById("btn_op_sqrt").onclick = function () {
        if (a === '') return;
        if (a !== '' && b !== '') {
            console.log(a, selectedOperation, b);
            a = getSelectedOperationResult(selectedOperation).toString();
            b = '';
        }
        selectedOperation = 'sqrt';
        outputElement.innerHTML = (`√${a}`);
    }

    document.getElementById("btn_op_clear").onclick = function () {
        a = '0'
        b = ''
        selectedOperation = ''
        expressionResult = ''
        outputElement.innerHTML = 0
    }

    document.getElementById("btn_op_equal").onclick = function () {
        if ((a === '' || !selectedOperation) || (b == '' && selectedOperation !== 'sqrt'))
            return
        
        console.log(selectedOperation);
        switch (selectedOperation) {
            case 'x':
                expressionResult = ((+a) * (+b)) * negativeFlag;
                break;
            case '+':
                expressionResult = ((+a) + (+b)) * negativeFlag;
                break;
            case '-':
                expressionResult = ((+a) - (+b)) * negativeFlag;
                break;
            case '/':
                expressionResult = ((+a) / (+b)) * negativeFlag;
                break;
            case 'sqrt':
                expressionResult = Math.sqrt(+a) * negativeFlag;
            default:
                break;
        }

        if (isNaN(expressionResult)) {
            a = "Error: square root of negative number";
        } else {
            a = expressionResult.toString();
        }

        b = '';
        selectedOperation = null;
        operationFinished = true;

        outputElement.innerHTML = a;
    }
};
