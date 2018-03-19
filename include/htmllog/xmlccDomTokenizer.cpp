/** 
 * @file xmlccDomTokenizer.cpp
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

#include "./xmlccDomTokenizer.h" // header

/******************************************************************************/

namespace XMLCC {

namespace DOM {

/******************************************************************************/

/// constructor
Tokenizer::Tokenizer( void ) {

  _strTool = new SYS::StringTool( );

} // Tokenizer

/// destructor
Tokenizer::~Tokenizer( void ) {

  delete _strTool;

} // ~Tokenizer

/******************************************************************************/

Object*  // convert a tag 2 object
Tokenizer::convertTag( String tag ) {

  Object* object = 0;

  tag = _strTool->trimS( tag );
  tag = _strTool->filterWs( tag );

  object = convert2Object( tag );

  return object;

} // Parser::convertTag

Object*  // convert a tag 2 object
Tokenizer::convertTagComplete( String tag ) {

  Object* object = 0;

  tag = _strTool->trimS( tag );
  tag = _strTool->filterWs( tag );

  object = convert2ObjectComplete( tag );

  return object;

} // Parser::convertTagComplete

Object* // convert a val 2 object
Tokenizer::convertValue( String value ) {

  Object* object = 0;

  value = _strTool->trimS( value );
  value = _strTool->filterWs( value );

  object = conv2Val( value );

  return object;

} // Parser::convertValue

/******************************************************************************/

bool /// check if tag is ending
Tokenizer::check4Ending( String tag ) {

  bool isTagEnding = false;

  tag = _strTool->trimS( tag );
  tag = _strTool->filterWs( tag );

  if( tag.length( ) > 0 ) {

    char m = tag[ 0 ];

    if( m == '/' )
      isTagEnding = true;
    else
      isTagEnding = false;

  } else
    throw ERR::Failure( "Tokenizer::check4TagEnding - no tag given; no chars" );
  
  return isTagEnding;

} // Tokenizer::check4TagEnding

bool /// check if tag is standalone
Tokenizer::check4StandAlone( String tag ) {

  bool isTagStandAlone = false;

  tag = _strTool->trimS( tag );
  tag = _strTool->filterWs( tag );

  size_t tagLength = tag.length( );

  if( tagLength > 0 ) {
    
    char m = tag[ tagLength - 1 ];
    
    if( m == '/' )
      isTagStandAlone = true;
    else
      isTagStandAlone = false;

  } else
    throw ERR::Failure( "Tokenizer::check4TagStandAlone - no tag given; no chars" );
  
  return isTagStandAlone;

} // Tokenizer::check4TagStandAlone

/******************************************************************************/

Object* /// filter a string and hand back objects
Tokenizer::convert2Object( String line ) {
  
  Object* object = 0;
  
  size_t length = line.size( );
  
  if( length < 1 )
    throw ERR::Failure( "Tokenizer::convert2Object - line has no char" );
  
  char m = line[ 0 ];

  if( m == '!' ) {  // check for comment

    if( length > 5 ) { // !---- has minimum of 5

      char s0 = line[ 0 ];
      char s1 = line[ 1 ];
      char s2 = line[ 2 ];

      if( ( s0 == '!' ) && ( s1 == '-' ) && ( s2 == '-' ) ) { // comment

        char e0 = line[ length - 1 ];
        char e1 = line[ length - 2 ];

        if( ( e1 == '-' ) && ( e0 == '-' ) ) { // found comment
          return conv2Comment( line );
        } // if --

      } // if !--

    } // if 5

  } // if !

  if( m == '?' ) { // check for a header

    char s0 = line[ 0 ];

    if( s0 == '?' ) {

      char e0 = line[ length - 1 ];

      if( e0 == '?' ) {
        return conv2Header( line );
      } // if ?

    } // if ?
  } // if ?  

  if( ( m != '!' ) && ( m != '?' ) ) { // check for a ending tag 

    char s0 = line[ 0 ];

    if( s0 == '/' ) {

      char e0 = line[ length-1 ];

      if( e0 != '/' ) { // have to be

        String tag = line.substr( 1, ( length - ( 1 ) ) );
        object = conv2Tag( tag );
        // std::cout << tag << std::endl << std::flush;

        // TODO implement first step 2 validation here
        //   handback an object, that has the same tag
        //   as the one created and check for the created one

        return object; // return zero

      } else { // useless else here
        throw ERR::Error( "Tokenizer::convert2Object - tag is malformed like </text/>" );
      } // if tag / ... /

    } // if ?
  } // if ?  

  // check for a tag starting
  if( ( m != '/' ) && ( m != '!' ) && ( m != '?' ) )
    return conv2Tag( line );

  return object;

} // Tokenizer::convert2Object

/******************************************************************************/

Object* /// filter a string and hand back objects
Tokenizer::convert2ObjectComplete( String line ) {
  
  Object* object = 0;
  
  size_t length = line.size( );
  
  if( length < 1 )
    throw ERR::Failure( "Tokenizer::convert2ObjectComplete - line has no char" );
  
  char a = line[ 0 ];

  if( a != '<' )
    throw ERR::Failure( "Tokenizer::convert2ObjectComplete - line has no starting <" );
  
  char e = line[ length - 1 ];

  if( e != '>' )
    throw ERR::Failure( "Tokenizer::convert2ObjectComplete - line has no ending >" );

  line = line.substr( 1, ( length - ( 1 + 1 ) ) ); // without < .. >
  length = line.size( );

  char m = line[ 0 ]; // the first after '<'

  if( m == '!' ) {  // check for comment


    if( length > 5 ) { // <!----> has minimum of 7 -> 3 for beginning

      char s0 = line[ 0 ]; 
      char s1 = line[ 1 ];
      char s2 = line[ 2 ];

      if( ( s0 == '!' ) && ( s1 == '-' ) && ( s2 == '-' ) ) { // comment

        char e0 = line[ length - 1 ]; // -
        char e1 = line[ length - 2 ]; // --

        if( ( e1 == '-' ) && ( e0 == '-' ) ) { // found <!---->
          return conv2Comment( line );
        } // if --

      } // if !--



      if( ( s0 == '!' ) && ( s1 == '[' ) && ( s2 == 'C' ) ) { // ![C -> DATA[

        if( length > 10 ) {

          char s3 = line[ 3 ]; // D
          char s4 = line[ 4 ]; // A
          char s5 = line[ 5 ]; // T
          char s6 = line[ 6 ]; // A
          char s7 = line[ 7 ]; // [

          if( ( s3 == 'D' ) && ( s4 == 'A' ) && ( s5 == 'T' )
           && ( s6 == 'A' ) && ( s7 == '[' ) ) {

            char e0 = line[ length - 1 ]; // ]
            char e1 = line[ length - 2 ]; // ]]

            if( ( e1 == ']' ) && ( e0 == ']' ) ) { // found comment

              return conv2CData( line );

            } // if "]]"

          } // if "DATA["

        } // if length > 10

      } // if "![C"



      if( ( s0 == '!' ) && ( s1 == 'D' || s1 == 'd' ) 
                        && ( s2 == 'O' || s2 == 'o' ) ) { // !DO

        if( length > 10 ) {

          char s3 = line[ 3 ]; // C
          char s4 = line[ 4 ]; // T
          char s5 = line[ 5 ]; // Y
          char s6 = line[ 6 ]; // P
          char s7 = line[ 7 ]; // E

          if( ( s3 == 'C' || s3 == 'c' ) && ( s4 == 'T' || s4 == 't' )
           && ( s5 == 'Y' || s5 == 'y' ) && ( s6 == 'P' || s6 == 'p' ) 
           && ( s7 == 'E' || s7 == 'e' ) ) {


            return conv2Doctype( line );

          } // if "CTYPE"

        } // if length > 10

      } // if "!DO"

    } // if 5

  } // if !

  if( m == '?' ) { // check for a header

    char s0 = line[ 0 ];

    if( s0 == '?' ) {

      char e0 = line[ length - 1 ];

      if( e0 == '?' ) {
        return conv2Header( line );
      } // if ?

    } // if ?
  } // if ?  

  if( ( m != '!' ) && ( m != '?' ) ) { // check for a ending tag 

    char s0 = line[ 0 ];

    if( s0 == '/' ) {

      char e0 = line[ length - 1 ];

      if( e0 != '/' ) { // have to be

        String tag = line.substr( 1, ( length - ( 1 + 1 ) ) );
        object = conv2Tag( tag );
        // std::cout << tag << std::endl << std::flush;

        // TODO implement first step 2 validation here
        //   handback an object, that has the same tag
        //   as the one created and check for the created one

        return object; // return zero

      } else { // useless else here
        throw ERR::Error( "Tokenizer::convert2ObjectComplete - tag is malformed like </text/>" );
      } // if tag / ... /

    } // if ?
  } // if ?  

  // check for a tag starting
  if( ( m != '/' ) && ( m != '!' ) && ( m != '?' ) )
    return conv2Tag( line );

  return object;

} // Tokenizer::convert2ObjectComplete

/******************************************************************************/

Object* /// convert a known header string to an object
Tokenizer::conv2Header( String line ) {

  Object* object = 0;

  line = line.substr( 1, ( line.length( ) - ( 1 + 1 ) ) );
  line = _strTool->trimS( line );

  String tag = getTag( line ); // search for tag first

  object = new OBJ::Header( tag );
  ListObjects* objList = convAttAndValList( line );

  for( int o = 0; o < objList->size( ); o++ )
    object->addObject( objList->get( o ) );

  delete objList;

  return object;

} // Tokenizer::convert2Tag

/******************************************************************************/

Object* /// convert a known comment string to an object
Tokenizer::conv2Comment( String line ) {

  Object* object = 0;

  line = line.substr( 3, ( line.length( ) - ( 3 + 2 ) ) );
  line = _strTool->trimS( line );
  line = _strTool->filterWs( line );

  object = new OBJ::Comment( line );

  return object;

} // Tokenizer::convert2Comment;

/******************************************************************************/

Object* /// convert CDATA to an object
Tokenizer::conv2CData( String line ) {

  Object* object = 0;

  /// <![CDATA[ ... ]]>
  line = line.substr( 8, ( line.length( ) - ( 8 + 2 ) ) );
  line = _strTool->trimS( line );
  line = _strTool->filterWs( line );

  object = new OBJ::CData( line );

  return object;

} // Tokenizer::convert2Comment;

/******************************************************************************/

Object* /// convert DOCTYPE to an object
Tokenizer::conv2Doctype( String line ) {

  Object* object = 0;

  /// <!DOCTYPE >
  line = line.substr( 8, ( line.length( ) - ( 8 + 2 ) ) );
  line = _strTool->trimS( line );
  line = _strTool->filterWs( line );

  // TODO: filter DOCTYPE to whitespaces and quotes
  object = new OBJ::Doctype( );

  return object;

} // Tokenizer::convert2Comment;

/******************************************************************************/

Object* /// convert a known starting tag string to an object
Tokenizer::conv2Tag( String line ) {

  Object* object = 0;

  char e0 = line[ line.length( ) - ( 1 ) ];

  if( e0 == '/' ) // standalone tag
    line = line.substr( 0, line.length( ) - ( 1 ) );
  else if( e0 != '/' ) // normal tag
    line = line.substr( 0, line.length( ) - ( 0 ) );
  else // useless else here
    throw ERR::Failure( "Tokenizer::conv2Tag - tag is not of chars" );

  line = _strTool->trimS( line );

  String tag = getTag( line ); // search for tag first

  object = new OBJ::Element( tag );

  ListObjects* objList = convAttAndValList( line );

  for( int o = 0; o < objList->size( ); o++ )
    object->addObject( objList->get( o ) );

  delete objList;

  return object;

} // Tokenizer::convert2Tag

/******************************************************************************/

ListObjects* /// get String with strings as: att="val"
Tokenizer::convAttAndValList( String line ) {

  ListStrings* strList = new ListStrings( 10 );

  bool firstWhiteSpace = false;
  bool firstExclamationMark = false;

  String str; // define here for collecting chars in foor loop

  for( String::iterator i = line.begin( ); i != line.end( ); i++ ) {

    char c = *i; // actual char

    if( firstWhiteSpace ) {

      if( c != ' ' )
        str += c;

      if( firstExclamationMark ) {

        if( c == ' ' )
          str += c; // now add whiteys

        if( ( c == '"' ) || ( i == ( line.end( ) - ( 1 ) ) ) ) {

          strList->add( str );

          str.clear( );

        } // "

      } // if

      if( c == '"' ) {

        if( !firstExclamationMark ) {
          firstExclamationMark = true;
        } else
          firstExclamationMark = false; {
        } // first

      } // "
    } // if not first white (after tag)

    if( !firstWhiteSpace && c == ' ' )
      firstWhiteSpace = true;

  } // for i

  ListObjects* objectList = new ListObjects( 5 );

  for( int s = 0; s < strList->size( ); s++ ) {

    String str = strList->get( s );

    Object* attribute = conv2AttAndVal( str );

    if( attribute != 0 )
      objectList->add( attribute );

  } // for s

  delete strList;

  return objectList;

} // Tokenizer::getAttAndValList

/******************************************************************************/

Object* /// convert a string to attribute and value object
Tokenizer::conv2AttAndVal( String line ) {

  Object* object = 0;

  line = _strTool->trimS( line );

  String str; // define here for collecting chars in foor loop

  ListStrings* strList = new ListStrings( 10 );

  for( String::iterator i = line.begin( ); i != line.end( ); i++ ) {

    char c = *i; // actual char

    if( ( c != '=' ) && ( c != '"' ) )
      str += c;

    if( c == '"' ) {

      str = _strTool->trimS( str );
      str = _strTool->filterWs( str );

      strList->add( str );

      str.clear( );

    } // if

  } // for i

  int strListSize = strList->size( );

  if( strListSize == 2 ) {

    String attributeStr = strList->get( 0 );
    String valueStr = strList->get( 1 );

    object = new OBJ::Attribute( attributeStr, valueStr );

  } else
    throw ERR::Error( "Tokenizer::conv2AttAndVal - attribute has no correct XML syntax" );

  delete strList;

  return object;

} // Tokenizer::convert2AttributeAndValue

/******************************************************************************/

Object* /// convert a known value string to an object
Tokenizer::conv2Val( String line ) {

  Object* object = 0;

  String str = _strTool->trimS( line );

  if( str.length( ) < 1 )
    return object;

  object = new OBJ::Value( str );

  return object;

} // Tokenizer::convert2Value

/******************************************************************************/

String // hand the tag back as string
Tokenizer::getTag( String line ) {

  // search for tag first
  String tag;

  size_t posOfFirstWhite = 0;
  size_t lineLength = line.length( );

  bool isFound = false;

  while( !isFound ) {

    char t = line[ posOfFirstWhite ];

    if( t != ' ' )
      tag += t;

    if( t == ' ' )
      isFound = true;

    if( posOfFirstWhite >= ( lineLength - ( 1 ) ) )
      isFound = true;

    posOfFirstWhite++;

  } // while

  return tag;

} // Tokenizer::getTag

/******************************************************************************/

} // namespace DOM 

} // namespace XMLCC

/******************************************************************************/
