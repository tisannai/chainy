# Chainy - Singly Linked List library

Chainy is a Singly Linked List type container library with emphasis
on efficiency and convenient usage. It provides a compact API with
basic operations. However, the API provides all that is needed.

List consists of nodes (Chainy Node, or simply Node) and each node
includes pointer to next node (except in last node) and user
data. User API does not expose the list structure explicitly, instead
list is accessed using list access object, namely Chainy.

Chainy contains Head and Link. Head is always pointing to the first
Node of the list, unless the list is empty. Link is a double pointer,
which points to a pointer that points to the Current node. Hence Link
accesses first the Next pointer of previous node to Current and then
follows that to return the Current node. When list has zero or one
node, Link points to head.

Typically list is filled sequentially and at each fill the
Current node is advanced. This way there is no need to search for
the list end starting from the list beginning at each addition.

Since Link is a double pointer, it provides the possibility to delete
the current and also to insert at the Current node efficiently. This
is required because in both cases the previous node must be updated.

Chainy reference is of type `ch_t`. Heap allocated and properly
initialized Chainy is returned by `ch_new()`. Stack allocated Chainy
is initialized with `ch_init()` function. Stack allocated variable
type is `ch_s` and `ch_t` is a pointer to that type.

Items are added to the list with `ch_add()`.

See Doxygen docs and `chainy.h` for details about Chainy API. Also
consult the test directory for usage examples.


## Chainy API documentation

See Doxygen documentation. Documentation can be created with:

    shell> doxygen .doxygen


## Examples

All functions and their use is visible in tests. Please refer `test`
directory for testcases.


## Building

Ceedling based flow is in use:

    shell> ceedling

Testing:

    shell> ceedling test:all

User defines can be placed into `project.yml`. Please refer to
Ceedling documentation for details.


## Ceedling

Chainy uses Ceedling for building and testing. Standard Ceedling files
are not in GIT. These can be added by executing:

    shell> ceedling new chainy

in the directory above Chainy. Ceedling prompts for file
overwrites. You should answer NO in order to use the customized files.
