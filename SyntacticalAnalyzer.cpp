/*******************************************************************************
* Assignment: Project 2 - Syntactical Analyzer for Scheme to C++ Translator    *
* Author: Dr. Watts                                                            *
* Date: Fall 2017                                                              *
* File: LexicalAnalyzer.h                                                      *
*                                                                              *
* Description: This file contains the                                          *
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include "SyntacticalAnalyzer.h"

using namespace std;

/*******************************************************************************
* Function: Constructor                                                        *
*                                                                              *
* Parameters: a filename                                                       *
* Return value: N/A                                                            *
* Description: This function will initialize our syntactical analyzer          *
*******************************************************************************/
SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
  lex = new LexicalAnalyzer (filename);
  string name = filename;
  string p2name = name.substr (0, name.length()-3) + ".p2"; 
  p2file.open (p2name.c_str());
  string p3name = name.substr(0, name.length()-3) + ".cpp";
  cppout.open (p3name.c_str());
  token = lex->GetToken();
  
  // Fill firsts sets
  /*
    defineFirsts.insert(LPAREN_T);
    moreDefinesFirsts.insert(LPAREN_T);
    token_type stmtFirsts [] = { IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T };
    statementFirsts.insert (stmtFirsts, stmtFirsts+5);
    statementListFirsts.insert (stmtFirsts, stmtFirsts+5); // same as stmt firsts
    token_type litFirsts [] = { NUMLIT_T, STRLIT_T, QUOTE_T };
    literalFirsts.insert (litFirsts, litFirsts+3);
    token_type more_tokensFirsts [] = { LPAREN_T, IDENT_T, NUMLIT_T, STRLIT_T, CONS_T,
        IF_T, DISPLAY_T, NEWLINE_T, LISTOP_T, AND_T, OR_T, NOT_T, DEFINE_T, NUMBERP_T,
        SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T,
        MODULO_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, QUOTE_T };
    moreTokensFirsts.insert (more_tokensFirsts, more_tokensFirsts+29);
    paramListFirsts.insert(IDENT_T);
    elsePartFirsts.insert (stmtFirsts, stmtFirsts+5); // same as stmt firsts
    statementPairFirsts.insert(IDENT_T);
    token_type stmt_pair_bodyFirsts [] = { LPAREN_T, IF_T, COND_T, LISTOP_T, CONS_T, AND_T,
        OR_T, NOT_T, NUMBERP_T, SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T,
        MINUS_T, DIV_T, MULT_T, MODULO_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, IDENT_T,
        DISPLAY_T, NEWLINE_T, NUMLIT_T, STRLIT_T, QUOTE_T };
    statementPairBodyFirsts.insert (stmt_pair_bodyFirsts, stmt_pair_bodyFirsts+30);
    morePairsFirsts.insert(LPAREN_T);
    token_type actFirsts [] = { IF_T, COND_T, LISTOP_T, CONS_T, AND_T, OR_T, NOT_T, NUMBERP_T,
        SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T,
        MODULO_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, IDENT_T, DISPLAY_T, NEWLINE_T };
    literalFirsts.insert (actFirsts, actFirsts+26);
    anyOtherTokenFirsts.insert (more_tokensFirsts, more_tokensFirsts+29); // same as more_tokens firsts
    quotedLiteralFirsts.insert(more_tokensFirsts, more_tokensFirsts+29); // same as more_tokens firsts
    
    // Fill follows sets
	defineFollows = {LPAREN_T, EOF_T};
	moreDefinesFollows = {RPAREN_T};
	statementListFollows = {RPAREN_T};
	statementFollows = {IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T, RPAREN_T};
	literalFollows = {RPAREN_T, IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T};
	quotedLiteralFollows = {RPAREN_T, IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T};
	moreTokensFollows = {RPAREN_T};
	paramListFollows = {RPAREN_T};
	elsePartFollows = {RPAREN_T};
	statementPairFollows = {LPAREN_T};
	statementPairBodyFollows = {RPAREN_T};
	morePairsFollows = {RPAREN_T};
	actionFollows = {RPAREN_T};
	anyOtherTokenFollows = {LPAREN_T, IDENT_T, NUMLIT_T, STRLIT_T, CONS_T, IF_T,
				DISPLAY_T, NEWLINE_T, LISTOP_T, AND_T, OR_T, NOT_T, DEFINE_T, 
				NUMBERP_T, SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, 
				PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, EQUALTO_T, GT_T, LT_T, 
				GTE_T, LTE_T, QUOTE_T, RPAREN_T };
     */
    
    // Start the analyzer
	Program ();
}

