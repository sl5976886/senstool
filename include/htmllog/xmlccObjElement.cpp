/** 
 * @file xmlccObjElement.cpp
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

#include <stdarg.h>
#include "./xmlccObjElement.h" // OBJ::Element
#include "./xmlccObjAttribute.h" // OBJ::Attribute
#include "./xmlccObjComment.h" // OBJ::Comment
#include "./xmlccObjCData.h" // OBJ::CData
#include "./xmlccObjValue.h" // OBJ::Value

/******************************************************************************/

namespace XMLCC {

namespace OBJ {

/******************************************************************************/

/// constructor
Element::Element( String tag ) 
       : Object( tag ) {
} // Element
  
/// constructor
Element::Element( String tag, 
                  String value ) 
       : Object( tag ) {
  addObject( new Value( value ) );
} // Element::Element

/******************************************************************************/

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0 ) 
       : Object( tag ) {
  addObject( obj0 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1 ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2 ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3 ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4 ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag,
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3, 
                  Object* obj4, Object* obj5 ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2,
                  Object* obj3, Object* obj4, Object* obj5, 
                  Object* obj6 ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2,
                  Object* obj3, Object* obj4, Object* obj5,
                  Object* obj6, Object* obj7 ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8 )
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9 ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB, 
                  Object* objC ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
  addObject( objC );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB, 
                  Object* objC, Object* objD ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
  addObject( objC );
  addObject( objD );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB, 
                  Object* objC, Object* objD, Object* objE ) 
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
  addObject( objC );
  addObject( objD );
  addObject( objE );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB, 
                  Object* objC, Object* objD, Object* objE, Object* objF )
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
  addObject( objC );
  addObject( objD );
  addObject( objE );
  addObject( objF );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB, 
                  Object* objC, Object* objD, Object* objE, Object* objF,
                  Object* objG )
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
  addObject( objC );
  addObject( objD );
  addObject( objE );
  addObject( objF );
  addObject( objG );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB, 
                  Object* objC, Object* objD, Object* objE, Object* objF,
                  Object* objG, Object* objH )
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
  addObject( objC );
  addObject( objD );
  addObject( objE );
  addObject( objF );
  addObject( objG );
  addObject( objH );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB, 
                  Object* objC, Object* objD, Object* objE, Object* objF,
                  Object* objG, Object* objH, Object* objI )
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
  addObject( objC );
  addObject( objD );
  addObject( objE );
  addObject( objF );
  addObject( objG );
  addObject( objH );
  addObject( objI );
} // Element::Element

/// COMPOSITE PATTERN
Element::Element( String tag, 
                  Object* obj0, Object* obj1, Object* obj2, Object* obj3,
                  Object* obj4, Object* obj5, Object* obj6, Object* obj7,
                  Object* obj8, Object* obj9, Object* objA, Object* objB, 
                  Object* objC, Object* objD, Object* objE, Object* objF,
                  Object* objG, Object* objH, Object* objI, Object* objJ )
       : Object( tag ) {
  addObject( obj0 );
  addObject( obj1 );
  addObject( obj2 );
  addObject( obj3 );
  addObject( obj4 );
  addObject( obj5 );
  addObject( obj6 );
  addObject( obj7 );
  addObject( obj8 );
  addObject( obj9 );
  addObject( objA );
  addObject( objB );
  addObject( objC );
  addObject( objD );
  addObject( objE );
  addObject( objF );
  addObject( objG );
  addObject( objH );
  addObject( objI );
  addObject( objJ );
} // Element::Element

/******************************************************************************/

/// COMPOSITE PATTERN for more than 20
Element::Element( String tag, int noOfObjects, Object* obj, ... ) 
       : Object( tag ) {

    addObject( obj );

    noOfObjects--; // due to that the first object is stored already

    va_list params = 0; 
    va_start( params, obj ); 

    Object* objNext = 0; 
    for( int o = 0; o < noOfObjects; o++ ) {
      
      objNext = va_arg( params, Object* );

      if( objNext != 0 )
          addObject( objNext );

    } // o
    
    va_end( params );

} // Element

