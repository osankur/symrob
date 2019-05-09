#ifndef __TCHECKER_SYSTEM_HH__
#define __TCHECKER_SYSTEM_HH__

#include <string>
#include <utility>
#include <vector>

#include <boost/container/flat_map.hpp>

#include "base/clockset.hh"
#include "base/index.hh"
#include "base/labelset.hh"
#include "base/range.hh"
#include "symbolic/constraints.hh"
#include "syntax/layout.hh"
#include "syntax/locs_edges.hh"
#include "syntax/system_builder.hh"
#include "syntax/system_fwd.hh"
#include "syntax/synchro.hh"
#include "syntax/sync_product.hh"


/*!
  \file system.hh
  \brief System of timed processes with synchronizations

  This is the interface that allows end-users to specify their
  models. A model is a system of timed processes that may synchronize
  by handshaking.

  Variables are global to the system. Discrete variables are defined
  thanks to layouts (see syntax::layout_t). A system is equiped with
  an allocator of layouts (see syntax::system_t::layout_allocator).
  Clock variables are defined directly calling method
  syntax::system_t::add_clock.

  Properties are specified by labeling locations. The set of labels is
  global to the system. They are defined by calling method
  syntax::system_t::add_label. Verification algorithms may then use
  these labels as atomic propositions.

  Clocks and labels are added to the global clock index and global
  label index respectively (see global_t::clock_index() and
  global_t::label_index()). They can only be added till the system is
  empty, that is till it has no process.

  Processes are defined by calling method
  syntax::system_t::add_process. Processes are defined by a
  name.

  Locations are added to processes using method
  syntax::system_t::add_location. They are defined by: the name of
  owner process, the name of the location, an invariant on clock
  variables, an assertion on other variables (layout), labels and flags.
  Flags allow to define initial locations, urgent locations and 
  committed locations. Time cannot elapse in urgent and committed
  locations. Moreover, when the system of timed processes evolve from
  a state where (at least) one process is in a committed location,
  then at least one of these committed processes must be involved.

  Edges are added to processes using method
  syntax::system_t::add_edge. They are defined by: the name of owner
  process, the names of source and target locations, a guard and a
  reset (on clock variables), an event name, and a guard and an update
  on layouts. Events allow to synchronize the edges (see below). For
  guards and updates on layouts, refer to syntax::layout_predicate_t
  and syntax::layout_update_t.
*/



/*!
  \namespace syntax
  \brief Syntax of timed automata
*/
namespace syntax {

  /*!
    \class system_t
    \brief System of timed processes
  */
  class system_t {
  public:
    /*!
      \brief Collection of edges
    */
    typedef std::vector<edge_t *> edge_collection_t;

    /*!
      \brief Index of locations: (pid, location name) <--> location
     */
    typedef index_t< std::pair<proc_id_t, std::string>, loc_t * > loc_index_t;

    /*!
      \brief Index of processes: pid <--> process name
    */
    typedef index_t<proc_id_t, std::string> proc_index_t;


    /*!
      \brief Constructor
      \post The system is empty and has a syntax::layout_t allocator
    */
    system_t();

    /*!
      \brief Constructor
      \param system_builder : a system builder
      \post The system has been built by system_builder
     */
    system_t(system_builder_t & system_builder);

    /*!
      \brief Destructor
    */
    ~system_t();

    /*!
      \brief Sets system name
      \param name : name to set
      \post The system's name has been set to name
     */
    void name(std::string const & name);
    
    /*!
      \brief Accessor
      \return system's name
     */
    std::string const & name() const;

    /*!
      \brief Adds a clock
      \param name : name of the clock to add
      \post The clock has been added to the global clock index (see ::global_t)
      \throw std::invalid_argument if name is a reserved name (see ::global_t)
      \throw std::runtime_error if some process has already been added to the
      system
    */
    void add_clock(std::string const & name);

    /*!
      \brief Adds a label
      \param name : name of the label to add
      \post The label has been added to the global label index (see ::global_t)
      \throw std::invalid_argument if name is a reserved name (see ::global_t)
      \throw std::runtime_error if some process has already been added to the
      system
    */
    void add_label(std::string const & name);

    /*!
      \brief Adds a process
      \param name : name of the process to add
      \post The process has been added to the system
      \throw std::runtime_error if called after synchronizations have been
      added to the system
      \throw std::invalid_argument if name is a reserved name (see ::global_t)
    */
    void add_process(std::string const & name);

