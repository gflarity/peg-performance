<?php

require_once("GameState.php");
require_once("Coordinate.php");
require_once("Move.php");

class SolutionFinder {

    private $gamesPlayed;
    private $solutions;
    private $startTime;
    private $endTime;
    
    public function run() {
    	$this->solutions = array();
        $this->startTime = microtime(true)*10000;
        $gs = GameState::newGame(5, new Coordinate(3, 2));
        $moveStack = array();
        $this->search($gs, $moveStack);
        $this->endTime = microtime(true)*10000;
        
        printf("Games played:    %6d\n", $this->gamesPlayed);
        printf("Solutions found: %6d\n", count($this->solutions));
        printf("Time elapsed:    %6dms\n", ($this->endTime - $this->startTime)/10);
    }
    
    private function search($gs, $moveStack) {
        if ($gs->pegsRemaining() == 1) {
           //echo "Found a winning sequence. Final state:\n";
           //echo $gs->toString();
            
            array_push($this->solutions, $moveStack);
            
            $this->gamesPlayed++;
            
            return;
        }
        
        $legalMoves = $gs->legalMoves();
        if (count($legalMoves) == 0) {
            $this->gamesPlayed++;
            return;
        }
        
        foreach ($legalMoves as $move) {
        	$nextState = $gs->apply($move);
        	array_push($moveStack,$move);
        	$this->search($nextState,$moveStack);
        	array_pop($moveStack);
        }
    }
}

$sf = new SolutionFinder();
$sf->run();
?>