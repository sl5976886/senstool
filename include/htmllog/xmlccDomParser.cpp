/** 
 * @file xmlccDomParser.cpp
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

#include "./xmlccDomParser.h" // header

/******************************************************************************/

namespace XMLCC {

namespace DOM {

/******************************************************************************/

/// constructor
Parser::Parser( void ) {
  _grabber   = new DOM::Grabber( );
  _tokenizer = new DOM::Tokenizer( );
  _strTool   = new SYS::StringTool( );
} // Parser

/// destructor
Parser::~Parser( void ) {
  delete _strTool;
  delete _grabber;
  delete _tokenizer;
} // ~Parser

/******************************************************************************/

Object* /// reads buffer of type std::string
Parser::parseBuffer( String buffer ) {

  if( buffer.length( ) <= 0 )
    throw ERR::Failure( "DOM::Parser::parseBuffer - buffer is empty" );
  
  Builder builder;
  String tag;
  String val;
  bool readTag = false;
  bool readVal = false;
  bool readAll = false;
  Object* root = builder.createRoot( ); // create root 
  ListObjects* hList = new ListObjects( 25 ); // extends automatically
  hList->add( root ); // add root already
  Object* element = 0;
  Object* before = 0;
  String line; // line by line
  int lineNo = 0; // count lines for telling XML file errors
  int charNo = 1; // count charaters for telling XML file errors
  int hLevel = 0; // increments and decreases during reading

  try {

    int bufferLength = (int)buffer.length( );
    if( bufferLength > 0 ) { // bug from version 1.0 fixed

      if ( buffer[ bufferLength - 1 ] == '\r' )
        buffer = buffer.substr( 0, buffer.length( ) - 1 );

      buffer = _strTool->filterTs( buffer ); // replace tabulator by 2 white spaces

      if( !isprint( buffer[ 0 ] ) ) {
        delete root; // free memory
        throw ERR::Failure( "DOM::Parser::parseBuffer - failing on character" );
      } // if

      for( String::iterator i = buffer.begin( ); i != buffer.end( ); i++ ) {

        char c = *i; // actual char

        if( c == '>' && !readAll && !readVal ) {
          readTag = false;
          Object* next = _tokenizer->convertTag( tag ); /// convert a tag 2 object
          if( hLevel > 0 ) {
            bool isTagEnding = _tokenizer->check4Ending( tag );
            if( !isTagEnding ) {
              if( _grabber->check4Comment( next ) ) {
                element->addObject( next );
              } else {

                bool isTagStandAlone = _tokenizer->check4StandAlone( tag );

                int noOfValues = _grabber->getNoOfValues( before );

                if( noOfValues == 0 && !isTagStandAlone ) { // here is no hierarchy

                  element->addObject( next );
                  int hListSize = hList->size( );

                  if( ( hLevel + 1 ) < hListSize )
                    hList->set( hLevel+1, next );
                  else
                    hList->add( next );

                  element = next;
                  before = next;
                  hLevel++;

                } else { // here no hierarchy

                  Object* last = hList->get( hLevel );
                  last->addObject( next );

                  if( !isTagStandAlone ) {

                    hList->set( hLevel + 1, next );
                    element = next;
                    before = last;
                    hLevel++;

                  } // if it is not stand alone

                } // no values && !standalone

              } // if it is comment

            } else { // ending tag goes here change hierarchy

              if( next != 0 ) { // neve ever

               delete next;
               next = 0;

              } // if

              hLevel--;
              Object* last = hList->get( hLevel );
              element = last;
              before = last;

            } // if isTagEnding

          } else {

            if( hLevel == 0 && _grabber->check4Header( next ) ) {

              root->addObject( next );

            } if( hLevel == 0 && _grabber->check4Comment( next ) ) {

              root->addObject( next );

            } if( hLevel == 0 && _grabber->check4Element( next ) ) {

              root->addObject( next );
              hList->add( next );
              hLevel++;
              element = next;
              before = next;
            } // if

          } // if
          tag.clear( );
        } // if hLevel > 0

        if( c =='<' && readVal && !readTag && !readAll ) {

          readVal = false;
          Object* value = _tokenizer->convertValue( val );

          if( value != 0 )
            element->addObject( value ); // element is the one from before

          val.clear( );

        } // if < readVal

        if( c =='<' && readTag && !readAll ) {

          String errorMsg = "DOM::Parser::parseBuffer - XML tag <";
          errorMsg.append( _strTool->trimS( tag ) );
          errorMsg.append( " was not closed by \">\"" );
          throw ERR::Error( errorMsg );

        } // if <bla <fasel

        if( c =='>' && readVal && !readAll ) {

          String errorMsg = "DOM::Parser::parseBuffer - XML tag after value ";
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

  } catch( ERR::Failure f ) {
    delete root;
    throw ERR::Failure( f.declare( ).append( " @ line no: " ).append( _strTool->doI2S( lineNo ) ).append( " @ char pos: " ).append( _strTool->doI2S( charNo ) ) );
  } catch( ERR::Error e  ) {
    delete root;
    throw ERR::Error( e.declare( ).append( " @ line no: " ).append( _strTool->doI2S( lineNo ) ) );
  } catch( std::exception e ) {
    delete root;
    throw e;
  } // try

  root = hList->get( 0 ); // get root
  delete hList; // free hierarchical list
  return root; // return root

} // Parser::parseBuffer

/******************************************************************************/

Object*  /// reads buffer of type char*
Parser::parseBuffer( char* buffer ) {
  return parseBuffer( String( buffer ) );
} //Parser::parseBuffer

/******************************************************************************/

OBJ::Root* /// reads XML file and returns root object
Parser::parseFile( String fileName ) {

  FileStr file;
  file.open( (char*)fileName.c_str( ), std::ios::in );
  if( file.fail( ) ) {
    String failureMsg = "Parser::parseFile - can not open file: ";
	  throw ERR::Failure( failureMsg.append( fileName ) );
  } // no file or locked
  Builder builder;
  
  String tag;
  String val;
  bool readTag = false;
  bool readVal = false;
  bool readAll = false;
  OBJ::Root* root = builder.createRoot( fileName ); // create root 
  ListObjects* hList = new ListObjects( 25 ); // extends automatically
  hList->add( root ); // add root already
  Object* element = 0;
  Object* before = 0;
  String line; // line by line
  int lineNo = 0; // count lines for telling XML file errors
  int charNo = 1; // count charaters for telling XML file errors
  int hLevel = 0; // increments and decreases during reading

  try {

    while( getline( file, line ) ) {

      int lineLength = (int)line.length( );
      if( lineLength > 0 ) { // bug from version 1.0 fixed

        if ( line[ lineLength - 1 ] == '\r' )
          line = line.substr( 0, line.length( ) - 1 );

        line = _strTool->filterTs( line ); // replace tabulator by 2 white spaces

        if( !isprint( line[ 0 ] ) ) {
          file.close( );
          delete root; // free memory
          throw ERR::Failure( "DOM::Parser::parseFile - failing on character" );
        } // if

        for( String::iterator i = line.begin( ); i != line.end( ); i++ ) {

          char c = *i; // actual char

          if( c == '>' && !readAll && !readVal ) {
            readTag = false;
            Object* next = _tokenizer->convertTag( tag ); /// convert a tag 2 object
            if( hLevel > 0 ) {
              bool isTagEnding = _tokenizer->check4Ending( tag );
              if( !isTagEnding ) {
                if( _grabber->check4Comment( next ) ) {
                  element->addObject( next );
                } else {
                  bool isTagStandAlone = _tokenizer->check4StandAlone( tag );
                  int noOfValues = _grabber->getNoOfValues( before );
                  if( noOfValues == 0 && !isTagStandAlone ) { // here is no hierarchy
                    element->addObject( next );
                    int hListSize = hList->size( );
                    if( hLevel+1 < hListSize )
                      hList->set( hLevel+1, next );
                    else
                      hList->add( next );
                    element = next;
                    before = next;
                    hLevel++;
                  } else { // here no hierarchy
                    Object* last = hList->get( hLevel );
                    last->addObject( next );
                    if( !isTagStandAlone ) {
                      hList->set( hLevel+1, next );
                      element = next;
                      before = last;
                      hLevel++;
                    } // if it is not stand alone
                  } // no values && !standalone
                } // if it is comment
              } else { // ending tag goes here change hierarchy
                if( next != 0 ) { // neve ever
                 delete next;
                 next = 0;
                } // if
                hLevel--;
                Object* last = hList->get( hLevel );
                element = last;
                before = last;
              } // if isTagEnding
            } else {
              if( hLevel == 0 && _grabber->check4Header( next ) ) {
                root->addObject( next );
              } if( hLevel == 0 && _grabber->check4Comment( next ) ) {
                root->addObject( next );
              } if( hLevel == 0 && _grabber->check4Element( next ) ) {
                root->addObject( next );
                hList->add( next );
                hLevel++;
                element = next;
                before = next;
              } // if
            } // if
            tag.clear( );
          } // if hLevel > 0

          if( c =='<' && readVal && !readTag && !readAll ) {
            readVal = false;
            Object* value = _tokenizer->convertValue( val );
            if( value != 0 )
              element->addObject( value ); // element is the one from before
            val.clear( );
          } // if < readVal

          if( c =='<' && readTag && !readAll ) {
            String errorMsg = "DOM::Parser::parseFile - XML tag <";
            errorMsg.append( _strTool->trimS( tag ) );
            errorMsg.append( " was not closed by \">\"" );
            throw ERR::Error( errorMsg );
          } // if <bla <fasel

          if( c =='>' && readVal && !readAll ) {
            String errorMsg = "DOM::Parser::parseFile - XML tag after value ";
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
    delete root;
    throw ERR::Failure( f.declare( ).append( " @ line no: " ).append( _strTool->doI2S( lineNo ) ).append( " @ char pos: " ).append( _strTool->doI2S( charNo ) ) );
  } catch( ERR::Error e  ) {
    delete root;
    throw ERR::Error( e.declare( ).append( " @ line no: " ).append( _strTool->doI2S( lineNo ) ) );
  } catch( std::exception e ) {
    delete root;
    throw e;
  } // try

  file.close( ); // close written file
  root = (OBJ::Root*)hList->get( 0 ); // get root
  delete hList; // free hierarchical list
  return root; // return root

} // Parser::parseFile

/******************************************************************************/

} // namespace DOM 

} // namespace XMLCC

/******************************************************************************/
