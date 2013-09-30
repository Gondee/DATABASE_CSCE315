
#include "Parser.h"
#include <sstream>
#include <iostream>


int Parse::Tokenize(string s)
{
    CURRENT_TOKEN ="";
    POSITION = 0; //empty token
    TOKENS.clear(); //make sure empty if instance is used twice
    INPUT = s;
    
    //while(POSITION != INPUT.size())
        //getToken(); //Do not call before ...
   
    
}


bool Parse::getToken()
{
    //cout<<INPUT.size()<<" - "<<POSITION<<endl;
    CURRENT_TOKEN = "";
    if(INPUT.size() == POSITION)
    {   
        //return false;
    }
    
    if(INPUT.at(POSITION) == ' ') //white space
    {
        POSITION++;
        //tokens.push_back(" "); don't push back whitespace for now
    }
    
    if(INPUT.at(POSITION) == '(')
    {
        CURRENT_TOKEN = "(";
        TOKENS.push_back(CURRENT_TOKEN);
        POSITION++;
        return true;
    }
    
    if(INPUT.at(POSITION) == ')')
    {
        CURRENT_TOKEN = ")";
        TOKENS.push_back(CURRENT_TOKEN);
        POSITION++;
        return true;
    }
    
    if(INPUT.at(POSITION) == ';')
    {
        CURRENT_TOKEN = ";";
        TOKENS.push_back(CURRENT_TOKEN);
        POSITION++;
        return true;
    }
    
    if(INPUT.at(POSITION) == ',')
    {
        CURRENT_TOKEN = ",";
        TOKENS.push_back(CURRENT_TOKEN);
        POSITION++;
        return true;
    }
    
    if(INPUT.at(POSITION) == '(')
    {
        CURRENT_TOKEN = "(";
        TOKENS.push_back(CURRENT_TOKEN);
        POSITION++;
        return true;
    }
    if(INPUT.at(POSITION) == '"') //Group whats inside the parentesis into one token
    {
        CURRENT_TOKEN = "\"";
        POSITION++;
        
        bool Par_Statement = true;
        while (Par_Statement)
        {
            if(INPUT.size() != POSITION && INPUT.at(POSITION) != '\"' && Par_Statement == true)
            {  
                
              CURRENT_TOKEN += INPUT.at(POSITION);  
              POSITION++;
              
              if(INPUT.size() == POSITION)//End of line, ERROR
              {
                  cout<<"BAD INPUT: Missing matching parenthesis!"<<endl;
                  return false;
                  
              }
              
              if(INPUT.at(POSITION) == '\"') //found second parenthesis
              {
                  Par_Statement = false;
                  
              }
                          
            }//end of master if
 
        }//End of while
        
        CURRENT_TOKEN += INPUT.at(POSITION);
        POSITION++;
        TOKENS.push_back(CURRENT_TOKEN);
          
        return true;
    }//end of PARENTHESIS FINDING
    
    
    while(true) //For tokens that are not critical characters 
    {
        
    
        while(INPUT.at(POSITION) != ' ' && INPUT.at(POSITION) != '(' && INPUT.at(POSITION) != ')' &&
                INPUT.at(POSITION) != ';' && INPUT.at(POSITION) != ',')
        {
            
            CURRENT_TOKEN += INPUT.at(POSITION);
            POSITION++;
            
            if(INPUT.length() <= POSITION)
            {
                cout<<"\n SEMICOLON REQUIRED TO END LINE"<<endl;
                return false;
            }
            
        }
        
        if(INPUT.size() == INPUT.at(POSITION))
        {
            TOKENS.push_back(CURRENT_TOKEN);
            return true;
        }
        
        if(INPUT.at(POSITION) == ' ') //white space
        {
           TOKENS.push_back(CURRENT_TOKEN);
           return true; 
            
        }
    
        if(INPUT.at(POSITION) == '(')
        {
            TOKENS.push_back(CURRENT_TOKEN);
            return true;
        }
        
        if(INPUT.at(POSITION) == ')')
        {
            TOKENS.push_back(CURRENT_TOKEN);
            return true;
        }
        
        if(INPUT.at(POSITION) == ';')
        {
            TOKENS.push_back(CURRENT_TOKEN);
            return true;
        }
        
        if(INPUT.at(POSITION) == ',')
        {
            TOKENS.push_back(CURRENT_TOKEN);
            return true;
        }
        
        if(INPUT.at(POSITION) == '(')
        {
            TOKENS.push_back(CURRENT_TOKEN);
            return true;
        }
    
    
    }//End of while
    
    return 1; //something went wrong
}

bool Parse::Expecting(string s)
{
    if(Validate(s) == true)//Making sure command is valid ->Validate()
        return true;
    
    else 
        return false;//String was not valid command as checked in function
    
}
    

bool Parse::Validate(string s)
{
    //Returning true if current token matches expected string
    //This function allows command strings to be changed in respective functions
    if(s == CURRENT_TOKEN)
    {
        getToken();
        return true;
        
    }
    else 
        return false; //input does not match a command/query
    
}


