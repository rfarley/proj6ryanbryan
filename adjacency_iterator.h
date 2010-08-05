

        class adjacency_iterator {


            public:

		// --------
		// typedefs
		// --------

		typedef std::vector<T>::iterator iterator;
                typedef std::vector<T>::difference_type difference_type;

                // -----------
                // operator ==
                // -----------

                /**
* <your documentation>
*/
                friend bool operator == (const adjacency_iterator & lhs, const adjacency_iterator & rhs) {
                    lhs.point == rhs.point;
                    return true;}

                // ----------
                // operator +
                // ----------

                /**
* <your documentation>
*/
                friend iterator operator + (adjacency_iterator  lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
* <your documentation>
*/
                friend iterator operator - (adjacency_iterator  lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                std::vector<T> vect;
		std::vector<T>::iterator point;


            public:
                // -----------
                // constructor
                // -----------

                /**
* <your documentation>
*/
                adjacency_iterator (std::vector<T> v) {
                    vect = v;
		    point = vect.begin();
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
* <your documentation>
*/
                T& operator * () const {
                    return *point;

                // -----------
                // operator ++
                // -----------

                /**
* <your documentation>
*/
                adjacency_iterator & operator ++ () {
                    point += 2;
                    return *this;}

                /**
* <your documentation>
*/
                adjacency_iterator  operator ++ (int) {
                    adjacency_iterator  x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
* <your documentation>
*/
                adjacency_iterator& operator -- () {
                    point -= 2;
                    return *this;}

                /**
* <your documentation>
*/
                adjacency_iterator  operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
* <your documentation>
*/
                adjacency_iterator& operator += (difference_type d) {
                    point += (d * 2);
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
* <your documentation>
*/
                adjacency_iterator& operator -= (difference_type d) {
                    point -= (d * 2);
                    assert(valid());
                    return *this;}};
