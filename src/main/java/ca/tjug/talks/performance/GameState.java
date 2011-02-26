/*
 * Created on Jan 1, 2010
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
import java.util.Iterator;
import java.util.List;

/**
 * Represents a state of the board in a game of "peg solitaire." The board is an
 * equilateral triangle arranged thusly:
 * 
 * <pre>
 * Row
 *   1     *
 *   2    * *
 *   3   * * *    (this diagram depicts a 5-row board)
 *   4  * * * *
 *   5 * * * * *
 * </pre>
 * 
 * Each asterisk represents a "hole" which can be in the "occupied" (contains a
 * peg) or "unoccupied" (no peg) state. Note that each row has the same number
 * of holes as its rank: row 1 has 1 hole, row 2 has 2 holes, and so on.
 * <p>
 * Given a board state, there are zero or more legal moves by which a different
 * board state can be reached.
 * 
 * @author fuerth
 */
public class GameState {

    private final int rowCount;
    
    private final List<Coordinate> occupiedHoles;

    /**
     * Creates a new game state with all holes occupied except the one given. On
     * a board with 5 rows, row 3 hole 2 is the traditional choice for the empty
     * hole.
     * 
     * @param rows
     */
    GameState(int rows, Coordinate emptyHole) {
        this.rowCount = rows;
        occupiedHoles = new ArrayList<Coordinate>();
        for (int row = 1; row <= rows; row++) {
            for (int hole = 1; hole <= row; hole++) {
                Coordinate peg = new Coordinate(row, hole);
                if (!peg.equals(emptyHole)) {
                    occupiedHoles.add(peg);
                }
            }
        }
    }

    /**
     * Creates a new game state by applying the given move to the given starting
     * state. Verifies the move's validity, throwing an exception if the move is
     * illegal.
     * 
     * @param initialState
     * @param applyMe
     */
    private GameState(GameState initialState, Move applyMe) {
        rowCount = initialState.rowCount;
        occupiedHoles = new ArrayList<Coordinate>(initialState.occupiedHoles);
        if (!occupiedHoles.remove(applyMe.getFrom())) {
            throw new IllegalArgumentException(
                    "Move is not consistent with game state: 'from' hole was unoccupied.");
        }
        if (!occupiedHoles.remove(applyMe.getJumped())) {
            throw new IllegalArgumentException(
                    "Move is not consistent with game state: jumped hole was unoccupied.");
        }
        if (occupiedHoles.contains(applyMe.getTo())) {
            throw new IllegalArgumentException(
                    "Move is not consistent with game state: 'to' hole was occupied.");
        }
        if (applyMe.getTo().getRow() > rowCount || applyMe.getTo().getRow() < 1) {
            throw new IllegalArgumentException(
                    "Move is not legal because the 'to' hole does not exist: " + applyMe.getTo());
        }
        occupiedHoles.add(applyMe.getTo());
    }
    
    public List<Move> legalMoves() {
        List<Move> legalMoves = new ArrayList<Move>();
        for (Coordinate c : occupiedHoles) {
            Collection<Move> possibleMoves = c.possibleMoves(rowCount);
            Iterator<Move> it = possibleMoves.iterator();
            while (it.hasNext()) {
                Move m = it.next();
                if (occupiedHoles.contains(m.getJumped()) && !occupiedHoles.contains(m.getTo())) {
                    legalMoves.add(m);
                }
            }
        }
        return legalMoves;
    }
    
    public GameState apply(Move move) {
        return new GameState(this, move);
    }

    public int pegsRemaining() {
        return occupiedHoles.size();
    }

    /**
     * Returns the full board state in a multiline string arranged to resemble a
     * real board. '*' characters signify occupied holes, and 'O' characters
     * signify empty ones.
     */
    @Override
    public String toString() {
        final String nl = System.getProperty("line.separator");
        StringBuilder sb = new StringBuilder();
        sb.append("Game with " + pegsRemaining() + " pegs:" + nl);
        for (int row = 1; row <= rowCount; row++) {
            int indent = rowCount - row;
            for (int i = 0; i < indent; i++) {
                sb.append(" ");
            }
            for (int hole = 1; hole <= row; hole++) {
                if (occupiedHoles.contains(new Coordinate(row, hole))) {
                    sb.append(" *");
                } else {
                    sb.append(" O");
                }
            }
            sb.append(nl);
        }
        return sb.toString();
    }

}
