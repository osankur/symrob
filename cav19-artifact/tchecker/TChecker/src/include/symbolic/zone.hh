#ifndef __TCHECKER_ZONE_HH__
#define __TCHECKER_ZONE_HH__

#include <functional>
#include <ostream>
#include <string>

#include "base/cast.hh"
#include "base/clockindex.hh"
#include "base/global.hh"
#include "base/intrusive_hashtable.hh"
#include "symbolic/clockbounds.hh"
#include "symbolic/constraints.hh"
#include "symbolic/dbm_utils.hh"

/*!
  \file zone.hh
  \brief Symbolic representations for zones

  Zone representation make use of clock_index_t to identify clocks. The clock
  with identifier 0 represents the value 0.

  The zone implementations below (class symbolic::zone_t and derivatives)
  provide an abstraction layer to manipulate sets of valuations independently
  of their representations. The manipulations that depend on a particular
  representation need to access the internal representation of zones.
  Typically, the internal representation is accessed for computing the
  zones in the states of semantics of timed automata (for an example, see
  semantics/operational.hh). On the other hand, zones are used at the abstract
  level in algorithms.

  There are two reasons for this choice:

  - it is much more efficient for a semantics that manipulates zones
    (see semantics::operational_t) to access the internal
    representation of zones (see the get() methods in implementations
    of symbolic::zone_t).

  - this allows to implement zones by efficient data structures that
    cannot represent all the zones, but only those that are reachable
    in timed automata.
*/


/*!
  \namespace symbolic
  \brief Symbolic tools for clock valuations
*/
namespace symbolic {

  // zone_t

  /*!
    \class zone_t
    \brief Interface to the representation of a clock zone.
  */
  class zone_t {
  public:
    /*!
      \brief Constructor
      \param index : defines the clocks, defaults to the global clock index
      \pre index contains the fake clock with identifier 0
      \post The zone is universal: it contains all possible valuations
    */
    zone_t(clock_index_t const & index = global_t::instance().clock_index());

    /*!
      \brief Constructor
      \param s : a conjunction of clock constraints (see
      parse_clock_constraints for syntax)
      \param index : encodes clocks as identifiers, defaults to the global
      clock index
      \post The zone represents the conjunction of constraints in s
      \throw std::invalid_argument : when s is not syntactically correct
    */
    zone_t(std::string const & s,
           clock_index_t const & index = global_t::instance().clock_index());

    /*!
      \brief Constructor
      \param collection : a conjunction of clock constraints
      \param index : defines the clocks, defaults to the global clock index
      \post The zone represents the conjunction of constraints in collection
    */
    zone_t(constraint_collection_t const & collection,
           clock_index_t const & index = global_t::instance().clock_index());

    /*!
      \brief Destructor
    */
    virtual ~zone_t();

    /*!
      \brief Copy operation
      \return A duplicate of this. The caller should handle the memory
      allocated for the returned zone
    */
    virtual zone_t * copy() const = 0;

    /*!
      \brief Sets to the empty zone
      \post The zone is empty
    */
    virtual void set_empty() = 0;

    /*!
      \brief Sets to the universal zone
      \post The zone is universal
    */
    virtual void set_universal() = 0;

    /*!
       \brief Equality predicate
       \param z : the zone to compare
       \return True if equals to z, false otherwise
    */
    virtual bool operator == (zone_t const & z) const = 0;

    /*!
      \brief Inclusion predicate
      \param z : the zone to compare
      \return True if included into z, false otherwise
    */
    virtual bool operator <= (zone_t const & z) const = 0;

    /*!
      \brief Checks inclusion wrt closure
      \param z : the zone to compare
      \param M : clock bounds
      \return True if closure of this contains z wrt M, false otherwise
      \pre this, z and M have been built using the same clock index
    */
    virtual bool closure_contains(zone_t const & z,
                                  clock_bounds_t const & M) const = 0;