/// COMPOSITE PATTERN for more than 20
Element::Element( String tag, String value, int noOfObjects, Object* obj, ... ) 
       : Object( tag ) {

    addObject( new Value( value ) );

    addObject( obj );

    noOfObjects--; // due to that the first object is stored already

    va_list params = 0; 
    va_start( params, obj ); 

    Object* objNext = 0; 
    for( int o = 0; o < noOfObjects; o++ ) {
      
      objNext = va_arg( params, Object* );

      if( objNext != 0 )
          addObject( objNext );

    } // o
    
    va_end( params );

} // Element
    
/******************************************************************************/

///// COMPOSITE PATTERN
//Element::Element( String tag, Object* obj, ... ) 
//       : Object( tag ) {
//
//    addObject( obj );
//
//    va_list params = 0; 
//    va_start( params, obj ); 
//
//    // TODO: NOT WORKING LIKE THIS??!
// 
//    Object* objNext = 0; 
//    while( *params != 0 ) {
//      
//      objNext = va_arg( params, Object* );
//
//      if( *params != 0 )
//          addObject( objNext );
//
//    } // while
//    
//    va_end( params );
//
//} // Element
//
///// COMPOSITE PATTERN
//Element::Element( String tag, String value, Object* obj, ... ) 
//       : Object( tag ) {
//
//    addObject( new Value( value ) );
//
//    addObject( obj );
//
//    va_list params = 0; 
//    va_start( params, obj ); 
//
//    // TODO: NOT WORKING LIKE THIS??!
// 
//    Object* objNext = 0; 
//    while( *params != 0 ) {
//      
//      objNext = va_arg( params, Object* );
//
//      if( *params != 0 )
//          addObject( objNext );
//
//    } // while
//    
//    va_end( params );
//
//} // Element
    
/******************************************************************************/

/// destructor
Element::~Element( void ) {
} // ~Element

/******************************************************************************/
  
String /// returns the stored tag of this element
Element::getTag( void ) {
  return getString( );
} // Element::getTag

void /// sets the tag of this element
Element::setTag( String tag ) {
  setString( tag );
} // Element::setTag

/******************************************************************************/

String /// returns the FIRST stored value of this element
Element::getValue( void ) {

  OBJ::Value* valueObj = 0;
  int noOfObjects = getNoOfObjects( );
  
  if( noOfObjects > 0 ) {
    
    int pos = 0;
    bool search = true;
    while( search ) {

      Object* sonObj = getObject( pos );

      if( dynamic_cast<OBJ::Value*>( sonObj ) != 0 ) {
        valueObj = (OBJ::Value*)sonObj;
        search = false;
      }

      if( pos + 1 == noOfObjects )
        search = false;

      pos++;
    } // search

  } // if is not standalone

  String value = "";

  if( valueObj != 0 )
    value = valueObj->getValue( );

  return value;

} // Element::getValue

/******************************************************************************/

String /// returns the FIRST stored value of this element
Element::getValue( int indx ) {

  OBJ::Value* valueObj = 0;
  int noOfObjects = getNoOfObjects( );
  
  if( noOfObjects > 0 ) {
    
    int pos = 0;
    int all = 0;
    bool search = true;
    while( search ) {

      Object* sonObj = getObject( indx );

      if( dynamic_cast<OBJ::Value*>( sonObj ) != 0 ) {
        valueObj = (OBJ::Value*)sonObj;
        pos++;
      }

      if( pos == indx )
        search = false;

      if( all + 1 == noOfObjects )
        search = false;

      all++;
    } // search

  } // if is not standalone

  String value = "";

  if( valueObj != 0 )
    value = valueObj->getValue( );

  return value;

} // Element::getValue

/******************************************************************************/

int /// sets the value of this element
Element::getNoOfValues( void ) {

  int noOfValues = 0;

  int noOfObjects = getNoOfObjects( );
  
  if( noOfObjects > 0 ) {
    
    int pos = 0;
    bool search = true;
    while( search ) {

      Object* sonObj = getObject( pos );

      if( dynamic_cast<OBJ::Value*>( sonObj ) != 0 )
        noOfValues++;

      if( pos + 1 == noOfObjects )
        search = false;

      pos++;
    } // search

  } // if is not standalone

  return noOfValues;

} // Element::getNoOfValues

/******************************************************************************/

void /// sets the value of this element
Element::addValue( String value ) {
  addObject( new OBJ::Value( value ) );
} // Element::addValue

/******************************************************************************/

