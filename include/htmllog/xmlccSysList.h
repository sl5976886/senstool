/** 
 * @file xmlccSysList.h
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

/******************************************************************************/

#ifndef __xmlccSysList_h__
#define __xmlccSysList_h__

#include <math.h> // floor( )
#include "./xmlccErrError.h" // for throwing XMLCC::Error
#include "./xmlccErrFailure.h" // for throwing XMLCC::Failure

/******************************************************************************/

namespace XMLCC {

namespace SYS {

// DEFINES TO MARK EXTERNAL List<T> VERSION AND DATE
// #define _VERSION_TYPES_List_   0.47 // 20100803
// #define _DATE_TYPES_List_      20100803
// #define _DEBUG_TYPES_List_

#define _XMLCC_VERSION_SYS_List_ 0.71 // 20100430
#define _XMLCC_DEBUG_SYS_List_

/******************************************************************************/

#ifdef _XMLCC_USE_TEST_ // see xmlccInclDefs.h

namespace TEST {

  void testList( void ); // global test function

} // namespace Test

#endif // _XMLCC_USE_TEST_

/*****************************************************************************
 * XMLCC::List<T> - template list for all kind of data types
 * remarks:
 * You can use this list for any kind of data; numbers, objects, pointers ...
 * It is not allocating memory until the first data is added using the
 * add( T data ) function. The allocated memory depends on the given
 * extension size, manifested by the member _ext. You can use the overloaded
 * constructor to manipulated this member from the start on. To get data, use
 * get( pos ) or the arr( void ) handing back an array of the added data.
 * In second case, do not forget to delete the array by delete [ ] dataArr
 * outside. Have fun ...
 ****************************************************************************/

template<class T> 
class List { // use this to add any data in an array
 public: // public functions

  List( void ); /// constructor
  List( int ext ); /// give the allocate memory size
  List( int ext, int div ); /// allocated memory size and divisor for speed up
  virtual ~List( void ); /// destructor; virtual 2 be calles when heritating

  int  size( void ); /// return the size of the list
  void add( T data ); /// add a new data in the first free position
  void set( int pos, T data ); /// set data to position pos
  void ins( int pos, T data ); /// insert data to position pos
  T    get( int pos ); /// return a copy of the data at position pos
  T*   arr( void ); /// copies the list to an array and returns a pointer
  void par( void ); /// optimizes the memory extension parameters 
  void opt( void ); /// optimizes the memory for added data
  void opt( int ext ); /// optimizes mem for added data by given extension

  // T     operator  [ ]   ( int n ) const; /// operator overloading

 private: // private functions and members

  void ext( int ext ); /// extend the allocated memory
  void shr( int pos ); /// shrink the memory to a new size

  T*  _data; /// array for data 2 be added, will be extended automatically
  int _pos;  /// next position in allocated memory 4 sotring data 2 _data arr
  int _ext;  /// extension size for next memory allocation to extend _data arr
  int _div;  /// divisor for calculating self allocating memory size
  int _size; /// current size of allocated memory for array _data

