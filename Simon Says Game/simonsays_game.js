let gameSeq = [];
let userSeq = [];

let btns = ["yellow","red","purple","green"];

let started = false;
let level = 0;

let h2 = document.querySelector("h2");

document.addEventListener("keypress", function() {  // we are selecting the entire document here any key can be pressed 
if(started == false) {
    console.log("game is started");
    started = true;

    levelUp();
} 
});

function levelUp() {
    level++;
    h2.innerText = `Level ${level}`;

    // random button choose
    let randIdx = Math.floor(Math.random()*3);
    let randColor = btns[randIdx];
    let randbtn = document.querySelector(`.${randColor}`);
    
    console.log(randIdx);
    console.log(randColor);
    console.log(randbtn);

    gameFlash(randbtn);
}

function gameFlash(btn) {
    btn.classList.add("flash"); // first we are adding this flash class to change the background color
    setTimeout(function() {    // the we are removing the flash class after 1 second to make a button flash effect
        btn.classList.remove("flash");
    },250);
}

function userFlash(btn) {
    btn.classList.add("userflash"); // first we are adding this flash class to change the background color
    setTimeout(function() {    // the we are removing the flash class after 1 second to make a button flash effect
        btn.classList.remove("userflash");
    },250);
}

function btnPress() {
    console.log(this)
    let btn = this;
    userFlash(btn); 
};

let allBtns = document.querySelectorAll(".btn");
for(btn of allBtns) {
    btn.addEventListener("click", btnPress)
}