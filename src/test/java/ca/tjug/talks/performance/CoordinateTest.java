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


import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;

import org.junit.Test;

public class CoordinateTest {

    @Test
    public void testPossibleMovesRow1() throws Exception {
        Coordinate c = new Coordinate(1, 1);
        Collection<Move> expected = Arrays.asList(
                new Move[] {
                        new Move(
                                new Coordinate(1, 1),
                                new Coordinate(2, 1),
                                new Coordinate(3, 1)),
                        new Move(
                                new Coordinate(1, 1),
                                new Coordinate(2, 2),
                                new Coordinate(3, 3)),
                });
        assertCollectionsEqual(expected, c.possibleMoves(5));
    }
    
    @Test
    public void testPossibleMovesRow1TooShort() throws Exception {
        Coordinate c = new Coordinate(1, 1);
        assertCollectionsEqual(Collections.emptyList(), c.possibleMoves(2));
    }

    @Test
    public void testPossibleMovesBottomLeft() throws Exception {
        Coordinate c = new Coordinate(5, 1);
        Collection<Move> expected = Arrays.asList(
                new Move[] {
                        new Move(
                                new Coordinate(5, 1),
                                new Coordinate(4, 1),
                                new Coordinate(3, 1)),
                        new Move(
                                new Coordinate(5, 1),
                                new Coordinate(5, 2),
                                new Coordinate(5, 3)),
                });
        assertCollectionsEqual(expected, c.possibleMoves(5));
    }
    
    @Test
    public void testPossibleMovesBottomRight() throws Exception {
        Coordinate c = new Coordinate(5, 5);
        Collection<Move> expected = Arrays.asList(
                new Move[] {
                        new Move(
                                new Coordinate(5, 5),
                                new Coordinate(4, 4),
                                new Coordinate(3, 3)),
                        new Move(
                                new Coordinate(5, 5),
                                new Coordinate(5, 4),
                                new Coordinate(5, 3)),
                });
        assertCollectionsEqual(expected, c.possibleMoves(5));
    }
    
    @Test
    public void testPossibleMovesBottomMiddle() throws Exception {
        Coordinate c = new Coordinate(5, 3);
        Collection<Move> expected = Arrays.asList(
                new Move[] {
                        new Move(
                                new Coordinate(5, 3),
                                new Coordinate(5, 4),
                                new Coordinate(5, 5)),
                        new Move(
                                new Coordinate(5, 3),
                                new Coordinate(5, 2),
                                new Coordinate(5, 1)),
                        new Move(
                                new Coordinate(5, 3),
                                new Coordinate(4, 2),
                                new Coordinate(3, 1)),
                        new Move(
                                new Coordinate(5, 3),
                                new Coordinate(4, 3),
                                new Coordinate(3, 3)),
                });
        assertCollectionsEqual(expected, c.possibleMoves(5));
    }
    
    @Test
    public void testPossibleMovesRightMiddle() throws Exception {
        Coordinate c = new Coordinate(3, 3);
        Collection<Move> expected = Arrays.asList(
                new Move[] {
                        new Move(
                                new Coordinate(3, 3),
                                new Coordinate(2, 2),
                                new Coordinate(1, 1)),
                        new Move(
                                new Coordinate(3, 3),
                                new Coordinate(4, 4),
                                new Coordinate(5, 5)),
                        new Move(
                                new Coordinate(3, 3),
                                new Coordinate(3, 2),
                                new Coordinate(3, 1)),
                        new Move(
                                new Coordinate(3, 3),
                                new Coordinate(4, 3),
                                new Coordinate(5, 3)),
                });
        assertCollectionsEqual(expected, c.possibleMoves(5));
    }

    @Test
    public void testPossibleMovesFromR4H4() throws Exception {
        Coordinate c = new Coordinate(4, 4);
        Collection<Move> expected = Arrays.asList(
                new Move[] {
                        new Move(
                                new Coordinate(4, 4),
                                new Coordinate(4, 3),
                                new Coordinate(4, 2)),
                        new Move(
                                new Coordinate(4, 4),
                                new Coordinate(3, 3),
                                new Coordinate(2, 2)),
                });
        assertCollectionsEqual(expected, c.possibleMoves(5));
    }

    /**
     * Asserts that the expected collection and the actual collection contain
     * all the same elements, disregarding order.
     * <p>
     * The algorithm is not 100% correct: it compares the given collections by
     * size and then by set equality, so collections A, A, B and A, B, B would
     * be considered equal. This limitation is not a grave risk when testing
     * lists of possible moves.
     * 
     * @param expected
     * @param actual
     */
    static void assertCollectionsEqual(Collection<?> expected, Collection<?> actual) {
        assertEquals(new HashSet<Object>(expected), new HashSet<Object>(actual));
        assertEquals(expected.size(), actual.size());
    }
}
