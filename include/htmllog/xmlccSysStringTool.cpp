/** 
 * @file xmlccSysStringTool.cpp
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

#include <stdlib.h> // atoi(), atof(), ...
#include "./xmlccSysStringTool.h" // header

/******************************************************************************/

namespace XMLCC {

namespace SYS {

/******************************************************************************/
  
/// constructor
StringTool::StringTool( void ) {
} // StringTool

/// destructor
StringTool::~StringTool( void ) {
} // ~StringTool

/******************************************************************************/

String // remove \ \n\t\r from left and right to first letter or number in string
StringTool::trimS( String str ) {
  // TODO check trimS for BUGs but first check trimS2L and trimS2R
  str = trimS2L( str );
  str = trimS2R( str );
  return str;
} // StringTool::trimS

String // remove \ \n\t\r from left to first letter or number in string
StringTool::trimS2L( String str ) {
  size_t i = 0;
  while( ( ( str[ i ] == ' '  ) 
        || ( str[ i ] == '\t' ) 
        || ( str[ i ] == '\r' ) 
        || ( str[ i ] == '\n' ) ) 
       && ( i < str.length( ) ) ) {
    i++;
  } // while
  return str.substr( i, str.length( ) );
} // StringTool::trimS2L

String // remove \ \n\t\r from right to first letter or number in string
StringTool::trimS2R( String str ) {
  if( str.length( ) > 0 ) {
    size_t i = str.length( )-1; 
    while( ( ( str[ i ] == ' '  )
          || ( str[ i ] == '\t' ) 
          || ( str[ i ] == '\r' ) 
          || ( str[ i ] == '\n' ) ) 
         && ( ((int)i) >= 0 ) ) {
      i--;
    } // while
    return str.substr( 0, i+1 );
  } else
    return str;
} // StringTool::trimS2R

/******************************************************************************/

String // remove more whitespaces followed by whitespaces
StringTool::filterWs( String str ) {
  bool foundW = false;
  String s = "";
  for( String::iterator i = str.begin( ); i != str.end(); i++ ) {    
    char c = *i; // actual char
    if( c == ' ' && !foundW ) {
      s += c;
      foundW = true;
    }
    if( !foundW )
      s += c;
    if( c != ' ' && foundW ) {
      s += c;
      foundW = false;
    }
  } // for
  return s;
} // StringTool::filterWs

/******************************************************************************/

String // remove more tabulators and replace with whitespace
StringTool::filterTs( String str ) {
  String s = "";
  for( String::iterator i = str.begin( ); i != str.end(); i++ ) {
    char c = *i; // actual char
    if( c == '\t' ) {
      s += ' ';
      s += ' ';
    } else {
      s += c;
    } // if tab
  } // for i
  return s;
} // StringTool::filterTs

/******************************************************************************/

String // lower all letters in string
StringTool::doS2low( String str ) {
  for( size_t s = 0; s < str.length( ); s++ )
    str[ s ] = (char)tolower( str[ s ] );
  return str;
} // StringTool::doS2low

String // upper all letters in string
StringTool::doS2up( String str ) {
  for( size_t s = 0; s < str.length( ); s++ )
    str[ s ] = (char)toupper( str[ s ] );
  return str;
} // StringTool::doS2up

/******************************************************************************/

String // convert integer to string
StringTool::doI2S( int value ) {
  std::ostringstream stream;
  stream << value;
  return stream.str( );
} // StringTool::doI2S

String // convert bool to string
StringTool::doB2S( bool value ) {
  std::ostringstream stream;
  if( value ) 
    stream << "TRUE";
  else
    stream << "FALSE";
  return stream.str( );
} // StringTool::doB2S

String // convert float to string
StringTool::doF2S( float value ) {
  std::ostringstream stream;
  stream << value;
  return stream.str( );
} // StringTool::doF2S

String // convert double to string
StringTool::doD2S( double value ) {
  std::ostringstream stream;
  stream << value;
  return stream.str( );
} // StringTool::doD2S

/******************************************************************************/

int // convert string to integer
StringTool::doS2I( String str ) {
  return (int)( atoi( (char*)str.c_str( ) ) );
} // StringTool::doS2I

bool // convert char to bool
StringTool::doS2B( String str ) {
  str = doS2low( str );
  if( str.compare( "true" ) == 0 )
    return true;
  else if( str.compare( "1" ) == 0 )
    return true;
  else if( str.compare( "y" ) == 0 )
    return true;
  else if( str.compare( "j" ) == 0 )
    return true;
  else if( str.compare( "ja" ) == 0 )
    return true;
  else if( str.compare( "ok" ) == 0 )
    return true;
  else if( str.compare( "yes" ) == 0 )
    return true;
  else if( str.compare( "okay" ) == 0 )
    return true;
  else if( str.compare( "done" ) == 0 )
    return true;
  else if( str.compare( "good" ) == 0 )
    return true;
  else if( str.compare( "fine" ) == 0 )
    return true;
  else if( str.compare( "ready" ) == 0 )
    return true;
  else if( str.compare( "finish" ) == 0 )
    return true;
  else if( str.compare( "perfect" ) == 0 )
    return true;
  else
    return false;
} // StringTool::doS2B

float // convert string to float
StringTool::doS2F( String str ) {
  return (float)( atof( (char*)str.c_str( ) ) );
} // StringTool::doS2F

double // convert string to double
StringTool::doS2D( String str ) {
  return (double)( atof( (char*)str.c_str( ) ) );
} // StringTool::doS2D

/******************************************************************************/

bool // check string for containing only standard characters
StringTool::checkS2Std( String str ) {
  for( size_t i = 0; i < str.length( ); i++ )
    if( str[ i ] < 0x20 || str[ i ] > 0x7E )
      return false;
  return true;
} // StringTool::checkS2Std

/******************************************************************************/

bool // check string for containing whitespaces
StringTool::checkS2Ws( String str ) {
  for( size_t i = 0; i < str.length( ); i++ )
    if( str[ i ] == ' ' )
      return true;
  return false;
} // StringTool::checkS2W

/******************************************************************************/

} // namespace SYS

} // namespace XMLCC

/******************************************************************************/
