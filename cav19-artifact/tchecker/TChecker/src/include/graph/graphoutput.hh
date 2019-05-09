
#ifndef __TCHECKER_GRAPHOUTPUT_HH__
#define __TCHECKER_GRAPHOUTPUT_HH__

#include <ostream>
#include <set>
#include <stdexcept>

#include "base/singleton.hh"
#include "graph/graph.hh"

/*!
  \file graphoutput.hh
  \brief Output graphs

  Allows to output nodes and edges on different layers. The background layer
  has number 0. New layers can be created automatically (with L_NEW) or
  manually (by picking a layer number). Different format of output are
  proposed below.
*/

namespace graph {


  /*!
    \brief Type of edge (defines how it is output)
  */
  enum edge_type_t {
    ET_NORMAL,       /*!< Normal edge (parent-child) */
    ET_PROPAGATION,  /*!< Propagation edge */
    ET_COVERING      /*!< Covering edge */
  };


  /*!
    \brief Layer selectors
  */
  enum layer_selector_t {
    L_BACKGROUND,    /*!< Background layer (number 0) */
    L_CURRENT,       /*!< Current layer */
    L_FRONTMOST,     /*!< Frontmost layer */
    L_NEW            /*!< New frontmost layer */
  };


  /*!
    \class output_t
    \brief Interface to graph output
   */
  class output_t {
  public:
    /*!
      \brief Constructor
      \param os : output stream
      \post layer has been initialized to 0 and output stream references os
    */
    output_t(std::ostream & os);

    /*!
      \brief Destructor
    */
    virtual ~output_t();

    /*!
      \brief Initialization of output. To be called before any other method
    */
    virtual void start() = 0;

    /*!
      \brief Finalization of output. To be called after all other methods
    */
    virtual void end() = 0;

    /*!
      \brief Output a node
      \param node : node to output
    */
    virtual void node(graph::node_t const & node) = 0;

    /*!
      \brief Output an edge
      \param src : source node
      \param tgt : target node
      \param edge_type : type of edge
    */
    virtual void edge(graph::node_t const & src, graph::node_t const & tgt,
		      enum edge_type_t edge_type = ET_NORMAL) = 0;

    /*!
      \brief Output a title
      \param title : to output
     */
    virtual void title(std::string const & title) = 0;

    /*!
      \brief Accessor (set current layer)
      \param layer : new layer number
      \post current layer has been set to "layer", "layer" has been added to
      the set of layers. "layer" becomes the frontmost layer if it has the
      highest number among all other layers
    */
    virtual void layer(unsigned layer);

    /*!
      \brief Accessor (set current layer)
      \param selector : layer selector
      \post Sets current layer to the layer selected by "selector". When
      selector=L_NEW, a new (frontmost) layer is created. See layer(unsigned)
      for extra information.
    */
    virtual void layer(layer_selector_t selector);
  protected:
    unsigned _layer;            /*!< Current layer */
    unsigned _frontmost_layer;  /*!< Frontmost layer */
    std::set<unsigned> _layers; /*!< Set of layer numbers */
    std::ostream & _os;         /*!< Output stream */
  };



  /*!
    \class no_output_t
    \brief Graph output that does nothing (used to preserve run-time when no
    output is expected)
   */
  class no_output_t : public output_t {
  public:
    /*!
      \brief Constructor
      \param os : output stream
      \post see output_t::output_t()
    */
    no_output_t(std::ostream & os);

    /*!
      \brief Destructor
    */
    virtual ~no_output_t();

    /*!
      \brief see output_t::start()
      \post Does nothing
    */
    virtual void start();

    /*!
      \brief see output_t::end()
      \post Does nothing
    */
    virtual void end();

    /*!
      \brief see output_t::node()
      \post Does nothing
    */
    virtual void node(graph::node_t const & node);

    /*!
      \brief see output_t::edge()
      \post Does nothing
    */
    virtual void edge(graph::node_t const & src, graph::node_t const & tgt,
		      enum edge_type_t edge_type = ET_NORMAL);

