
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <algorithm>
#include "../objects/test.hpp"
#include "../helpers/random_values.hpp"
#include "../helpers/helpers.hpp"

template <class X>
void bucket_tests(X* = 0)
{
    typedef typename X::size_type size_type;
    typedef typename X::const_local_iterator const_local_iterator;
    test::random_values<X> v(1000);

    X x(v.begin(), v.end());

    BOOST_TEST(x.bucket_count() < x.max_bucket_count());
    std::cerr<<x.bucket_count()<<"<"<<x.max_bucket_count()<<"\n";

    for(typename test::random_values<X>::const_iterator
            it = v.begin(), end = v.end(); it != end; ++it)
    {
        size_type bucket = x.bucket(test::get_key<X>(*it));

        BOOST_TEST(bucket < x.bucket_count());
        if(bucket < x.max_bucket_count()) {
            // lit? lend?? I need a new naming scheme.
            const_local_iterator lit = x.begin(bucket), lend = x.end(bucket);
            while(lit != lend && test::get_key<X>(*it) != test::get_key<X>(*lit)) ++lit;
            BOOST_TEST(lit != lend);
        }
    }

    for(size_type i = 0; i < x.bucket_count(); ++i) {
        BOOST_TEST(x.bucket_size(i) == (size_type) std::distance(x.begin(i), x.end(i)));
        X const& x_ref = x;
        BOOST_TEST(x.bucket_size(i) == (size_type) std::distance(x_ref.begin(i), x_ref.end(i)));
    }
}

int main()
{
    bucket_tests((boost::unordered_set<int>*) 0);
    bucket_tests((boost::unordered_multiset<int>*) 0);
    bucket_tests((boost::unordered_map<int, int>*) 0);
    bucket_tests((boost::unordered_multimap<int, int>*) 0);

    bucket_tests((boost::unordered_set<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    bucket_tests((boost::unordered_multiset<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    bucket_tests((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    bucket_tests((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    return boost::report_errors();
}
