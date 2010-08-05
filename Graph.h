// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2010
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector> // vector

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

	typedef int T;

        typedef T vertex_descriptor; // fix!
        typedef T edge_descriptor; // fix!

        typedef T* vertex_iterator; // fix!
        typedef T* edge_iterator; // fix!
        typedef T* adjacency_iterator; // fix!

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
* <your documentation>
*/
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor source, vertex_descriptor target, Graph& graph) {
	    if(source == target) return std::make_pair(-1, false);
            std::vector<std::vector<int> >::iterator b = graph.g.begin();
            std::vector<std::vector<int> >::iterator e = graph.g.end();
	    std::vector<int>* svect;
	    bool foundtarget = false;
	    bool foundsource = false;
	    edge_descriptor ed = graph.edges;
	    while(b != e){
		std::vector<int>& vect = *b;
		if(vect[0] == target){
 			foundtarget = true;
			if(foundsource){
				(*svect).push_back(ed);
				(*svect).push_back(target);
				graph.edges++;
 				return std::make_pair(ed,true);
				}
			}
		else if(vect[0] == source){
			foundsource = true;
			svect = &vect;
	                std::vector<int>::iterator point = vect.begin();
	                std::vector<int>::iterator pend = vect.end();
			point += 2;
			while(point < pend){
				if(target == *point) return std::make_pair(*(point-1), false);
				point+=2;
				}
			if(foundtarget){ 
				vect.push_back(ed);
				vect.push_back(target);
				graph.edges++;
				return std::make_pair(ed,true);
			}
		}
		b++;
	    }
            return std::make_pair(-1, false);}

        // ----------
        // add_vertex
        // ----------

        /**
* <your documentation>
*/
        friend vertex_descriptor add_vertex (Graph& graph) {
            vertex_descriptor v = graph.vertices;
	    std::vector<T> vect(1);
	    vect[0] = v;
            graph.g.push_back(vect);
	    graph.vertices++;
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
* <your documentation>
*/
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor, const Graph&) {
            // <your code>
            adjacency_iterator b = adjacency_iterator();
            adjacency_iterator e = adjacency_iterator();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
* <your documentation>
*/
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor, vertex_descriptor, const Graph&) {
            // <your code>
            edge_descriptor ed;
            bool b;
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
* O(1) in space
* O(1) in time
* <your documentation>
*/
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph&) {
            // <your code>
            edge_iterator b;
            edge_iterator e;
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
* <your documentation>
*/
        friend edges_size_type num_edges (const Graph&) {
            // <your code>
            edges_size_type s;
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
* <your documentation>
*/
        friend vertices_size_type num_vertices (const Graph&) {
            // <your code>
            vertices_size_type s;
            return s;}

        // ------
        // source
        // ------

        /**
* <your documentation>
*/
        friend vertex_descriptor source (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v;
            return v;}

        // ------
        // target
        // ------

        /**
* <your documentation>
*/
        friend vertex_descriptor target (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v;
            return v;}

        // ------
        // vertex
        // ------

        /**
* <your documentation>
*/
        friend vertex_descriptor vertex (vertices_size_type, const Graph&) {
            // <your code>
            vertex_descriptor vd;
            return vd;}

        // --------
        // vertices
        // --------

        /**
* <your documentation>
*/
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph&) {
            // <your code>
            vertex_iterator b = vertex_iterator();
            vertex_iterator e = vertex_iterator();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

	T vertices;
	T edges;
 	std::vector< std::vector<vertex_descriptor> > g; // something like this



        // -----
        // valid
        // -----

        /**
* <your documentation>
*/
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
* <your documentation>
*/
        Graph () : g() {
            vertices = 0;
	    edges = 0;
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h


