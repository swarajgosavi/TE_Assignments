// menu.js

let selectedItemIndex = null;

function addItem() {
    const itemName = document.getElementById('itemName').value;
    const itemPrice = document.getElementById('itemPrice').value;

    if (itemName && itemPrice) {
        const table = document.getElementById('menuTable');
        const newRow = table.insertRow(-1);
        const cell1 = newRow.insertCell(0);
        const cell2 = newRow.insertCell(1);
        const cell3 = newRow.insertCell(2);
        const cell4 = newRow.insertCell(3);

        cell1.textContent = table.rows.length - 1;
        cell2.textContent = itemName;
        cell3.textContent = itemPrice;
        cell4.innerHTML = '<button onclick="editItem(' + (table.rows.length - 1) + ')">Edit</button>' +
                          '<button onclick="deleteItem(' + (table.rows.length - 1) + ')">Delete</button>';

        clearForm();
    }
}

function editItem(index) {
    const table = document.getElementById('menuTable');
    const selectedItem = table.rows[index].cells;

    document.getElementById('itemName').value = selectedItem[1].textContent;
    document.getElementById('itemPrice').value = selectedItem[2].textContent;

    selectedItemIndex = index;
    toggleButtons(true);
}

function updateItem() {
    const itemName = document.getElementById('itemName').value;
    const itemPrice = document.getElementById('itemPrice').value;

    if (itemName && itemPrice) {
        const table = document.getElementById('menuTable');
        const selectedItem = table.rows[selectedItemIndex].cells;

        selectedItem[1].textContent = itemName;
        selectedItem[2].textContent = itemPrice;

        clearForm();
    }
}

function deleteItem(index) {
    const table = document.getElementById('menuTable');
    table.deleteRow(index);
    clearForm();
}

function clearForm() {
    document.getElementById('itemName').value = '';
    document.getElementById('itemPrice').value = '';
    selectedItemIndex = null;
    toggleButtons(false);
}

function toggleButtons(isEdit) {
    const addButton = document.querySelector('#menuForm button:first-of-type');
    const updateButton = document.querySelector('#menuForm button:last-of-type');

    addButton.disabled = isEdit;
    updateButton.disabled = !isEdit;
}
