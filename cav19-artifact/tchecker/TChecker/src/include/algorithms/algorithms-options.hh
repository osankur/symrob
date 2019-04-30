#ifndef __TCHECKER_ALGORITHMS_OPTIONS_HH__
#define __TCHECKER_ALGORITHMS_OPTIONS_HH__

#include <ostream>
#include <string>

#include "graph/graphoutput.hh"
#include "graph/nodescmp.hh"
#include "semantics/semantics.hh"

/*!
  \file algorithms-options.hh
  \brief Options for TChecker algorithms
 */

namespace algorithms {

  /*!
    \class options_t
    \brief Options for TChecker algorithms
  */
  class options_t {
  public:
    // Accepting labels

    std::string accepting_labels;  /*< Accepting labels */


    // Algorithm

    /*!
      \enum algorithm_t
      \brief Type of algorithm
     */
    typedef enum {
      ALGO_BUCHIEMPTY,  /*!< Büchi emptiness algorithm */
      ALGO_EMPTY,       /*!< Emptiness algorithm (reachability) */
      ALGO_EXPLORE      /*!< Graph exploration algorithm */
    } algorithm_flags_t;

    algorithm_flags_t algorithm_flags; /*!< Type of algorithm */



    // Check flag

    bool check_flag;  /*!< Checks correctness of algorithm's outcome */



    // Graph
    
    /*!
      \enum graph_t
      \brief Type of graphs traversed by algorithms
     */
    typedef enum {
      G_GZG,     /*!< Guessing Zone Graph */
      G_TA,      /*!< Timed Automaton */
      G_ZG       /*!< Zone graph */
    } graph_flags_t;

    graph_flags_t graph_flags;   /*!< Graph traversed by the algorithm */

    syntax::model_flags_t model_flags;  /*!< Model configuration */

    semantics::sem_flags_t semantics_flags;  /*!< Semantics for zone graphs */



    // Output

    std::ostream * os;                       /*!< Output stream */
    graph::output_flags_t go_flags;          /*!< Graph output flags */


    
    // Propagation strategy

    /*!
      \enum propagation_strategy_t
      \brief Bounds propagation strategy
    */
    typedef enum {
      PS_FIFO,    /*!< FIFO propagation */
      PS_YFP      /*!< Propagation from youngest node first */
    } propagation_strategy_flags_t;

    /*!< Propagation strategy */
    propagation_strategy_flags_t propagation_strategy_flags;



    // Search strategy

    /*!
      \enum search_strategy_t
      \brief Graph traversal strategy
     */
    typedef enum {
      SS_BFS,    /*!< Breadth-First Search */
      SS_DFS,    /*!< Depth-First Search */
      SS_OFS,    /*!< Oldest node-First Search */
      SS_YFS,    /*!< Youngest node-First Search */
      SS_BZBFS,  /*!< Biggest-Zone Breadth-First Search */
      SS_BZDFS   /*!< Biggest-Zone Depth-First Search */
    } search_strategy_flags_t;

    /*!< Graph traversal strategy */
    search_strategy_flags_t search_strategy_flags;



    // Statistics
    
    /*!< Statistics level
      0 : basic stats, for benchmarks
      1 : more stats, easily computed
      2 : full stats, may take time and memory to compute
     */
    unsigned stats_level;



    // Termination strategy

    /* Passed Waiting list */
    graph::nodes_binpred_flags_t pw_leq_flags;  /*!< PW leq predicate */

    /*!
      \enum dynamic_covering_t
      \brief Dynamic covering for termination
     */
    typedef enum {
      DYNCOVER_NO,              /*!< No dynamic covering */
      DYNCOVER_ALU_FSTTCS11,    /*!< aLU, bounds from FSTTCS'11 algorithm */
      DYNCOVER_ALU_CAV13,       /*!< aLU, bounds from CAV'13 algorithm */
    } dynamic_covering_flags_t;

    /*!< Dynamic covering (termination) */
    dynamic_covering_flags_t dynamic_covering_flags;

    typedef enum {
      REFINE_DEFAULT,                /*!< Disable the CEGAR approach */
      REFINE_LOCAL_CUT,                    /*!< refinement function cut the tree */
      REFINE_LOCAL_TOP,                    /*!< refinement function propagates the interpolant downards, cut only the top node on refinement if covered*/
      REFINE_LOCAL_HIGH,                    /*!< refinement function propagates the interpolant downards, cut only the highest node on refinement if covered*/
      REFINE_GLOBAL_CUT,                    /*!< refinement function cut the tree */
      REFINE_GLOBAL_TOP,                    /*!< refinement function propagates the interpolant downards, cut only the top node on refinement if covered*/
      REFINE_GLOBAL_HIGH,                    /*!< refinement function propagates the interpolant downards, cut only the highest node on refinement if covered*/
      REFINE_SYNTAX_CUT,                    /*!< refinement function cut the tree */
      REFINE_SYNTAX_TOP,                    /*!< refinement function propagates the interpolant downards, cut only the top node on refinement if covered*/
      REFINE_SYNTAX_HIGH,                    /*!< refinement function propagates the interpolant downards, cut only the highest node on refinement if covered*/
    } refinement_flags_t;