/*******************************************************************************
* Function: deconstructor                                                      *
*                                                                              *
* Parameters: N/A                                                              *
* Return value: N/A                                                            *
* Description: This function will deconstruct our analyzer                     *
*******************************************************************************/
SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
	p2file.close ();
	cppout.close ();
}

/*******************************************************************************
* Function: Program()                                                          *
*                                                                              *
* Parameters: N/A                                                              *
* Return value: The amout of errors it found                                   *
* Description: This function will follow the <program> item in our grammar     *
*******************************************************************************/
int SyntacticalAnalyzer::Program ()
{
	p2file << "Entering Program function; current token is: "
	       << lex->GetTokenName (token) << ", lexeme: " << lex->GetLexeme() << endl;
    
	int errors = 0;
    
	// token should be in firsts of Program
	// Body of function goes here.
	p2file << "Using Rule 1" << endl;
	cppout << "#include <iostream>\n"
	       << "#include \"Object.h\"\n"
	       << "using namespace std\n";
	
	errors += Define ();
	errors += More_Defines ();
	if (token != EOF_T)
	{
		errors++;
		lex->ReportError ("Missing end of file at end of program");
	}
	// token should be in follows of Program
	p2file << "Exiting Program function; current token is: "
	       << lex->GetTokenName (token) << endl;
	return errors;
}

/*******************************************************************************
 * Function: Define()                                                           *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <define> item in our grammar      *
 *******************************************************************************/
int SyntacticalAnalyzer::Define() 
{
  p2file << "Entering Define function; current token is: "
	 << lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
  
  int errors = 0;
  p2file << "Using Rule 2" << endl;
  
  // token = lex->GetToken();
  if(token != LPAREN_T){
    errors++;
  }
  
  token = lex->GetToken();
  if(token != DEFINE_T){
    errors++;
  }
    
  token = lex->GetToken();
  if(token != LPAREN_T){
    errors++;
  }
  
  token = lex->GetToken();
  if(token != IDENT_T){
    errors++;
  }

  if (lex->GetLexeme() == "main")
    {
      cppout << "int main(";
      isMain = true;
    }
  
  else
    {
      cppout << "Object " << lex->GetLexeme() << "(";
      isMain = false;
    }
  
  token = lex->GetToken();
  errors += Param_List();
  
  cppout << "){\n";
  
  //TODO: go looking for this!!!
  if(token != RPAREN_T){
    errors++;
  }
  
  token = lex->GetToken();
  errors += Statement();
  
  //token = lex->GetToken();
  //errors += Statement_List();
  errors += Statement_List(lex->GetLexeme());
    
  token = lex->GetToken();
  if(token != RPAREN_T){
    errors++;
  }

  if (isMain){
    cppout << "return 0;\n"
	   << "}\n";
  }

  else{
    cppout << "return __RetVal;\n"
	   << "}\n";
  }
  
  p2file << "Exiting Define function; current token is: " << lex->GetTokenName (token) << endl;
  
  return errors;
		
}

/*******************************************************************************
 * Function: More_Defines()                                                     *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <more_defines> item in our grammar*
 *******************************************************************************/
int SyntacticalAnalyzer::More_Defines()
{
	p2file << "Entering More_Defines function; current token is: "
        << lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
    
	int errors = 0;
	if(token == LPAREN_T){
		p2file << "Using Rule 3" << endl;
		errors += Define();
		errors += More_Defines();
		p2file << "Exiting More_Defines function; current token is: "
			<< lex->GetTokenName(token) << endl;
		return errors;	
	}
	
	p2file << "Using Rule 4" << endl;
	p2file << "Exiting More_Defines function; current token is: "
		<< lex->GetTokenName(token) << endl;
	return errors;
}

