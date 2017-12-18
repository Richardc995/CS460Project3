/*******************************************************************************
* Assignment: Project 1 - Lexical Analyzer for Scheme to C++ Translator        *
* Author: Dr. Watts                                                             *
* Date: Fall 2017                                                              *
* File: LexicalAnalyzer.h                                                      *
*                                                                              *
* Description: This file contains the                                          *
*******************************************************************************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include <set>
#include "LexicalAnalyzer.h"

using namespace std;

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    private:
	LexicalAnalyzer * lex;
	ofstream p2file;
	ofstream cppout;
	token_type token;

	bool first_param;
	int Program ();
	int Define ();
	int More_Defines ();
	int Statement_List ();
	int Statement_List (string op);
	int Statement ();
	int Literal ();
	int Quoted_Literal ();
	int More_Tokens ();
	int Param_List ();
	int Else_Part ();
	int Statement_Pair ();
	int Statement_Pair_Body ();
	int More_Pairs ();
	int Action ();
	int Any_Other_Token ();

	bool isMain = false;
	bool isDisplay = false;
	
    // Firsts sets
    /*
    set<token_type> defineFirsts;
    set<token_type> moreDefinesFirsts;
    set<token_type> statementFirsts;
    set<token_type> statementListFirsts;
    set<token_type> literalFirsts;
    set<token_type> quotedLiteralFirsts;
    set<token_type> moreTokensFirsts;
    set<token_type> paramListFirsts;
    set<token_type> elsePartFirsts;
    set<token_type> statementPairFirsts;
    set<token_type> statementPairBodyFirsts;
    set<token_type> morePairsFirsts;
    set<token_type> actionFirsts;
    set<token_type> anyOtherTokenFirsts;
    
	set<token_type> defineFollows;
	set<token_type> moreDefinesFollows;
	set<token_type> statementListFollows;
	set<token_type> statementFollows;
	set<token_type> literalFollows;
	set<token_type> quotedLiteralFollows;
	set<token_type> moreTokensFollows;
	set<token_type> paramListFollows;
	set<token_type> elsePartFollows;
	set<token_type> statementPairFollows;
	set<token_type> statementPairBodyFollows;
	set<token_type> morePairsFollows;
	set<token_type> actionFollows;
	set<token_type> anyOtherTokenFollows;*/
    

};
	
#endif
