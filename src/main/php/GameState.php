<?php

require_once("utils.php");
class GameState {

    private $rowCount;
    private $occupiedHoles;

 
    private function __construct() {
     
    }
    
    /**
     * Creates a new game state with all holes occupied except the one given. On
     * a board with 5 rows, row 3 hole 2 is the traditional choice for the empty
     * hole.
     * 
     * @param rows
     */   
	public static function newGame($rows, $emptyHole) {
		$gameState = new GameState();
		$gameState->rowCount = $rows;
     	$gameState->occupiedHoles = array();
     	for ($row = 1; $row <= $rows; $row++) {
     		for ($hole = 1; $hole <= $row; $hole++) {
     			$peg = new Coordinate($row, $hole);
     			if ($peg != $emptyHole) {
     				array_push($gameState->occupiedHoles, $peg);
     			}
      		}
     	}
        return $gameState;
	}
	
    /**
     * Creates a new game state by applying the given move to the given starting
     * state. Verifies the move's validity, throwing an exception if the move is
     * illegal.
     * 
     * @param initialState
     * @param applyMe
     */
    
    public static function applyMove($initialState, $applyMe) {
    	$gameState = new GameState();
    	$gameState->rowCount = $initialState->rowCount;
    	$gameState->occupiedHoles = $initialState->occupiedHoles; // this is a copy
    	$gameState->occupiedHoles = array_remove($gameState->occupiedHoles, $applyMe->getFrom());
    	if ($gameState->occupiedHoles === false) {
    		throw new Exception("Move is not consistent with game state: 'from' hole was unoccupied.");
    	}
    	$gameState->occupiedHoles = array_remove($gameState->occupiedHoles, $applyMe->getJumped());
    	if ($gameState->occupiedHoles === false) {
    		throw new Exception("Move is not consistent with game state: jumped hole was unoccupied.");
    	}
    	if (array_search($applyMe->getTo(),$gameState->occupiedHoles) !== false) {
    		throw new Exception("Move is not consistent with game state: 'to' hole was occupied.");	
    	}
    	if ($applyMe->getTo()->getRow() > $gameState->rowCount || $applyMe->getTo()->getRow() < 1) {
    		throw new Exception("Move is not legal because the 'to' hole does not exist: ".$applyMe->getTo());
    	}
    	array_push($gameState->occupiedHoles,$applyMe->getTo());
    	return $gameState;
    }

	public function legalMoves() {
		$legalMoves = array();
		foreach($this->occupiedHoles as $coordinate)  {
			$possibleMoves = $coordinate->possibleMoves($this->rowCount);
			foreach($possibleMoves as $move) {
				if ((array_search($move->getJumped(),$this->occupiedHoles) !== false) && !(array_search($move->getTo(),$this->occupiedHoles) !== false)) {
					array_push($legalMoves,$move);
				}
			}
		}
		return $legalMoves;
	}
 
    public function apply($move) {
        return $this->applyMove($this, $move);
    }

    public function pegsRemaining() {
        return count($this->occupiedHoles);
    }

    /**
     * Returns the full board state in a multiline string arranged to resemble a
     * real board. '*' characters signify occupied holes, and 'O' characters
     * signify empty ones.
     */
    public function toString() {
		$out = "";
        $out .= "Game with " . $this->pegsRemaining() . " pegs:\n";
        for ($row = 1; $row <= $this->rowCount; $row++) {
            $indent = $this->rowCount - $row;
            for ($i = 0; $i < $indent; $i++) {
                $out .= " ";
            }
            for ($hole = 1; $hole <= $row; $hole++) {
            	if (array_search(new Coordinate($row, $hole),$this->occupiedHoles) !== false) {
            		$out .= " *";
                } else {
                   	$out .= " O";
                }
            }
            $out .= "\n";
        }
        return $out;
    }
    
  
    
}
?>
