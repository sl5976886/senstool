/** 
 * @file xmlccDomGrabber.cpp
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

#include "./xmlccDomGrabber.h" // header

/******************************************************************************/

namespace XMLCC {

namespace DOM {

/******************************************************************************/

/// constructor
Grabber::Grabber( void ) {
} // Grabber

/// destructor
Grabber::~Grabber( void ) {
} // ~Grabber

/******************************************************************************/

String /// returns a string keeping FIRST value 4 this object
Grabber::getValue4Object( Object* object ) {

  String value( "" );

  int noOfValues = 0;
  Object** valuesList = 0;
  sort2Values( noOfValues, valuesList, object );

  if( noOfValues > 0 )
    value = valuesList[ 0 ]->getString( );

  delete [ ] valuesList;

  return value;

} // Grabber::getValue4Object

ListStrings* /// returns a list keeping strings for all set values 4 this object
Grabber::getValues4Object( Object* object ) {

  ListStrings* values = new ListStrings( 3 );

  int noOfValues = 0;
  Object** valuesList = 0;
  sort2Values( noOfValues, valuesList, object );

  if( noOfValues > 0 )
    for( int v = 0; v < noOfValues; v++ )
      values->add( valuesList[ v ]->getString( ) );

  delete [ ] valuesList;

  return values;

} // Grabber::getValue4Object

/******************************************************************************/

String /// returns a string keeping label 4 FIRST attribute 4 this object
Grabber::getAttributeName4Object( Object* object ) {

  String attributeName( "" );

  int noOfAttribute = 0;
  Object** attributesList = 0;
  sort2Attributes( noOfAttribute, attributesList, object );

  if( noOfAttribute > 0 )
    attributeName = attributesList[ 0 ]->getString( );

  delete [ ] attributesList;

  return attributeName;

} // Grabber::getAttributeName4Object

ListStrings* /// returns a list keeping values 4 for all set attributes
Grabber::getAttributeNames4Object( Object* object ) {

  ListStrings* attributeNames = new ListStrings( 3 );

  int noOfAttribute = 0;
  Object** attributesList = 0;
  sort2Attributes( noOfAttribute, attributesList, object );

  if( noOfAttribute > 0 )
    for( int v = 0; v < noOfAttribute; v++ )
      attributeNames->add( attributesList[ v ]->getString( ) );

  delete [ ] attributesList;

  return attributeNames;
} // Grabber::getAttributeNames4Object

String /// returns a string keeping label 4 FIRST attribute 4 this object
Grabber::getAttributeValue4Object( Object* object ) {

  String attributeValue( "" );

  int noOfAttribute = 0;
  Object** attributesList = 0;
  sort2Attributes( noOfAttribute, attributesList, object );

  if( noOfAttribute > 0 ) {

    Object* oAttributeValue = 0;

    try {

      oAttributeValue = attributesList[ 0 ]->getObject( 0 );

      if( oAttributeValue != 0 )
        attributeValue = oAttributeValue->getString( );

    } catch( ERR::Exception e ) {
      // do nothing here if no value object is attached
    } // try

  } // if

  delete [ ] attributesList;

  return attributeValue;

} // Grabber::getAttributeValue4Object

ListStrings* /// returns a list keeping values 4 for all set attributes
Grabber::getAttributeValues4Object( Object* object ) {

  ListStrings* attributeValues = new ListStrings( 3 );

  int noOfAttribute = 0;
  Object** attributesList = 0;
  sort2Attributes( noOfAttribute, attributesList, object );

  if( noOfAttribute > 0 )
    for( int v = 0; v < noOfAttribute; v++ ) {

      Object* oAttributeValue = 0;

      try {

        oAttributeValue = attributesList[ v ]->getObject( 0 );

        if( oAttributeValue != 0 )
          attributeValues->add( oAttributeValue->getString( ) );

      } catch( ERR::Exception e ) {
        // do nothing here if no value object is attached
      } // try

    } // v

  delete [ ] attributesList;

  return attributeValues;

} // Grabber::getAttributeValues4Object

/******************************************************************************/

String /// pass OBJ::Element and attribute name, receive value or an exception
Grabber::tryAttributeName4Object( Object* object, String attributeName ) {

  String attributeValue = "";

  ListStrings* attributeNames4Object = getAttributeNames4Object( object );

  int noOfAttributeNames = attributeNames4Object->size( );

  int position = -1;

  for( int a = 0; a < noOfAttributeNames; a++ )
    if( attributeName.compare( attributeNames4Object->get( a ) ) == 0 )
      position = a;

  delete attributeNames4Object;

  if( position > -1 ) {

    ListStrings* attributeValues4Object = getAttributeValues4Object( object );

    attributeValue = attributeValues4Object->get( position );

    delete attributeValues4Object;

  } else {
    throw ERR::Failure( "Grabber::tryAttributeName4Object - no attribute found for passsed attribute name" );
  } // if

  return attributeValue;

} // Grabber::tryAttributeName4Object

/******************************************************************************/

String /// returns a string keeping FIRST comment 4 this object
Grabber::getComment4Object( Object* object ) {
  
  String comment( "" );

  int noOfComments = 0;
  Object** commentsList = 0;
  sort2Comments( noOfComments, commentsList, object );

  if( noOfComments > 0 )
    comment = commentsList[ 0 ]->getString( );

  delete [ ] commentsList;

  return comment;

} // Grabber::getComment4Object

ListStrings* /// returns a list keeping strings for all set comments 4 this object
Grabber::getComments4Object( Object* object ) {

  ListStrings* comments = new ListStrings( 3 );
  
  int noOfComments = 0;
  Object** commentsList = 0;
  sort2Comments( noOfComments, commentsList, object );

  if( noOfComments > 0 )
    for( int v = 0; v < noOfComments; v++ )
      comments->add( commentsList[ v ]->getString( ) );

  delete [ ] commentsList;

  return comments;

} // Grabber::getComments4Object

/******************************************************************************/

bool /// return true if object is of type Element
Grabber::check4Root( Object* object ) {

  if( dynamic_cast<OBJ::Root*>( object ) != 0 )
    return true;

  return false;

} // Grabber::check4Element

bool /// return true if object is of type Element
Grabber::check4Header( Object* object ) {

  if( dynamic_cast<OBJ::Header*>( object ) != 0 )
    return true;

  return false;

} // Grabber::check4Element

bool /// return true if object is of type Element
Grabber::check4Element( Object* object ) {

  if( dynamic_cast<OBJ::Element*>( object ) != 0 )
    return true;

  return false;

} // Grabber::check4Element

bool /// return true if object is of type Attribute
Grabber::check4Attribute( Object* object ) {

  if( dynamic_cast<OBJ::Attribute*>( object ) != 0 )
    return true;

  return false;

} // Grabber::check4Attribute

bool /// return true if object is of type Value
Grabber::check4Value( Object* object ) {

  if( dynamic_cast<OBJ::Value*>( object ) != 0 )
    return true;

  return false;

} // Grabber::check4Value

bool /// return true if object is of type CDATA
Grabber::check4CData( Object* object ) {

  if( dynamic_cast<OBJ::CData*>( object ) != 0 )
    return true;

  return false;

} // Grabber::check4CData

bool /// return true if object is of type Comment
Grabber::check4Comment( Object* object ) {

  if( dynamic_cast<OBJ::Comment*>( object ) != 0 )
    return true;

  return false;

} // Grabber::check4Comment

/******************************************************************************/

int /// get number of headers added at an object
Grabber::getNoOfHeaders( Object* object ) {

  int noOfHits = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::getNoOfHeaders - no object given" );

  for( int o = 0; o < object->getNoOfObjects( ); o++ )
    if( check4Header( object->getObject( o ) ) )
      noOfHits++;

  return noOfHits;

} // Grabber::getNoOfHeaders

int /// get number of meta data added at an object
Grabber::getNoOfCData( Object* object ) {

  int noOfHits = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::getNoOfCDataData - no object given" );

  for( int o = 0; o < object->getNoOfObjects( ); o++ )
    if( check4CData( object->getObject( o ) ) )
      noOfHits++;

  return noOfHits;

} // Grabber::getNoOfCData

int /// get number of attributes added at an object
Grabber::getNoOfAttributes( Object* object ) {

  int noOfHits = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::getNoOfAttributes - no object given" );

  for( int o = 0; o < object->getNoOfObjects( ); o++ )
    if( check4Attribute( object->getObject( o ) ) )
      noOfHits++;

  return noOfHits;

} // Grabber::getNoOfAttributes

int /// get number of values added at an object
Grabber::getNoOfValues( Object* object ) {

  int noOfHits = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::getNoOfValues - no object given" );

  for( int o = 0; o < object->getNoOfObjects( ); o++ )
    if( check4Value( object->getObject( o ) ) )
      noOfHits++;

  return noOfHits;

} // Grabber::getNoOfValues

int /// get number of elements added at an object
Grabber::getNoOfElements( Object* object ) {

  int noOfHits = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::getNoOfElements - no object given" );

  for( int o = 0; o < object->getNoOfObjects( ); o++ )
    if( check4Element( object->getObject( o ) ) )
      noOfHits++;

  return noOfHits;

} // Grabber::getnoOfElements

int /// get number of comments added at an object
Grabber::getNoOfComments( Object* object ) {

  int noOfHits = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::getNoOfComments - no object given" );

  for( int o = 0; o < object->getNoOfObjects( ); o++ )
    if( check4Comment( object->getObject( o ) ) )
      noOfHits++;

  return noOfHits;

} // Grabber::getNoOfComments

/******************************************************************************/

void  /// get all meta data of an object by a generated array
Grabber::sort2Headers( int& sizeOfList, Object**& list, Object* object ) {
  
  sizeOfList = 0;
  
  if( object == 0 )
    throw ERR::Failure( "Grabber::sort2Headers - no object given" );
  
  ListObjects* objectList = new ListObjects( 10 );

  int noOfObjects = object->getNoOfObjects( );

  for( int o = 0; o < noOfObjects; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Header( unknown ) )
      objectList->add( unknown );

  } // o

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::sort2Headers

void  /// get all CDATA of an object by a generated array
Grabber::sort2CData( int& sizeOfList, Object**& list, Object* object ) {

  sizeOfList = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::sort2CData - no object given" );

  ListObjects* objectList = new ListObjects( 10 );

  int noOfObjects = object->getNoOfObjects( );

  for( int o = 0; o < noOfObjects; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4CData( unknown ) )
      objectList->add( unknown );

  } // o

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::sort2CData

void /// get all attributes of an object by a generated array
Grabber::sort2Attributes( int& sizeOfList, Object**& list, Object* object ) {

  sizeOfList = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::sort2Attributes - no object given" );

  ListObjects* objectList = new ListObjects( 10 );

  int noOfObjects = object->getNoOfObjects( );

  for( int o = 0; o < noOfObjects; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Attribute( unknown ) )
      objectList->add( unknown );

  } // o

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::sort2Attributes

void /// get all values of an object by a generated array
Grabber::sort2Values( int& sizeOfList, Object**& list, Object* object ) {

  sizeOfList = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::sort2Values - no object given" );

  ListObjects* objectList = new ListObjects( 10 );

  int noOfObjects = object->getNoOfObjects( );

  for( int o = 0; o < noOfObjects; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Value( unknown ) )
      objectList->add( unknown );

  } // o

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::sort2Values

void /// get all elements of an object by a generated array
Grabber::sort2Elements( int& sizeOfList, Object**& list, Object* object ) {

  sizeOfList = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::sort2Elements - no object given" );

  ListObjects* objectList = new ListObjects( 10 );

  int noOfObjects = object->getNoOfObjects( );

  for( int o = 0; o < noOfObjects; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Element( unknown ) )
      objectList->add( unknown );

  } // o

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::sort2Elements

void /// get all comments of an object by a generated array
Grabber::sort2Comments( int& sizeOfList, Object**& list, Object* object ) {

  sizeOfList = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::sort2Comments - no object given" );

  ListObjects* objectList = new ListObjects( 10 );

  int noOfObjects = object->getNoOfObjects( );

  for( int o = 0; o < noOfObjects; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Comment( unknown ) )
      objectList->add( unknown );

  } // o

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::sort2Comments

/******************************************************************************/

int // find all tags in structure and hand back no of
Grabber::findNoOfTags( Object* object, String tag ) {
  
  int noOfFoundTags = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::findNoOfTags - no object given" );

  if( check4Element( object ) ) {

    String str = object->getString( );

    if( tag.compare( str ) == 0 )
      noOfFoundTags++;

  } // if

  int objectSize = object->getNoOfObjects( );

  for( int o = 0; o < objectSize; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Element( unknown ) )
      noOfFoundTags += findNoOfTags( unknown, tag );

  } // for o