/*******************************************************************************
 * Function: StatementList()                                                    *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <stmt_list> item in our grammar   *
 *******************************************************************************/
int SyntacticalAnalyzer::Statement_List(string op)
{
	p2file << "Entering Stmt_List function; current token is: "
			<< lex->GetTokenName (token) << ", lexeme: " << lex->GetLexeme() << endl;
    
	int errors = 0;


	if(token == RPAREN_T) {
		p2file << "Using Rule 6" << endl;
		p2file << "Exiting Stmt_List function; current token is: "
					<< lex->GetTokenName (token) << endl;
		first_param = false;
		return errors;
	}
	p2file << "Using Rule 5" << endl;
	errors += Statement();
	if(token == RPAREN_T) {
	  cppout << " " << op << " ";
	}
	errors += Statement_List(op);
	p2file << "Exiting Stmt_List function; current token is: "
			<< lex->GetTokenName(token) << endl;
	return errors;
}

/*******************************************************************************
 * Function: Statement()                                                        *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amount of errors found                                     *
 * Description: This function will follow the <stmt> item in our grammar        *
 *******************************************************************************/
int SyntacticalAnalyzer::Statement () {
	p2file << "Entering Stmt function; current token is: "
			<< lex->GetTokenName (token) << ", lexeme: " << lex->GetLexeme() << endl;
    
	int errors = 0;
	if(token == IDENT_T) {
		p2file << "Using Rule 8" << endl;
		cppout << lex->GetLexeme();
		token = lex->GetToken();
		p2file << "Exiting Stmt function; current token is: "
			<< lex->GetTokenName(token) << endl;
		return errors;
	}

	if(token == LPAREN_T) {
		p2file << "Using Rule 9" << endl;
		cppout << "(";
		token = lex->GetToken();
		errors += Action();
		while(token != RPAREN_T && token != EOF_T) {

			errors++;
			lex->ReportError ("Missing ) after action");
			exit(1);;
			token = lex->GetToken();
		}
		cppout << ")";
		token = lex->GetToken();
	} else {
		p2file << "Using Rule 7" << endl;
		errors += Literal();
	}
	p2file << "Exiting Stmt function; current token is: "
	       << lex->GetTokenName(token) << endl;
	return errors;
}

/*******************************************************************************
 * Function: Literal ()     ***                                                 *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amount of errors found                                     *
 * Description: This function will follow the <literal> item in our grammar     *
 *******************************************************************************/
int SyntacticalAnalyzer::Literal() {
	p2file << "Entering Literal function; current token is: "
			<< lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
    
	int errors = 0;
	bool found = false;
	switch (token) {
		case NUMLIT_T:
			p2file << "Using Rule 10" << endl;
			found = true;
			cppout << "Object (" << lex->GetLexeme() << ")";
			token = lex->GetToken();
			break;
		case STRLIT_T:
			p2file << "Using Rule 11" << endl;
			found = true;
			cppout << "Object (" << lex->GetLexeme() << ")";
			token = lex->GetToken();
			break;
		case QUOTE_T:
			p2file << "Using Rule 12" << endl;
			found = true;
			cppout << "Object (\"" << lex->GetLexeme();
			token = lex->GetToken();
			errors += Quoted_Literal();
			cppout << "\")";
			break;
		default:
			token = lex->GetToken();
			errors++;
			lex->ReportError("Expected literal but not found");
			p2file << "Exiting Literal funciton; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
	}
	
	if (found) {
		p2file << "Exiting Literal function; current token is: " 
			<< lex->GetTokenName(token) << endl;
		return errors;
	}
	p2file << "Exiting Literal function; current token is: "
		<< lex->GetTokenName(token) << endl;
	return errors;
}

