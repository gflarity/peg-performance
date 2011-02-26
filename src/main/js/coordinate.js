/* 
 * coordinate.js
 * 
 * Copyright (c) 2010, Jonathan Fuerth
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Jonathan Fuerth nor the names of other
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

function Coordinate(row, hole) {

	if (hole < 1) {
		throw new IllegalArgumentException("Illegal hole number: " + hole + " < 1");
	}
	if (hole > row) {
		throw new IllegalArgumentException("Illegal hole number: " + hole + " on row " + row);
	}

	this.getRow = function() { return row; }
	this.getHole = function() { return hole; }
	
	this.possibleMoves = function(rowCount) {
		var moves = [];

		// upward (needs at least 2 rows above)
		if (row >= 3) {

			// up-left
			if (hole >= 3) {
				moves.push(new Move(
						this,
						new Coordinate(row - 1, hole - 1),
						new Coordinate(row - 2, hole - 2)));
			}

			// up-right
			if (row - hole >= 2) {
				moves.push(new Move(
						this,
						new Coordinate(row - 1, hole),
						new Coordinate(row - 2, hole)));
			}
		}

		// leftward (needs at least 2 pegs to the left)
		if (hole >= 3) {
			moves.push(new Move(
					this,
					new Coordinate(row, hole - 1),
					new Coordinate(row, hole - 2)));
		}

		// rightward (needs at least 2 holes to the right)
		if (row - hole >= 2) {
			moves.push(new Move(
					this,
					new Coordinate(row, hole + 1),
					new Coordinate(row, hole + 2)));
		}

		// downward (needs at least 2 rows below)
		if (rowCount - row >= 2) {

			// down-left (always possible when there are at least 2 rows below)
			moves.push(new Move(
					this,
					new Coordinate(row + 1, hole),
					new Coordinate(row + 2, hole)));

			// down-right (always possible when there are at least 2 rows below)
			moves.push(new Move(
					this,
					new Coordinate(row + 1, hole + 1),
					new Coordinate(row + 2, hole + 2)));
		}

		return moves;
	}

	this.toString = function() {
        return "r" + row + "h" + hole;
	}
	
	this.equals = function(obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (this.prototype != obj.prototype)
            return false;
        
        if (obj.getHole == undefined) {
        	throw new Error("The given object doesn't look like a coordinate");
        }
        
        if (hole != obj.getHole())
            return false;
        if (row != obj.getRow())
            return false;
        return true;
	}
};
