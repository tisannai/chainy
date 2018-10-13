/**
 * @file   test_basic.c
 * @author Tero Isannainen <tero.isannainen@gmail.com>
 * @date   Sun Oct  7 20:22:58 2018
 *
 * @brief  Test for Chainy.
 *
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "unity.h"
#include "chainy.h"



void gdb_break( void ) {}

int ch_cmp( void* a_u, void* b_u )
{
    int a;
    int b;

    a = *( (int*)a_u );
    b = *( (int*)b_u );

    if ( a > b ) {
        return 1;
    } else if ( a < b ) {
        return -1;
    } else {
        return 0;
    }
}


void ch_node_add_one( cn_t node, void* env )
{
    int* val;

    if ( env == NULL ) {
        val = node->data;
        *val = *val + 1;
    }
}




void test_create_and_destroy( void )
{
    ch_t      ch;
    cn_t      node;
    int       items[ 12 ];
    ch_size_t size;
    ch_bool_t truth;
    int* val;
    cn_t iter;

    ch = ch_new();

    for ( int i = 0; i < 12; i++ ) {
        items[ i ] = i;
    }


    /* Test some corner cases before adding any items to list. */

    truth = ch_is_empty( ch );
    TEST_ASSERT_EQUAL( ch_true, truth );

    node = ch_last( ch );
    TEST_ASSERT_EQUAL( node, NULL );
    ch_to_last( ch );
    TEST_ASSERT_EQUAL( ch->link, &ch->head );

    val = ch_data_return_and_to_next( ch->link );
    TEST_ASSERT_EQUAL( val, NULL );


    /* Fill list and start "normal" mode testing. */

    for ( int i = 0; i < 3; i++ ) {
        ch_add( ch, &( items[ i ] ) );
    }

    truth = ch_is_empty( ch );
    TEST_ASSERT_EQUAL( ch_false, truth );

    ch_to_first( ch );
    node = ch_last( ch );
    TEST_ASSERT_NOT_EQUAL( node, NULL );
    ch_to_last( ch );

    node = ch_first( ch );
    TEST_ASSERT_EQUAL( 0, *( (int*)node->data ) );
    node = ch_next( ch );
    TEST_ASSERT_EQUAL( node, NULL );
    node = ch_last( ch );
    TEST_ASSERT_EQUAL( 2, *( (int*)node->data ) );

    TEST_ASSERT_EQUAL( ch_false, ch_at_first( ch ) );
    ch_to_first( ch );
    TEST_ASSERT_EQUAL( 0, *( (int*)ch_data( ch ) ) );
    TEST_ASSERT_EQUAL( ch_true, ch_at_first( ch ) );
    ch_to_next( ch );
    TEST_ASSERT_EQUAL( 1, *( (int*)ch_data( ch ) ) );
    ch_to_next( ch );
    TEST_ASSERT_EQUAL( 2, *( (int*)ch_data( ch ) ) );
    node = ch_to_next( ch );
    TEST_ASSERT_EQUAL( 2, *( (int*)ch_data( ch ) ) );
    TEST_ASSERT_EQUAL( node, NULL );

    node = ch_current( ch );

    ch_to_first( ch );
    TEST_ASSERT_EQUAL( ch_false, ch_at_last( ch ) );
    ch_to_last( ch );
    TEST_ASSERT_EQUAL( ch_true, ch_at_last( ch ) );

    ch_each_with( ch, ch_node_add_one, NULL );

    iter = ch->head;
    ch_each( iter, val, int* )
    {
        *val = *val - 1;
    }

    ch_bool_t ret;

    size = ch_length( ch );
    TEST_ASSERT_EQUAL( 3, size );

    ret = ch_remove( ch, &items[ 1 ] );
    TEST_ASSERT( ret == ch_true );

    size = ch_length( ch );
    TEST_ASSERT_EQUAL( 2, size );

    ret = ch_remove( ch, &items[ 10 ] );
    TEST_ASSERT( ret == ch_false );

    ch_to_first( ch );
    ch_add( ch, &( items[ 1 ] ) );

    ch_to_last( ch );
    ch_set_link( ch, &ch->head );
    TEST_ASSERT_EQUAL( ch_true, ch_at_first( ch ) );

    cn_p node_ref;
    node_ref = ch_find( ch, ch_cmp, &items[ 10 ] );
    TEST_ASSERT_EQUAL( node_ref, NULL );

    node_ref = ch_find( ch, ch_cmp, &items[ 2 ] );
    ch_set_link( ch, node_ref );
    TEST_ASSERT_EQUAL( ch_true, ch_at_last( ch ) );

    ch_destroy( ch );
}