/*******************************************************************************
 * Function: Quoted_Literal()                                                   *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <quoted_lit> item in our grammar  *
 *******************************************************************************/
int SyntacticalAnalyzer::Quoted_Literal() {
	int errors = 0;
	p2file << "Entering Quoted_Lit function; current token is: "
			<< lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
	
	p2file << "Using Rule 13" << endl;
	errors += Any_Other_Token();
	p2file << "Exiting Quoted_Lit function; current token is: "
			<< lex->GetTokenName(token) << endl;
	return errors;
}

/*******************************************************************************
 * Function: More_Tokens()                                                      *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <more_tokens> item in our grammar *
 *******************************************************************************/
int SyntacticalAnalyzer::More_Tokens() {
	p2file << "Entering More_Tokens function; current token is: "
			<< lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
    
	int errors = 0;
	if (token == EOF_T){
		errors++;
		// report error
		p2file << "Exiting More_Tokens function; current token is: "
			<< lex->GetTokenName(token) << endl;
		return errors;
	}
	if (token == RPAREN_T) {
		p2file << "Using Rule 15" << endl;
		p2file << "Exiting More_Tokens function; current token is: "
			<< lex->GetTokenName(token) << endl;
		return errors;
	}
	p2file << "Using Rule 14" << endl;
	errors += Any_Other_Token();
	errors += More_Tokens();
	p2file << "Exiting More_Tokens function; current token is: "
		<< lex->GetTokenName(token) << endl;
	return errors;	
}

/*******************************************************************************
 * Function: Param_List()                                                       *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <param_list> item in our grammar  *
 *******************************************************************************/
int SyntacticalAnalyzer::Param_List() {
    p2file << "Entering Param_List function; current token is: "
    << lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
    
    int errors = 0;
    
    if(token == RPAREN_T) {
        p2file << "Using Rule 17" << endl;
        p2file << "Exiting Param_List function; current token is: " << lex->GetTokenName (token) << endl;
        return errors;
    } else {
        while(token != IDENT_T) {
            errors++;
            lex->ReportError ("Error in P List Missing Ident");
            exit(1);
            token = lex->GetToken();
        }
        p2file << "Using Rule 16" << endl;
		if (first_param) {
			cppout << "Object " << lex->GetLexeme() << " ";
			first_param = false;
		}
		else{
			cppout << ",Object " <<lex->GetLexeme()<<" ";
		}
        token = lex->GetToken();
        errors += Param_List();
    }
    
    p2file << "Exiting Param_List function; current token is: "
    << lex->GetTokenName(token) << endl;
    return errors;
}

/*******************************************************************************
 * Function: Else_Part()                                                        *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <else_part> item in our grammar   *
 *******************************************************************************/
int SyntacticalAnalyzer::Else_Part() {
	
	p2file << "Entering Else_Part function; current token is: "
			<< lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
    
	int errors = 0;
	if (token == EOF_T) {
		errors++;
		// report error
		p2file << "Exiting Else_Part function; current token is: "
			<< lex->GetTokenName(token) << endl;
		return errors;
	}
	if (token == RPAREN_T) {
		p2file << "Using Rule 19" << endl;
		p2file << "Exiting Else_Part function; current token is: "
			<< lex->GetTokenName(token) << endl;
		return errors;
	}

	p2file << "Using Rule 18" << endl;
	errors += Statement();
	p2file << "Exiting Else_Part function; current token is: "
		<< lex->GetTokenName(token) << endl;
	return errors;	
}

/*******************************************************************************
 * Function: Statement_Pair()         ***                                       *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <stmt_pair> item in our grammar   *
 *******************************************************************************/
int SyntacticalAnalyzer::Statement_Pair() {


	p2file << "Entering Stmt_Pair function; current token is: "
			<< lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
    
	int errors = 0;
	while (token != LPAREN_T){
		errors ++;
		lex->ReportError("Does not look; No ");
		exit(1);;
		token = lex->GetToken();	
	}
	cppout << "if (";
	token = lex->GetToken();
	p2file << "Using Rule 20" << endl;
	errors	+= Statement_Pair_Body();
	while (token != RPAREN_T){
		errors++;
		lex->ReportError("Does not look good; No ");
		exit(1);;
		token = lex->GetToken();
	}
	token = lex->GetToken();
	p2file << "Exiting Stmt_Pair function; current token is: "
			<< lex->GetTokenName(token) << endl;
	return errors;
}

