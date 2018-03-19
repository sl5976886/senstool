/** 
 * @file xmlccDevParser.h
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

#ifndef __xmlccDevParser_h__
#define __xmlccDevParser_h__

/******************************************************************************/

#include "./xmlccDomTokenizer.h" // for string manipulations
#include "./xmlccDomGrabber.h" // for sorting objects
#include "./xmlccBuilder.h" // for building objects

/******************************************************************************/

namespace XMLCC {

namespace DEV {

/******************************************************************************/

#define _XMLCC_VERSION_DEV_Parser_ 0.71 // 20100430
// #define _XMLCC_DEBUG_DEV_Parser_

/******************************************************************************/

class /// class parses from file or buffer and hands back a DEV structure
Parser {
 public:

  Parser( void ); /// constructor
  virtual ~Parser( void ); /// destructor

  OBJ::Root* parseFile( String fileName ); /// reads XML file and returns root object
  Object*    parseBuffer( char* buffer ); /// reads buffer of type char*
  Object*    parseBuffer( String buffer ); /// reads buffer of type std::string

 private:

  void init( void ); /// init member vars
  void parse( void ); /// do all stuff here

  void readTag( char c ); // parse a tag
  void readValue( char c ); // parse value
  void readHeader( char c ); // parse a header
  void readCData( char c ); // parse CDATA
  void readComment( char c ); // parse a comment
  void readDoctype( char c ); // parse a DOCTYPE
  void look4CDataCommentDoctype( char c ); // choose what is next

  int  _lineNo; /// count lines for telling XML file errors
  int  _charNo; /// count charaters for telling XML file errors
  int  _hLevel; /// increments and decreases during reading
  
  // COMMON
  bool _isReadingContent; /// true if parsed characters are of type content
  bool _isReadingTag; /// true if a tag is parsed currently
  bool _isReadingValue; /// true if an elements' value is parsed currently

  // HEADER <? .. ?>
  bool _isReadingHeader; /// true if a header is parsed currently
  bool _isWaitingHeaderEnd; /// true if a header end is parsed like '?'

  // COMMENT, CDATA, DOCTYPE
  bool _isReadingCommentCDataDoctype; /// true if this '<!' was parsed 

  // COMMENT <!-- .. -->
  bool _isReadingComment; /// true if a comment is parsed currently
  bool _isWaitingCommentStart; /// true if parsed '<!' and awaits next '-'
  bool _isWaitingCommentEnd1; /// true if a comment end is parsed like '-'
  bool _isWaitingCommentEnd2; /// true if a comment end is parsed like '--'

  // CDATA <![CDATA[ .. ]]>
  bool _isReadingCData; /// true if a CData section is parsed currently
  bool _isWaitingCDataEnd1; /// true if parsed ']' and awaits next ']'
  bool _isWaitingCDataEnd2; /// true if parsed ']]' and awaits next '>'

  // DOCTYPE <!DOCTYPE .. >
  bool _isReadingDoctype; /// true if a HTML DOCTYPE is parsed currently

  String _tag; /// the current name of a read tag
  String _value; /// the current value of a read tag, if exists

  String       _line; /// the current processed line with snippets of xml syntax
  Object*      _root; /// represents the file itself, not root xml element
  Object*      _element; /// the current xml element to be filled
  ListObjects* _hList; /// is filled by each new element of each hierarchy
  FileStr      _file; /// the file stream to read data if available

  Builder*         _builder; // builder class for the follwoing objects
  DOM::Grabber*    _grabber; /// a grabber for objects
  DOM::Tokenizer*  _tokenizer; /// a converter for strings of type String
  SYS::StringTool* _strTool; /// a filter to convert strings with tags 2 objects

}; // class Parser

/******************************************************************************/

} // namespace DEV

} // namespace XMLCC

/******************************************************************************/

#endif // __xmlccDevParser_h__