    /*!
      \brief Checks inclusion wrt aLU
      \param z : the zone to compare
      \param L : lower bounds
      \param U : upper bounds
      \return True if aLU of this contains z wrt L and U, false otherwise
      \pre this, z, L and U have been built using the same clock index
    */
    virtual bool aLU_contains(zone_t const & z, clock_bounds_t const & L,
                              clock_bounds_t const & U) const = 0;

    /*!
      \brief Emptiness check
      \return True if the zone is empty, false otherwise
    */
    virtual bool empty() const = 0;

    /*!
      \brief Universality check
      \return True if the zone is universal, false otherwise
    */
    virtual bool universal() const = 0;

    /*!
      \brief Hash function
      \return Hash code of the zone
    */
    virtual std::size_t hash() const = 0;

    /*!
      \brief Access to zone dimension
      \return Dimension of the zone
    */
    virtual std::size_t dim() const = 0;

    /*!
      \brief Access to the zone as a DBM
      \param dbm : DBM to set
      \pre dbm is an allocated dim()*dim() raw_t matrix
      \post this has been written as a DBM in dbm
     */
    virtual void to_dbm(raw_t * dbm) const = 0;

    /*!
      \brief Applies a function to the zone
      \param f : function to apply, takes a raw_t * DBM and its cindex_t
      dimension
      \post f has been applied to the zone
      \note If the zone is empty, the DBM passed to f may not be closed and
      it has a non-positive value on its diagonal
    */
    virtual void apply(std::function<void(raw_t *, cindex_t)> const & f) = 0;

    /*!
      \brief Outputs the zone
      \param os : output stream
      \param index : translates clock identifiers into clock names, defaults
      to the global clock index
      \post this has been output to os
    */
    virtual void output(std::ostream & os,
                        clock_index_t const & index =
        global_t::instance().clock_index()) const = 0;

    /*!
      \brief Accessor to memory footprint
      \return The memory footprint of the zone
     */
    virtual std::size_t memsize() const = 0;
  };


  
  /*!
    \brief Boost compatible hash function on zones
    \param z : zone
    \return Hash value for zone z
  */
  std::size_t hash_value(zone_t const & z);





  // zone_dbm_t

#if defined IU // implicit universal zones

