#ifndef BFS_ITERATOR_HPP
#define BFS_ITERATOR_HPP

#include "preorder_iterator.hpp"
#include <queue>

namespace vpr {

/**
 * @brief Type alias for Breadth-First Search (BFS) Traversal.
 * 
 * This type alias defines a tree traversal policy that uses a queue (FIFO) 
 * to perform breadth-first traversal, visiting nodes level by level. 
 * It employs the `StraightPush` functor to push children in straight order.
 * 
 * @tparam TreeType The type of the tree being traversed.
 * 
 * @details
 * BFS can be simplified using the `GeneralTraversal` template because both BFS 
 * and other traversals (e.g., Pre-order) share a common structure. They involve:
 *  - Visiting a node.
 *  - Pushing its children into a container.
 * 
 * The key differences lie in:
 *  - **ContainerType**: BFS uses a `queue` (FIFO) to ensure nodes are visited level-by-level, 
 *    whereas Pre-order traversal uses a `stack` (LIFO) to traverse depth-first.
 *  - **PushChildrenFunc**: BFS uses `StraightPush` to push children in natural left-to-right order. 
 *    In contrast, Pre-order might use `ReversePush` to control child processing order.
 * 
 * These differences are abstracted within the `GeneralTraversal` class, allowing flexible 
 * configuration for various traversal strategies, such as BFS or DFS, simply by changing 
 * the container type and push function.
 */
template <typename TreeType>
using BFSTraversal = GeneralTraversal<TreeType, std::queue<size_t>, StraightPush>;

//template <typename TreeType>
//using ReverseBFSTraversal = GeneralTraversal<TreeType, std::queue<size_t>, ReversePush>;

} // namespace vpr

#endif // BFS_ITERATOR_HPP