    /*!
      \brief Adds a location to a process in the system
      \param proc_name : name of the process
      \param loc_name : name of the location to add
      \param inv : invariant of the location
      \param labels : labels of the location
      \param flags : flags of the location
      \param lassert : assertion on layouts
      \pre inv must satisfy the grammar of ::parse_clock_constraints,
      labels must satisfy the grammar of ::parse_id_list
      \post A location with given datas has been added to the system. Stores
      a const reference to lassert
      \throw std::invalid_argument if process proc_name has not been added
      before or if loc_name is a reserved name (see ::global_t)
    */
    void add_location(std::string const & proc_name,
		      std::string const & loc_name,
		      std::string const & inv = "",
		      std::string const & labels = "",
		      loc_t::flags_t flags = loc_t::NO,
		      layout_predicate_t const & lassert = layout_true);

    /*!
      \brief Adds an edge to a process in the system
      \param proc_name : name of the process
      \param src_name : name of the source location
      \param tgt_name : name of the target location
      \param guard : guard on clocks
      \param reset : clocks to be reset on the edge
      \param event : synchronization event
      \param lguard : guard on layout
      \param lupdate : update on layout
      \pre guard must satisfy the grammar of ::parse_clock_constraints,
      reset must satisfy the grammar of ::pasre_id_list
      \post An edge with given datas has been added to the system and event
      has been added to the system. Stores a const reference to lguard and
      lupdate
      \throw std::invalid_argument if proc_name, src_name, tgt_name or event
      is a reserved name, or if proc_name, src_name, tgt_name has not been
      added before
    */
    void add_edge(std::string const & proc_name,
		  std::string const & src_name,
		  std::string const & tgt_name,
		  std::string const & guard = "",
		  std::string const & reset = "",
		  std::string const & event = "",
		  layout_predicate_t const & lguard = layout_true,
		  layout_update_t const & lupdate = layout_id);

    /*!
      \brief Adds an edge with synchronized label to a process in the system
      \param proc_name : name of the process
      \param src_name : name of the source location
      \param tgt_name : name of the target location
      \param guard : guard on clocks
      \param reset : clocks to be reset on the edge
      \param event : synchronization label
      \param lguard : guard on layout
      \param lupdate : update on layout
      \pre guard must satisfy the grammar of ::parse_clock_constraints,
      reset must satisfy the grammar of ::pasre_id_list
      \post An edge with given datas has been added to the system and event
      has been added to the system. Stores a const reference to lguard and
      lupdate
      \throw std::invalid_argument if proc_name, src_name, tgt_name or event
      is a reserved name, or if proc_name, src_name, tgt_name has not been
      added before
    */
    void add_edge_sync(std::string const & proc_name,
		       std::string const & src_name,
		       std::string const & tgt_name,
		       std::string const & guard = "",
		       std::string const & reset = "",
		       sync_label_t const * event = sync_label_t::null,
		       layout_predicate_t const & lguard = layout_true,
		       layout_update_t const & lupdate = layout_id);

    /*!
      \brief Sets the synchronizer
      \tparam SYNCHRONIZER : type of synchronizer to construct
      \tparam OPTIONS : type of parameters for constructing the synchronizer
      \param options : parameters for constructing the synchronizer
      \post An instance of SYNCHRONIZER has been constructed with parameters
      options. Previous synchronizer has been deleted.
      \return The synchronizer that has been constructed
      */
    template <class SYNCHRONIZER, class... OPTIONS>
    SYNCHRONIZER & synchronizer(OPTIONS && ... options) {
      if (_synchronizer != nullptr)
	delete _synchronizer;
      SYNCHRONIZER * s = new SYNCHRONIZER(options...);
      _synchronizer = s;
      return (* s);
    }

    /*!
      \brief Accessor
      \return The synchronizer
      \throw std::runtime_error if synchronizer is not set
    */
    synchronizer_t const & synchronizer() const;
    