  return noOfFoundTags;

} // Grabber::findNoOfTags

/******************************************************************************/

int // find all values in structure and hand back no of
Grabber::findNoOfValues( Object* object, String value ) {

  int noOfFoundValues = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::findNoOfValues - no object given" );

  int objectSize = object->getNoOfObjects( );

  if( check4Element( object ) ) {

    for( int o = 0; o < objectSize; o++ ) {  

      Object* unknown = object->getObject( o );

      if( check4Value( unknown ) ) {

        String str = unknown->getString( );

        if( value.compare( str ) == 0 )
          noOfFoundValues++;

      } // if
    } // o
  } // if

  for( int o = 0; o < objectSize; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Element( unknown ) )
      noOfFoundValues += findNoOfValues( unknown, value );

  } // for o

  return noOfFoundValues;

} // Grabber::findNoOfValues

/******************************************************************************/

int // find all tags with value in structure and hand back no of
Grabber::findNoOfTagsWithValue( Object* object, String tag, String value ) {

  int noOfFoundTagsWithValue = 0;

  if( object == 0 )
    throw ERR::Failure( "Grabber::findNoOfValues - no object given" );

  int objectSize = object->getNoOfObjects( );

  if( check4Element( object ) ) {

    String strT = object->getString( );

    if( tag.compare( strT ) == 0 ) {

      for( int o = 0; o < objectSize; o++ ) { 

        Object* unknown = object->getObject( o );

        if( check4Value( unknown ) ) {

          String strV = unknown->getString( );

          if( value.compare( strV ) == 0 )
            noOfFoundTagsWithValue++;

        } // if
      } // o
    } // if
  } // if

  for( int o = 0; o < objectSize; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Element( unknown ) )
      noOfFoundTagsWithValue += findNoOfTagsWithValue( unknown, tag, value );

  } // for o

  return noOfFoundTagsWithValue;

} // Grabber::findNoOfTagsWithValue

