/*
 * C solution to 15-Hole Peg Soltaire
 *
 * Copyright (c) 2013, Matthew Ling
 *
 * Do what you want, porting to other languages is encouraged
 *
 * The current state of a game can be stored naturally in 15 bits. This program
 * uses a more complex 54 bit form, 3 bits for each of the 18 'triplets'.
 * eg
 *            A
 *           B F
 *          C G J
 *         D H K M
 *        E I L N O
 * Simple form : ABCDEFGHIJKLMNO
 * Complex form: ABCBCDCDEFGHGHIJKLAFJFJMJMOBGKGKNCHLEILILNLNODHKHKMCGJ
 *
 * Notes:
 * * The game state is stored as triplets to make checking for valid moves a
 *   shift and mod operation.
 * * Each triplet has the potential to be 2 valid moves (011 and 110)
 * * Iterating the game state is an addition with a pre-computed constant
 * * All games are played simultaneously in a pool
 * * When a solution is found, the solution list is generated from an array
 *   that has kept track of what moves were done and in what game
 * * Symmetry in the initial game state means we only need to check half the
 *   games, memory allocation is heavily reduced and execution time is sped up
 */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

static struct timeval startTime;
static struct timeval endTime;

static long diff_usec(struct timeval start, struct timeval end)
{
  time_t secs = end.tv_sec - start.tv_sec;
  suseconds_t usecs = end.tv_usec - start.tv_usec;

  return (long) (secs * 1000000L) + usecs;
}

#define SIMPLE_A (1<<14)
#define SIMPLE_B (1<<13)
#define SIMPLE_C (1<<12)
#define SIMPLE_D (1<<11)
#define SIMPLE_E (1<<10)
#define SIMPLE_F (1<< 9)
#define SIMPLE_G (1<< 8)
#define SIMPLE_H (1<< 7)
#define SIMPLE_I (1<< 6)
#define SIMPLE_J (1<< 5)
#define SIMPLE_K (1<< 4)
#define SIMPLE_L (1<< 3)
#define SIMPLE_M (1<< 2)
#define SIMPLE_N (1<< 1)
#define SIMPLE_O (1<< 0)
uint64_t complex_to_simple(uint64_t complex)
{
  uint64_t simple=0ULL;
  if((complex>> 9)%2)
    simple+=SIMPLE_O;
  if((complex>>10)%2)
    simple+=SIMPLE_N;
  if((complex>> 3)%2)
    simple+=SIMPLE_M;
  if((complex>>11)%2)
    simple+=SIMPLE_L;
  if((complex>> 4)%2)
    simple+=SIMPLE_K;
  if((complex>> 0)%2)
    simple+=SIMPLE_J;
  if((complex>>14)%2)
    simple+=SIMPLE_I;
  if((complex>> 5)%2)
    simple+=SIMPLE_H;
  if((complex>> 1)%2)
    simple+=SIMPLE_G;
  if((complex>>32)%2)
    simple+=SIMPLE_F;
  if((complex>>17)%2)
    simple+=SIMPLE_E;
  if((complex>> 8)%2)
    simple+=SIMPLE_D;
  if((complex>> 2)%2)
    simple+=SIMPLE_C;
  if((complex>>26)%2)
    simple+=SIMPLE_B;
  if((complex>>35)%2)
    simple+=SIMPLE_A;
  return simple;
}

int won(uint64_t complex)
{
  uint64_t simple=complex_to_simple(complex);
  if(
      simple==SIMPLE_A || simple==SIMPLE_B || simple==SIMPLE_C || 
      simple==SIMPLE_D || simple==SIMPLE_E || simple==SIMPLE_F || 
      simple==SIMPLE_G || simple==SIMPLE_H || simple==SIMPLE_I || 
      simple==SIMPLE_J || simple==SIMPLE_K || simple==SIMPLE_L || 
      simple==SIMPLE_M || simple==SIMPLE_N || simple==SIMPLE_O
    )
    return 1;
  return 0;
}

