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

/**@file  statistics.h
 * @brief Class for collecting statistical information
 */
#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#ifndef SOPLEX_LEGACY
#include <iostream>

#include "soplex.h"
#include "timer.h"

namespace soplex
{
   /**@class   Statistics
    * @brief   Class for collecting statistical information
    * @ingroup Algo
    */
   class SoPlex::Statistics
   {

   public:

      //**@name Construction, resetting, printing */
      //@{

      /// default constructor
      Statistics(Timer::TYPE ttype = Timer::USER_TIME);

      /// copy constructor
      Statistics(const Statistics& base);

      /// assignment operator
      Statistics& operator=(const Statistics& rhs);

      /// destructor
      ~Statistics()
      {
         // we need to free all timers again (allocation happens in constructor)
         readingTime->~Timer();
         solvingTime->~Timer();
         preprocessingTime->~Timer();
         simplexTime->~Timer();
         syncTime->~Timer();
         transformTime->~Timer();
         rationalTime->~Timer();
         reconstructionTime->~Timer();
         spx_free(readingTime);
         spx_free(solvingTime);
         spx_free(preprocessingTime);
         spx_free(simplexTime);
         spx_free(syncTime);
         spx_free(transformTime);
         spx_free(rationalTime);
         spx_free(reconstructionTime);
      }

      /// clears all statistics
      void clearAllData();

      /// clears statistics on solving process
      void clearSolvingData();

      /// prints statistics
      void print(std::ostream& os);

      //@}


      //**@name Data */
      //@{

      Timer* readingTime; ///< reading time not included in solving time
      Timer* solvingTime; ///< solving time
      Timer* preprocessingTime; ///< preprocessing time
      Timer* simplexTime; ///< simplex time
      Timer* syncTime; ///< time for synchronization between real and rational LP (included in solving time)
      Timer* transformTime; ///< time for transforming LPs (included in solving time)
      Timer* rationalTime; ///< time for rational LP solving (included in solving time)
      Timer* reconstructionTime; ///< time for rational reconstructions
      Timer::TYPE timerType; ///< type of timer (user or wallclock)
      Real luFactorizationTimeReal; ///< time for factorizing bases matrices in real precision
      Real luSolveTimeReal; ///< time for solving linear systems in real precision
      Real luFactorizationTimeRational; ///< time for factorizing bases matrices in rational precision
      Real luSolveTimeRational; ///< time for solving linear systems in rational precision
      int iterations; ///< number of iterations/pivots
      int iterationsPrimal; ///< number of iterations with Primal
      int iterationsFromBasis; ///< number of iterations from Basis
      int iterationsPolish; ///< number of iterations during solution polishing
      int boundflips; ///< number of dual bound flips
      int luFactorizationsReal; ///< number of basis matrix factorizations in real precision
      int luSolvesReal; ///< number of (forward and backward) solves with basis matrix in real precision
      int luFactorizationsRational; ///< number of basis matrix factorizations in rational precision
      int rationalReconstructions; ///< number of rational reconstructions performed
      int refinements; ///< number of refinement steps
      int stallRefinements; ///< number of refinement steps without pivots
      int pivotRefinements; ///< number of refinement steps until final basis is reached
      int feasRefinements; ///< number of refinement steps during infeasibility test
      int unbdRefinements; ///< number of refinement steps during undboundedness test
      int backstepping; ///< total number of backstepping in qp refinement iterations
      int resolve; ///< number of resolve operations in qp refinement

      //@}
   };
} // namespace soplex
#endif
#endif // _STATISTICS_H_