bool Parse::Begin_Parse()
 {
     //cout<<"(Begin Parse) Parsing starting..."<<endl;
     getToken();//Loading a token into the Current Token
     
     if(Command_Check())
     {
         if(TOKENS[TOKENS.size()-1] != ";") //End of line may be current or next character
         {
             getToken();
             if(CURRENT_TOKEN == ";")
                 return true;//Command Line done, everything worked
         }
         return true; //Not sure if that belongs yet
         
     }
     if(Query_Check())
     {  
         
         //getToken(); //Gets name of thing being queeried
         //Expression();
     }
     
     
     return false; //Statement is nothing, skip
 }
 
 bool Parse::Command_Check()
 {
     //If any of the checks return true, then statement is a command
    if(C_Close()==true)
        return true;
    if(C_Write() ==true)
        return true;
    if(C_Exit() == true)
        return true;
    if(C_Show() == true)
        return true;
    if(C_Create()==true)
        return true;
    if(C_Update()==true)
        return true;
    if(C_Insert()==true)
        return true;
    if(C_Delete()==true)
        return true;
    if(C_Open()==true)
        return true;
     
     
     return false; //Not a command
 }
 
 bool Parse::Query_Check()
 {
     //cout<<"Potential Query"<<endl;
     if(RelationsWord())
     {
         //getToken();
         if(Validate("<-"))
         {
             //cout<<"TOKEN: "<<CURRENT_TOKEN<<endl;
             if(RelationsWord())
             {
                 
                 bool temp = false;
                 if(Expecting("*"))
                 {
                     //cout<<"Query * found"<<endl;
                     temp = true;
                     RelationsWord();
                     return true;;
                     
                 }
                 if(Expecting("+"))
                 {
                     //cout<<"Query + found"<<endl;
                     temp = true;
                     RelationsWord();
                     return true;
                     
                 }
                 if(Expecting("-"))
                 {
                     //cout<<"Query - found"<<endl;
                     temp = true;
                     RelationsWord();
                     return true;
                     
                 }
                 
                 TOKENS.erase(TOKENS.begin()+POSITION);
                 POSITION--;                    //Moving back if no signs were found
                 CURRENT_TOKEN = TOKENS.back();
                 //cout<<"TOKEN: "<<CURRENT_TOKEN<<endl;
                 
             }
             
             
            //cout<<"Query found"<<endl; 
            return Expression();
         }
     }
     
  return false;   
 }
 

bool Parse::C_Close() //Done
{
    if(Validate("CLOSE"))
    {
        return RelationsWord();
    }
    return false;

}
bool Parse::C_Write() //Done
{
    if(Validate("WRITE"))
    {
        return RelationsWord();
    }
    return false; //if not a relation after WRITE

}
bool Parse::C_Open() //Done
{
    if(Validate("OPEN"))
    {
        return RelationsWord();
    }
    return false; //if not a relation after WRITE

}
bool Parse::C_Exit() //Done
{
    if(Validate("EXIT"))
    {
        return true;
    }
    return false;

}
bool Parse::C_Show() 
{
    if(Validate("SHOW"))
    {
        if(AtomicExpr())
        {
            return true;
        }
    }
    return false;
}
bool Parse::C_Create()
{
    if(Validate("CREATE"))
    {
        //CREATE TABLE enemies (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);
        Expecting("TABLE");
        if(RelationsWord())
        {
            Expecting("(");
            
            if(Create_AttList())
            {
               Expecting(")");
               Expecting("PRIMARY");
               Expecting("KEY");
               Expecting("(");
               
               if(ListedAttributes())
               {
                   return true;
               }
               
                
            }
            
        }
    }
    return false;
}



bool Parse::C_Update()
{
    if(Validate("UPDATE"))
    {
        //UPDATE dots SET x1 = 0 WHERE x1 < 0;
        if(RelationsWord())
        {
            Expecting("SET");
            if(RelationsWord())
            {
                Operation();
                RelationsWord();
                if(Expecting("WHERE"))
                {
                    RelationsWord();
                    if(Operation())
                    {
                    RelationsWord();
                    return true;
                    }
                    
                }
            }
        }
        
    }
    return false;

}


bool Parse::C_Insert()
{
    if(Validate("INSERT"))
    {
        //cout<<CURRENT_TOKEN<<endl;
        Validate("INTO");
        //cout<<CURRENT_TOKEN<<endl;
        if(RelationsWord())
        {
            //cout<<CURRENT_TOKEN<<endl;
            Expecting("VALUES");
            Expecting("FROM");
            if(Expecting("("))
            {
                //cout<<"Detected ("<<endl;
                ListedAttributes();
                
            }
            if(Expecting(")"))
                return true;
   
        }
        
    }
    return false;

}
bool Parse::C_Delete() //Done
{
    if(Validate("DELETE"))
    {
        //DELETE FROM dots WHERE (y1 <= 0);
        Expecting("FROM");
        if(RelationsWord())
        {
            Expecting("WHERE");
            Expecting("(");
            if(RelationsWord())
            {
                Operation();
                RelationsWord();
                Expecting(")");
                return true;
            }
        }
    }
    return false;

}