/*******************************************************************************
 * Function: Statement_Pair_Body()                                              *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <stmt_pair_body>                  *
 *              item in our grammar                                             *
 *******************************************************************************/
int SyntacticalAnalyzer::Statement_Pair_Body() {
    p2file << "Entering Stmt_Pair_Body function; current token is: "
    << lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
    
    int errors = 0;
    
    if(token == LPAREN_T) {
        p2file << "Using Rule 21" << endl;
        token = lex->GetToken();
        errors += Action();
        
        while(token != RPAREN_T ) {
            errors++;
            lex->ReportError ("Missing a ) ");
            exit(1);;
            token = lex->GetToken();
        }
		cppout <<"){\n";
        token = lex->GetToken();
        errors += Statement();
		cppout << "}\n";
    } else if(token == NUMLIT_T || token == STRLIT_T || token == QUOTE_T) {
        p2file << "Using Rule 23" << endl;
        errors += Literal();
        cppout << ")\n";
    } else {
        p2file << "Using Rule 22" << endl;
        errors += Action();
        cppout << ")\n";
    }
    p2file << "Exiting Stmt_Pair_Body function; current token is: "
    << lex->GetTokenName(token) << endl;
    return errors;
}

/*******************************************************************************
 * Function: More_Pairs()                                                       *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <more_pairs> item in our grammar  *
 *******************************************************************************/
int SyntacticalAnalyzer::More_Pairs() {
	p2file << "Entering More_Pairs function; current token is: "
			<< lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
	int errors = 0;
	if (token == EOF_T){
		errors++;
		lex->ReportError("Missing right parentheses");
		p2file << "Exiting More_Pairs function; current token is: "
			<< lex->GetTokenName(token) << endl;
		return errors;
	}
	if (token == RPAREN_T){
		p2file << "Using Rule 25" << endl;
		p2file << "Exiting More_Pairs function; current token is: "
			<< lex->GetTokenName(token) << endl;
		return errors;
	}

	p2file << "Using Rule 24" << endl;
	errors += Statement_Pair();
	errors += More_Pairs();
	p2file << "Exiting More_Pairs function; current token is: "
			<< lex->GetTokenName(token) << endl;
	return errors;	
}

/*******************************************************************************
 * Function: Action()                                                           *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <action> item in our grammar      *
 *******************************************************************************/
