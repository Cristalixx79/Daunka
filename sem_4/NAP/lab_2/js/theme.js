const btn = document.getElementById('btn');
btn.addEventListener("click", function() {
    const buttons = document.querySelectorAll('._changable');
    for (let i = 0; i < buttons.length; i++) {
        if (buttons[i].classList.contains('_black')) {
            buttons[i].classList.remove('_black');
            buttons[i].classList.add('_white');
        }
        else if (buttons[i].classList.contains('_white')) {
            buttons[i].classList.remove('_white');
            buttons[i].classList.add('_black');
        }
    }
});
