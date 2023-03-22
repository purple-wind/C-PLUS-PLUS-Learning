#ifndef __MY_PRIORITY_QUEUE_H__
#define __MY_PRIORITY_QUEUE_H__
#include<algorithm>
//优先队列
using namespace std;
template<typename _Tp, typename _Sequence = vector<_Tp>, typename _Compare  = less<typename _Sequence::value_type> >
class my_priority_queue
{
    template<typename _Alloc> using _Uses = typename enable_if<uses_allocator<_Sequence, _Alloc>::value>::type;

    public:
        typedef typename	_Sequence::value_type		value_type;
        typedef typename	_Sequence::reference		reference;
        typedef typename	_Sequence::const_reference	const_reference;
        typedef typename	_Sequence::size_type		size_type;
        typedef		_Sequence			container_type;
        // _GLIBCXX_RESOLVE_LIB_DEFECTS
        // DR 2684. priority_queue lacking comparator typedef
        typedef	       _Compare				value_compare;

    protected:
        //  See queue::c for notes on these names.
        _Sequence  c;
        _Compare   comp;

    public:
        /**
     *  @brief  Default constructor creates no elements.
     */
        template<typename _Seq = _Sequence,
                 typename _Requires = typename enable_if<__and_<is_default_constructible<_Compare>,
                 is_default_constructible<_Seq>>::value>::type>
            my_priority_queue(): c(), comp() { }

        explicit my_priority_queue(const _Compare& __x, const _Sequence& __s): c(__s), comp(__x)
        { std::make_heap(c.begin(), c.end(), comp); }

        explicit my_priority_queue(const _Compare& __x, _Sequence&& __s = _Sequence()): c(std::move(__s)), comp(__x)
        { std::make_heap(c.begin(), c.end(), comp); }

        template<typename _Alloc, typename _Requires = _Uses<_Alloc>>explicit my_priority_queue(const _Alloc& __a): c(__a), comp() { }

        template<typename _Alloc, typename _Requires = _Uses<_Alloc>>my_priority_queue(const _Compare& __x, const _Alloc& __a): c(__a), comp(__x) { }

        // _GLIBCXX_RESOLVE_LIB_DEFECTS
        // 2537. Constructors [...] taking allocators should call make_heap
        template<typename _Alloc, typename _Requires = _Uses<_Alloc>>
        my_priority_queue(const _Compare& __x, const _Sequence& __c, const _Alloc& __a): c(__c, __a), comp(__x)
        { std::make_heap(c.begin(), c.end(), comp); }

        template<typename _Alloc, typename _Requires = _Uses<_Alloc>>
        my_priority_queue(const _Compare& __x, _Sequence&& __c, const _Alloc& __a): c(std::move(__c), __a), comp(__x)
        { std::make_heap(c.begin(), c.end(), comp); }

        template<typename _Alloc, typename _Requires = _Uses<_Alloc>>
        my_priority_queue(const my_priority_queue& __q, const _Alloc& __a): c(__q.c, __a), comp(__q.comp) { }

        template<typename _Alloc, typename _Requires = _Uses<_Alloc>>
        my_priority_queue(my_priority_queue&& __q, const _Alloc& __a): c(std::move(__q.c), __a), comp(std::move(__q.comp)) { }

        /**
     *  @brief  Builds a %queue from a range.
     *  @param  __first  An input iterator.
     *  @param  __last  An input iterator.
     *  @param  __x  A comparison functor describing a strict weak ordering.
     *  @param  __s  An initial sequence with which to start.
     *
     *  Begins by copying @a __s, inserting a copy of the elements
     *  from @a [first,last) into the copy of @a __s, then ordering
     *  the copy according to @a __x.
     *
     *  For more information on function objects, see the
     *  documentation on @link functors functor base
     *  classes@endlink.
     */

        template<typename _InputIterator>
        my_priority_queue(_InputIterator __first, _InputIterator __last, const _Compare& __x, const _Sequence& __s): c(__s), comp(__x)
        {
            __glibcxx_requires_valid_range(__first, __last);
            c.insert(c.end(), __first, __last);
            std::make_heap(c.begin(), c.end(), comp);
        }

        template<typename _InputIterator>
        my_priority_queue(_InputIterator __first, _InputIterator __last, const _Compare& __x = _Compare(), _Sequence&& __s = _Sequence()): c(std::move(__s)), comp(__x)
        {
            __glibcxx_requires_valid_range(__first, __last);
            c.insert(c.end(), __first, __last);
            std::make_heap(c.begin(), c.end(), comp);
        }

        /**
     *  Returns true if the %queue is empty.
     */
        _GLIBCXX_NODISCARD bool empty() const
        { return c.empty(); }

        /**  Returns the number of elements in the %queue.  */
        size_type size() const
        { return c.size(); }

        /**
     *  Returns a read-only (constant) reference to the data at the first
     *  element of the %queue.
     */
        const_reference top() const
        {
            __glibcxx_requires_nonempty();
            return c.front();
        }

        /**
     *  @brief  Add data to the %queue.
     *  @param  __x  Data to be added.
     *
     *  This is a typical %queue operation.
     *  The time complexity of the operation depends on the underlying
     *  sequence.
     */
        void push(const value_type& __x)
        {
            c.push_back(__x);
            std::push_heap(c.begin(), c.end(), comp);
        }

        void push(value_type&& __x)
        {
            c.push_back(std::move(__x));
            std::push_heap(c.begin(), c.end(), comp);
        }

        template<typename... _Args> void emplace(_Args&&... __args)
        {
            c.emplace_back(std::forward<_Args>(__args)...);
            std::push_heap(c.begin(), c.end(), comp);
        }

        /**
     *  @brief  Removes first element.
     *
     *  This is a typical %queue operation.  It shrinks the %queue
     *  by one.  The time complexity of the operation depends on the
     *  underlying sequence.
     *
     *  Note that no data is returned, and if the first element's
     *  data is needed, it should be retrieved before pop() is
     *  called.
     */
        void pop()
        {
            __glibcxx_requires_nonempty();
            std::pop_heap(c.begin(), c.end(), comp);
            c.pop_back();
        }

        void swap(my_priority_queue& __pq)noexcept(__and_<__is_nothrow_swappable<_Tp>,__is_nothrow_swappable<_Compare> >::value)
        {
            using std::swap;
            swap(c, __pq.c);
            swap(comp, __pq.comp);
        }
};

#endif __MY_PRIORITY_QUEUE_H__
