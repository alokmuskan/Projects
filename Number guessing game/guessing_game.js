const max = prompt("Enter the max number");
const random = Math.floor(Math.random()*max)+1;
let guess = prompt("Guess the number");
while(true){
    if(guess=="quit"){
        console.log("User quit the game");
        break;
    }

    if(guess==random){
        console.log("You are right ! Congrats !!. Random number was",random);
        break;
    } else if(guess<random){
        guess = prompt("hint : your guess was small. Please try again.");
    } else {
        guess = prompt("hint : your guess was too large . Please try again.");
    }
    // else {
    //     guess = prompt("Your guess was wrong. Please try again .");
    // }
}


 