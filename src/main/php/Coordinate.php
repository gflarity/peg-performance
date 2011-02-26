<?php

class Coordinate {
	private $hole;
	private $row;
	
	public function __construct($row, $hole) {
		if ($hole < 1) {
			throw new Exception("Illegal hole number: " . $hole . " < 1");
		}
		if ($hole > $row) {
			throw new Exception("Illegal hole number: " . $hole . " on row " . $row);
		}
		$this->hole = $hole;
		$this->row = $row;
	}
	
	public function getRow() {
		return $this->row;
	}
	
	public function getHole() {
		return $this->hole;
	}
	
	public function possibleMoves($rowCount) {
		$moves = array();
		
		// upward
		if ($this->row >= 3) {
			
			// up-left
			if ($this->hole >= 3) {
				array_push($moves,new Move($this, 
					new Coordinate($this->row - 1, $this->hole - 1),
					new Coordinate($this->row - 2, $this->hole - 2)));
			}
			
			// up-right
			if ($this->row - $this->hole >= 2) {
				array_push($moves,new Move($this, 
					new Coordinate($this->row - 1, $this->hole),
					new Coordinate($this->row - 2, $this->hole)));
			}
		}	
		
		// leftward (needs 2 pegs to left)
		if ($this->hole >= 3) {
			array_push($moves,new Move($this,
				new Coordinate($this->row, $this->hole - 1),
				new Coordinate($this->row, $this->hole - 2)));	
		}
		
		// rightward
		if (($this->row - $this->hole) >= 2) {
			array_push($moves,new Move($this,
				new Coordinate($this->row, $this->hole + 1),
				new Coordinate($this->row, $this->hole + 2)));
		}
		
		// downward
		if ($rowCount - $this->row >= 2) {
			
				//down-left
				array_push($moves,new Move($this,
					new Coordinate($this->row + 1, $this->hole),
					new Coordinate($this->row + 2, $this->hole)));
				
				// down-right
				array_push($moves,new Move($this,
					 new Coordinate($this->row + 1, $this->hole + 1),
					 new Coordinate($this->row + 2, $this->hole + 2)));
		}
		
		return $moves;
	}
	
	public function toString() {
		return "r" . $this->row . "h" . $this->hole;
	}
}

?>