std::ostream& /// std::ostream
operator << ( std::ostream& s, Element* obj ) {

  obj->doIndent( s );

  s << "<" 
    << obj->getTag( )
    << std::flush;

  int noOfObjects = obj->getNoOfObjects( );

  int countCData = 0;
  int countValues = 0;
  int countComments = 0;
  int countElements = 0;
  for( int o = 0; o < noOfObjects; o++ ) {

    Object* sonObj = obj->getObject( o );
    
    if( dynamic_cast<OBJ::Attribute*>( sonObj ) != 0 ) {
      
      Attribute* attribute = (Attribute*)sonObj;

      s << " "
        << attribute 
        << std::flush;

    } // if attribute

    if( dynamic_cast<OBJ::CData*>( sonObj ) != 0 )
      countCData++;

    if( dynamic_cast<OBJ::Value*>( sonObj ) != 0 )
      countValues++;

    if( dynamic_cast<OBJ::Comment*>( sonObj ) != 0 )
      countComments++;

    if( dynamic_cast<OBJ::Element*>( sonObj ) != 0 )
      countElements++;

  } // o

  String value = obj->getValue( );

  bool hasValue = false;
  if( value.compare( "" ) != 0 )
    hasValue = true;

  if( countElements == 0 
   && countComments == 0 
   && countCData == 0 ) {

    if( countValues == 0 ) {

      s << "/>"
        << std::endl
        << std::flush;

    } else if( countValues == 1 ) {

      s << ">"
        << std::flush;

      for( int o = 0; o < noOfObjects; o++ ) {

        Object* sonObj = obj->getObject( o );

        if( dynamic_cast<OBJ::Value*>( sonObj ) != 0 ) {

          OBJ::Value* valueObj = (OBJ::Value*)sonObj;

          valueObj->incIndent( obj );
 
          s << valueObj
            << std::flush;
         
          valueObj->decIndent( obj );

        } // if value

      } // for

      s << "</" 
        << obj->getTag( ) 
        << ">" 
        << std::endl
        << std::flush;

    } else {

      s << ">"
        << std::endl
        << std::flush;

      for( int o = 0; o < noOfObjects; o++ ) {

        Object* sonObj = obj->getObject( o );

        if( dynamic_cast<OBJ::Value*>( sonObj ) != 0 ) {

          OBJ::Value* valueObj = (OBJ::Value*)sonObj;

          valueObj->incIndent( obj );
   
          valueObj->doIndent( s );

          s << valueObj
            << std::endl
            << std::flush;
         
          valueObj->decIndent( obj );

        } // if value

      } // for

      obj->doIndent( s );

      s << "</" 
        << obj->getTag( ) 
        << ">" 
        << std::endl
        << std::flush;

    } // hasValue

  } else {

    s << ">"
      << std::endl
      << std::flush;

    for( int o = 0; o < noOfObjects; o++ ) {

      Object* sonObj = obj->getObject( o );
      
      if( dynamic_cast<OBJ::Element*>( sonObj ) != 0 ) {
        
        OBJ::Element* elementObj = (OBJ::Element*)sonObj;
          
        elementObj->incIndent( obj );

        s << elementObj
          << std::flush;

        elementObj->decIndent( obj );

      } // if element

      if( dynamic_cast<OBJ::Value*>( sonObj ) != 0 ) {
        
        OBJ::Value* valueObj = (OBJ::Value*)sonObj;

        valueObj->incIndent( obj );

        valueObj->doIndent( s );

        s << valueObj
          << std::endl
          << std::flush;

        valueObj->decIndent( obj );

      } // if value

      if( dynamic_cast<OBJ::Comment*>( sonObj ) != 0 ) {
        
        OBJ::Comment* commentObj = (OBJ::Comment*)sonObj;

        commentObj->incIndent( obj );

        s << commentObj
          << std::flush;

        commentObj->decIndent( obj );

      } // if comment

      if( dynamic_cast<OBJ::CData*>( sonObj ) != 0 ) {
        
        OBJ::CData* cdataObj = (OBJ::CData*)sonObj;

        cdataObj->incIndent( obj );

        s << cdataObj
          << std::flush;
        
        cdataObj->decIndent( obj );

      } // if cdata

    } // o

    obj->doIndent( s );

    s << "</" 
      << obj->getTag( ) 
      << ">" 
      << std::endl
      << std::flush;

  } // if has sub elements

  return s;

} // Object::operator <<

/******************************************************************************/

} // namespace OBJ

} // namespace XMLCC

/******************************************************************************/
