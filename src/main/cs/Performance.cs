/*
 * Performance.cs: C# implementation of the peg solitaire solver.
 * C# translation by Jeffrey Mo
 * 
 * License from the original Java version:
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

using System;
using System.Collections.Generic;
using System.Text;

namespace ca.tjug.talks.performance
{
    public class Coordinate
    {
        private readonly int hole;
        private readonly int row;

        /// <summary>
        /// Creates a new coordinate instance. Arguments are checked to ensure they
        /// make sense according to the board's structure.
        /// </summary>
        /// <param name="row"></param>
        /// <param name="hole"></param>
        /// <exception cref="System.ArgumentException">
        /// if <tt>hole &lt; 1</tt> or <tt>hole &gt; row</tt>.
        /// </exception>
        public Coordinate(int row, int hole)
        {
            if (hole < 1)
            {
                throw new System.ArgumentException("Illegal hole number: " + hole + " < 1");
            }
            if (hole > row)
            {
                throw new System.ArgumentException("Illegal hole number: " + hole + " > " + row);
            }
            this.hole = hole;
            this.row = row;
        }

        public int GetRow()
        {
            return row;
        }

        public int GetHole()
        {
            return hole;
        }

        /// <summary>
        /// Returns all possible moves from this coordinate, regardless of board 
        /// state.
        /// </summary>
        /// <param name="rowCount">
        /// the number of rows on the board to which the moves will be
        /// applied. This is needed in order to avoid returning moves
        /// that go past the bottom of your board.
        /// </param>

        public ICollection<Move> PossibleMoves(int rowCount)
        {
            List<Move> moves = new List<Move>();
            if (row >= 3)
            {
                // up-left
                if (hole >= 3)
                {
                    moves.Add(new Move(
                            this,
                            new Coordinate(row - 1, hole - 1),
                            new Coordinate(row - 2, hole - 2)));
                }

                // up-right
                if (row - hole >= 2)
                {
                    moves.Add(new Move(
                            this,
                            new Coordinate(row - 1, hole),
                            new Coordinate(row - 2, hole)));
                }
            }

            // leftward (needs at least 2 pegs to the left)
            if (hole >= 3)
            {
                moves.Add(new Move(
                        this,
                        new Coordinate(row, hole - 1),
                        new Coordinate(row, hole - 2)));
            }

            // rightward (needs at least 2 holes to the right)
            if (row - hole >= 2)
            {
                moves.Add(new Move(
                        this,
                        new Coordinate(row, hole + 1),
                        new Coordinate(row, hole + 2)));
            }

            // downward (needs at least 2 rows below)
            if (rowCount - row >= 2)
            {

                // down-left (always possible when there are at least 2 rows below)
                moves.Add(new Move(
                        this,
                        new Coordinate(row + 1, hole),
                        new Coordinate(row + 2, hole)));

                // down-right (always possible when there are at least 2 rows below)
                moves.Add(new Move(
                        this,
                        new Coordinate(row + 1, hole + 1),
                        new Coordinate(row + 2, hole + 2)));
            }

            return moves;
        }

        public override String ToString()
        {
            return "r" + row + "h" + hole;
        }

        public override int GetHashCode()
        {
            const int prime = 31;
            int result = 1;
            result = prime * result + hole;
            result = prime * result + row;
            return result;
        }

        public override bool Equals(Object obj)
        {
            if (this == obj)
                return true;
            if (obj == null)
                return false;
            if (GetType() != obj.GetType())
                return false;
            Coordinate other = (Coordinate)obj;
            if (hole != other.hole)
                return false;
            if (row != other.row)
                return false;
            return true;
        }
    }

    /// <summary>
    /// Represents a single move in the game. No effort is made to ensure the move is
    /// </summary>
    public class Move
    {
        private readonly Coordinate from;
        private readonly Coordinate jumped;
        private readonly Coordinate to;

        /// <summary>
        /// </summary>
        /// <param name="from"></param>
        /// <param name="jumped"></param>
        /// <param name="to"></param>
        public Move(Coordinate from, Coordinate jumped, Coordinate to)
        {
            this.from = from;
            this.jumped = jumped;
            this.to = to;
        }

        public Coordinate GetFrom()
        {
            return from;
        }

        public Coordinate GetJumped()
        {
            return jumped;
        }

        public Coordinate GetTo()
        {
            return to;
        }

        public override String ToString()
        {
            return from + " -> " + jumped + " -> " + to;
        }

        public override int GetHashCode()
        {
            const int prime = 31;
            int result = 1;
            result = prime * result + ((from == null) ? 0 : from.GetHashCode());
            result = prime * result + ((jumped == null) ? 0 : jumped.GetHashCode());
            result = prime * result + ((to == null) ? 0 : to.GetHashCode());
            return result;
        }

        public override bool Equals(Object obj)
        {
            if (this == obj)
                return true;
            if (obj == null)
                return false;
            if (GetType() != obj.GetType())
                return false;
            Move other = (Move)obj;
            if (from == null)
            {
                if (other.from != null)
                    return false;
            }
            else if (!from.Equals(other.from))
                return false;
            if (jumped == null)
            {
                if (other.jumped != null)
                    return false;
            }
            else if (!jumped.Equals(other.jumped))
                return false;
            if (to == null)
            {
                if (other.to != null)
                    return false;
            }
            else if (!to.Equals(other.to))
                return false;
            return true;
        }
    }

    /// <summary>
    /// Represents a state of the board in a game of "peg solitaire." The board is an
    /// equilateral triangle arranged thusly:
    /// <pre>
    /// Row
    /// 1     *
    /// 2    * *
    /// 3   * * *    (this diagram depicts a 5-row board)
    /// 4  * * * *
    /// 5 * * * * *
    /// </pre>
    /// 
    /// Each asterisk represents a "hole" which can be in the "occupied" (contains a
    /// peg) or "unoccupied" (no peg) state. Note that each row has the same number
    /// of holes as its rank: row 1 has 1 hole, row 2 has 2 holes, and so on.
    /// <p>
    /// Given a board state, there are zero or more legal moves by which a different
    /// board state can be reached.
    /// </summary>
    public class GameState
    {
        private readonly int rowCount;
        private readonly List<Coordinate> occupiedHoles;

        /// <summary>
        /// Creates a new game state with all holes occupied except the one given. 
        /// On a board with 5 rows, row 3 hole 2 is the traditional choice for the
        /// empty hole.
        /// </summary>
        /// <param name="rows"/>
        /// <param name="emptyHole"/>
        public GameState(int rows, Coordinate emptyHole)
        {
            this.rowCount = rows;
            occupiedHoles = new List<Coordinate>();
            for (int row = 1; row <= rows; row++)
            {
                for (int hole = 1; hole <= row; hole++)
                {
                    Coordinate peg = new Coordinate(row, hole);
                    if (!peg.Equals(emptyHole))
                    {
                        occupiedHoles.Add(peg);
                    }
                }
            }
        }

        /// <summary>
        /// Creates a new game state by applying the given move to the given starting
        /// state. Verifies the move's validity, throwing an exception if the move is
        /// illegal.
        /// </summary>
        /// <param name="initialState"></param>
        /// <param name="applyMe"></param>
        private GameState(GameState initialState, Move applyMe)
        {
            rowCount = initialState.rowCount;
            occupiedHoles = new List<Coordinate>(initialState.occupiedHoles);
            if (!occupiedHoles.Remove(applyMe.GetFrom()))
            {
                throw new ArgumentException(
                        "Move is not consistent with game state: 'from' hole was unoccupied.");
            }
            if (!occupiedHoles.Remove(applyMe.GetJumped()))
            {
                throw new ArgumentException(
                        "Move is not consistent with game state: jumped hole was unoccupied.");
            }
            if (occupiedHoles.Contains(applyMe.GetTo()))
            {
                throw new ArgumentException(
                        "Move is not consistent with game state: 'to' hole was occupied.");
            }
            if (applyMe.GetTo().GetRow() > rowCount || applyMe.GetTo().GetRow() < 1)
            {
                throw new ArgumentException(
                        "Move is not legal because the 'to' hole does not exist: " + applyMe.GetTo());
            }
            occupiedHoles.Add(applyMe.GetTo());
        }

        public List<Move> LegalMoves()
        {
            List<Move> legalMoves = new List<Move>();
            foreach (Coordinate c in occupiedHoles)
            {
                ICollection<Move> possibleMoves = c.PossibleMoves(rowCount);

                foreach (Move m in possibleMoves)
                {
                    if (occupiedHoles.Contains(m.GetJumped()) && !occupiedHoles.Contains(m.GetTo()))
                    {
                        legalMoves.Add(m);
                    }
                }
            }
            return legalMoves;
        }

        public GameState Apply(Move move)
        {
            return new GameState(this, move);
        }

        public int PegsRemaining()
        {
            return occupiedHoles.Count;
        }

        /// <summary>
        /// Returns the full board state in a multiline string arranged to resemble a
        /// real board. '*' characters signify occupied holes, and 'O' characters
        /// signify empty ones.
        /// </summary>
        public override String ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Game with " + PegsRemaining() + " pegs:" + "\n");
            for (int row = 1; row <= rowCount; row++)
            {
                int indent = rowCount - row;
                for (int i = 0; i < indent; i++)
                {
                    sb.Append(" ");
                }
                for (int hole = 1; hole <= row; hole++)
                {
                    if (occupiedHoles.Contains(new Coordinate(row, hole)))
                    {
                        sb.Append(" *");
                    }
                    else
                    {
                        sb.Append(" O");
                    }
                }
                sb.Append("\n");
            }
            return sb.ToString();
        }

    }

    /// <summary>
    /// This is the test driver for the other classes in this package. It creates an
    /// initial game state and then searches that board's entire state space,
    /// collecting the winning sequences of moves and final board states as it goes.
    /// </summary>
    public class SolutionFinder
    {
        private long gamesPlayed;
        private List<List<Move>> solutions = new List<List<Move>>();
        private long startTime;
        private long endTime;

        private void search(GameState gs, Stack<Move> moveStack)
        {
            if (gs.PegsRemaining() == 1)
            {
                //            System.out.println("Found a winning sequence. Final state:");
                //            System.out.println(gs);

                solutions.Add(new List<Move>(moveStack));

                gamesPlayed++;

                return;
            }

            List<Move> legalMoves = gs.LegalMoves();

            if (legalMoves.Count == 0)
            {
                gamesPlayed++;
                return;
            }

            foreach (Move m in legalMoves)
            {
                GameState nextState = gs.Apply(m);
                moveStack.Push(m);
                search(nextState, moveStack);
                moveStack.Pop();
            }
        }


        public void run()
        {
            startTime = DateTime.Now.Ticks; // 1 "Tick" = 100 nanoseconds
            GameState gs = new GameState(5, new Coordinate(3, 2));
            search(gs, new Stack<Move>());
            endTime = DateTime.Now.Ticks;

            Console.WriteLine(String.Format("Games played:    {0,6:d}", gamesPlayed));
            Console.WriteLine(String.Format("Solutions found: {0,6:d}", solutions.Count));
            Console.WriteLine(String.Format("Time elapsed:    {0,6:d}ms", (endTime - startTime) / 10000));
        }

        static void Main(string[] args)
        {
            new SolutionFinder().run();
        }
    }
}
