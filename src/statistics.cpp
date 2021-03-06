/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the class library                   */
/*       SoPlex --- the Sequential object-oriented simPlex.                  */
/*                                                                           */
/*    Copyright (C) 1996-2016 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SoPlex is distributed under the terms of the ZIB Academic Licence.       */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SoPlex; see the file COPYING. If not email to soplex@zib.de.  */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SOPLEX_LEGACY
#include <iostream>
#include <assert.h>

#include "statistics.h"
#include "timerfactory.h"

namespace soplex
{

   /// default constructor
   SoPlex::Statistics::Statistics(Timer::TYPE ttype)
   {
      timerType = ttype;
      readingTime = TimerFactory::createTimer(timerType);
      solvingTime = TimerFactory::createTimer(timerType);
      preprocessingTime = TimerFactory::createTimer(timerType);
      simplexTime = TimerFactory::createTimer(timerType);
      syncTime = TimerFactory::createTimer(timerType);
      transformTime = TimerFactory::createTimer(timerType);
      rationalTime = TimerFactory::createTimer(timerType);
      reconstructionTime = TimerFactory::createTimer(timerType);
      clearAllData();
   }

   /// copy constructor
   SoPlex::Statistics::Statistics(const Statistics& base)
   {
      timerType = base.timerType;
      readingTime = TimerFactory::createTimer(timerType);
      solvingTime = TimerFactory::createTimer(timerType);
      preprocessingTime = TimerFactory::createTimer(timerType);
      simplexTime = TimerFactory::createTimer(timerType);
      syncTime = TimerFactory::createTimer(timerType);
      transformTime = TimerFactory::createTimer(timerType);
      rationalTime = TimerFactory::createTimer(timerType);
      reconstructionTime = TimerFactory::createTimer(timerType);
      clearAllData();
   }

   /// assignment operator
   SoPlex::Statistics& SoPlex::Statistics::operator=(const Statistics &rhs)
   {
      *readingTime = *(rhs.readingTime);
      *solvingTime = *(rhs.solvingTime);
      *preprocessingTime = *(rhs.preprocessingTime);
      *simplexTime = *(rhs.simplexTime);
      *syncTime = *(rhs.syncTime);
      *transformTime = *(rhs.transformTime);
      *rationalTime = *(rhs.rationalTime);
      *reconstructionTime = *(rhs.reconstructionTime);
      timerType = rhs.timerType;
      luFactorizationTimeReal = rhs.luFactorizationTimeReal;
      luSolveTimeReal = rhs.luSolveTimeReal;
      luFactorizationTimeRational = rhs.luFactorizationTimeRational;
      luSolveTimeRational = rhs.luSolveTimeRational;
      iterations = rhs.iterations;
      iterationsPrimal = rhs.iterationsPrimal;
      iterationsFromBasis = rhs.iterationsFromBasis;
      iterationsPolish = rhs.iterationsPolish;
      boundflips = rhs.boundflips;
      luFactorizationsReal = rhs.luFactorizationsReal;
      luSolvesReal = rhs.luSolvesReal;
      luFactorizationsRational = rhs.luFactorizationsRational;
      rationalReconstructions = rhs.rationalReconstructions;
      refinements = rhs.refinements;
      stallRefinements = rhs.stallRefinements;
      pivotRefinements = rhs.pivotRefinements;
      feasRefinements = rhs.feasRefinements;
      unbdRefinements = rhs.unbdRefinements;
      backstepping = rhs.backstepping;
      resolve =  rhs.resolve;

      return *this;
   }

   /// clears all statistics
   void SoPlex::Statistics::clearAllData()
   {
      readingTime->reset();
      clearSolvingData();
   }

   /// clears statistics on solving process
   void SoPlex::Statistics::clearSolvingData()
   {
      solvingTime->reset();
      preprocessingTime->reset();
      simplexTime->reset();
      syncTime->reset();
      transformTime->reset();
      rationalTime->reset();
      reconstructionTime->reset();
      luFactorizationTimeReal = 0.0;
      luSolveTimeReal = 0.0;
      luFactorizationTimeRational = 0.0;
      luSolveTimeRational = 0.0;
      iterations = 0;
      iterationsPrimal = 0;
      iterationsFromBasis = 0;
      iterationsPolish = 0;
      boundflips = 0;
      luFactorizationsReal = 0;
      luSolvesReal = 0;
      luFactorizationsRational = 0;
      rationalReconstructions = 0;
      refinements = 0;
      stallRefinements = 0;
      pivotRefinements = 0;
      feasRefinements = 0;
      unbdRefinements = 0;
      backstepping = 0;
      resolve =  0;

   }