int SyntacticalAnalyzer::Action() {
	p2file << "Entering Action function; current token is: "
        << lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
	int errors = 0;

	switch(token) {
		case IF_T :
			p2file << "Using Rule 26" << endl;
			cppout << "if (";
			token = lex->GetToken();
			errors += Statement();
			cppout << "){\n";
			errors += Statement();
			cppout << "}\nelse{\n";
			errors += Else_Part();
			cppout << "}\n";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case COND_T :
			p2file << "Using Rule 27" << endl;
			token = lex->GetToken();
			errors += Statement_Pair();
			errors += More_Pairs();
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case LISTOP_T :
			p2file << "Using Rule 28" << endl;
			token = lex->GetToken();
			cppout << lex->GetLexeme() << "(";
			errors += Statement();
			cppout << ");\n";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case CONS_T :
			p2file << "Using Rule 29" << endl;
			cppout << "cons(";
			token = lex->GetToken();
			errors += Statement();
			cppout << ", ";
			errors += Statement();
			cppout << ");\n";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case AND_T :
			p2file << "Using Rule 30" << endl;
			token = lex->GetToken();
			errors += Statement_List("&&");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case OR_T :
			p2file << "Using Rule 31" << endl;
			token = lex->GetToken();
			errors += Statement_List("||");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case NOT_T :
			p2file << "Using Rule 32" << endl;
			token = lex->GetToken();
            cppout << "!(";
			errors += Statement();
            cppout << ")";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
        
        //unsure how to use object class for these
		case NUMBERP_T :
			p2file << "Using Rule 33" << endl;
			token = lex->GetToken();
			cppout << "Object(";
			errors += Statement();
			cppout << ").isNumber()";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case SYMBOLP_T :
			p2file << "Using Rule 34" << endl;
			cppout << "Object(";
			token = lex->GetToken();
			errors += Statement();
			cppout << ").isSymbol()";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case LISTP_T :
			p2file << "Using Rule 35" << endl;
			cppout << "Object(";
			token = lex->GetToken();
			errors += Statement();
			cppout << ").isList()";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case ZEROP_T :
			p2file << "Using Rule 36" << endl;
			cppout << "Object(";
			token = lex->GetToken();
			errors += Statement();
			cppout << ").isZero()";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case NULLP_T :
			p2file << "Using Rule 37" << endl;
			token = lex->GetToken();
			errors += Statement();
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case STRINGP_T :
			p2file << "Using Rule 38" << endl;
			cppout << "Object(";
			token = lex->GetToken();
			errors += Statement();
			cppout << ").isString()";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
        // end unsure
            
		case PLUS_T :
			p2file << "Using Rule 39" << endl;
			token = lex->GetToken();
			errors += Statement_List("+");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case MINUS_T :
			p2file << "Using Rule 40" << endl;
			token = lex->GetToken();
			cppout << "-";
			errors += Statement_List("-");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case DIV_T :
			p2file << "Using Rule 41" << endl;
			token = lex->GetToken();
			errors += Statement();
			errors += Statement_List("/");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case MULT_T :
			p2file << "Using Rule 42" << endl;
			token = lex->GetToken();
			errors += Statement_List("*");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case MODULO_T :
			p2file << "Using Rule 43" << endl;
			token = lex->GetToken();
			errors += Statement();
            cppout << " % ";
			errors += Statement();
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case EQUALTO_T :
			p2file << "Using Rule 44" << endl;
			token = lex->GetToken();
			errors += Statement_List("==");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case GT_T :
			p2file << "Using Rule 45" << endl;
			token = lex->GetToken();
			errors += Statement_List(">");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case LT_T :
			p2file << "Using Rule 46" << endl;
			token = lex->GetToken();
			errors += Statement_List("<");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case GTE_T :
			p2file << "Using Rule 47" << endl;
			token = lex->GetToken();
			errors += Statement_List(">=");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case LTE_T :
			p2file << "Using Rule 48" << endl;
			token = lex->GetToken();
			errors += Statement_List("<=");
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case IDENT_T :
			p2file << "Using Rule 49" << endl;
			cppout << lex->GetLexeme() << " ";
			token = lex->GetToken();
			errors += Statement_List(lex->GetLexeme());
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case DISPLAY_T :
			p2file << "Using Rule 50" << endl;
            cppout << "cout << ";
			token = lex->GetToken();
			errors += Statement();
			cppout << ";\n";
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		case NEWLINE_T :
			p2file << "Using Rule 51" << endl;
            cppout << "cout << endl;";
			token = lex->GetToken();
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
		default:
			errors++;
			lex->ReportError ("Failed to find good action");
			token = lex->GetToken();
			p2file << "Exiting Action function; current token is: "
				<< lex->GetTokenName(token) << endl;
			return errors;
	}

}

/*******************************************************************************
 * Function: Any_Other_Token()                                                  *
 *                                                                              *
 * Parameters: N/A                                                              *
 * Return value: The amout of errors it found                                   *
 * Description: This function will follow the <any_other_token>                 *
 *              item in our grammar                                             *
 *******************************************************************************/
