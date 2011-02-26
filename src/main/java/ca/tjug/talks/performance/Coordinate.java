/*
 * Created on Jan 2, 2010
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
package ca.tjug.talks.performance;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

class Coordinate {
    private final int hole;
    private final int row;

    /**
     * Creates a new coordinate instance. Arguments are checked to ensure they
     * make sense according to the board's structure.
     * 
     * @param row
     *            The row number. The first row is number 1, not 0.
     * @param hole
     *            The hole number within the given row, counting from the left.
     *            The first hole is 1, not 0.
     * @throws IllegalArgumentException
     *             if <tt>hole &lt; 1</tt> or <tt>hole &gt; row</tt>.
     */
    public Coordinate(int row, int hole) {
        if (hole < 1) {
            throw new IllegalArgumentException("Illegal hole number: " + hole + " < 1");
        }
        if (hole > row) {
            throw new IllegalArgumentException("Illegal hole number: " + hole + " on row " + row);
        }
        this.hole = hole;
        this.row = row;
    }

    public int getRow() {
        return row;
    }
    
    public int getHole() {
        return hole;
    }
    
    /**
     * Returns all possible moves from this coordinate, regardless of board
     * state.
     * 
     * @param rowCount
     *            the number of rows on the board to which the moves will be
     *            applied. This is needed in order to avoid returning moves
     *            that go past the bottom of your board.
     */
    public Collection<Move> possibleMoves(int rowCount) {
        List<Move> moves = new ArrayList<Move>();
        
        // upward (needs at least 2 rows above)
        if (row >= 3) {
            
            // up-left
            if (hole >= 3) {
                moves.add(new Move(
                        this,
                        new Coordinate(row - 1, hole - 1),
                        new Coordinate(row - 2, hole - 2)));
            }
            
            // up-right
            if (row - hole >= 2) {
                moves.add(new Move(
                        this,
                        new Coordinate(row - 1, hole),
                        new Coordinate(row - 2, hole)));
            }
        }
        
        // leftward (needs at least 2 pegs to the left)
        if (hole >= 3) {
            moves.add(new Move(
                    this,
                    new Coordinate(row, hole - 1),
                    new Coordinate(row, hole - 2)));
        }
        
        // rightward (needs at least 2 holes to the right)
        if (row - hole >= 2) {
            moves.add(new Move(
                    this,
                    new Coordinate(row, hole + 1),
                    new Coordinate(row, hole + 2)));
        }

        // downward (needs at least 2 rows below)
        if (rowCount - row >= 2) {
            
            // down-left (always possible when there are at least 2 rows below)
            moves.add(new Move(
                    this,
                    new Coordinate(row + 1, hole),
                    new Coordinate(row + 2, hole)));
            
            // down-right (always possible when there are at least 2 rows below)
            moves.add(new Move(
                    this,
                    new Coordinate(row + 1, hole + 1),
                    new Coordinate(row + 2, hole + 2)));
        }
        
        return moves;
    }

    @Override
    public String toString() {
        return "r" + row + "h" + hole;
    }
    
    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + hole;
        result = prime * result + row;
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Coordinate other = (Coordinate) obj;
        if (hole != other.hole)
            return false;
        if (row != other.row)
            return false;
        return true;
    }

}