#ifndef CEGAR_REFINEMENT_HH
#define CEGAR_REFINEMENT_HH

#include <chrono>
#include "algorithms/cegaremptiness.hh"
#include "base/clockset.hh"
#include "graph/graph.hh"
#include "graph/graphoutput.hh"
#include "graph/nodescmp.hh"
#include "graph/pw.hh"
#include "symbolic/timemeasure.hh"
#include "semantics/semantics.hh"
#include "semantics/zg.hh"
#include "symbolic/clockbounds.hh"
#include "syntax/system_builder.hh"
#include "syntax/ta.hh"
#include "symbolic/abstraction_table.hh"

namespace algorithms {

  namespace cegaremptiness {

    class global_abstraction_node_t : public algorithms::cegaremptiness::node_t<global_abstraction_node_t> {
    public:
      virtual ~global_abstraction_node_t();
      static void init(syntax::model_t* model);
      void init_abstraction();
      static void print_stats() {}
      bool abstract();
      symbolic::zone_t* abstract_zone();
      void add_interpolant(raw_t* cc,
                           syntax::vedge_t const & vedge);
      static symbolic::abstraction_table_t* _table;
      static syntax::model_t* _model;
    };

    class local_abstraction_node_t : public algorithms::cegaremptiness::node_t<local_abstraction_node_t> {
    public:
      virtual ~local_abstraction_node_t();
      static void init(syntax::model_t* model);
      void init_abstraction();
      bool abstract();

      static void print_stats() {}
      symbolic::zone_t* abstract_zone();
      void add_interpolant(raw_t* cc,
                           syntax::vedge_t const & vedge);

      symbolic::abstraction_table_t* _table;
      static syntax::model_t* _model;
    };


    class syntax_abstraction_node_t : public algorithms::cegaremptiness::node_t<syntax_abstraction_node_t> {
    public:
      virtual ~syntax_abstraction_node_t();
      static void init(syntax::model_t* model);
      void init_abstraction();
      bool abstract();

      static void print_stats() {

//        std::cout<<"Temps pour la cloture dans abstract: "<< symbolic::time_measurement::abstract_time.count()/1000000<< "\n";
//        unsigned max_size = 0;
//        clock_id_t dim= global_t::instance().clock_index().size() ;

//        cindex_t i,j;
//        for (i = 0; i < dim; ++i)
//          {
//            for (j = 0; j < dim; ++j) if (i != j)
//              {
//                unsigned size =0;

//                for(auto loc_table : *_table)
//                  {
//                    size += loc_table.second.at(i,j).size();
//                  }
//                max_size = std::max(max_size, size);
//              }
//          }
//        std::cout<<"Nombre max de valeur par couple d'horloge: "<< max_size<< "\n";
      }
      symbolic::zone_t* abstract_zone();
      void add_interpolant(raw_t* cc,
                           syntax::vedge_t const & vedge);
      
      
      static symbolic::syntax_abstraction_table_t* _table;
      static syntax::model_t* _model;
    };

    namespace cut {
      
      template <class NODE>
      bool nodes_cover(NODE const * n1, NODE const * n2) {
        return ( graph::nodes_distinct(n1, n2) &&
                 graph::nodes_syntax_eq(n1, n2) &&
                 graph::nodes_zone_leq(n1,n2) );
      }
      
      template <class NODE>
      class algorithm_t
          : public algorithms::cegaremptiness::algorithm_t<NODE> {
      public:
        
        algorithm_t(syntax::system_builder_t & system_builder,
                    algorithms::options_t const & options): algorithms::cegaremptiness::algorithm_t<NODE>(system_builder,
                                                                                                          options,
                                                                                                          nodes_cover<NODE>) {}
      protected:
        
        NODE* where_cut(std::vector<NODE*> path, std::vector<NODE *> &uncovered) {
          if (!path.front()->covered()) {

              auto it = std::find(uncovered.begin(), uncovered.end(), path.front());
              if (it != uncovered.end()){
                  uncovered.erase(it);
                }
              uncovered.push_back(path.front());
            }
          return path.front();
          
        }

      };
      
      
    }
    namespace highest_covered {
      template <class NODE>
      bool nodes_cover(NODE const * n1, NODE const * n2) {
        return ( graph::nodes_distinct(n1, n2) &&
                 graph::nodes_syntax_eq(n1, n2) &&
                 graph::nodes_zone_leq(n1,n2) );
      }
      