int main(int argc, char* argv[])
{
  uint_fast32_t games=0, solutions=0, games_state_num=1;

  uint_fast64_t *games_state;
  uint_fast32_t *backtrack;
  uint_fast8_t *solutions_data;

  uint_fast32_t curr_iteration=0;
  uint_fast8_t alt;
  uint_fast32_t prev;
  int_fast8_t i;

  gettimeofday(&startTime, NULL);

  games_state=malloc(sizeof(uint_fast64_t)*161936);
  backtrack=malloc(sizeof(uint_fast32_t)*161936);
  solutions_data=malloc(sizeof(int_fast8_t)*13*1550);

  int max_states=1;
  games_state[0]=18014261047454639ULL;//going down one half of the board, where the first move is I hops J

  //hop codes, sorted in symmetrical pairs for easy arithmetic later
#define CHOPB 0
#define JHOPF 18

#define AHOPB 1
#define AHOPF 19

#define DHOPC 2
#define MHOPJ 20

#define BHOPC 3
#define FHOPJ 21

#define EHOPD 4
#define OHOPM 22

#define CHOPD 5
#define JHOPM 23

#define HHOPG 6
#define KHOPG 24

#define FHOPG 7
#define BHOPG 25

#define IHOPH 8
#define NHOPK 26

#define GHOPH 9
#define GHOPK 27

#define LHOPK 10
#define LHOPH 28

#define JHOPK 11
#define CHOPH 29

#define LHOPI 12
#define LHOPN 30

#define EHOPI 13
#define OHOPN 31

#define NHOPL 14
#define IHOPL 32

#define KHOPH 15
#define HHOPK 33

#define DHOPH 16
#define MHOPK 34

#define JHOPG 17
#define CHOPG 35

  while(curr_iteration<games_state_num)
  {
    alt=0;
    switch((games_state[curr_iteration]>>0)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(CHOPB<<24);games_state[games_state_num++]=games_state[curr_iteration]+ 2944205946093569ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(AHOPB<<24);games_state[games_state_num++]=games_state[curr_iteration]- 2966196262535173ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>3)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(DHOPC<<24);games_state[games_state_num++]=games_state[curr_iteration]+    5358756560968ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(BHOPC<<24);games_state[games_state_num++]=games_state[curr_iteration]-    5633676411112ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>6)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(EHOPD<<24);games_state[games_state_num++]=games_state[curr_iteration]+  346208702300176ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(CHOPD<<24);games_state[games_state_num++]=games_state[curr_iteration]-  357203819626832ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>9)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(HHOPG<<24);games_state[games_state_num++]=games_state[curr_iteration]+      68583461376ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(FHOPG<<24);games_state[games_state_num++]=games_state[curr_iteration]-      68587665920ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>12)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(IHOPH<<24);games_state[games_state_num++]=games_state[curr_iteration]+     481034011648ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(GHOPH<<24);games_state[games_state_num++]=games_state[curr_iteration]-     618473575424ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>15)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(LHOPK<<24);games_state[games_state_num++]=games_state[curr_iteration]+   34565896542208ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(JHOPK<<24);games_state[games_state_num++]=games_state[curr_iteration]-   35665408333824ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>18)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(JHOPF<<24);games_state[games_state_num++]=games_state[curr_iteration]+ 2949920978065252ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(AHOPF<<24);games_state[games_state_num++]=games_state[curr_iteration]- 2960916095391908ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>21)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(MHOPJ<<24);games_state[games_state_num++]=games_state[curr_iteration]+   10857696193458ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(FHOPJ<<24);games_state[games_state_num++]=games_state[curr_iteration]-   11132616043602ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>24)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(OHOPM<<24);games_state[games_state_num++]=games_state[curr_iteration]+ 5618366983176110ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(JHOPM<<24);games_state[games_state_num++]=games_state[curr_iteration]- 5640357299617714ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>27)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(KHOPG<<24);games_state[games_state_num++]=games_state[curr_iteration]+     284675800569ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(BHOPG<<24);games_state[games_state_num++]=games_state[curr_iteration]-     287360155145ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>30)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(NHOPK<<24);games_state[games_state_num++]=games_state[curr_iteration]+   17326166507511ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(GHOPK<<24);games_state[games_state_num++]=games_state[curr_iteration]-   17898470899705ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>33)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(LHOPH<<24);games_state[games_state_num++]=games_state[curr_iteration]+ 8989333801402367ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(CHOPH<<24);games_state[games_state_num++]=games_state[curr_iteration]- 9024561123164159ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>36)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(LHOPI<<24);games_state[games_state_num++]=games_state[curr_iteration]+      79972489137ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(EHOPI<<24);games_state[games_state_num++]=games_state[curr_iteration]-     354892339281ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>39)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(NHOPL<<24);games_state[games_state_num++]=games_state[curr_iteration]+    4947843661666ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(IHOPL<<24);games_state[games_state_num++]=games_state[curr_iteration]-   15942960988322ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>42)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(OHOPN<<24);games_state[games_state_num++]=games_state[curr_iteration]+    1120943996766ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(LHOPN<<24);games_state[games_state_num++]=games_state[curr_iteration]-   23111260438370ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>45)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(KHOPH<<24);games_state[games_state_num++]=games_state[curr_iteration]+ 2568459163401988ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(DHOPH<<24);games_state[games_state_num++]=games_state[curr_iteration]- 3272146605179140ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>48)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(MHOPK<<24);games_state[games_state_num++]=games_state[curr_iteration]+ 2322168623922940ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(HHOPK<<24);games_state[games_state_num++]=games_state[curr_iteration]- 8233143136943876ULL;++alt;break;
    }
    switch((games_state[curr_iteration]>>51)%8)
    {
      case 3:backtrack[games_state_num]=curr_iteration+(JHOPG<<24);games_state[games_state_num++]=games_state[curr_iteration]+  422246756646908ULL;++alt;break;
      case 6:backtrack[games_state_num]=curr_iteration+(CHOPG<<24);games_state[games_state_num++]=games_state[curr_iteration]-11681245959290876ULL;++alt;break;
    }

    if(!alt)
    {
      //end of game, check to see if we have won
      games+=2;
      if(won(games_state[curr_iteration]))
      {
        //use backtrack to create solution list
        prev=backtrack[curr_iteration];
        i=12;
        while(i>=0)
        {
          solutions_data[(solutions*13)+i]=prev>>24;//solution
          solutions_data[((1+solutions)*13)+i]=(solutions_data[(solutions*13)+i]+18)%36;//symmetrical solution
          prev=backtrack[prev%524288];
          --i;
        }
        solutions+=2;
      }
    }
    ++curr_iteration;
  }

  free(games_state);
  free(backtrack);
  free(solutions_data);

  gettimeofday(&endTime, NULL);

  printf("Games played:    %6u \n", (unsigned int)games);
  printf("Solutions found: %6u\n", (unsigned int)solutions);
  printf("Time elapsed:    %6ldms\n", diff_usec(startTime, endTime) / 1000);
}