  /*!
    \class zone_dbm_t
    \brief Implementation of zones using DBMs with implicit representation of
    universal zones
  */
  class zone_dbm_t : public zone_t {
  public:
    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_dbm_t(clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_dbm_t(std::string const & s,
               clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_dbm_t(constraint_collection_t const & collection,
               clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Copy-constructor
      \param z : zone to copy from
      \post this is a copy of z
    */
    zone_dbm_t(zone_dbm_t const & z);

    /*!
      \brief Move constructor
      \param z : zone to move
      \post z has been moved to this
    */
    zone_dbm_t(zone_dbm_t && z);

    /*!
      \brief Destructor
    */
    virtual ~zone_dbm_t();

    /*!
      \brief Copy operation (see zone_t::copy)
    */
    zone_t * copy() const;

    /*!
      \brief Sets to the empty zone (see zone_t::set_empty)
    */
    void set_empty();

    /*!
      \brief Sets to the universal zone (see zone_t::set_universal)
    */
    void set_universal();

    /*!
      \brief Assignement operator
      \param z : zone to assign from
      \post z has been assigned to this
    */
    zone_dbm_t & operator = (zone_dbm_t const & z);

    /*!
      \brief Move assignement operator
      \param z : zone to move
      \post z have been moved to this
    */
    zone_dbm_t & operator = (zone_dbm_t && z);

    /*!
       \brief Equality predicate (see zone_t::operator==)
       \pre z is an instance of zone_dbm_t. z has the same dimension as this.
       \throw std::invalid_argument : when dimensions differ
    */
    bool operator == (zone_t const & z) const;

    /*!
      \brief Inclusion predicate (see zone_t::operator<=)
       \pre z is an instance of zone_dbm_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool operator <= (zone_t const & z) const;

    /*!
      \brief Checks inclusion wrt closure (see zone_t::closure_contains)
      \pre z is an instance of zone_dbm_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool closure_contains(zone_t const & z,
                          clock_bounds_t const & M) const;

    /*!
      \brief Checks inclusion wrt aLU (see zone_t::aLU)
      \pre z is an instance of zone_dbm_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool aLU_contains(zone_t const & z, clock_bounds_t const & L,
                      clock_bounds_t const & U) const;

    /*!
      \brief Emptiness check (see zone_t::empty)
    */
    bool empty() const;

    /*!
      \brief Universality check (see zone_t::universal)
    */
    bool universal() const;

    /*!
      \brief Hash function (see zone_t::hash)
    */
    std::size_t hash() const;

    /*!
      \brief Access to zone dimension (see zone_t::dim)
    */
    std::size_t dim() const;

    /*!
      \brief Access to the zone as a DBM (see zone_t::to_dbm)
     */
    void to_dbm(raw_t * dbm) const;

    /*!
      \brief Access to internal DBM
      \return A non-mutable access to internal DBM. The returned DBM is closed
      unless the zone is empty (then dbm_isEmpty() returns TRUE)
    */
    raw_t const * get() const;

    /*!
      \brief Applies a function to the zone (see zone_t::apply)
      \post f has been applied to the internal DBM, which has then been
      normalized
    */
    void apply(std::function<void(raw_t *, cindex_t)> const & f);

    /*!
      \brief Outputs the zone (see zone_t::output)
    */
    void output(std::ostream & output,
                clock_index_t const & index =
        global_t::instance().clock_index()) const;

    /*!
      \brief Accessor to memory footprint (see zone_t::memsize)
     */
    std::size_t memsize() const;
  protected:
    /*!
      \brief Normalizes the zone
      \post If the zone is empty or universe, _dbm has been released and
      universal flag has been set. The hash code of the zone has been computed.
    */
    void normalize();

    /*!
      \brief Sets to the universal zone (see zone_t::set_universal)
      \param hash : hash code of universal zone with dimension _dim
      \pre hash must be equal to dbm_universal_hash(_dim) (checked by assertion)
      \note Compared to zone_dbm_t::set_universal, this function avoids computing
      the hash code when it is already known (copy, etc)
     */
    void _set_universal(std::size_t hash);

    raw_t * _dbm;       /*!< The DBM representation of the zone */
    cindex_t _dim;      /*!< Dimension of the DBM */
    dbm_flags_t _flags; /*!< Flags on DBM */
    std::size_t _hash;  /*!< Hash code */
  };

#else // not IU

  /*!
    \class zone_dbm_t
    \brief Implementation of zones using DBMs
  */
  class zone_dbm_t : public zone_t {
  public:
    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_dbm_t(clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_dbm_t(std::string const & s,
               clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_dbm_t(constraint_collection_t const & collection,
               clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Copy-constructor
      \param z : zone to copy from
      \post this is a copy of z
    */
    zone_dbm_t(zone_dbm_t const & z);

    /*!
      \brief Move constructor
      \param z : zone to move
      \post z has been moved to this
    */
    zone_dbm_t(zone_dbm_t && z);

    /*!
      \brief Destructor
    */
    virtual ~zone_dbm_t();

    /*!
      \brief Copy operation (see zone_t::copy)
    */
    zone_t * copy() const;

    /*!
      \brief Sets to the empty zone (see zone_t::set_empty)
    */
    void set_empty();

    /*!
      \brief Sets to the universal zone (see zone_t::set_universal)
    */
    void set_universal();

    /*!
      \brief Assignement operator
      \param z : zone to assign from
      \post z has been assigned to this
    */
    zone_dbm_t & operator = (zone_dbm_t const & z);

    /*!
      \brief Move assignement operator
      \param z : zone to move
      \post z have been moved to this
    */
    zone_dbm_t & operator = (zone_dbm_t && z);

    /*!
       \brief Equality predicate (see zone_t::operator==)
       \pre z is an instance of zone_dbm_t. z has the same dimension as this.
       \throw std::invalid_argument : when dimensions differ
    */
    bool operator == (zone_t const & z) const;

    /*!
      \brief Inclusion predicate (see zone_t::operator<=)
       \pre z is an instance of zone_dbm_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool operator <= (zone_t const & z) const;

    /*!
      \brief Checks inclusion wrt closure (see zone_t::closure_contains)
      \pre z is an instance of zone_dbm_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool closure_contains(zone_t const & z,
                          clock_bounds_t const & M) const;

    /*!
      \brief Checks inclusion wrt aLU (see zone_t::aLU)
      \pre z is an instance of zone_dbm_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool aLU_contains(zone_t const & z, clock_bounds_t const & L,
                      clock_bounds_t const & U) const;

    /*!
      \brief Emptiness check (see zone_t::empty)
    */
    bool empty() const;

    /*!
      \brief Universality check (see zone_t::universal)
    */
    bool universal() const;

    /*!
      \brief Hash function (see zone_t::hash)
    */
    std::size_t hash() const;

    /*!
      \brief Access to zone dimension (see zone_t::dim)
    */
    std::size_t dim() const;

    /*!
      \brief Access to the zone as a DBM (see zone_t::to_dbm)
     */
    void to_dbm(raw_t * dbm) const;

    /*!
      \brief Access to internal DBM
      \return A non-mutable access to internal DBM. The returned DBM is closed
      unless the zone is empty (then dbm_isEmpty() returns TRUE)
    */
    raw_t const * get() const;

    /*!
      \brief Applies a function to the zone (see zone_t::apply)
      \post f has been applied to the internal DBM, which has then been
      normalized
    */
    void apply(std::function<void(raw_t *, cindex_t)> const & f);

    /*!
      \brief Outputs the zone (see zone_t::output)
    */
    void output(std::ostream & output,
                clock_index_t const & index =
        global_t::instance().clock_index()) const;

    /*!
      \brief Accessor to memory footprint (see zone_t::memsize)
     */
    std::size_t memsize() const;
  protected:
    /*!
      \brief Normalizes the zone
      \post If the zone is empty or universe, _dbm has been released and
      universal flag has been set. The hash code of the zone has been computed.
    */
    void normalize();

    raw_t * _dbm;       /*!< The DBM representation of the zone */
    cindex_t _dim;      /*!< Dimension of the DBM */
    dbm_flags_t _flags; /*!< Flags on DBM */
    std::size_t _hash;  /*!< Hash code */
  };

#endif // IU



  
  // zone_mg_t

  /*!
    \class zone_mg_t
    \brief Implementation of zones using min graphs
  */
  class zone_mg_t : public zone_t {
  public:
    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_mg_t(clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_mg_t(std::string const & s,
              clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_mg_t(constraint_collection_t const & collection,
              clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Constructor from a DBM
      \param dbm : the DBM
      \param dim : the dimension of dbm
      \pre dbm is an allocated raw_t[dim * dim]. dbm==nullptr or
      dbm_isEmpty(dbm, dim) or dbm_isClosed(dbm, dim) (checked by assertion)
      \post The zone has been initialized to the min graph corresponding to
      dbm
     */
    zone_mg_t(raw_t const * dbm, cindex_t dim);

    /*!
      \brief Copy-constructor
      \param z : zone to copy from
      \post this is a copy of z
    */
    zone_mg_t(zone_mg_t const & z);

    /*!
      \brief Move constructor
      \param z : zone to move
      \post z has been moved to this
     */
    zone_mg_t(zone_mg_t && z);

    /*!
      \brief Destructor
    */
    virtual ~zone_mg_t();

    /*!
      \brief Copy operation (see zone_t::copy)
    */
    zone_t * copy() const;

    /*!
      \brief Sets to the empty zone (see zone_t::set_empty)
    */
    void set_empty();

    /*!
      \brief Sets to the universal zone (see zone_t::set_universal)
    */
    void set_universal();


    /*!
      \brief Assignement operator
      \param z : zone to assign from
      \post z has been assigned to this
    */
    zone_mg_t & operator = (zone_mg_t const & z);

    /*!
      \brief Move assignement operator
      \param z : zone to move
      \post z has been moved to this
    */
    zone_mg_t & operator = (zone_mg_t && z);

    /*!
      \brief Equality predicate (see zone_t::operator==)
      \pre z is an instance of zone_mg_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool operator == (zone_t const & z) const;

    /*!
      \brief Inclusion predicate (see zone_t::operator<=)
      \pre z is an instance of zone_mg_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool operator <= (zone_t const & z) const;

    /*!
      \brief Checks inclusion wrt closure (see zone_t::closure_contains)
      \pre z is an instance of zone_mg_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool closure_contains(zone_t const & z,
                          clock_bounds_t const & M) const;

    /*!
      \brief Checks inclusion wrt aLU (see zone_t::aLU_contains)
      \pre z is an instance of zone_mg_t. z has the same dimension as this.
      \throw std::invalid_argument : when dimensions differ
    */
    bool aLU_contains(zone_t const & z, clock_bounds_t const & L,
                      clock_bounds_t const & U) const;

    /*!
      \brief Emptiness check (see zone_t::empty)
    */
    bool empty() const;

    /*!
      \brief Universality check (see zone_t::universal)
    */
    bool universal() const;

    /*!
      \brief Hash function (see zone_t::hash)
    */
    std::size_t hash() const;

    /*!
      \brief Access to zone dimension (see zone_t::dim)
    */
    std::size_t dim() const;

    /*!
      \brief Access to the zone as a DBM (see zone_t::to_dbm)
     */
    void to_dbm(raw_t * dbm) const;

    /*!
      \brief Access to internal mingraph
      \return A non-mutable access to internal mingraph
    */
    int32_t const * get() const;

    /*!
      \brief Applies a function to the zone
      \param f : function to apply, takes a raw_t * DBM and its cindex_t
      dimension
      \post f has been applied to a DBM representation of the zone that has
      been converted back to a mingraph
      \note If the zone is empty, the DBM passed to f may not be closed and
      it has a non-positive value on its diagonal
      \note Each call requires the allocation of a DBM, decoding the mingraph
      as a DBM, and encoding back
    */
    void apply(std::function<void(raw_t *, cindex_t)> const & f);

    /*!
      \brief Outputs the zone (see zone_t::output)
    */
    void output(std::ostream & output,
                clock_index_t const & index =
        global_t::instance().clock_index()) const;

    /*!
      \brief Accessor to memory footprint (see zone_t::memsize)
      \note Requires computation of number of edges in mingraph (quadratic in
      number of clocks at most)
     */
    std::size_t memsize() const;
  protected:
    int32_t * _mg;  /*!< The min graph representation of the zone */
    cindex_t _dim;  /*!< Dimension of the zone */

    /*!
      \brief Initialises mingraph to universal zone
      \pre _dim is the dimension of the min graph
      \post _mg has been initialized to the min graph representing
      the universal zone of dimension _dim
    */
    void initialize();

    /*!
      \brief Initialises min graph from constraints
      \param collection : the conjunction of constraints to initialize from
      \pre _dim is the dimension of the min graph
      \post _mg has been initialized to the min graph representing
      collection
    */
    void initialize(constraint_collection_t const & collection);

    /*!
      \brief Initializes min graph from another min graph
      \param mg : min graph to initialize from
      \pre current min graph and mg have the same dimension
      \post mg has been memcopied to _mg
    */
    void initialize(int32_t const * mg);

    /*!
      \brief Initializes min graph from a DBM
      \param dbm : the DBM
      \param dim : the dimension of dbm
      \pre dbm is an allocated raw_t[dim * dim]. dbm is closed and it is
      not empty
      \post The zone has been initialized to the min graph that represents
      dbm
    */
    void initialize(raw_t const * dbm, cindex_t dim);

    /*!
      \brief Converts to a DBM
      \return A pointer to a DBM of dimension _dim equivalent to the min graph
      \post Memory has been allocated for the returned DBM
    */
    raw_t * to_dbm() const;
  };




  // Shared zones

  /*!
    \class shared_zone_t
    \brief Shared zone with reference counter and intrusive hash table hook
    \note DO NOT DERIVE FROM THIS CLASS AS release() SUICIDES (this would only
    partially delete in a derivative class)
   */
  class shared_zone_t
      : public boost::intrusive::unordered_set_base_hook
      < boost::intrusive::link_mode<boost::intrusive::auto_unlink> > {
  public:
    /*!
      \brief Constructor
      \post this does not own any zone
     */
    shared_zone_t();

    /*!
      \brief Constructor
      \param zone : zone to share
      \pre zone != nullptr (checked by assertion)
      \post this stores zone with reference count 1
      \note zone MUST NOT BE DELETED
     */
    shared_zone_t(zone_t * zone);

    /*!
      \brief Copy constructor (deleted)
     */
    shared_zone_t(shared_zone_t const & szone) = delete;
    
    /*!
      \brief Destructor
     */
    virtual ~shared_zone_t();
    
    /*!
      \brief Duplication
      \return An UNSHARED copy of this
     */
    shared_zone_t * unshared_copy() const;

    /*!
      \brief Assignement operator (deleted)
    */
    shared_zone_t & operator = (shared_zone_t const & szone) = delete;

    /*!
      \brief Takes a reference on shared zone
      \post The reference has been obtained
      \note Overflow of the reference counter is checked by assertion
     */
    void take();

    /*!
      \brief Releases a reference on shared zone
      \post The reference has been released. If this was the last reference
      the shared zone has been deleted
      \note The shared zone may not be
     */
    void release();

    /*!
      \brief Accessor to memory footprint
      \return The memory footprint of the shared zone
     */
    std::size_t memsize() const;

    zone_t * _zone;      /*!< Shared zone */
    unsigned _refcount;  /*!< Reference count */
  };
  



  /*!
    \class shared_zone_hash_t
    \brief Hash function on shared zones (for cache)
   */
  class shared_zone_hash_t {
  public:
    /*!
      \brief Hash operator
      \return The hash code of the shared zone
     */
    std::size_t operator () (shared_zone_t const & szone) const;
  };



  
  /*!
    \class shared_zone_equal_t
    \brief Equality function on shared zones (for cache)
   */
  class shared_zone_equal_t {
  public:
    /*!
      \brief Equality predicate
      \return True if the shared zones are equal, false otherwise
     */
    bool operator () (shared_zone_t const & szone1,
                      shared_zone_t const & szone2) const;
  };

  

  /*!
    \brief Cache of shared zones
  */
  typedef intrusive_hashtable_t
  < shared_zone_t,
  boost::intrusive::constant_time_size<false>,
  boost::intrusive::power_2_buckets<true>,
  boost::intrusive::hash<shared_zone_hash_t>,
  boost::intrusive::equal<shared_zone_equal_t> > shared_zone_cache_t;


  /*!
    \class zone_sh_t
    \brief Implementation of zone_t based on shared zones
    \tparam ZONE : type of shared zones
   */
  template <class ZONE>
  class zone_sh_t : public zone_t {

    static_assert( std::is_base_of<zone_t, ZONE>(),
                   "*** zone_sh_t: ZONE must derive from zone_t" );

  public:
    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_sh_t(clock_index_t const & index =
        global_t::instance().clock_index()) : _czone(nullptr),
      _cache(nullptr) {
      initialize(new ZONE(index));
    }

    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_sh_t(std::string const & s,
              clock_index_t const & index
              = global_t::instance().clock_index()) : _czone(nullptr),
      _cache(nullptr) {
      initialize(new ZONE(s, index));
    }

    /*!
      \brief Constructor (see zone_t::zone_t)
    */
    zone_sh_t(constraint_collection_t const & collection,
              clock_index_t const & index
              = global_t::instance().clock_index()) : _czone(nullptr),
      _cache(nullptr) {
      initialize(new ZONE(collection, index));
    }

    /*!
      \brief Copy-constructor
      \param z : zone to copy from
      \post this is an UNSHARED copy of z
     */
    zone_sh_t(zone_sh_t<ZONE> const & z) : _czone(nullptr),
      _cache(nullptr) {
      _czone = z._czone->unshared_copy();
    }

    /*!
      \brief Move constructor
      \param z : zone to move
      \post z has been moved to this
     */
    zone_sh_t(zone_sh_t<ZONE> && z) : _czone(z._czone),
      _cache(z._cache) {
      z._czone = nullptr; // invalidates z
      z._cache = nullptr;
    }

    /*!
      \brief Destructor
    */
    virtual ~zone_sh_t() {
      _czone->release();
      // IMPLEMENTATION NOTE: DO NOT DELETE _czone AND _cache.
    }

    /*!
      \brief Copy operation (see zone_t::copy)
      \return An UNSHARED copy of this
    */
    zone_t * copy() const {
      zone_sh_t<ZONE> * zone = new zone_sh_t<ZONE>();
      zone->_czone = _czone->unshared_copy();
      zone->_cache = nullptr;
      return zone;
    }

    /*!
      \brief Sets to the empty zone (see zone_t::set_empty)
      \pre this is not shared
      \throw std::logic_error : if this is shared
    */
    void set_empty() {
      if (shared())
        throw std::logic_error("*** zone_sh_t::set_empty: zone is shared");
      _czone->_zone->set_empty();
    }

    /*!
      \brief Sets to the universal zone (see zone_t::set_empty)
      \pre this is not shared
      \throw std::logic_error : if this is shared
    */
    void set_universal() {
      if (shared())
        throw std::logic_error("*** zone_sh_t::set_universal: zone is shared");
      _czone->_zone->set_universal();
    }

    /*!
      \brief Assignement operator
      \param z : zone to assign from
      \post this is an UNSHARED copy of z
     */
    zone_sh_t<ZONE> & operator = (zone_sh_t<ZONE> const & z) {
      if (&z != this) {
          _czone->release();
          _cache = nullptr;
          _czone = z._czone->unshared_copy();
        }
      return *this;
    }

    /*!
      \brief Move assignement operator
      \param z : zone to move
      \post z has been moved to this
     */
    zone_sh_t<ZONE> & operator = (zone_sh_t<ZONE> && z) {
      if (&z != this) {
          _czone = z._czone;
          _cache = z._cache;
          z._czone = nullptr; // invalidates z
          z._cache = nullptr;
        }
      return *this;
    }

    /*!
      \brief Equality predicate (see zone_t::operator==)
      \pre z is an instance of zone_sh_t<ZONE>
    */
    bool operator == (zone_t const & z) const {
      zone_sh_t<ZONE> const & zone = CAST(zone_sh_t<ZONE> const &, z);

      if ( shared() && (_cache == zone._cache) ) // both cached in same cache
        return (_czone == zone._czone); // pointer equality
      return ( * _czone->_zone == * zone._czone->_zone );
    }

    /*!
      \brief Inclusion predicate (see zone_t::operator<=)
      \pre z is an instance of zone_sh_t<ZONE>
    */
    bool operator <= (zone_t const & z) const {
      zone_sh_t<ZONE> const & zone = CAST(zone_sh_t<ZONE> const &, z);

      if ( shared() && (_cache == zone._cache) && (_czone == zone._czone) )
        return true; // shared in same cache and equal
      return ( * _czone->_zone <= * zone._czone->_zone );
    }

    /*!
      \brief Checks inclusion wrt closure (see zone_t::closure_contains)
      \pre z is an instance of zone_sh_t<ZONE>
    */
    bool closure_contains(zone_t const & z,
                          clock_bounds_t const & M) const {
      zone_sh_t<ZONE> const & zone = CAST(zone_sh_t<ZONE> const &, z);
      
      if ( shared() && (_cache == zone._cache) && (_czone == zone._czone) )
        return true; // shared in same cache and equal
      return _czone->_zone->closure_contains(* zone._czone->_zone, M);
    }

    /*!
      \brief Checks inclusion wrt aLU (see zone_t::aLU_contains)
      \pre z is an instance of zone_sh_t<ZONE>
    */
    bool aLU_contains(zone_t const & z, clock_bounds_t const & L,
                      clock_bounds_t const & U) const {
      zone_sh_t<ZONE> const & zone = CAST(zone_sh_t<ZONE> const &, z);
      
      if ( shared() && (_cache == zone._cache) && (_czone == zone._czone) )
        return true; // shared in same cache and equal
      return _czone->_zone->aLU_contains(* zone._czone->_zone, L, U);
    }

    /*!
      \brief Emptiness check (see zone_t::empty)
    */
    bool empty() const {
      return _czone->_zone->empty();
    }

    /*!
      \brief Universality check (see zone_t::universal)
    */
    bool universal() const {
      return _czone->_zone->universal();
    }

    /*!
      \brief Hash function (see zone_t::hash)
    */
    std::size_t hash() const {
      return _czone->_zone->hash();
    }

    /*!
      \brief Access to zone dimension (see zone_t::dim)
    */
    std::size_t dim() const {
      return _czone->_zone->dim();
    }

    /*!
      \brief Access to the zone as a DBM (see zone_t::to_dbm)
     */
    void to_dbm(raw_t * dbm) const {
      return _czone->_zone->to_dbm(dbm);
    }

    /*!
      \brief Applies a function to the zone (see zone_t::apply)
      \pre this is not shared
      \throw std::logic_error : if this is shared
    */
    void apply(std::function<void(raw_t *, cindex_t)> const & f) {
      if (shared())
        throw std::logic_error("*** zone_sh_t::apply: zone is shared");
      _czone->_zone->apply(f);
    }

    /*!
      \brief Outputs the zone (see zone_t::output)
    */
    void output(std::ostream & os,
                clock_index_t const & index =
        global_t::instance().clock_index()) const {
      _czone->_zone->output(os, index);
    }

    /*!
      \brief Accessor to memory footprint (see zone_t::memsize)
      \return The memory footprint of the zone, including footprint of
      underlying shared zone
     */
    std::size_t memsize() const {
      return ( sizeof(*this) + _czone->memsize() );
    }

    /*!
      \brief Checks is the zone is shared
      \return True if this is shared, false otherwise
     */
    bool shared() const {
      return (_cache != nullptr);
    }

    /*!
      \brief Shares the zone
      \param cache : cache of shared zone
      \post the shared zone has been set to same zone in cache if any,
      otherwise, it has been added to cache
    */
    void share(shared_zone_cache_t & cache) {
      auto p = cache.insert(* _czone);
      if (! p.second) { // already in cache
          _czone->release(); // deletes _czone if not referenced anymore
          _czone = &(* p.first);
          _czone->take();
        }
      _cache = &cache;
    }

    /*!
      \brief Unshares the zone
      \post this holds an UNSHARED copy of its previous value
     */
    void unshare() {
      if ( ! shared() )
        return;
      shared_zone_t * copy = _czone->unshared_copy();
      _czone->release(); // deletes _czone if not referenced anymore
      _czone = copy;
      _cache = nullptr;
    }
  protected:
    /*!
      \brief Initialization with a zone
      \param zone : initial zone
      \post _czone has been initialized from zone
     */
    inline void initialize(zone_t * zone) {
      assert( zone != nullptr );
      _czone = new shared_zone_t(zone);
      assert( _czone != nullptr );
    }

    shared_zone_t * _czone;        /*!< Cachable zone */
    shared_zone_cache_t * _cache;  /*!< Address of cache (if cached) */
  };


  /* Specializations of zone_sh_t */

  /*!
    \brief Zones with shared DBMs
   */
  typedef zone_sh_t<zone_dbm_t> zone_shdbm_t;

} // end of namespace symbolic

#endif // __TCHECKER_ZONE_HH__
