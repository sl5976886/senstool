/** 
 * @file xmlccSysStringTool.h
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

#ifndef __xmlccSysStringTool_h__
#define __xmlccSysStringTool_h__

/******************************************************************************/

#include "./xmlccInclDefs.h" /// common include file for headers and typedefs

/******************************************************************************/

namespace XMLCC {

namespace SYS {

/******************************************************************************/

#define _XMLCC_VERSION_SYS_StringTool_ 0.71 // 20100430
#define _XMLCC_DEBUG_SYS_StringTool_

/******************************************************************************/

class /// class for manipulating std::string and char*
StringTool {
 public:

  StringTool( void ); /// constructor
  virtual ~StringTool( void ); /// destructor
    
  String trimS( String str ); /// remove \ \n\t\r from left and right to first letter or number in string
  String trimS2L( String str ); /// remove \ \n\t\r from left to first letter or number in string
  String trimS2R( String str ); /// remove \ \n\t\r from right to first letter or number in string

  String filterWs( String str ); /// remove more whitespaces followed by whitespaces
  String filterTs( String str ); /// remove more tabulators and replace with whitespace

  String doS2low( String str ); /// lower all letters in string
  String doS2up( String str ); /// upper all letters in string

  String doI2S( int value ); // convert integer to string
  String doB2S( bool value ); // convert bool to string
  String doF2S( float value ); // convert float to string
  String doD2S( double value ); // convert double to string
  int    doS2I( String str ); // convert string to integer
  bool   doS2B( String str ); // convert string to bool
  float  doS2F( String str ); // convert string to float
  double doS2D( String str ); // convert string to double

  bool checkS2Std( String str ); /// check string for containing only standard characters
  bool checkS2Ws( String str ); /// check string for containing whitespaces

}; // class StringTool

/******************************************************************************/

} // namespace SYS

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccSysStringTool_h__