bool Parse::alphaCheck(char c) //Found this function online help from michel
{
    if((int)c < 123 && (int)c > 96){ 
        return true;
    }
    else if((int)c < 91 && (int)c > 64)
    {
        return true;
    }
        else if (c == '_')
        {
                return true;
        }
    else 
        return false;
}

bool Parse::digitCheck(char c) //Found this function online help from michel
{
    if((int)c < 58 && (int)c > 47)
    {
        return true;
    }
    else 
        return false;
}

bool Parse::AtomicExpr()
{
                 
    //cout<<"Entering Atomic Expression: "<<CURRENT_TOKEN<<endl;
        if(CURRENT_TOKEN == "(")
        {
            //cout<<"Entering Atomic Expression: ["<<CURRENT_TOKEN<<"] : Size: "<<TOKENS.size()<<endl;
            getToken();
            if(Expression())
            {
                if(CURRENT_TOKEN == "*")
                {           
                    getToken();
                    return AtomicExpr();
                }
                
                    Expecting(")");
                    return true;
            }
            else
            {
                    return false;
            }
        }
    if(RelationsWord()){
        return true;
    }
    return false;
}

bool Parse::Expression()
{
    //cout<<"Expression:["<<CURRENT_TOKEN<<"]"<<endl;
    if(Selection())
    {
        return true;
    }
    if(Projection())
    {
        return true;
    }
    
    if(Union())
    {
        return true;
    }
    if(Renaming())
    {
        return true;   
    }
    
    if(Product())
    {
        return true;    
    }
    if(Difference())
    {
        
        return true;
    }
    if(AtomicExpr())
    {
        return true;
    }
    
 return false;   
}


bool Parse::Projection()
{
   if(Validate("project"))
   {
      Expecting("(");
      if(ListedAttributes()) 
      {
          Expecting(")");
          return AtomicExpr();
      }
       
   }
   return false;
}
bool Parse::Selection()
{
    if(Validate("select")) //select is lowercase
    {
        
        Expecting("(");
        RelationsWord();
        if(Operation())
        {
            RelationsWord();
            Expecting(")");
            return AtomicExpr();
        }
    }
    return false;
    
}

bool Parse::Union() //May not need
{
  return false;  
}

bool Parse::Renaming()
{
    //rename_test <- rename (v_fname, v_lname, v_personality, v_bounty) enemies;
    //cout<<"Renaming"<<endl;
    if(Validate("rename"))
   {
      Expecting("(");
      if(ListedAttributes()) 
      {
          Expecting(")");
          return AtomicExpr();
      }
       
   }
   return false;
    
}

bool Parse::Difference() //Not sure if function possible here
{
    //cout<<"difference: "<<CURRENT_TOKEN<<endl;
   
    return false;   
}

bool Parse::Product()
{
    if(Expecting("*"))
    {
        cout<<"Validated a *"<<endl;
        getToken();
        return true;        
    }
    
}
bool Parse::ListedAttributes() //Gathers the entire comma seperated list into the token list
{
    //cout<<"Entering Listed Attributes on Token: "<<CURRENT_TOKEN<<endl;
    if(RelationsWord())
    {
        while(CURRENT_TOKEN ==",")
        {
            //cout<<CURRENT_TOKEN<<endl;
            getToken();
            RelationsWord();
                
        }
     return true; //List compiled  
    }
 
    return false;
}

bool Parse::Operation(){
        //Testing if is avaliable opertaion based on assignment sheet, not specific
    if(CURRENT_TOKEN == "==" 
            || CURRENT_TOKEN == "!=" 
            || CURRENT_TOKEN == "<"
            || CURRENT_TOKEN == ">" 
            || CURRENT_TOKEN == "<=" 
            || CURRENT_TOKEN == ">="
            || CURRENT_TOKEN == "=") //added = for update function 
    {
        getToken(); //Move token forward from operation, assuming return to next expression
        return true;
    }
    return false;
}

bool Parse::RelationsWord() //Was isIdentifer
{  
    //cout<<"Relations/KeyWord"<<endl;
    getToken();
    return true;
}

bool Parse::Type()
{
        
    if(Validate("VARCHAR"))
    {
        Expecting("(");
        
        if(Integer())
        {
            Expecting(")");
            return true; //Good type check
        }
        else 
            return false;
    }
    else
    {
        return Validate("INTEGER");
    }
}

bool Parse::Integer() //Found this function skelton online
{
    istringstream IStream(CURRENT_TOKEN);
    
    double inputV = 0.0;
    
    if(IStream >> inputV)
    {
        getToken();
        return true;
    }
    else 
        return false;    
}


bool Parse::Create_AttList() //Syntax designed for create function, workaround -jk
{
  if(RelationsWord())
    {
        if(Type())
        {

            while(CURRENT_TOKEN ==",")
            {
                //cout<<CURRENT_TOKEN<<endl;
                getToken();
                RelationsWord();
                Type();

            }
        return true; //List compiled  
        }
    }
 
    return false;  
    
}