// script.js

let buffer = [];

function handleNumber(element) {
    let num = element.value;

    if (num == 0 && buffer[1] == "÷") {
        alert("Cannot divide by zero");
        handleAC()
        return
    }

    buffer.push(num)

    updateScreen();
}

function handleOperation(element) {
    let ope = element.value;

    buffer.push(ope)
    updateScreen();
}

function handleAC() {
    document.getElementById("screen").value = null;
    buffer = [];
}

function handleEquals() {
    if (buffer.length < 3) {
        alert("Invalid expression");
        return;
    }

    let lhs = Number(buffer[0]);
    let sign = buffer[1];
    let rhs = Number(buffer[2]);

    let result;

    switch (sign) {
        case "+":
            result = lhs + rhs;
            break;
        case "−":
            result = lhs - rhs;
            break;
        case "×":
            result = lhs * rhs;
            break;
        case "÷":
            if (rhs === 0) {
                alert("Cannot divide by zero");
                handleAC();
                return;
            }
            result = lhs / rhs;
            break;
        default:
            result = "Error"
    }
    buffer = [result]
    updateScreen();
}

function updateScreen() {
    let show = buffer.join("");
    document.getElementById("screen").value = show;
}