/******************************************************************************/

ListObjects* // find all tags in structure and hand back an object list
Grabber::findObjectsByTag( Object* object, String tag ) {
  
  ListObjects* objectList = new ListObjects( 10 );
  
  if( object == 0 )
    throw ERR::Failure( "Grabber::findObjectsByTag - no object given" );
  
  if( check4Element( object ) ) {
    
    String str = object->getString( );
    
    if( tag.compare( str ) == 0 )
      objectList->add( object );

  } // if
  
  int objectSize = object->getNoOfObjects( );
  
  for( int o = 0; o < objectSize; o++ ) {
    
    Object* unknown = object->getObject( o );
    
    if( check4Element( unknown ) ) {

      ListObjects* unknownList = 0;
      unknownList = findObjectsByTag( unknown, tag );

      int unknownListSize = unknownList->size( );

      for( int u = 0; u < unknownListSize; u++ )
        objectList->add( unknownList->get( u ) );

      delete unknownList;

    } // if

  } // for o

  return objectList;

} // Grabber::findObjectsWithTags

void // find all tags in structure and hand back an object list
Grabber::findObjectsByTag( int& sizeOfList, Object**& list, Object* object, String tag ) {

  ListObjects* objectList = findObjectsByTag( object, tag );

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::findObjectsWithTags

/******************************************************************************/

ListObjects* // find all values in structure and hand back an object list
Grabber::findObjectsByValue( Object* object, String value ) {

  ListObjects* objectList = new ListObjects( 10 );

  if( object == 0 )
    throw ERR::Failure( "Grabber::findObjectsByValue - no object given" );

  int objectSize = object->getNoOfObjects( );

  if( check4Element( object ) ) {

    for( int o = 0; o < objectSize; o++ ) {  

      Object* unknown = object->getObject( o );

      if( check4Value( unknown ) ) {

        String str = unknown->getString( );

        if( value.compare( str ) == 0 )
          objectList->add( unknown );

      } // if
    } // o
  } // if

  for( int o = 0; o < objectSize; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Element( unknown ) ) {

      ListObjects* unknownList = 0;

      unknownList = findObjectsByValue( unknown, value );

      int unknownListSize = unknownList->size( );

      for( int u = 0; u < unknownListSize; u++ )
        objectList->add( unknownList->get( u ) );

      delete unknownList;

    } // if
  } // for o

  return objectList;

} // Grabber::findObjectsByValue