      template <class NODE>
      class algorithm_t
          : public algorithms::cegaremptiness::algorithm_t<NODE> {
      public:
        
        algorithm_t(syntax::system_builder_t & system_builder,
                    algorithms::options_t const & options): algorithms::cegaremptiness::algorithm_t<NODE>(system_builder,
                                                                                                          options,
                                                                                                          nodes_cover<NODE>) {}
        
        
        NODE* where_cut(std::vector<NODE*> path, std::vector<NODE *> &uncovered) {
          bool result = false;
          std::function<void(NODE *)> f = &NODE::abstract;
          
          NODE * node;

          
          //we look at the first node of the path that is empty, alreay covered, or will be covered once in the passed waiting list
          //NOTE: all the node of path up to the selected node are inserted in pw or covered by a node of pw
          while (!result) {

              std::vector<NODE *> covered_nodes;
              NODE * covering_node =nullptr ;
              node = path.front();
              if (node->zone()->empty())
                // we reached the first empty node in path, we will cut here
                result =true;
              else if (node->covered())
                //the node is covered, we will cut at this node if his covering node is not one of his descendant
                result =true /*&& !node->is_ancestor(node->covering_node)*/;
              else
                {
                  auto it = std::find(uncovered.begin(), uncovered.end(), node);
                  if (it != uncovered.end()){
                      uncovered.erase(it);
                    }
                  this->concrete(node);
                  for (NODE * n : uncovered)
                    {
                      assert(!this->_pw->pfind(n));
                      if (this->_pw_cover(node, n)&& /*!node->is_ancestor(n)&&*/n!=node)
                        {// beaucoup d'options: insérer n immédiatement, mettre node à la fin de uncovered (il sera necessairement couvert, mais peut-etre pas par n)

                          result = true;
                        }

                    }

                  if (result)
                    {

                      assert(node->covered_nodes.empty());
                      uncovered.push_back(node);
                    } // it was covered by one of the uncovered node
                  else if ( !this->_pw->insert_passed_function(node, covering_node, covered_nodes, f))
                    { //the node is inserted and covered, we will cut at this node if his covering node is not one of his descendant
                      assert(covered_nodes.empty());
                      this->_go->node(*node);
                      this->_asg.cover(node,covering_node);/*
                      if (node->is_ancestor(node->covering_node))
                        node->abstract(); //not gonna be cut, internal node should always contain the abstracted zone, even if covered.
                      else*/ result = true; //
                    }
                  else
                    {
                      assert( covering_node == nullptr );
                      for (NODE * n : covered_nodes)
                        {
                          if (n->snumber == 0)
                            this->_go->node(*n);
                          this->_asg.cover(n,node);

                        }
                    }
                }
              path.erase(path.begin());
            }
          return node;
        }
        // Peut grandmeent etre améliorée avec des early return.
      };
    }
    namespace top_covered {
      template <class NODE>
      bool nodes_cover(NODE const * n1, NODE const * n2) {
        return ( graph::nodes_distinct(n1, n2) &&
                 graph::nodes_syntax_eq(n1, n2) &&
                 graph::nodes_zone_leq(n1,n2) );
      }
      
      template <class NODE>
      class algorithm_t
          : public algorithms::cegaremptiness::algorithm_t<NODE> {
      public:
        
        algorithm_t(syntax::system_builder_t & system_builder,
                    algorithms::options_t const & options): algorithms::cegaremptiness::algorithm_t<NODE>(system_builder,
                                                                                                          options,
                                                                                                          nodes_cover<NODE>) {}
      protected:
        
        NODE* where_cut(std::vector<NODE*> path, std::vector<NODE *> &uncovered) {
          std::function<void(NODE *)> f = &NODE::abstract;
          NODE * node=path.front();
          //we test if teh first node of path is covered or empty
          if (node->zone()->empty()) {return node;}
          else if (node->covered() /*&& !node->is_ancestor(node->covering_node)*/) {return node;}
          else
            {
              auto it = std::find(uncovered.begin(), uncovered.end(), node);
              if (it != uncovered.end())
                {
                  uncovered.erase(it);
                }
              std::vector<NODE *> covered_nodes;
              NODE * covering_node;
              this->concrete(node);
              for (NODE * n : uncovered)
                {
                  if (nodes_cover(node, n)/*&& !node->is_ancestor(n)*/&&node!=n)
                    {// beaucoup d'options: insérer n immédiatement, mettre node à la fin de uncovered (il sera necessairement couvert, mais peut-etre pas pas n)

                      uncovered.push_back(node);
                      return node;
                      break;
                    }

                }
              if ( !this->_pw->insert_passed_function(node, covering_node, covered_nodes, f))
                { //the node is inserted and covered, we will cut at this node if his covering node is not one of his descendant
                  this->_go->node(*node);
                  this->_asg.cover(node,covering_node);
                  /*if (node->is_ancestor(node->covering_node))
                    node->abstract(); //not gonna be cut, internal node should always contain the abstracted zone, even if covered.
                  else */return node; //
                }
              else
                {
                  assert( covering_node == nullptr );
                  for (NODE * n : covered_nodes)
                    {
                      if (n->snumber == 0)
                        this->_go->node(*n);
                      this->_asg.cover(n,node);

                    }
                }
            }
          path.erase(path.begin());;
          while (!path.empty())
            {
              
              node= path.front();
              if (node->zone()->empty() || node->covered()) {}
              else
                {
                  auto it = std::find(uncovered.begin(), uncovered.end(), node);
                  if (it != uncovered.end()){
                      uncovered.erase(it);
                    }
                  uncovered.push_back(node);
                }

              path.erase(path.begin());;
            }

          // all the nodes of path have been inserted or covered
          return node;
        }

      };
    }
    
    
  }

}
#endif // CEGAR_REFINEMENT_HH
