/** 
 * @file xmlccDevParser.cpp
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

#include "./xmlccDevParser.h" // header

/******************************************************************************/

namespace XMLCC {

namespace DEV {

/******************************************************************************/

/// constructor
Parser::Parser( void ) {

  _builder   = new Builder( );
  _grabber   = new DOM::Grabber( );
  _tokenizer = new DOM::Tokenizer( );
  _strTool   = new SYS::StringTool( );

  _root      = 0;
  _element   = 0;

} // Parser

/// destructor
Parser::~Parser( void ) {

  delete _builder;
  delete _strTool;
  delete _grabber;
  delete _tokenizer;

} // ~Parser

/******************************************************************************/

OBJ::Root* /// reads XML file and returns root object
Parser::parseFile( String fileName ) {

  try { // try anything ~8>

    _file.open( (char*)fileName.c_str( ), std::ios::in );
    if( _file.fail( ) ) {

      String failureMsg = "Parser::parseFile - can not open file: ";
	    throw ERR::Failure( failureMsg.append( fileName ) );

    } // no file or locked 

    init( ); // init all member variables

    _root->setString( fileName );

    _element = _root;

    while( getline( _file, _line ) ) { // parse more than one line

      parse( ); // do all stuff in member func with member vars

      //if( _isReadingTag ) // if it is a tag
      //  _tag += ' '; // replace a break by a whitespace

      if( this->_isReadingCData )
        _tag += '\n'; // add break line if there is one in CDATA

      if( this->_isReadingComment )
        _tag += '\n'; // add break line if there is one in comment

      _charNo = 0; // chars are counted for each line

      _lineNo++; // count lines

    } // while

  } catch( ERR::Failure f ) {

    if( !_file.fail( ) )
      _file.close( );

    // delete _root;

    throw ERR::Failure( 
      f.declare( ).append( " @ line no: " ).
                   append( _strTool->doI2S( _lineNo ) ).
                   append( " @ char pos: " ).
                   append( _strTool->doI2S( _charNo ) ) );

  } catch( ERR::Error e  ) {

    if( !_file.fail( ) )
      _file.close( );

    delete _root;

    throw ERR::Error( 
      e.declare( ).append( " @ line no: " ).
                   append( _strTool->doI2S( _lineNo ) ) );

  } catch( std::exception e ) {

    if( !_file.fail( ) )
      _file.close( );

    delete _root;

    throw ERR::Exception( "DEV::Parser::parseFile - std::exception caught" );

  } // try

  _file.close( ); // close written file

  Object* res = _hList->get( 0 ); // get root

  delete _hList; // free hierarchical list

  _root = 0;
  _element = 0;

  return (OBJ::Root*)res; // return root

} // Parser::parseFile

/******************************************************************************/

Object* /// reads buffer of type std::string
Parser::parseBuffer( String buffer ) {

  if( buffer.length( ) <= 0 )
    throw ERR::Failure( "DEV::Parser::parseBuffer - buffer is empty" );
  
  init( ); // init all member variables

  _line = buffer; // hand bufferto a single long line of data
    
  _element = _root;

  parse( ); // do all stuff by members for same function

  Object* res = _hList->get( 0 ); // get root

  delete _hList; // free hierarchical list

  _root = 0;
  _element = 0;

  return res; // return root

} // Parser::parseBuffer

/******************************************************************************/

Object*  /// reads buffer of type char*
Parser::parseBuffer( char* buffer ) {

  return parseBuffer( String( buffer ) );

} //Parser::parseBuffer

/******************************************************************************/

void /// init member vars
Parser::init( void ) {

  _isReadingTag          = false; /// true if a tag is parsed currently
  _isReadingHeader       = false; /// true if a header is parsed currently
  _isReadingComment      = false; /// true if a comment is parsed currently
  _isReadingDoctype      = false; /// true if a HTML DOCTYPE is parsed currently
  _isReadingValue        = false; /// true if an elements' value is parsed currently
  _isReadingCData        = false; /// true if a CData section is parsed currently
  _isReadingContent      = false; /// true if parsed characters are of type content
  _isReadingCommentCDataDoctype = false; /// true if this '<!' was parsed 

  _isWaitingHeaderEnd    = false; /// true if a header end is parsed like '?'
  _isWaitingCommentStart = false; /// true if parsed '<!' and awaits next '-'
  _isWaitingCommentEnd1  = false; /// true if parsed '-' and awaits next '--'
  _isWaitingCommentEnd2  = false; /// true if parsed '--' and awaits next '>'
  _isWaitingCDataEnd1    = false; /// true if parsed ']' and awaits next ']'
  _isWaitingCDataEnd2    = false; /// true if parsed ']]' and awaits next '>'

  _root    = _builder->createRoot( ); // create root 

  _hList   = new ListObjects( 25 ); // extends automatically if hierarchy is exceded

  _element = 0; // not yet
  _lineNo  = 0; // count lines for telling XML file errors
  _charNo  = 1; // count charaters for telling XML file errors
  _hLevel  = 0; // increments and decreases during reading

  _hList->add( _root ); // add root already

} // Parser::init

void // this function parses a line char by char
Parser::parse( void ) {

  try {

    int lineLength = (int)_line.length( );
    if( lineLength > 0 ) { // bug from version 1.0 fixed

      if ( _line[ lineLength - 1 ] == '\r' )
        _line = _line.substr( 0, _line.length( ) - 1 );

      _line = _strTool->filterTs( _line ); // replace tabulator by 2 white spaces

      if( !isprint( _line[ 0 ] ) )
        throw ERR::Failure( "DEV::Parser::parse - failing on character" );

      for( String::iterator i = _line.begin( ); i != _line.end( ); i++ ) {


        char c = *i; // actual character


        if( _isReadingHeader ) {

          readHeader( c ); // <? .. ?>

        } else if( _isReadingCommentCDataDoctype ) {

          look4CDataCommentDoctype( c );  // <! .. > 

        } else if( _isReadingComment ) {

          readComment( c ); // <!-- .. -->

        } else if( _isReadingCData ) {

          readCData( c ); // <![CDATA[ .. ]]>

        } else if( _isReadingDoctype ) {

          readDoctype( c ); // <!DOCTYPE HTML PUBLIC "" "">

        } else if( _isReadingValue ) {

          readValue( c ); // <tag> .. </tag>

        } else if( _isReadingTag ) {

          readTag( c ); // < .. ></ .. > or < .. />

        } else { // control

          
          if( c == '<' && !_isReadingContent ) {

            _isReadingTag = true;
            _isReadingValue = false;

            _tag += c;

          } // if

          if( c == '>' && !_isReadingContent ) {
            
            _isReadingTag = false;
            _isReadingValue = true;

          } // switch vice versa always to get a values

        } // if( _isReadingTag )


        _charNo++; // position of next char

      } // for c

    } // empty lines are ignored

  } catch( ERR::Failure f ) {

    delete _root;
    throw ERR::Failure( 
      f.declare( ).append( " @ char pos: " ).
                   append( _strTool->doI2S( _charNo ) ) );

  } catch( ERR::Error e  ) {

    delete _root;
    throw ERR::Error(
      e.declare( ).append( " @ char pos: " ).
                   append( _strTool->doI2S( _charNo ) ) );

  } catch( std::exception e ) {

    delete _root;
    throw ERR::Exception( "DEV::Parser::parse - std::exception caught" );

  } // try

} // Parser::parse

/******************************************************************************/

void // parse a tag
Parser::readTag( char c ) {

  if( c == '?' && !_isReadingContent ) {

    _isReadingHeader = true;

  } else if( c == '!' && !_isReadingContent ) {

    _isReadingCommentCDataDoctype = true;

  } else if( c == '>' && !_isReadingContent ) {

    _isReadingTag     = false;
    _isReadingValue   = true;

  } // if ends

  _tag += c;

  if( !_isReadingTag ) {

    #ifdef _XMLCC_DEBUG_DEV_Parser_
      std::cout << _tag << std::endl << std::flush;
    #endif
                          
    String tag_cut = _tag.substr( 1, ( _tag.length( ) - ( 1 + 1 ) ) ); /// TODO: solve round about
    bool isEnding = _tokenizer->check4Ending( tag_cut );
    bool isStandAlone = _tokenizer->check4StandAlone( tag_cut );

    if( !isEnding && !isStandAlone ) { // < .. >

      Object* tag = _tokenizer->convertTagComplete( _tag );
      _element->addObject( tag );

      _element = tag; // next hierarchy

      _tag.clear( );

      int hListSize = _hList->size( );

      if( ( _hLevel + 1 ) < hListSize )
        _hList->set( ( _hLevel + 1 ), tag );
      else
        _hList->add( tag );

      _hLevel++; // current hierarchy

    } else if( isStandAlone ) { // < .. />

      Object* tag = _tokenizer->convertTagComplete( _tag );
      _element->addObject( tag );

      _element = _element; // no hierarchy

      _tag.clear( );

    } else if( isEnding ) { // </ .. >

      // TODO: check if ending Tag matches to _element;
      _hLevel--;

      Object* last = _hList->get( _hLevel );
      _element = last;

      _tag.clear( );

    } else {

      throw ERR::Failure( "DEV::Parser::parse - tag is neither starting, standalone, or ending" );

    } // if kind of tag

  }  // if

} // ParseR::readTag

void // parse value
Parser::readValue( char c ) {

  if( c == '<' && !_isReadingContent ) {

    _isReadingTag = true;
    _isReadingValue = false;
    _tag += c;

  } // if a tag starts again

  if( _isReadingValue )
    _value += c;

  if( !_isReadingValue ) {

    Object* value = _tokenizer->convertValue( _value );

    if( value != 0 ) { // if _value was empty

      #ifdef _XMLCC_DEBUG_DEV_Parser_
        std::cout << _value << std::endl << std::flush;
      #endif

      _element->addObject( value );

    } // if value is found

    _value.clear( );

  } // if

} // Parser::readValue

void // parse a header
Parser::readHeader( char c ) {

  if( c == '?' && !_isReadingContent ) {

    _isWaitingHeaderEnd = true;

  } else if( c == '>' && _isWaitingHeaderEnd && !_isReadingContent ) {

    _isWaitingHeaderEnd = false;
    _isReadingHeader    = false;
    _isReadingTag       = false;
    _isReadingValue     = true;

  } // if

  _tag += c;

  if( !_isReadingHeader ) {

    #ifdef _XMLCC_DEBUG_DEV_Parser_
      std::cout << _tag << std::endl << std::flush;
    #endif

    Object* header = _tokenizer->convertTagComplete( _tag );
    _element->addObject( header );

    _tag.clear( );

  } // if

} // Parser::readHeader
   

void // parse CDATA
Parser::readCData( char c ) {

  if( c == '>' && _isWaitingCDataEnd1 && _isWaitingCDataEnd2 && _isReadingContent ) {

    _isWaitingCDataEnd1 = false;
    _isWaitingCDataEnd2 = false;
    _isReadingCData     = false;
    _isReadingContent   = false;
    _isReadingTag       = false;
    _isReadingValue     = true;

  } else if( c == ']' && _isWaitingCDataEnd1 && _isReadingContent ) {

    _isWaitingCDataEnd2 = true;

  } else if( c == ']' && _isReadingContent ) {

    _isWaitingCDataEnd1 = true;

  } // if

  _tag += c;

  if( !_isReadingCData ) {

    #ifdef _XMLCC_DEBUG_DEV_Parser_
      std::cout << _tag << std::endl << std::flush;
    #endif

    Object* cdata = _tokenizer->convertTagComplete( _tag );
    _element->addObject( cdata );

    _tag.clear( );

  } // if

} // Parser::readCData


void // parse a comment
Parser::readComment( char c ) {

  if( c == '>' && _isWaitingCommentEnd1 && _isWaitingCommentEnd2 && !_isReadingContent ) {

    _isWaitingCommentEnd1 = false;
    _isWaitingCommentEnd2 = false;
    _isReadingComment     = false;
    _isReadingTag         = false;
    _isReadingValue       = true;

  } else if( c == '-' && _isWaitingCommentEnd1 && !_isReadingContent ) {

    _isWaitingCommentEnd2 = true;

  } else  if( c == '-' && !_isReadingContent ) {

    _isWaitingCommentEnd1 = true;

  } // if end

  _tag += c;

  if( !_isReadingComment ) {

    #ifdef _XMLCC_DEBUG_DEV_Parser_
      std::cout << _tag << std::endl << std::flush;
    #endif

    Object* comment = _tokenizer->convertTagComplete( _tag );
    _element->addObject( comment );

    _tag.clear( );

  } // if

} // Parser::readComment


void // parse a DOCTYPE
Parser::readDoctype( char c ) {

  // TODO: Add to Tokenizer: <!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">


  if( c == '>' && !_isReadingContent ) {

    _isReadingDoctype    = false;
    _isReadingTag        = false;
    _isReadingValue      = true;

  } // if

  _tag += c;

  if( !_isReadingDoctype ) {

    #ifdef _XMLCC_DEBUG_DEV_Parser_
      std::cout << _tag << std::endl << std::flush;
    #endif

    Object* doctype = _tokenizer->convertTagComplete( _tag );
    _element->addObject( doctype );
    
    _tag.clear( );

  } // if DONE

} // Parser::readDoctype


void // choose what is next
Parser::look4CDataCommentDoctype( char c ) {

  if( c == '[' && !_isReadingContent ) {

    _isReadingCommentCDataDoctype = false;
    _isReadingCData          = true;
    _isReadingContent        = true;

  } else if( ( c == 'D' || c == 'd' ) && !_isReadingContent ) {

    _isReadingCommentCDataDoctype = false;
    _isReadingDoctype = true;

  } else if( c == '-' && _isWaitingCommentStart && !_isReadingContent ) {
    
    _isReadingCommentCDataDoctype = false;
    _isWaitingCommentStart   = false;
    _isReadingComment        = true;

  } else if( c == '-' && !_isReadingContent ) {

    _isWaitingCommentStart = true;


  } else {

    std::cout << " else _isReadingCommentCDataDoctype " << std::flush;

  }

  _tag += c;

} // Parser::look4CDataCommentDoctype

/******************************************************************************/

} // namespace DEV 

} // namespace XMLCC

/******************************************************************************/
