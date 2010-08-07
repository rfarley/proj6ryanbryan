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
#include <set> //set
#include <map>
#include <iterator>
#include <sstream>

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

        typedef std::vector<T>::iterator vertex_iterator; // fix!
        typedef std::vector<T>::iterator edge_iterator; // fix!
	typedef std::vector<T>::iterator adjacency_iterator;//fix

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
            graph.parents[target].push_back(source);
            std::vector<std::vector<T> >::iterator b = graph.g.begin();
            std::vector<std::vector<T> >::iterator c = graph.h.begin();
            std::vector<std::vector<T> >::iterator e = graph.g.end();
	    std::vector<T>* svect;
	    std::vector<T>* edsvect;
	    bool foundtarget = false;
	    bool foundsource = false;
	    edge_descriptor ed = graph.edges;
	    while(b != e){
		std::vector<T>& vect = *b;
		std::vector<T>& edvect = *c;
		if(vect[0] == target){
 			foundtarget = true;
			if(foundsource){
				(*edsvect).push_back(ed);
				graph.elist.push_back(ed);
				(*svect).push_back(target);
				graph.edges++;
 				return std::make_pair(ed,true);
				}
			}
		else if(vect[0] == source){
			foundsource = true;
			svect = &vect;
			edsvect = &edvect;
	                std::vector<T>::iterator edpoint = edvect.begin();
	                std::vector<T>::iterator point = vect.begin();
	                std::vector<T>::iterator pend = vect.end();
			point ++;
			while(point < pend){
				if(target == *point) return std::make_pair(*edpoint, false);
				point++;
				edpoint++;
				}
			if(foundtarget){ 
				edvect.push_back(ed);
				graph.elist.push_back(ed);
				vect.push_back(target);
				graph.edges++;
				return std::make_pair(ed,true);
			}
		}
		b++; c++;
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
	    graph.h.push_back(vect);
	    graph.vlist.push_back(v);
	    graph.parents.insert(std::pair<T, std::list<T> >(v, std::list<T>()));
	    graph.vertices++;
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
* <your documentation>
*/
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& graph) {
	    Graph* grp = const_cast<Graph*>(&graph);
            std::vector<std::vector<T> >::iterator b = (*grp).g.begin();
            std::vector<std::vector<T> >::iterator e = (*grp).g.end();
	    
	    while(b != e){
		if((*b)[0] == v){
			return std::make_pair((*b).begin()+1, (*b).end());
		}
		++b;
	    }
	    std::vector<T> dummy(10);
	  
            return std::make_pair(dummy.begin(), dummy.end());}

        // ----
        // edge
        // ----

        /**
* <your documentation>
*/
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor source, vertex_descriptor target, const Graph& graph) {
	    Graph* grp = const_cast<Graph*>(&graph);
            std::vector<std::vector<T> >::iterator b = (*grp).g.begin();
            std::vector<std::vector<T> >::iterator e = (*grp).g.end();
	    int row = 0;
	    int column = 0;

	    while(b != e){
		if((*b)[0] == source){
			std::vector<T>::iterator b2 = (*b).begin();
			std::vector<T>::iterator e2 = (*b).end();
			while(b2 != e2){
				if((*b2) == target){
					return std::make_pair((*grp).h[row][column], true);
				}
			++column;
			++b2;
			}
		}
		++row;
		column = 0;
		++b;
	    }

            return std::make_pair(-1, false);}

        // -----
        // edges
        // -----

        /**
* O(1) in space
* O(1) in time
* <your documentation>
*/
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& graph) {
	    Graph* grp = const_cast<Graph*>(&graph);
            edge_iterator b = (*grp).elist.begin();
            edge_iterator e = (*grp).elist.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
* <your documentation>
*/
        friend edges_size_type num_edges (const Graph& graph) {
            edges_size_type s = graph.edges;
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
* <your documentation>
*/
        friend vertices_size_type num_vertices (const Graph& graph) {
            vertices_size_type s = graph.vertices;
            return s;}

        // ------
        // source
        // ------

        /**
* <your documentation>
*/
        friend vertex_descriptor source (edge_descriptor edge, const Graph& graph) {
	    Graph* grp = const_cast<Graph*>(&graph);
            std::vector<std::vector<T> >::iterator b = (*grp).h.begin();
            std::vector<std::vector<T> >::iterator e = (*grp).h.end();
	    int row = 0;

	    while(b != e){
		std::vector<T>::iterator b2 = (*b).begin();
		std::vector<T>::iterator e2 = (*b).end();
		while(b2 != e2){
			if((*b2) == edge){
				return (*grp).h[row][0];
			}
		++b2;
		}
		++row;
		++b;
	    }
            return -1;}

        // ------
        // target
        // ------

        /**
* <your documentation>
*/
        friend vertex_descriptor target (edge_descriptor edge, const Graph& graph) {
	    Graph* grp = const_cast<Graph*>(&graph);
            std::vector<std::vector<T> >::iterator b = (*grp).h.begin();
            std::vector<std::vector<T> >::iterator e = (*grp).h.end();
	    int row = 0;
	    int column = 1;

	    while(b != e){
		std::vector<T>::iterator b2 = (*b).begin()+1;
		std::vector<T>::iterator e2 = (*b).end();
		while(b2 != e2){
			if((*b2) == edge){
				return (*grp).g[row][column];
			}
		++b2;
		++column;
		}
		++row;
		column = 1;
		++b;
	    }
            return -1;}

        // ------
        // vertex
        // ------

        /**
* <your documentation>
*/
        friend vertex_descriptor vertex (vertices_size_type s, const Graph& graph) {
	    Graph* grp = const_cast<Graph*>(&graph);
            vertex_descriptor vd = (*grp).g[s][0];
            return vd;}

        // --------
        // vertices
        // --------

        /**
* <your documentation>
*/
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& graph) {
	    Graph* grp = const_cast<Graph*>(&graph);
            vertex_iterator b = (*grp).vlist.begin();
            vertex_iterator e = (*grp).vlist.end();
            return std::make_pair(b, e);}

        // --------
        // has_cycle
        // --------

        /**
* <your documentation>
*/
        friend bool has_cycle (const Graph& graph) {
	       using namespace std;
	       Graph* grp = const_cast<Graph*>(&graph);
		std::vector<std::vector<T> > visitarray(0);
		std::vector<std::vector<T> >::iterator point = (*grp).g.begin();
		for(int i = 0; i < (int)(*grp).g.size(); i++){
			std::vector<T> a(2,0);
			a[0] = (*point)[0];
			visitarray.push_back(a);
			point++;
		}
		std::vector<std::vector<T> >::iterator b = visitarray.begin();
		std::vector<std::vector<T> >::iterator e = visitarray.end();
		while( b != e){
			
			if((*b)[1] == 0){
				if((*grp).has_cycle_help(b, visitarray)) return true;} 
			b++;
		}
            return false;}

	friend void topological_sort_kahn (const Graph& graph, std::ostream_iterator<vertex_descriptor> ois){
		if(has_cycle(graph)) return;
		using namespace std;
		Graph* grp = const_cast<Graph*>(&graph);
		list<T> s;
		map<T, std::list<T> > parents = (*grp).parents;
		map<T, std::list<T> >::iterator b = parents.begin();
		map<T, std::list<T> >::iterator e = parents.end();
		while(b != e){
			if((*b).second.empty()){ 
				s.push_back((*b).first);
			}
			b++;
		}
		list<T> l;
		while(s.size() != 0){
			T node = *(s.begin());
			s.remove(node);
			l.push_back(node);
			std::vector<T>::iterator vb = (*grp).g[node].begin();
			std::vector<T>::iterator ve = (*grp).g[node].end();
			++vb;
			while(vb != ve){
				parents[*vb].remove(node);
				if(parents[*vb].empty()){
 					s.push_back(*vb);
				}
				vb++;
			}
		}
		list<T>::iterator lb = l.begin();
		list<T>::iterator le = l.end();
		while(lb != le){
			std::cout << (*lb) <<".";
			lb++;
		}
		std::cout << std::endl;
	}

	friend void topological_sort(const Graph& graph, std::ostream_iterator<vertex_descriptor> ois){
		if(has_cycle(graph)) return;
		using namespace std;
		Graph* grp = const_cast<Graph*>(&graph);
		list<T> s;
		list<T> l;
		map<T, std::list<T> > parents = (*grp).parents;
		map<T, std::list<T> >::iterator b = parents.begin();
		map<T, std::list<T> >::iterator e = parents.end();
		while(b != e){
			if((*b).second.empty()){ 
				s.push_back((*b).first);
			}
			b++;
		}
		std::vector<std::vector<T> > visitarray(0);
		std::vector<std::vector<T> >::iterator point = (*grp).g.begin();
		for(int i = 0; i < (int)(*grp).g.size(); i++){
			std::vector<T> a(2,0);
			a[0] = (*point)[0];
			visitarray.push_back(a);
			point++;
		}
		list<T>::iterator sb = s.begin();
		list<T>::iterator se = s.end();
		while(sb != se){
			(*grp).visit(*sb, visitarray, l);
			sb++;
		}
		list<T>::iterator lb = l.begin();
		list<T>::iterator le = l.end();
		while(lb != le){
			std::cout << (*lb) <<".";
			lb++;
		}
		std::cout << std::endl;
	}

    private:
        // ----
        // data
        // ----

	size_t vertices;
	size_t edges;
 	std::vector< std::vector<vertex_descriptor> > g; // something like this
 	std::vector< std::vector<edge_descriptor> > h; // something like this
	std::vector<T> elist;
	std::vector<T> vlist;
	std::map<T, std::list<T> > parents;



        // -----
        // valid
        // -----

        /**
* <your documentation>
*/
        bool valid () const {
            // <your code>
            return true;}

	void print() {
	using namespace std;
	/**
	cout << "g: " << endl;
            std::vector<std::vector<T> >::iterator b = g.begin();
            std::vector<std::vector<T> >::iterator e = g.end();
	    while(b != e){
		std::vector<T>::iterator b2 = (*b).begin();
		std::vector<T>::iterator e2 = (*b).end();
			while(b2 != e2){
			cout << *b2 << ".";
			++b2;
			}
		cout << endl;
		++b;
	    }
	cout << endl;
	cout << "h: " << endl;
             b = h.begin();
             e = h.end();
	    while(b != e){
		std::vector<T>::iterator b2 = (*b).begin();
		std::vector<T>::iterator e2 = (*b).end();
			while(b2 != e2){
			cout << *b2 << ".";
			++b2;
			}
		cout << endl;
		++b;
	    }
	  **/
	
	}

	bool has_cycle_help(std::vector<std::vector<T> >::iterator& beg, std::vector<std::vector<T> >& visitarray){
		using namespace std;
		(*beg)[1] = 1;
		std::vector<T> successors = g[(*beg)[0]];
                std::vector<T>::iterator b = successors.begin()+1;
                std::vector<T>::iterator e = successors.end();
		while(b != e){
			if (visitarray[*b][1] == 1) return true;
			if (visitarray[*b][1] == 2){
				std::vector<std::vector<T> >::iterator beg2 = visitarray.begin() + *b;
				if (has_cycle_help(beg2, visitarray)) return true;
			}
			b++;
		}
		(*beg)[1] = 2;
		return false;
	}

	void visit (vertex_descriptor n, std::vector<std::vector<T> >& visitarray, std::list<T>& l){
		if(visitarray[n][1] == 0){
			visitarray[n][1] = 1;
			std::vector<T>::iterator vb = g[n].begin();
			std::vector<T>::iterator ve = g[n].end();
			++vb;
			while(vb != ve){
				visit(*vb, visitarray, l);
				vb++;
			}
			l.push_back(n);
		}
	}



    public:
        // ------------
        // constructors
        // ------------

        /**
* <your documentation>
*/
        Graph () : g(), h(), elist(), vlist(), parents() {
            vertices = 0;
	    edges = 0;
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h


