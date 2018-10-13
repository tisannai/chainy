/**
 * @file   chainy.c
 * @author Tero Isannainen <tero.isannainen@gmail.com>
 * @date   Sun Oct  7 20:22:58 2018
 *
 * @brief  Singly linked list library.
 *
 */


#include <sixten.h>
#include "chainy.h"


#define cur( c ) ( *c->link )


const char* ch_version = "0.0.1";


static cn_t cn_new( ch_d data )
{
    cn_t node;

    node = ch_malloc( sizeof( cn_t ) );
    node->next = NULL;
    node->data = data;

    return node;
}

static cn_t cn_del( cn_t node )
{
    ch_free( node );
    return NULL;
}


/* ------------------------------------------------------------
 * Linked list:
 * ------------------------------------------------------------ */

ch_t ch_new( void )
{
    ch_t c;

    c = ch_malloc( sizeof( ch_s ) );
    ch_init( c );

    return c;
}


void ch_init( ch_t c )
{
    c->head = NULL;
    c->link = &c->head;
}


void ch_destroy_list( ch_t c )
{
    cn_t node;

    node = c->head;

    while ( node ) {
        c->head = node->next;
        cn_del( node );
        node = c->head;
    }

    ch_init( c );
}


ch_t ch_destroy( ch_t c )
{
    ch_destroy_list( c );
    ch_free( c );
    return NULL;
}


void ch_add( ch_t c, ch_d data )
{
    cn_t node;

    node = cn_new( data );

    if ( c->head == NULL ) {
        /* First entry. */
        c->head = node;
        // c->link = &node->next;
    } else if ( cur( c )->next == NULL ) {
        /* Add to end. */
        cur( c )->next = node;
        c->link = &( cur( c )->next );
    } else {
        /* Insert. */
        cn_t next;
        next = cur( c )->next;
        cur( c ) = node;
        c->link = &( cur( c )->next );
        node->next = next;
    }
}


ch_bool_t ch_remove( ch_t c, ch_d data )
{
    cn_p      prev;
    cn_t      node;
    ch_bool_t ret;

    prev = &c->head;
    node = c->head;
    ret = ch_false;

    while ( node ) {
        if ( node->data == data ) {
            if ( c->link == &( node->next ) )
                c->link = prev;
            *prev = node->next;
            ch_free( node );
            node = *prev;
            ret = ch_true;
        } else {
            prev = &node->next;
            node = node->next;
        }
    }

    return ret;
}


cn_t ch_next( ch_t c )
{
    return cur( c )->next;
}


cn_t ch_to_next( ch_t c )
{
    if ( cur( c )->next ) {
        c->link = &( cur( c )->next );
        return cur( c );
    } else {
        return NULL;
    }
}


cn_t ch_first( ch_t c )
{
    return c->head;
}


cn_t ch_to_first( ch_t c )
{
    c->link = &c->head;
    return cur( c );
}


ch_bool_t ch_at_first( ch_t c )
{
    if ( cur( c ) == c->head )
        return ch_true;
    else
        return ch_false;
}


cn_t ch_last( ch_t c )
{
    cn_t node = cur( c );

    if ( node == NULL )
        return NULL;

    while ( node->next != NULL )
        node = node->next;

    return node;
}


cn_t ch_to_last( ch_t c )
{
    if ( c->head ) {

        cn_p prev;
        cn_t node;

        prev = c->link;
        node = cur(c);

        while ( node->next ) {
            prev = &node->next;
            node = node->next;
        }

        c->link = prev;

        return cur( c );

    } else {

        return NULL;
    }
}


ch_bool_t ch_at_last( ch_t c )
{
    if ( cur( c )->next == NULL )
        return ch_true;
    else
        return ch_false;
}


void ch_set_link( ch_t c, cn_p node )
{
    c->link = node;
}


cn_p ch_find( ch_t c, ch_cmp_f comp, ch_d data )
{
    cn_p prev;
    cn_t node;

    prev = &c->head;
    node = c->head;

    while ( node ) {
        if ( comp( node->data, data ) == 0 ) {
            return prev;
        } else {
            prev = &node->next;
            node = node->next;
        }
    }

    return NULL;
}


ch_size_t ch_length( ch_t c )
{
    cn_t      node;
    ch_size_t len = 0;

    node = c->head;

    while ( node ) {
        node = node->next;
        len++;
    }

    return len;
}


ch_bool_t ch_is_empty( ch_t c )
{
    if ( c->head == NULL ) {
        return ch_true;
    } else {
        return ch_false;
    }
}


cn_t ch_current( ch_t c )
{
    return cur( c );
}


ch_d ch_data( ch_t c )
{
    return ( *c->link )->data;
}


void ch_each_with( ch_t c, ch_node_f fn, void* env )
{
    cn_t node;

    node = c->head;
    while ( node ) {
        fn( node, env );
        node = node->next;
    }
}


ch_d ch_data_return_and_to_next( cn_p node_ref )
{
    ch_d ret;

    if ( *node_ref ) {
        ret = ( *node_ref )->data;
        *node_ref = ( *node_ref )->next;
        return ret;
    } else {
        return NULL;
    }
}
