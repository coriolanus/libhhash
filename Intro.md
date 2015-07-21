# When Is It Appropriate #

This is an implementation of the Hopscotch hash tables in C, see http://en.wikipedia.org/wiki/Hopscotch_hashing. These hash tables use [open addressing](http://en.wikipedia.org/wiki/Hash_table#Open_addressing), and have the following advantages:
  1. Memory locality and compactness and thus cache efficiency.
  1. Serialization as the table is contained in the arrays _H_, hop info, and _V_, values.
  1. Concurrency by dividing the array into segments each with locks, though this has not been implemented here.

Hash tables with [open addressing](http://en.wikipedia.org/wiki/Hash_table#Open_addressing) only makes sense if your elements actually fit into the elements of the array. Here we use _unsigned integers_. If you have a 64-bit architecture you could substitute _uint_ with _ulong_. It might still be sensible to increase the size of the elements of the value array into twice of the size of elements of the hop info array. C99 standard provides a data type _long long_ which is 64-bits long even in 32-bit architectures. However, it should be noted that the memory usage in this case is worse than with a normal hash table with linked-list buckets if the table is less that 2/3 full.

It makes no sense to put references into this hash table. It would invalidate the point 1) above, and the point 2) becomes less clear as well. In fact, some of the advantage 3) is because of 2). Thus if your elements do not fit into _uint_ use normal hash tables with linked-list buckets. It will easier to implement and fast enough for you!

# On the Implementation #

The presented implementation uses the machine instructions clz, count-leading-zeros, and ctz, count-trailing-zeros, which are available in most modern architectures. In GCC they are provided as `__builtin_clz` and `__builtin__ctz`. The implementation here should be the cleanest and simplest in existence.


# References #

Herlihy, Maurice and Shavit, Nir and Tzafrir, Moran;
Hopscotch Hashing. DISC '08: Proceedings of the 22nd international
symposium on Distributed Computing. Arcachon, France:
Springer-Verlag, 2008. pp. 350--364.