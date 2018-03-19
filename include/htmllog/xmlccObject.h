/** 
 * @file xmlccObject.h
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

#ifndef __xmlccObject_h__
#define __xmlccObject_h__

/******************************************************************************/

#include "./xmlccSysList.h" // 2 add objects
#include "./xmlccSysStringTool.h" // manipulate strings

/******************************************************************************/

namespace XMLCC {

/******************************************************************************/

#define _XMLCC_VERSION_Object_ 0.71 // 20100430
#define _XMLCC_DEBUG_Object_

/******************************************************************************/

namespace OBJ {
  
  class Root;
  class Header;
  class Doctype;
  class Comment;
  class CData;
  class Element;
  class Attribute;
  class Value;

} // namespace OBJ

/******************************************************************************/

class /// Composite Pattern Base class
Object {
// Object : protected SYS::List< Object* > {

 protected:

  Object( String tag ); /// constructor

 public:

  virtual ~Object( void ); /// destructor

  void   setString( String string ); /// set string for an object
  String getString( void ); /// get string of an object

  void addObject( Object* object ); /// push object back 2 list

  int      getNoOfObjects( void ); /// get no of objects
  Object*  getObject( int no ); /// get object of internal no
  Object** getObjects( void ); /// get all objects as an array; delete the array

  int  getIndent( void ); /// get indention for std::ostream
  void setIndent( Object* obj ); /// set indention for std::ostream
  void incIndent( Object* obj ); /// increase indention
  void decIndent( Object* obj ); /// decrease indention
  void doIndent( std::ostream& s ); /// add indention to ostream

  friend std::ostream& operator << ( std::ostream& s, Object* obj ); /// std::cout
  friend std::ostream& operator << ( std::ostream& s, int indention ); /// std::cout

 protected:

  String _string; /// name of the current XMLCC object
  SYS::List< Object* >* _listOfObjects; /// list of current added objects
  int _indent; /// indention for ostream; number of leading whitespaces
  int _indentSize; /// set the number of whitespaces for each indention

}; // class Object

/******************************************************************************/

typedef SYS::List< Object* >   ListObjects; // template typedef
typedef SYS::List< String >    ListStrings; // template typedef

/******************************************************************************/

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccObject_h__
