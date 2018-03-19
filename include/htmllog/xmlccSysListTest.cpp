/** 
 * @file xmlccSysListTest.cpp
 * @author Christian Scheiblich
 *
 * DESCRIPTION
 *
 * XMLCC is an XML library written in C++ based on design patterns
 * for generating, searching, and parsing even malformed XML files.
 * Two Parsers are available: C++ SAX API for event based parsing and
 * a C++ DOM like Parser based on a document object model.
 * splendid time indeed ~8>
 * 
 * This file is part of XMLCC.
 * 
 * XMLCC Copyright (C) 2008-2012 Christian Scheiblich
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. 
 * You may obtain a copy of the License at 
 *  
 *     http://www.apache.org/licenses/LICENSE-2.0 
 *      
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. 
 * 
 */

#include "./xmlccSysList.h" // for throwing XMLCC::Error

/******************************************************************************/

#ifdef _XMLCC_USE_TEST_ // see xmlccInclDefs.h

/****************************************************************************/

namespace XMLCC {

namespace SYS {

/****************************************************************************/

#define _XMLCC_VERSION_SYS_List_Test_ 0.71 // 20100430 created this test

/*****************************************************************************
 * XMLCC::List<T> - template list for all kind of data types
 * remarks:
 * This cpp file is for testing the template implemented in xmlccList.h.
 * It is not necessary but checks for correct operation of XMLCC::List<T>.
 * Three examples are shown: for doubles, for objects, and for pointers.
 * Have fun ...
 ****************************************************************************/

namespace TEST {

/****************************************************************************/

struct // dummy for list test
Dummy {
  Dummy( void ) {
  } // Dummy
  ~Dummy( void ) {
  } // Dummy
  double _val;
}; // struct Dummy

/****************************************************************************/

void // global test function
testList( void ) {

  // /// //// DOUBLE //// /// //
  int ext = 1000;
  List<double>* list = new List<double>( ext );

  int size = 10 + 10 * ext;

  for( int d = 0; d < size; d++ ) // test add( )
    list->add( (double)( d + 1 ) );

  list->opt( ); // test opt( )

  double res = 0;

  size = list->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test get( )
    res = list->get( d );
    if( res != (double)( d + 1 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::add( ) - failed" );
  } // for d

  double* dArr = list->arr( ); // test arr ( );
  size = list->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test arr[ ]
    res = dArr[ d ];
    if( res != (double)( d + 1 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::arr( ) - failed" );
  } // for d
  delete [ ] dArr;

  size = list->size( ); // test size( )
  for( int d = 0; d < size; d++ )  // test set( )
    list->set( d, (double)( d + 2 ) );

  size = list->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test get( )
    res = list->get( d );
    if( res != (double)( d + 2 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::set( ) - failed" );
  } // for d
  
  size = list->size( ); // test size( )
  for( int d = 0; d < size; d++ )  // test set( )
    list->set( d, (double)( d + 1 ) );

  list->ins( 100, 23. ); // test ins( )
  int sizeIns = list->size( );
  if( sizeIns != size + 1 )
    throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - failed by size( )" );
  for( int d = 0; d < sizeIns; d++ ) {  // test get( )
    res = list->get( d );
    if( d == 100 )
      if( res != 23. )
        throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - failed by value" );
    if( d < 100 ) { 
      if( res != (double)( d + 1 ) ) {
        throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - failed before value" );
      } else if( d > 100 ) {
        if( res != (double)( d ) ) {
          throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - failed after value" );
        } // wrong result
      } // d > 100
    } // d < 100
  } // for d

  list->opt( 100 ); // test opt( ext )

  delete list;
  // /// //// DOUBLE //// /// //

/****************************************************************************/

  // /// //// DUMMY //// /// //
  ext = 1000;
  List<Dummy>* listDummy = new List<Dummy>( ext );

  size = 10 + 10 * ext;

  for( int d = 0; d < size; d++ ) {// test add( )
    Dummy dummy;
    dummy._val = (double)( d + 1 );
    listDummy->add( dummy );
  } // for d

  listDummy->opt( ); // test opt( )

  Dummy resDummy;

  size = listDummy->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test get( )
    resDummy = listDummy->get( d );
    if( resDummy._val != (double)( d + 1 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::add( ) - Dummy - failed" );
  } // for d

  Dummy* dummyArr = listDummy->arr( ); // test arr ( );
  size = listDummy->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test arr[ ]
    resDummy = dummyArr[ d ];
    if( resDummy._val != (double)( d + 1 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::arr( ) - Dummy - failed" );
  } // for d
  delete [ ] dummyArr;

  size = listDummy->size( ); // test size( )
  for( int d = 0; d < size; d++ ) { // test set( )
    resDummy = listDummy->get( d );
    resDummy._val = (double)( d + 2 );
    listDummy->set( d, resDummy );
  } // for d

  size = listDummy->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test get( )
    resDummy = listDummy->get( d );
    if( resDummy._val != (double)( d + 2 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::set( ) - Dummy - failed" );
  } // for d
  
  size = listDummy->size( ); // test size( )
  for( int d = 0; d < size; d++ ) { // test set( )
    resDummy = listDummy->get( d );
    resDummy._val = (double)( d + 1 );
    listDummy->set( d, resDummy );
  } // for d

  Dummy insDummy;
  insDummy._val = 0.;
  listDummy->ins( 100, insDummy ); // test ins( )
  sizeIns = listDummy->size( );
  if( sizeIns != size + 1 )
    throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - Dummy - failed by size( )" );
  for( int d = 0; d < sizeIns; d++ ) {  // test get( )
    resDummy = listDummy->get( d );
    if( d == 100 )
      if( resDummy._val != 0. )
        throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - Dummy - failed by value" );
    if( d < 100 ) {
      if( resDummy._val != (double)( d + 1 ) )
        throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - Dummy - failed before value" );
    } else if( d > 100 ) {
       if( resDummy._val != (double)( d ) )
          throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - Dummy - failed after value" );
    }
  } // for d

  listDummy->opt( 100 ); // test opt( ext )

  delete listDummy;
  // /// //// DUMMY //// /// //

/****************************************************************************/

  // /// //// DUMMY* //// /// //
  ext = 1000;
  List<Dummy*>* listDummyPtr = new List<Dummy*>( ext );

  size = 10 + 10 * ext;

  for( int d = 0; d < size; d++ ) {// test add( )
    Dummy* dummy = new Dummy( );
    dummy->_val = (double)( d + 1 );
    listDummyPtr->add( dummy );
  } // for d

  listDummyPtr->opt( ); // test opt( )

  Dummy* resDummyPtr;

  size = listDummyPtr->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test get( )
    resDummyPtr = listDummyPtr->get( d );
    if( resDummyPtr->_val != (double)( d + 1 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::add( ) - Dummy* - failed" );
  } // for d

  Dummy** dummyPtrArr = listDummyPtr->arr( ); // test arr ( );
  size = listDummyPtr->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test arr[ ]
    resDummyPtr = dummyPtrArr[ d ];
    if( resDummyPtr->_val != (double)( d + 1 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::arr( ) - Dummy* - failed" );
  } // for d
  delete [ ] dummyPtrArr;

  size = listDummyPtr->size( ); // test size( )
  for( int d = 0; d < size; d++ ) { // test set( )
    resDummyPtr = listDummyPtr->get( d );
    resDummyPtr->_val = (double)( d + 2 );
    listDummyPtr->set( d, resDummyPtr );
  } // for d

  size = listDummyPtr->size( ); // test size( )
  for( int d = 0; d < size; d++ ) {  // test get( )
    resDummyPtr = listDummyPtr->get( d );
    if( resDummyPtr->_val != (double)( d + 2 ) )
      throw ERR::Error( "XMLCC::TEST::List<T>::set( ) - Dummy* - failed" );
  } // for d
  
  size = listDummyPtr->size( ); // test size( )
  for( int d = 0; d < size; d++ ) { // test set( )
    resDummyPtr = listDummyPtr->get( d );
    resDummyPtr->_val = (double)( d + 1 );
    listDummyPtr->set( d, resDummyPtr );
  } // for d

  Dummy* insDummyPtr = new Dummy( );
  insDummyPtr->_val = 0.;
  listDummyPtr->ins( 100, insDummyPtr ); // test ins( )
  sizeIns = listDummyPtr->size( );
  if( sizeIns != size + 1 )
    throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - Dummy* - failed by size( )" );
  for( int d = 0; d < sizeIns; d++ ) {  // test get( )
    resDummyPtr = listDummyPtr->get( d );
    if( d == 100 )
      if( resDummyPtr->_val != 0. )
        throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - Dummy* - failed by value" );
    if( d < 100 ) {
      if( resDummyPtr->_val != (double)( d + 1 ) )
        throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - Dummy* - failed before value" );
    } else if( d > 100 ) {
      if( resDummyPtr->_val != (double)( d ) )
        throw ERR::Error( "XMLCC::TEST::List<T>::ins( ) - Dummy* - failed after value" );
    }
  } // for d

  listDummyPtr->opt( 100 ); // test opt( ext )

  size = listDummyPtr->size( ); // test size( )
  for( int d = 0; d < size; d++ ) // test get( )
    delete listDummyPtr->get( d ); // do not forget to delete
  delete listDummyPtr;
  // /// //// DUMMY* //// /// //

}; // testXMLCCList

/****************************************************************************/

} // namespace TEST

} // namespace SYS

} // namespace XMLCC

/****************************************************************************/

#endif // _XMLCC_USE_TEST_