   /// prints statistics
   void SoPlex::Statistics::print(std::ostream& os)
   {
      Real solTime = solvingTime->time();
      Real totTime = readingTime->time() + solTime;
      Real otherTime = solTime - syncTime->time() - transformTime->time() - preprocessingTime->time() - simplexTime->time() - rationalTime->time();

      os << std::fixed << std::setprecision(2);

      os << "Total time          : " << totTime << "\n"
         << "  Reading           : " << readingTime->time() << "\n"
         << "  Solving           : " << solTime << "\n"
         << "  Preprocessing     : " << preprocessingTime->time();
      if( solTime > 0 )
         os << " (" << 100 * (preprocessingTime->time() / solTime) << "% of solving time)";
      os << "\n  Simplex           : " << simplexTime->time();
      if( solTime > 0 )
         os << " (" << 100 * (simplexTime->time() / solTime) << "% of solving time)";
      os << "\n  Synchronization   : " << syncTime->time();
      if( solTime > 0 )
         os << " (" << 100 * (syncTime->time() / solTime) << "% of solving time)";
      os << "\n  Transformation    : " << transformTime->time();
      if( solTime > 0 )
         os << " (" << 100*transformTime->time() / solTime << "% of solving time)";
      os << "\n  Rational          : " << rationalTime->time();
      if( solTime > 0 )
         os << " (" << 100*rationalTime->time() / solTime << "% of solving time)";
      os << "\n  Other             : " << otherTime;
      if( solTime > 0  )
         os << " (" << 100*otherTime / solTime << "% of solving time)";

      os << "\nRefinements         : " << refinements << "\n"
         << "  Stalling          : " << stallRefinements << "\n"
         << "  Pivoting          : " << pivotRefinements << "\n"
         << "  Feasibility       : " << feasRefinements << "\n"
         << "  Unboundedness     : " << unbdRefinements << "\n";

      os << "Iterations          : " << iterations << "\n"
         << "  From scratch      : " << iterations - iterationsFromBasis;
      if( iterations > 0 )
         os << " (" << 100*double((iterations - iterationsFromBasis))/double(iterations) << "%)";
      os << "\n  From basis        : " << iterationsFromBasis;
      if( iterations > 0 )
         os << " (" << 100*double(iterationsFromBasis)/double(iterations) << "%)";
      os << "\n  Primal            : " << iterationsPrimal;
      if( iterations > 0 )
         os << " (" << 100*double(iterationsPrimal)/double(iterations) << "%)";
      os << "\n  Dual              : " << iterations - iterationsPrimal - iterationsPolish;
      if( iterations > 0 )
         os << " (" << 100*double((iterations - iterationsPrimal))/double(iterations) << "%)";
      os << "\n  Bound flips       : " << boundflips;
      os << "\n  Sol. polishing    : " << iterationsPolish;
      os << "\n  QP backstepping   : " << backstepping;
      os << "\n  QP resolves       : " << resolve;

      os << "\nLU factorizations   : " << luFactorizationsReal << "\n"
         << "  Factor. frequency : ";
      if( luFactorizationsReal > 0 )
         os << double(iterations) / double(luFactorizationsReal) << " iterations per factorization\n";
      else
         os << "-\n";
      os << "  Factor. time      : " << luFactorizationTimeReal << "\n";

      os << "LU solves           : " << luSolvesReal << "\n"
         << "  Solve frequency   : ";
      if( luSolvesReal > 0 )
         os << double(luSolvesReal) / double(iterations) << " solves per iteration\n";
      else
         os << "-\n";
      os << "  Solve time        : " << luSolveTimeReal << "\n";

      os << "Rat. factorizations : " << luFactorizationsRational << "\n"
         << "  Rat. factor. time : " << luFactorizationTimeRational << "\n"
         << "  Rat. solve time   : " << luSolveTimeRational << "\n";

      os << "Rat. reconstructions: " << rationalReconstructions << "\n"
         << "  Rat. rec. time    : " << reconstructionTime->time() << "\n";
   }
} // namespace soplex
#endif
