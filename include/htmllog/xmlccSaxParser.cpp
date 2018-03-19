/** 
 * @file xmlccSaxParser.cpp
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

#include "./xmlccSaxParser.h" // header

/******************************************************************************/

namespace XMLCC {

namespace SAX {

/******************************************************************************/

/// constructor
Parser::Parser( ParserHandler* handler ) {
  _tokenizer = new DOM::Tokenizer( );
  _grabber = new DOM::Grabber( );
  _strTool = new SYS::StringTool( );
  _handler = handler;
} // Parser

/// destructor
Parser::~Parser( void ) {
  delete _strTool;
  delete _grabber;
  delete _handler;
  delete _tokenizer;
} // ~Parser

/******************************************************************************/

void /// reads buffer of type char*
Parser::parseBuffer( char* buffer ) {
  parseBuffer( String( buffer ) );
} // Parser::parseBuffer

/******************************************************************************/

void /// reads buffer of type std::string
Parser::parseBuffer( String buffer ) {

  if( buffer.length( ) <= 0 )
    throw ERR::Failure( "SAX::Parser::parseBuffer - buffer is empty" );

  Builder builder;
  String tag;
  String val;
  bool readTag = false;
  bool readVal = false;
  bool readAll = false;
  String line; // line by line
  int lineNo = 0; // count lines for telling XML file errors
  int charNo = 0; // count charaters for telling XML file errors

  _handler->startDocument( ); // call the handler

  try {

    int bufferLength = (int)buffer.length( );
    if( bufferLength > 0 ) { // bug from version 1.0 fixed

      if ( buffer[ bufferLength - 1 ] == '\r' )
        buffer = buffer.substr( 0, buffer.length( ) - 1 );

      buffer = _strTool->filterTs( buffer ); // replace tabulator by 2 white spaces

      if( !isprint( buffer[ 0 ] ) ) {
        throw ERR::Failure( "SAX::Parser::parseBuffer - failing on character" );
      } // if

      for( String::iterator i = line.begin( ); i != line.end( ); i++ ) {

        char c = *i; // actual char

        if( c == '>' && !readAll && !readVal ) {
          readTag = false;
          // bool isTagStandAlone = _tokenizer->check4StandAlone( tag );
          bool isTagEnding = _tokenizer->check4Ending( tag );
          Object* element = _tokenizer->convertTag( tag ); /// convert a tag 2 object
          if( element != 0 ) {
            if( !isTagEnding )
              _handler->startObject( element );
            else
              _handler->endObject( element );
            delete element;
            element = 0;
          } //if
          tag.clear( );
        } // if >

        if( c =='<' && readVal && !readTag && !readAll ) {
          readVal = false;
          Object* value = _tokenizer->convertValue( val );
          if( value != 0 ) {
            _handler->characters( value );
            delete value;
            value = 0;
          } // if
          val.clear( );
        } // if < readVal

        if( c =='<' && readTag && !readAll ) {
          String errorMsg = "SAX::Parser::parseFile - XML tag <";
          errorMsg.append( _strTool->trimS( tag ) );
          errorMsg.append( " was not closed by \">\"" );
          throw ERR::Error( errorMsg );
        } // if <bla <fasel

        if( c =='>' && readVal && !readAll ) {
          String errorMsg = "SAX::Parser::parseFile - XML tag after value ";
          errorMsg.append( _strTool->trimS( val ) );
          errorMsg.append( "> has not starting" );
          throw ERR::Error( errorMsg );
        } // if bla> fasel>

        if( readTag ) // if it is a tag
          tag += c; // read from char

        if( readVal ) // if it is a value
          val += c; // read from char

        if( c == '"' && readTag )
          readAll = !readAll; // interchange

        if( c == '<' && !readAll ) // start reading tags
          readTag = true;

        if( c == '>' && !readAll ) // start reading values
          readVal = true;

        charNo++; // position of next char

      } // for c

    } // empty lines are ignored

    if( readTag ) // if it is a tag
      tag += ' '; // replace a break by a whitespace

    if( readVal ) // if it is a value
      val += ' '; // replace a break by a whitespace

    charNo = 0; // chars are counted for each line

  } catch( ERR::Failure f ) {
    throw ERR::Failure( f.declare( ).append( " @ line no: " ).append( _strTool->doI2S( lineNo ) ).append( " @ char pos: " ).append( _strTool->doI2S( charNo ) ) );
  } catch( ERR::Error e  ) {
    throw ERR::Error( e.declare( ).append( " @ line no: " ).append( _strTool->doI2S( lineNo ) ) );
  } catch( std::exception e ) {
    throw e;
  } // try

  _handler->endDocument( ); // called for ending the document

} // Parser::parseBuffer

/******************************************************************************/

void /// parses XML from file and calls handler's virtual functions
Parser::parseFile( String fileName ) {

  FileStr file;
  file.open( (char*)fileName.c_str( ), std::ios::in );
  if( file.fail( ) ) {
    String failureMsg = "SAX::Parser::parseFile - can not open file: ";
    throw ERR::Failure( failureMsg.append( fileName ) );
  } // no file or locked
  Builder builder;
  
  String tag;
  String val;
  bool readTag = false;
  bool readVal = false;
  bool readAll = false;
  String line; // line by line
  int lineNo = 0; // count lines for telling XML file errors
  int charNo = 0; // count charaters for telling XML file errors

  _handler->startDocument( ); // call the handler

  try {

    while( getline( file, line ) ) {

      int lineLength = (int)line.length( );
      if( lineLength > 0 ) { // bug from version 1.0 fixed

        if ( line[ lineLength - 1 ] == '\r' )
          line = line.substr( 0, line.length( ) - 1 );

        line = _strTool->filterTs( line ); // replace tabulator by 2 white spaces

        if( !isprint( line[ 0 ] ) ) {
          file.close( );
          throw ERR::Failure( "SAX::Parser::parseFile - failing on character" );
        } // if

        for( String::iterator i = line.begin( ); i != line.end( ); i++ ) {

          char c = *i; // actual char

          if( c == '>' && !readAll && !readVal ) {
            readTag = false;
            // bool isTagStandAlone = _tokenizer->check4StandAlone( tag );
            bool isTagEnding = _tokenizer->check4Ending( tag );
            Object* element = _tokenizer->convertTag( tag ); /// convert a tag 2 object
            if( element != 0 ) {
              if( !isTagEnding )
                _handler->startObject( element );
              else
                _handler->endObject( element );
              delete element;
              element = 0;
            } //if
            tag.clear( );
          } // if >

          if( c =='<' && readVal && !readTag && !readAll ) {
            readVal = false;
            Object* value = _tokenizer->convertValue( val );
            if( value != 0 ) {
              _handler->characters( value );
              delete value;
              value = 0;
            } // if
            val.clear( );
          } // if < readVal

          if( c =='<' && readTag && !readAll ) {
            String errorMsg = "SAX::Parser::parseFile - XML tag <";
            errorMsg.append( _strTool->trimS( tag ) );
            errorMsg.append( " was not closed by \">\"" );
            throw ERR::Error( errorMsg );
          } // if <bla <fasel

          if( c =='>' && readVal && !readAll ) {
            String errorMsg = "SAX::Parser::parseFile - XML tag after value ";
            errorMsg.append( _strTool->trimS( val ) );
            errorMsg.append( "> has not starting" );
            throw ERR::Error( errorMsg );
          } // if bla> fasel>

          if( readTag ) // if it is a tag
            tag += c; // read from char

          if( readVal ) // if it is a value
            val += c; // read from char

          if( c == '"' && readTag )
            readAll = !readAll; // interchange

          if( c == '<' && !readAll ) // start reading tags
            readTag = true;

          if( c == '>' && !readAll ) // start reading values
            readVal = true;

          charNo++; // position of next char

        } // for c

      } // empty lines are ignored

      if( readTag ) // if it is a tag
        tag += ' '; // replace a break by a whitespace

      if( readVal ) // if it is a value
        val += ' '; // replace a break by a whitespace

      charNo = 0; // chars are counted for each line

      lineNo++; // count lines

    } // while

  } catch( ERR::Failure f ) {
    throw ERR::Failure( f.declare( ).append( " @ line no: " ).append( _strTool->doI2S( lineNo ) ).append( " @ char pos: " ).append( _strTool->doI2S( charNo ) ) );
  } catch( ERR::Error e  ) {
    throw ERR::Error( e.declare( ).append( " @ line no: " ).append( _strTool->doI2S( lineNo ) ) );
  } catch( std::exception e ) {
    throw e;
  } // try

  file.close( ); // close written file

  _handler->endDocument( ); // called for ending the document

} // Parser::parseFile

/******************************************************************************/

} // namespace SAX

} // namespace XMLCC

/******************************************************************************/