    /*!< Dynamic covering (termination) */
    refinement_flags_t refinement_flags;
    


    /*!
      \brief Constructor
      \post Options have been initialized to:
      check_flag                 = false
      graph_flags                = G_ZG
      semantics_flags            = semantics::SEM_DEFAULT
      os                         = &std::cout
      go_flags                   = graph::OUTPUT_DEFAULT
      propagation_strategy_flags = PS_FIFO
      search_strategy_flags      = SS_BFS
      stats_level                = 0
      pw_leq_flags               = graph::NPRED_ZG_LEQ
      dynamic_covering_flags     = DYNCOVER_NO
      refinement_flags           = REFINE_DEFAULT
    */
    options_t();

    /*!
      \brief Sets options to mimic UPPAAL reachability algorithm:
      check_flag                 = false
      dump_flag                  = false
      verbose_flag               = false
      graph_flags                = G_ZG
      semantics_flags            = semantics::SEM_EL | semantics::SEM_EXLUL |
                                   semantics::SEM_DBM
      go_flags                   = graph::OUTPUT_DEFAULT
      propagation_strategy_flags = PS_FIFO
      search_strategy_flags      = SS_BFS
      stats_level                = 0
      pw_leq_flags               = graph::NPRED_ZG_LEQ
      dynamic_covering_flags     = DYNCOVER_NO
      refinement_flags           = REFINE_DEFAULT
    */
    void preset_uppaal();

    /*!
      \brief Sets options for algorithm: FSTTCS'11 (otf bounds) + LICS'12 (aLU)
      check_flag                 = false
      dump_flag                  = false
      verbose_flag               = false
      graph_flags                = G_ZG
      semantics_flags            = semantics::SEM_EL | semantics::SEM_EXLUL |
                                   semantics::SEM_DBM
      go_flags                   = graph::OUTPUT_DEFAULT
      propagation_strategy_flags = PS_FIFO
      search_strategy_flags      = SS_BFS
      stats_level                = 0
      pw_leq_flags               = graph::NPRED_ZG_LEQ
      dynamic_covering_flags     = DYNCOVER_ALU_ALL
      refinement_flags           = REFINE_DEFAULT
    */
    void preset_fsttcs11();

    /*!
      \brief Sets options for algorithm: CAV'13 disabled bounds + LICS'12 (aLU)
      check_flag                 = false
      dump_flag                  = false
      verbose_flag               = false
      graph_flags                = G_ZG
      semantics_flags            = semantics::SEM_EL | semantics::SEM_EXLUL |
                                   semantics::SEM_DBM
      go_flags                   = graph::OUTPUT_DEFAULT
      propagation_strategy_flags = PS_FIFO
      search_strategy_flags      = SS_BFS
      stats_level                = 0
      pw_leq_flags               = graph::NPRED_ZG_LEQ
      dynamic_covering_flags     = DYNCOVER_ALU_DISABLED
      refinement_flags           = REFINE_DEFAULT
    */
    void preset_cav13();
    /*!
      \brief Sets options to mimic UPPAAL reachability algorithm:
      check_flag                 = false
      dump_flag                  = false
      verbose_flag               = false
      graph_flags                = G_ZG
      semantics_flags            = semantics::SEM_EL | semantics::SEM_EXNO |
                                   semantics::SEM_DBM
      go_flags                   = graph::OUTPUT_DEFAULT
      propagation_strategy_flags = PS_FIFO
      search_strategy_flags      = SS_BFS
      stats_level                = 0
      pw_leq_flags               = graph::NPRED_ZG_LEQ
      dynamic_covering_flags     = DYNCOVER_NO
      refinement_flags           = REFINE_CUT
    */
    void preset_ASGT_cut();

    void preset_ASGT_down();


    void preset_Lcut();

    void preset_Ltop();

    void preset_Lhigh();
    void preset_Scut();

    void preset_Stop();

    void preset_Shigh();
    void preset_Gcut();

    void preset_Gtop();

    void preset_Ghigh();
  };

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_OPTIONS_HH__