    /*!
      \brief Sets the layout allocator
      \tparam LAYOUT_ALLOC : type of layout allocator to construct
      \tparam OPTIONS : type of parameters for constructing the allocator
      \param options : parameters for constructing the allocator
      \post An instance of LAYOUT_ALLOC has been constructed with parameters
      options. Previous layout allocator has been deleted.
      \return The allocator that has been constructed
    */
    template <class LAYOUT_ALLOC, class... OPTIONS>
    LAYOUT_ALLOC & layout_alloc(OPTIONS && ... options) {
      if (_layout_alloc != nullptr)
	delete _layout_alloc;
      LAYOUT_ALLOC * la = new LAYOUT_ALLOC(options...);
      _layout_alloc = la;
      return (* la);
    }

    /*!
      \brief Accessor
      \return The system layout allocator
      \throw std::runtime_error : if the layout allocator has not been set
    */
    layout_alloc_t const & layout_alloc() const;


    // Accessors to processes

    /*!
      \brief Accessor
      \return The system process index
    */
    proc_index_t const & procs() const;

    /*!
      \brief Accessor
      \param name : a process name
      \return Identifier of process name
      \throw std::invalid_argument : if process name does not exist
    */
    proc_id_t pid(std::string const & name) const;


    // Accessors to locations
    
    /*!
      \class location_range_t
      \brief Range of locations
    */
    class location_range_t
      : public proxy_range_t< iterator_range_t<loc_index_t::iterator>,
			      loc_t const * > {
    public:
      /*!
	\brief Constructor
	\param locations : index of locations
	\post this ranges over locations
      */
      location_range_t(loc_index_t const & locations)
	: proxy_range_t< iterator_range_t<loc_index_t::iterator>,
			 loc_t const * >
	( iterator_range_t<loc_index_t::iterator>(locations.begin(),
						  locations.end()) )
      {}

      /*!
	\brief Copy constructor
	\param r : range to copy
	\post this is a copy of r
      */
      location_range_t(location_range_t const & r)
	: proxy_range_t< iterator_range_t<loc_index_t::iterator>,
			 loc_t const * >(r)
      {}

      /*!
	\brief Destructor
      */
      virtual ~location_range_t() = default;

      /*!
	\brief see range_t::current
	\return current location in range
      */
      virtual loc_t const * current() {
	return _r.current().second;
      }
    };


    /*!
      \brief Accessor
      \return Range of locations in the system
      \note Adding a location (with add_location) invalidates the iterators
     */    
    location_range_t locations() const;

    /*!
      \brief Accessor
      \param pid : identifier of a process
      \param loc_name : name of a location
      \return Pointer to location of name loc_name in process pid
      \throw std::invalid_argument if location loc_name does not exist in
      process pid      
    */
    loc_t const * location(proc_id_t pid, std::string const & loc_name) const;

    /*!
      \brief Accessor
      \return ID of initial location of process pid
      \throw std::invalid_argument if no process has identifier pid or if
      process pid does not have an initial location
    */
    loc_t const * initial_location(proc_id_t pid) const;

 

    // Accessor to edges

    /*!
      \brief Range of edges
    */
    typedef container_range_t< std::vector<edge_t *> const,
			       std::vector<edge_t *>::const_iterator,
			       edge_t const *> edge_range_t;

    /*!
      \brief Accessor
      \return Range of edges in the system
      \note Adding an edge (with add_edge or add_edge_sync) invalidates the
      iterators
     */
    edge_range_t edges() const;
    

    /*!
      \brief Checks if a system definition is valid
      - every process must have an initial location
      - a layout allocator has been defined
      - a synchronizer has been defined
      \return True if the systme is valid, false otherwise
     */
    bool valid() const;

    /*!
      \brief Makes a system Strongly non-Zeno

      Strongly non-Zeno Automata are such that every infinite accepting run is
      non-Zeno.

      \param labels : accepting labels for emptiness checking
      \pre labels contains all the accepting labels for checking emptiness and
      snz_name1 and snz_name2 are not among them. The system has not be made
      SNZ yet.
      \post The system has been made SNZ. All the infinite runs that visit
      labels snz_name1 and snz_name2 infinitely often are non-Zeno. To that
      purpose, a process and a clock have been added to ensure that every
      consecutive occurrences of label snz_name1 (resp. snz_name2) are
      separated by at least 1 time unit
      \throw std::runtime_error if the system has already been made SNZ or
      when snz_name is already an accepting label
    */
    void make_snz(labels_t & accepting_labels);