void // find all values in structure and hand back an object list
Grabber::findObjectsByValue( int& sizeOfList, Object**& list, Object* object, String value ) {

  ListObjects* objectList = findObjectsByValue( object, value );

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::findObjectsByValue

/******************************************************************************/

ListObjects* // find all objects keeping this tag and value in structure and hand back an object list
Grabber::findObjectsByTagAndValue( Object* object, String tag, String value ) {
  
  ListObjects* objectList = new ListObjects( 10 );
  
  if( object == 0 )
    throw ERR::Failure( "Grabber::findObjectsByTagAndValue - no object given" );

  int objectSize = object->getNoOfObjects( );

  if( check4Element( object ) ) {

    String strTag = object->getString( );

    if( tag.compare( strTag ) == 0 ) {

      for( int o = 0; o < objectSize; o++ ) {  

        Object* unknown = object->getObject( o );

        if( check4Value( unknown ) ) {

          String strValue = unknown->getString( );

          if( value.compare( strValue ) == 0 )
            objectList->add( unknown );

        } // if
      } // o
    } // if
  } // if

  for( int o = 0; o < objectSize; o++ ) {

    Object* unknown = object->getObject( o );

    if( check4Element( unknown ) ) {

      ListObjects* unknownList = 0;
      unknownList = findObjectsByTagAndValue( unknown, tag, value );

      int unknownListSize = unknownList->size( );

      for( int u = 0; u < unknownListSize; u++ )
        objectList->add( unknownList->get( u ) );

      delete unknownList;

    } // if
  } // for o

  return objectList;

} // Grabber::findObjectsByTagAndValue

void // find all objects keeping this tag and value in structure and hand back an object list
Grabber::findObjectsByTagAndValue( int& sizeOfList, Object**& list, Object* object, String tag, String value ) {

  ListObjects* objectList = findObjectsByTagAndValue( object, tag, value );

  sizeOfList = objectList->size( );

  list = objectList->arr( );

  delete objectList;

} // Grabber::findObjectsByTagAndValue

/******************************************************************************/

} // namespace DOM

} // namespace XMLCC

/******************************************************************************/
