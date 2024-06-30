//Helper class that will deal with text regarding helpful information
class Helper {
    constructor() {
        this.snookerTable = snookerTable;
        this.textX = this.snookerTable.x;
        this.textY = this.snookerTable.y + this.snookerTable.height/2 + 50;
        this.textSize = 16;
        this.text = ["Welcome to Snooker!", "Press '1, 2, or 3' to reset the game in different states", "Press and hold 'alt+right-click' to place the cue ball in the ARC of the table", 
            "Press and hold 'space+right-click' and pull the mouse to control the cue and how hard you hit"];
    }
    //Function to draw the helper text to canvas for additional information of how to play the game
    draw() {
        push();
        fill(255);
        textSize(this.textSize);
        textAlign(CENTER);
        this.text.forEach((line, index) => {
            text(line, this.textX, this.textY + (index+1)*this.textSize);
        });
        pop();
    }
}