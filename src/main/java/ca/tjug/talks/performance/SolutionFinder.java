/*
 * Created on Jan 3, 2010
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
import java.util.List;
import java.util.Stack;

/**
 * This is the test driver for the other classes in this package. It creates an
 * initial game state and then searches that board's entire state space,
 * collecting the winning sequences of moves and final board states as it goes.
 * 
 * @author fuerth
 */
public class SolutionFinder {

    private long gamesPlayed;
    private List<List<Move>> solutions = new ArrayList<List<Move>>();
    private long startTime;
    private long endTime;
    
    private void search(GameState gs, Stack<Move> moveStack) {
        if (gs.pegsRemaining() == 1) {
//            System.out.println("Found a winning sequence. Final state:");
//            System.out.println(gs);
            
            solutions.add(new ArrayList<Move>(moveStack));
            
            gamesPlayed++;
            
            return;
        }
        
        List<Move> legalMoves = gs.legalMoves();
        
        if (legalMoves.isEmpty()) {
            gamesPlayed++;
            return;
        }
        
        for (Move m : legalMoves) {
            GameState nextState = gs.apply(m);
            moveStack.push(m);
            search(nextState, moveStack);
            moveStack.pop();
        }
    }

    public void run() {
        startTime = System.nanoTime();
        GameState gs = new GameState(5, new Coordinate(3, 2));
        search(gs, new Stack<Move>());
        endTime = System.nanoTime();
        
        System.out.printf("Games played:    %6d%n", gamesPlayed);
        System.out.printf("Solutions found: %6d%n", solutions.size());
        System.out.printf("Time elapsed:    %6dms%n", (endTime - startTime) / 1000000);
    }
    
    public static void main(String[] args) {
        new SolutionFinder().run();
    }

}