    /*!
      \brief Checks if the system has been made Strongly non-Zeno
      \return True if make_snz() has been called, false otherwise
     */
    bool has_been_made_snz() const;

    /*!
      \brief Check existence of an event in a process.
      \param pid : process to check
      \param evid : event to check
      \return True if evid labels a transition in process pid, false otherwise
     */
    bool has_event(proc_id_t pid, sync_label_t const * evid) const;
  protected:
    /*!
      \brief Initialization
      \post The system has a layout_t allocator
      SHOULD BE CALLED FIRST BY ALL CONSTRUCTORS, AND ONLY BY CONSTRUCTORS
     */
    void _initialize();

    /*!
      \brief Adds a clock

      This function does not perform name checking unlike system_t::add_clock

      \param name : name of the clock to add
      \pre The system does not contain any process
      \post Clock name has been added to the global clock index
      (see ::global_t)
      \throw std::invalid_argument if name is empty
    */
    void _add_clock(std::string const & name);

    /*!
      \brief Adds a label

      This function does not perform name checking unlike system_t::add_label

      \param name : name of the label to add
      \pre The system does not contain any process
      \post Label name has been added to the global clock index (see ::global_t)
      \throw std::invalid_argument : if name is empty
     */
    void _add_label(std::string const & name);

    /*!
      \brief Adds a process

      This function does not perform reserved name checking unlike
      system_t::add_process

      \param name : name of the process to add
      \pre name is not empty. There is no process name already in the system.
      \post Process name has been added
      \throw std::invalid_argument if name is empty or if the system already
      has a process with the same name
    */
    void _add_process(std::string const & name);

    /*!
      \brief Adds a location

      This function does not perform reserved name checking unlike
      system_t::add_location

      \param pid : process identifier that owns the location
      \param loc_name : name of the location
      \param inv : invariant of the location
      \param labels : labels of the location
      \param flags : flags of the location
      \param lassert : assertion on layouts
      \pre pid is an existing process index, loc_name is not empty and there is
      no location with name loc_name in process pid. If process pid already has
      an initial location, then flags does not set the init flag
      \post A location with given datas has been added to the system
      \throw std::invalid_argument if loc_name is empty or already used in
      process pid, or if the init flag is set despite process pid already has
      an initial location, or if inv sets a lower bound on clock, or if inv
      sets a strict upper bound x < 0
     */
    void _add_location(proc_id_t pid,
		       std::string const & loc_name,
		       symbolic::constraint_collection_t const & inv,
		       labels_t const & labels,
		       loc_t::flags_t flags,
		       layout_predicate_t const & lassert);

    /*!
      \brief Adds a edge
      \param pid : identifier of process owning the egde
      \param src : source location
      \param tgt : target location
      \param guard : guard on clocks
      \param reset : clocks to reset on the edge
      \param event : synchronization event
      \param lguard : guard on layouts
      \param lupdate : update to apply on layouts
      \pre pid, src_id, tgt_id are valid identifiers in the system. lguard
      and lupdate do not point to nullptr.
      \post An edge with given datas has been added to the system and event has
      been added to the system.
      \throw std::invalid_argument if guard sets a strict upper bound x < 0
     */
    void _add_edge(proc_id_t pid,
		   loc_t * src,
		   loc_t * tgt,
		   symbolic::constraint_collection_t const & guard,
		   clocks_t const & reset,
		   sync_label_t const * event,
		   layout_predicate_t const & lguard,
		   layout_update_t const & lupdate);

    /*!
      \brief Guarded access to locations
      \param pid : process identifier
      \param loc_name : location to find
      \return location with name "loc_name" in process with identifier "pid"
      \throw std::invalid_argument if pid or loc_name are unknown
     */
    loc_t * _location(proc_id_t pid, std::string const & loc_name);

    /*!< system name */
    std::string _name;
    /*!< layout allocator */
    layout_alloc_t const * _layout_alloc;
    /*!< index of locations */
    loc_index_t _locations;
    /*!< collection of edges */
    edge_collection_t _edges;
    /*!< index of processes */
    proc_index_t _proc_index;
    /*!< initial location by process id */
    boost::container::flat_map< proc_id_t, loc_t const * > _initial_locations;
    /*!< collection of synchronization vectors */
    synchronizer_t const * _synchronizer;
  };

} // end of namespace syntax

#endif // __TCHECKER_SYSTEM_HH__