    /*!
      \brief see output_t::title()
      \post Does nothing
     */
    virtual void title(std::string const & title);
  };


  
  
  /*!
    \class raw_output_t
    \brief Output a graph as raw text
  */
  class raw_output_t : public output_t {
  public:
    /*!
      \brief Constructor
      \param os : output stream
    */
    raw_output_t(std::ostream & os);

    /*!
      \brief Destructor
    */
    virtual ~raw_output_t();

    /*!
      \brief Initialization of output. To be called before any other method
      \post Does nothing
    */
    virtual void start();

    /*!
      \brief Finalization of output. To be called after all other methods
      \post Does nothing
    */
    virtual void end();

    /*!
      \brief Output a node
      \param node : node to output
      \post node has been output to current layer
    */
    virtual void node(graph::node_t const & node);

    /*!
      \brief Output an edge
      \param src : source node
      \param tgt : target node
      \param edge_type : type of edge
      \post an edge of type edge_type from src to tgt has been output to
      current layer
    */
    virtual void edge(graph::node_t const & src, graph::node_t const & tgt,
		      enum edge_type_t edge_type = ET_NORMAL);

    /*!
      \brief see output_t::title()
      \post title has been output to current layer
     */
    virtual void title(std::string const & title);
  };
  

  
  /*!
    \class dot_output_t
    \brief Output a graph in the DOT language
  */
  class dot_output_t : public output_t {
  public:
    /*!
      \brief Constructor
      \param os : output stream
    */
    dot_output_t(std::ostream & os);

    /*!
      \brief Destructor
     */
    virtual ~dot_output_t();

    /*!
      \brief see output_t::start()
      \post Outputs dot digraph definition
    */
    virtual void start();

    /*!
      \brief see output_t::end()
      \post Outputs layers and finalizes dot output
    */
    virtual void end();

    /*!
      \brief see output_t::node()
      \post Outputs node in dot format to current layer
    */
    virtual void node(graph::node_t const & node);


    /*!
      \brief see output_t::edge()
      \post Outputs edge from src to tgt with type edge_type in dot format
      to current layer
    */
    virtual void edge(graph::node_t const & src, graph::node_t const & tgt,
		      enum edge_type_t edge_type = ET_NORMAL);

    /*!
      \brief see output_t::title()
      \post title has been output in dot format to current layer
     */
    virtual void title(std::string const & title);
  };


  
  /* Graph output factory */

  /*!
    \brief Setup flags for graph output
  */
  typedef char output_flags_t;

  const output_flags_t OUTPUT_NO  = 0; /*!< No output */
  const output_flags_t OUTPUT_RAW = 1; /*!< Raw text output */
  const output_flags_t OUTPUT_DOT = 2; /*!< Graphviz dot output */

  /*!< Default output (no output) */
  const output_flags_t OUTPUT_DEFAULT = OUTPUT_NO;

  /*!
    \class output_factory_t
    \brief Graph output factory
   */
  class output_factory_t : public singleton_t<output_factory_t> {
    
    friend class singleton_t<output_factory_t>;  // Grants access to cons/Des

  public:
    /*!
      \brief Builds a new graph output
      \param os : output stream
      \param flags : type of graph output to build
      \return A new graph output of type required by flags
      \throw std::logic_error : if flags is invalid
     */
    output_t * new_output(std::ostream & os,
			  output_flags_t flags = OUTPUT_DEFAULT) {
      output_t * output;

      switch (flags) {
      case OUTPUT_NO:
	output = new no_output_t(os);
	break;
      case OUTPUT_RAW:
	output = new raw_output_t(os);
	break;
      case OUTPUT_DOT:
	output = new dot_output_t(os);
	break;
      default:
	throw std::logic_error("*** graph::output_factory_t: invalid flags");
      }

      return output;
    }
  private:
    /*!
      \brief Constructor (made private)
    */
    output_factory_t() = default;

    /*!
      \brief Destructor (made private)
    */
    ~output_factory_t() = default;
  };

} // end of namespace graph

#endif // __TCHECKER_GRAPHOUTPUT_HH__
