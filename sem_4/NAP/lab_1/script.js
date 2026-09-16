let btn = document.getElementById('btn');
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

    const background = document.querySelectorAll('.calculator_bg');
    if (background[1].classList.contains('_white') && background[1].classList.contains('_invisible')) {
        console.log(background.length);
        background[1].classList.remove('_invisible');
        background[0].classList.add('_invisible');
    } else if (background[0].classList.contains('_black') && background[0].classList.contains('_invisible')) {
        console.log(background.length);
        background[0].classList.remove('_invisible');
        background[1].classList.add('_invisible');
    }
});

function ibg() {
    let ibg = document.querySelectorAll(".ibg");
    for (var i = 0; i < ibg.length; i++) {
        if (ibg[i].querySelector('img')) {
            ibg[i].style.backgroundImage = 'url(' + ibg[i].querySelector('img').getAttribute('src') + ')';
        }
    }
}

ibg();