  typedef ERR::Exception ListError; /// namespace typedef

}; // List<T>

/****************************************************************************/

template<class T>
List<T>::List( ) {

	_ext  = 3; // memory optimzed
	_pos  = 0;
  _div  = 4;
	_size = 0;
  _data = 0;

} // List<T>::List

/****************************************************************************/

template<class T>
List<T>::List( int ext ) {

	if( ext < 1 )
    ext = 1; // 20081206 fix user failure instead of exception

	_ext  = ext;
	_pos  = 0;
  _div  = 4;
	_size = 0;
  _data = 0;

} // List<T>::List

/****************************************************************************/

template<class T>
List<T>::List( int ext, int div ) {

	if( ext < 1 )
    ext = 1; // 20081206 fix user failure instead of exception

	if( div < 1 )
    div = 1; // 20100803 only use a qualified divisor

  if( div > 10 ) // 20100803 do not allow a divisor > 10; does not make sense
    div = 10;

	_ext  = ext;
	_pos  = 0;
  _div  = div;
	_size = 0;
  _data = 0;

} // List<T>::List

/****************************************************************************/

template<class T>
List<T>::~List( void ) {

	delete [ ] _data;

} // List<T>::~List

/****************************************************************************/

template<class T> int
List<T>::size( void ) { 

	return _pos; 

} // List<T>::size

/****************************************************************************/

template<class T> void
List<T>::add( T data ) {

	if( _pos == _size )
		ext( _ext );

	_data[ _pos ] = data;
	_pos++;

} // List<T>::add

/****************************************************************************/

template<class T> void
List<T>::set( int pos, T data ) {

  if( pos < 0 )
    throw ListError( "List<T>::set - pos is < than zero" );

  if( pos >= _pos ) {

		ext( pos - _pos + 1 ); // extend 2 requested set position
    _pos = _size;

  } // hard copy it

  _data[ pos ] = data;

} // List<T>::set

/****************************************************************************/

template<class T> void
List<T>::ins( int pos, T data ) {

  if( pos >= _pos )
    throw ListError( "List<T>::ins - pos is >= than size of list" );

  if( pos < 0 )
    throw ListError( "List<T>::ins - pos is < than zero" );

  if( _pos == _size )
		ext( _ext );

  for( int i = _pos; i > pos; i-- )
    _data[ i ] = _data[ i - 1 ];

  _data[ pos ] = data;
  _pos++;

} // List<T>::ins

/****************************************************************************/

template<class T> T
List<T>::get( int pos ) {

	if( _pos == 0 )
		throw ListError( "List<T>::get - not data set yet; data array is empty" );

  if( pos >= _pos )
    throw ListError( "List<T>::get - pos >= than size of list" );

  if( pos < 0 )
    throw ListError( "List<T>::get - pos < than zero" );

	T data = _data[ pos ];

	return data;

} // List<T>::get

/****************************************************************************/

template<class T> T* 
List<T>::arr( void ) {

  if( _pos <= 0 )
    return 0; // do not throw an error here

	T* arr = new T[ _pos ];

	for( int i = 0; i < _pos; i++ )
		arr[ i ] = _data[ i ];

	return arr;  // do not forget to do: delete [ ] arr

} // List<T>::arr

/****************************************************************************/

template<class T> void
List<T>::par( void ) {

 int ext = (int)(floor( (double)(_size) / (double)(_div) )); // extension size

 if( ext > _ext ) // as long as ext is greater than set _ext; speed up faster
   _ext = ext;

} // List<T>::par

/****************************************************************************/

template<class T> void
List<T>::opt( void ) {

	if( _size > _pos ) {

		shr( _pos );

    par( );

	} // if

} // List<T>::opt

/****************************************************************************/

template<class T> void
List<T>::opt( int ext ) {

  if( _size > _pos ) 
		shr( _pos );

	if( ext < 1 )
		ext = 1;

	_ext = ext; // take user's extensions size

} // List<T>::opt

/****************************************************************************/

template<class T> void
List<T>::ext( int ext ) {

	T* tmp = 0;

	if( _size != 0 ) { // data 2 tmp

		tmp = new T[ _size ];

		for( int i = 0; i < _size; i++ )
			tmp[ i ] = _data[ i ];

		delete [ ] _data;

	} // if

	int newSize = _size + ext;

	_data = new T[ newSize ];

	if( _size != 0 ) { // tmp 2 data

		for( int i = 0; i < _size; i++ )
			_data[ i ] = tmp[ i ];

		delete [ ] tmp;

	} // if

	_size = newSize; // set new size

  par( ); // calculate next extenstion size

} // List<T>::ext

/****************************************************************************/

template<class T> void
List<T>::shr( int pos ) { // shrink to size of pos

  if( pos > _size )
    throw ListError( "List<T>::shr - pos is > than size of list" );

  if( pos < 0 )
    throw ListError( "List<T>::shr - pos is < than zero" );

  if( pos > 0 ) {

	  T* tmp = new T[ pos ];

	  for( int i = 0; i < pos; i++ )
		  tmp[ i ] = _data[ i ]; // data 2 tmp

	  delete [ ] _data;

	  _data = new T[ pos ];

	  for( int i = 0; i < pos; i++ )
		  _data[ i ] = tmp[ i ]; // tmp 2 data

	  delete [ ] tmp;

    _size = pos;

  } // if

} // List<T>::shr

/****************************************************************************/

//template<class T> T  /// operator overloading
//List<T>::operator [ ] ( int n ) const {
//  return this->get( n ); 
//} // List<T>::operator [ ]

/****************************************************************************/

} // namespace SYS

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccSysList_h__

/******************************************************************************/
