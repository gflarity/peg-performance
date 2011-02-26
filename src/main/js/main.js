// This main file is designed to work with node.js
// To run in a browser, use performance.html

var gamesPlayed = 0;
var solutions = [];

function search(gs, moveStack) {
    if (gs.pegsRemaining() == 1) {
//        console.log("Found a winning sequence. Final state:\n");
//        console.log(gs);
//        console.log("\n");

        var moveStackCopy = [];
        for (var i = 0; i < moveStack.length; i++) {
            moveStackCopy[i] = moveStack[i];
        }
        solutions.push(moveStackCopy);
        
        gamesPlayed++;
        
        return;
    }
    
    var legalMoves = gs.legalMoves();
    
    if (legalMoves.length == 0) {
        gamesPlayed++;
        return;
    }
    
    for (var i = 0; i < legalMoves.length; i++) {
    	var m = legalMoves[i];
        var nextState = gs.applyMove(m);
        moveStack.push(m);
        search(nextState, moveStack);
        moveStack.pop();
    }
}

var start = new Date;
var gs = new GameState(5, new Coordinate(3, 2));
search(gs, []);
var end = new Date;

console.log("Games played:    " + gamesPlayed);
console.log("Solutions found: " + solutions.length);
console.log("Time elapsed:    " + (end - start) + "ms");
