#ifndef CHAINY_H
#define CHAINY_H


/**
 * @file   chainy.h
 *
 * @author Tero Isannainen <tero.isannainen@gmail.com>
 * @date   Sun Oct  7 20:22:58 2018
 *
 * @brief  Chainy - Singly Linked List library
 *
 */


/** Chainy library version. */
extern const char* chainy_version;


/* ------------------------------------------------------------
 * Type definitions:
 * ------------------------------------------------------------ */


typedef void* ch_d;
typedef enum
{
    ch_false = 0,
    ch_true = 1
} ch_bool_t;
typedef size_t ch_size_t;

/**
 * Chainy node.
 */
struct cn_struct_s
{
    struct cn_struct_s* next; /**< Following node. */
    ch_d                data; /**< Node data. */
};
typedef struct cn_struct_s cn_s; /**< Node struct. */
typedef cn_s*              cn_t; /**< Node. */
typedef cn_t*              cn_p; /**< Node reference. */


/**
 * Chainy cursor.
 */
struct ch_struct_s
{
    cn_t  head; /**< List head node. */
    cn_t* link; /**< List link (state). */
};
typedef struct ch_struct_s ch_s; /**< Cursor struct. */
typedef ch_s*              ch_t; /**< Cursor. */
typedef ch_t*              ch_p; /**< Cursor reference. */




#ifdef CHAINY_MEM_API

/*
 * CHAINY_MEM_API allows to use custom memory allocation functions,
 * instead of the default: ch_malloc, ch_free, ch_realloc.
 *
 * If CHAINY_MEM_API is used, the user must provide implementation for the
 * below functions and they must be compatible with malloc etc.
 */

extern void* ch_malloc( size_t size );
extern void  ch_free( void* ptr );
extern void* ch_realloc( void* ptr, size_t size );

#else

/* Default to common memory management functions. */

/** Reserve memory. */
#define ch_malloc malloc

/** Release memory. */
#define ch_free free

/** Re-reserve memory. */
#define ch_realloc realloc

#endif


/**
 * Chainy node iterator:
 *
 * * node  : Node reference (cn_p).
 * * item  : Item variable
 * * cast  : Item variable type
 *
 */
#define ch_each( node, item, cast ) \
    for ( item = ( cast )( node )->data; node; item = (cast)ch_data_return_and_to_next( &node ) )


/**
 * Chainy data compare.
 *
 * * Return  1 if a is greater than b.
 * * Return  0 on match.
 * * Return -1 if a is smaller than b.
 */
typedef int ( *ch_cmp_f )( void* a, void* b );


/**
 * Chainy action type function pointer.
 *
 * * node  : Node reference.
 * * env   : User env.
 */
typedef void ( *ch_node_f )( cn_t node, void* env );



/* ------------------------------------------------------------
 * Linked list:
 * ------------------------------------------------------------ */


/**
 * Create new Chainy.
 *
 * Initialize Chainy to empty.
 *
 * @return Chainy.
 */
ch_t ch_new( void );


/**
 * Initialize Chainy.
 *
 * @param c Chainy.
 */
void ch_init( ch_t c );


/**
 * Destroy list content
 *
 * @param c Chainy.
 */
void ch_destroy_list( ch_t c );


/**
 * Destroy list content and Chainy.
 *
 * @param c Chainy.
 *
 * @return NULL
 */
ch_t ch_destroy( ch_t c );


/**
 * Add data node to Chainy.
 *
 * Append to current.
 *
 * @param c    Chainy.
 * @param data Data to add.
 */
void ch_add( ch_t c, ch_d data );


/**
 * Remove current node.
 *
 * @param c Chainy.
 *
 * @return True unless empty.
 */
ch_bool_t ch_remove( ch_t c, ch_d data );


/**
 * Return next node.
 *
 * @param c Chainy.
 *
 * @return Node.
 */
cn_t ch_next( ch_t c );


/**
 * Jump to next node (if exists).
 *
 * @param c Chainy.
 *
 * @return Next node (or NULL).
 */
cn_t ch_to_next( ch_t c );


/**
 * Return first node.
 *
 * @param c Chainy.
 *
 * @return Node.
 */
cn_t ch_first( ch_t c );


/**
 * Jump to first node.
 *
 * @param c Chainy.
 *
 * @return True if jumped.
 */
cn_t ch_to_first( ch_t c );


/**
 * At first node?
 *
 * @param c Chainy.
 *
 * @return True if at first.
 */
ch_bool_t ch_at_first( ch_t c );


/**
 * Return last node.
 *
 * @param c Chainy.
 *
 * @return Node.
 */
cn_t ch_last( ch_t c );


/**
 * Jump to last node.
 *
 * @param c Chainy.
 *
 * @return True if jumped.
 */
cn_t ch_to_last( ch_t c );


/**
 * At last node?
 *
 * @param c Chainy.
 *
 * @return Truen if at last.
 */
ch_bool_t ch_at_last( ch_t c );


/**
 * Set link to node.
 *
 * @param c    Chainy.
 * @param node Node to reference.
 */
void ch_set_link( ch_t c, cn_p node );


/**
 * Find data using compare function.
 *
 * @param c    Chainy.
 * @param comp Compare function.
 * @param data Data to find.
 *
 * @return Node for data (or NULL).
 */
cn_p ch_find( ch_t c, ch_cmp_f comp, ch_d data );


/**
 * Return length of Chainy.
 *
 * @param c Chainy.
 *
 * @return Length.
 */
ch_size_t ch_length( ch_t c );


/**
 * Is Chainy empty?
 *
 * @param c Chainy.
 *
 * @return True if empty.
 */
ch_bool_t ch_is_empty( ch_t c );


/**
 * Return current node.
 *
 * @param c Chainy.
 *
 * @return Node.
 */
cn_t ch_current( ch_t c );


/**
 * Return current data.
 *
 * @param c Chainy.
 *
 * @return Data.
 */
ch_d ch_data( ch_t c );


/**
 * Iterate over list.
 *
 * @param c   Chainy.
 * @param fn  Node function (user).
 * @param env User env for function (2nd arg).
 */
void ch_each_with( ch_t c, ch_node_f fn, void* env );


/**
 * Advance node reference to next node and return data if available.
 *
 * This function is used by the "ch_each" macro.
 *
 * @param node_ref Node reference.
 *
 * @return Data of next node (if any).
 */
ch_d ch_data_return_and_to_next( cn_p node_ref );


#endif
