#ifndef ABSTRACTION_TABLE_HH
#define ABSTRACTION_TABLE_HH
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <dbm/constraints.h>

#include "base/clockindex.hh"
#include "base/global.hh"
#include "symbolic/clockbounds.hh"
#include "symbolic/constraints.hh"
#include "syntax/locs_edges.hh"

namespace symbolic {

//  struct pair_hash {
//      template <class T1, class T2>
//      std::size_t operator () (const std::pair<T1,T2> &p) const {
//          size_t seed = 0;
//          boost::hash_combine(seed, p.first);
//          boost::hash_combine(seed, p.second);
//          return seed;
//      }
//  };
  struct pair_hash {
      template <class T1, class T2>
      std::size_t operator () (const std::pair<T1,T2> &p) const {
          auto h1 = std::hash<T1>{}(p.first);
          auto h2 = std::hash<T2>{}(p.second);

          // Mainly for demonstration purposes, i.e. works but is overly simple
          // In the real world, use sth. like boost.hash_combine
          return h1 ^ h2;
      }
  };

//  class abstraction_table_t : public std::unordered_map<std::pair<clock_id_t, clock_id_t>, std::set<int32_t> ,pair_hash> {
//  public:
//    abstraction_table_t(clock_id_t dim);


//    abstraction_table_t * copy() const {
//      abstraction_table_t * t = new abstraction_table_t(*this);
//      assert(t != nullptr);
//      return t;}

//    abstraction_table_t(clock_bounds_t L, clock_bounds_t U, clock_id_t dim= global_t::instance().clock_index().size() );
//    void add(constraint_t c);

//    void add(constraint_collection_t c);
//    void add(abstraction_table_t t, clock_id_t dim);
//    raw_t abstraction(int32_t val, clock_id_t x, clock_id_t y);

//    void dbm_abstraction(raw_t *dbm, cindex_t dim);

//    long close_duration;

//  };


  class abstraction_table_t {
  public:
    abstraction_table_t(clock_id_t dim= global_t::instance().clock_index().size());

    abstraction_table_t(const syntax::loc_t* loc,clock_id_t dim= global_t::instance().clock_index().size());

    abstraction_table_t * copy() const {
      abstraction_table_t * t = new abstraction_table_t(*this);
      assert(t != nullptr);
      return t;}

    abstraction_table_t(clock_bounds_t L, clock_bounds_t U, clock_id_t dim= global_t::instance().clock_index().size() );
    void add(constraint_t c);
    std::set<int32_t>&  at(clock_id_t x, clock_id_t y) {return _table[x*_dim +y];}
    void add(constraint_collection_t c);
    void add(abstraction_table_t t);
    raw_t abstraction(int32_t val, clock_id_t x, clock_id_t y);

    void dbm_abstraction(raw_t *dbm, cindex_t dim);

    long close_duration;
    clock_id_t _dim;
    std::set<int32_t>* _table;
  };
  class syntax_abstraction_table_t : public std::unordered_map<const syntax::loc_t*, symbolic::abstraction_table_t > {
  public:
    syntax_abstraction_table_t() {};


    void add(constraint_t c,const syntax::loc_t* loc);
    void init(const syntax::vloc_t &vloc, clock_id_t dim= global_t::instance().clock_index().size() );
    void add(constraint_collection_t c,const syntax::loc_t* loc);
    void add(abstraction_table_t t, clock_id_t dim,const syntax::loc_t* loc);
    raw_t abstraction(int32_t val, clock_id_t x, clock_id_t y, std::vector<abstraction_table_t*> &vtable, const clock_bounds_t& L, const clock_bounds_t& U);
    raw_t abstraction(int32_t val, clock_id_t x, clock_id_t y, std::vector<abstraction_table_t*> &vtable);

    void dbm_abstraction(raw_t *dbm, cindex_t dim, const syntax::vloc_t& vloc);
    void dbm_abstraction(raw_t *dbm, cindex_t dim, const syntax::vloc_t& vloc, const clock_bounds_t& L, const clock_bounds_t& U);
    long close_duration;
  };

} // end of namespace symbolic
#endif // ABSTRACTION_TABLE_HH