int SyntacticalAnalyzer::Any_Other_Token() {
    p2file << "Entering Any_Other_Token function; current token is: "
    << lex->GetTokenName(token) << ", lexeme: " << lex->GetLexeme() << endl;
    int errors = 0;
   // bool found = false;
    if (token == LPAREN_T){
        token = lex->GetToken();
        p2file << "Using Rule 52" << endl;
        errors += More_Tokens();
        while (token != RPAREN_T && token != EOF_T){
            errors++;
            lex->ReportError("Missing right parentheses");
            exit(1);
        }
        token = lex->GetToken();
        p2file << "Exiting Any_Other_Token function; current token is: "
        << lex->GetTokenName(token) << endl;
        return errors;
    }
    else{
        switch (token) {
            case IDENT_T:
               // found = true;
                p2file << "Using Rule 53" << endl;
                break;
            case NUMLIT_T:
               // found = true;
                p2file << "Using Rule 54" << endl;
                break;
            case STRLIT_T:
               // found = true;
                p2file << "Using Rule 55" << endl;
                break;
            case CONS_T:
               // found = true;
                p2file << "Using Rule 56" << endl;
                break;
            case IF_T:
              //  found = true;
                p2file << "Using Rule 57" << endl;
                break;
            case DISPLAY_T:
               // found = true;
                p2file << "Using Rule 58" << endl;
                break;
            case NEWLINE_T:
               // found = true;
                p2file << "Using Rule 59" << endl;
                break;
            case LISTOP_T:
               // found = true;
                p2file << "Using Rule 60" << endl;
                break;
            case AND_T:
               // found = true;
                p2file << "Using Rule 61" << endl;
                break;
            case OR_T:
               // found = true;
                p2file << "Using Rule 62" << endl;
                break;
            case NOT_T:
               // found = true;
                p2file << "Using Rule 63" << endl;
                break;
            case DEFINE_T:
               // found = true;
                p2file << "Using Rule 64" << endl;
                break;
            case NUMBERP_T:
               // found = true;
                p2file << "Using Rule 65" << endl;
                break;
            case SYMBOLP_T:
               // found = true;
                p2file << "Using Rule 66" << endl;
                break;
            case LISTP_T:
               // found = true;
                p2file << "Using Rule 67" << endl;
                break;
            case ZEROP_T:
               // found = true;
                p2file << "Using Rule 68" << endl;
                break;
            case NULLP_T:
                //found = true;
                p2file << "Using Rule 69" << endl;
                break;
            case STRINGP_T:
               // found = true;
                p2file << "Using Rule 70" << endl;
                break;
            case PLUS_T:
               // found = true;
                p2file << "Using Rule 71" << endl;
                break;
            case MINUS_T:
               // found = true;
                p2file << "Using Rule 72" << endl;
                break;
            case DIV_T:
               // found = true;
                p2file << "Using Rule 73" << endl;
                break;
            case MULT_T:
               // found = true;
                p2file << "Using Rule 74" << endl;
                break;
            case MODULO_T:
               // found = true;
                p2file << "Using Rule 75" << endl;
                break;
            case EQUALTO_T:
               // found = true;
                p2file << "Using Rule 76" << endl;
                break;
            case GT_T:
               //found = true;
                p2file << "Using Rule 77" << endl;
                break;
            case LT_T:
               // found = true;
                p2file << "Using Rule 78" << endl;
                break;
            case GTE_T:
               // found = true;
                p2file << "Using Rule 79" << endl;
                break;
            case LTE_T:
               // found = true;
                p2file << "Using Rule 80" << endl;
                break;
            case QUOTE_T:
                token = lex->GetToken();
                errors += Any_Other_Token();
               // found = true;
                p2file << "Using Rule 81" << endl;
                break;
            default:
                errors++;
                lex->ReportError("Ya dun goofed");
                token = lex->GetToken();
                p2file << "Exiting Any_Other_Token function; current token is: "
                << lex->GetTokenName(token) << endl;
                return errors;
        }
    }
	cppout << lex->GetLexeme() << " ";
    token = lex->GetToken();
    p2file << "Exiting Any_Other_Token function; current token is: "
		<< lex->GetTokenName(token) << endl;
    return errors;

}
