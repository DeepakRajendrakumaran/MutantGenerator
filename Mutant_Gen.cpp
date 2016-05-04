
#include <string>

#include <sstream>

#include <istream>
#include <iostream>
#include <fstream>
#include <iterator>




#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Rewrite/Core/Rewriter.h"

#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"

#include "clang/AST/AST.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/raw_os_ostream.h"

#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"


using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::driver;
using namespace clang::tooling;



static llvm::cl::OptionCategory ToolingSampleCategory("Matcher Sample");


int no_of_operations = 0;
int preprocessing_done = false;
std::vector< std::string > pathList;
StringRef File_Path;
//std::string newFile;

template <typename T>
static std::string getText(const SourceManager &SourceManager, const T &Node) {
  SourceLocation StartSpellingLocation =
      SourceManager.getSpellingLoc(Node.getLocStart());
  SourceLocation EndSpellingLocation =
      SourceManager.getSpellingLoc(Node.getLocEnd());
  if (!StartSpellingLocation.isValid() || !EndSpellingLocation.isValid()) {
    return std::string();
  }
  bool Invalid = true;
  const char *Text =
      SourceManager.getCharacterData(StartSpellingLocation, &Invalid);
  if (Invalid) {
    return std::string();
  }
  std::pair<FileID, unsigned> Start =
      SourceManager.getDecomposedLoc(StartSpellingLocation);
  std::pair<FileID, unsigned> End =
      SourceManager.getDecomposedLoc(Lexer::getLocForEndOfToken(
          EndSpellingLocation, 0, SourceManager, LangOptions()));
  if (Start.first != End.first) {
    // Start and end are in different files.
    return std::string();
  }
  if (End.second < Start.second) {
    // Shuffling text with macros may cause this.
    return std::string();
  }
  return std::string(Text, End.second - Start.second);
}

static std::string getNextFile(StringRef currFileName){
      std::string newFile = currFileName.str();
      std::string ext = std::to_string(no_of_operations++);
      size_t pos = newFile.find(".cpp");
      newFile.insert(pos,  ext);
      std::ifstream  src(pathList[0], std::ios::binary);
      std::ofstream  dst(newFile,   std::ios::binary);

      dst << src.rdbuf();

      return newFile;
  }

static std::vector<clang::BinaryOperator::Opcode> viableBinMutantOpcodes(clang::BinaryOperator::Opcode Operator){

    std::vector<clang::BinaryOperator::Opcode> OpCode;
    StringRef Operat_str = clang::BinaryOperator::getOpcodeStr(Operator);
    if(clang::BinaryOperator::isComparisonOp(Operator)){
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_LT)) != true)
            OpCode.push_back(clang::BO_LT);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_GT)) != true)
            OpCode.push_back(clang::BO_GT);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_LE)) != true)
            OpCode.push_back(clang::BO_LE);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_GE)) != true)
            OpCode.push_back(clang::BO_GE);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_EQ)) != true)
            OpCode.push_back(clang::BO_EQ);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_NE)) != true)
            OpCode.push_back(clang::BO_NE);
    }


    else if((clang::BinaryOperator::isMultiplicativeOp(Operator)) || (clang::BinaryOperator::isAdditiveOp(Operator))){
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Mul)) != true)
            OpCode.push_back(clang::BO_Mul);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Div)) != true)
            OpCode.push_back(clang::BO_Div);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Rem)) != true)
            OpCode.push_back(clang::BO_Rem);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Sub)) != true)
            OpCode.push_back(clang::BO_Sub);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Add)) != true)
            OpCode.push_back(clang::BO_Add);
       
    }

     else if(clang::BinaryOperator::isShiftAssignOp (Operator)){
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Shl)) != true)
            OpCode.push_back(clang::BO_Mul);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Shr)) != true)
            OpCode.push_back(clang::BO_Div);
      
    }

    return OpCode;
/*

      BO_PtrMemD 	
      BO_PtrMemI 	
BO_Mul 	
BO_Div 	
BO_Rem 	
BO_Add 	
BO_Sub 	
BO_Shl 	
BO_Shr 	
BO_LT 	
BO_GT 	
BO_LE 	
BO_GE 	
BO_EQ 	
BO_NE 	
BO_And 	
BO_Xor 	
BO_Or 	
BO_LAnd 	
BO_LOr 	
BO_Assign 	
BO_MulAssign 	
BO_DivAssign 	
BO_RemAssign 	
BO_AddAssign 	
BO_SubAssign 	
BO_ShlAssign 	
BO_ShrAssign 	
BO_AndAssign 	
BO_XorAssign 	
BO_OrAssign 	
BO_Comma 

      return newFile;*/
  }






class BinaryOperatorHandler : public MatchFinder::MatchCallback {
public:
  BinaryOperatorHandler(Replacements *Replace) : Replace(Replace) {}

  virtual void run(const MatchFinder::MatchResult &Result) {
     
      if (const BinaryOperator *binOp = Result.Nodes.getNodeAs<clang::BinaryOperator>("binaryOperator")) {
          // llvm::outs()<<"\nisInSystemHeader = \n"<<Result.SourceManager->isInSystemHeader(binOp->getExprLoc())<<"\n";
          if((Result.SourceManager->isInMainFile(binOp->getExprLoc())==true) &&
                  (Result.SourceManager->isInSystemHeader(binOp->getExprLoc())==0)){
             
                

              std::string temp;
              temp = getText(*(Result.SourceManager),*binOp);
              llvm::outs()<<"\nBinaryOperator: "<<temp<<"\n";
              StringRef 	operand = binOp->getOpcodeStr(binOp->getOpcode () );
              // llvm::outs()<<"Opcode: "<<operand.str()<<"\n";
              clang::BinaryOperator::Opcode binOpCode = binOp->getOpcode ();

              std::vector<clang::BinaryOperator::Opcode> mutant_Ops = viableBinMutantOpcodes(binOpCode);
              Expr * lhs =binOp->getLHS () ;
              Expr * rhs =binOp->getRHS () ;
              std::string new_replacement;
              for(std::vector<clang::BinaryOperator::Opcode>::iterator op_it = mutant_Ops.begin();op_it != mutant_Ops.end(); ++op_it){
                    new_replacement = getText(*(Result.SourceManager),*lhs)+" "+clang::BinaryOperator::getOpcodeStr(*op_it).str()
                        +" " +new_replacement + new_replacement +getText(*(Result.SourceManager),*rhs);
                    StringRef currFileName =Result.SourceManager->getFilename(binOp->getExprLoc());
                    std::string newFile =getNextFile(currFileName);
                    Replacement Rep(*(Result.SourceManager), binOp, new_replacement);
                    Replacement Rep1(newFile, Rep.getOffset (), Rep.getLength(),new_replacement);
                    Replace->insert(Rep1);
              }

              
              /*      Expr * lhs =binOp->getLHS () ;
                    Expr * rhs =binOp->getRHS () ;
                    std::string new_replacement;

                    for(std::vector<clang::BinaryOperator::Opcode>::iterator op_it = mutant_Ops.begin();op_it != mutant_Ops.end(); ++op_it);{
                        new_replacement = getText(*(Result.SourceManager),*lhs)+clang::BinaryOperator::getOpcodeStr(op_it)+getText(*(Result.SourceManager),*rhs);
                        llvm::outs()<<"\nExpr: "<<new_replacement<<"\n";
                        StringRef currFileName =Result.SourceManager->getFilename(binOp->getExprLoc());
                        std::string newFile =getNextFile(currFileName);
                        Replacement Rep(*(Result.SourceManager), binOp, new_replacement);
                        Replacement Rep1(newFile, Rep.getOffset (), Rep.getLength(),new_replacement);
                        Replace->insert(Rep1);
                    }*/


              

                
               if(binOp->isComparisonOp ()){
                   llvm::outs()<<"Comparison Opcode: "<<operand.str()<<"\n";
               }
              if(binOp->isMultiplicativeOp ()){
                   llvm::outs()<<"Multiplicative Opcode: "<<operand.str()<<"\n";
                   //createAndWrite2File();
              }
               if(binOp->isAdditiveOp ()){
                   llvm::outs()<<"Additive Opcode: "<<operand.str()<<"\n";
              }
               if(binOp->isShiftOp ()){
                   llvm::outs()<<"Shift Opcode: "<<operand.str()<<"\n";
              }
               if(binOp->isBitwiseOp ()){
                   llvm::outs()<<"Bitwise Opcode: "<<operand.str()<<"\n";
              }
               if(binOp->isRelationalOp ()){
                   llvm::outs()<<"Relational Opcode: "<<operand.str()<<"\n";
                  
              }
               if(binOp->isEqualityOp ()){
                   llvm::outs()<<"Equality Opcode: "<<operand.str()<<"\n";
              }
              
               if(binOp->isLogicalOp ()){
                   llvm::outs()<<"Logical Opcode: "<<operand.str()<<"\n";
              }
               if(binOp->isAssignmentOp ()){
                   llvm::outs()<<"Assignment Opcode: "<<operand.str()<<"\n";
              }
               if(binOp->isCompoundAssignmentOp ()){
                   llvm::outs()<<"CompoundAssignment Opcode: "<<operand.str()<<"\n";
              }
               if(binOp->isShiftAssignOp ()){
                   llvm::outs()<<"ShiftAssign Opcode: "<<operand.str()<<"\n";
              }

           
    }
  }
  
}

private:
  Replacements *Replace;
};

class unaryOperatorHandler : public MatchFinder::MatchCallback {
public:
  unaryOperatorHandler(Replacements *Replace) : Replace(Replace) {}

  virtual void run(const MatchFinder::MatchResult &Result) {
   
    if (const UnaryOperator *unOp = Result.Nodes.getNodeAs<clang::UnaryOperator>("unaryOperator")) {
        if((Result.SourceManager->isInMainFile(unOp->getExprLoc())==true) &&
                  (Result.SourceManager->isInSystemHeader(unOp->getExprLoc())==0)){
            std::string temp;
            temp = getText(*(Result.SourceManager),*unOp);
            llvm::outs()<<"\nUnaryOperator\n"<<temp<<"\n";
            StringRef 	operand = unOp->getOpcodeStr(unOp->getOpcode () );
            //llvm::outs()<<"Opcode: "<<operand.str()<<"\n";
            clang::UnaryOperator::Opcode UnOpCode = unOp->getOpcode ();
            if(unOp->isIncrementOp ()){
                llvm::outs()<<"Increment Opcode: "<<operand.str()<<"\n";
            }
            else if(unOp->isDecrementOp ()){
                llvm::outs()<<"Decrement Opcode: "<<operand.str()<<"\n";
            }
            else if(unOp->isIncrementDecrementOp ()){
                llvm::outs()<<"IncrementDecrement Opcode: "<<operand.str()<<"\n";
            }
            else if(unOp->isArithmeticOp ()){
                llvm::outs()<<"Arithmetic Opcode: "<<operand.str()<<"\n";
            }
    }
  }
}

private:
    Replacements *Replace;
};



void createAndWrite2File()
{
    std::string newFile = pathList[0];
    /*newFile=newFile+ std::to_string(no_of_operations);
    newFile.replace(newFile.size ()-5, newFile.size ()-4, "1.cpp");*/

    std::string ext = std::to_string(no_of_operations);
    size_t pos = newFile.find(".cpp");
              //llvm::outs()<<"newFile =: "<<newFile<<"\n";
              //llvm::outs()<<"FileName =: "<<FileName.str()<<"\n";
              //llvm::outs()<<"Position =: "<<pos<<"\n";
     newFile.insert(pos,  ext);
    
    /*std::ofstream outfile (newFile);
    outfile.close();*/

    /*std::fstream finFile(pathList[0], std::fstream::in|std::fstream::binary);
    finFile << std::noskipws;
    std::istream_iterator<std::istream> begin(finFile);
    std::istream_iterator end;
    std::fstream foutFile("output.txt",std::fstream::out|std::fstream::trunc|std::fstream::binary);
    std::ostream_iterator<std::ostream> begin2(newFile);
    std::copy(begin, end, begin2);*/

    /*std::ifstream inFile(pathList[0], std::ios::binary);
    std::ofstream outFile(newFile, std::ios::binary);

    while (inFile.good())  // Though perhaps this condition is wrong
    {
        outFile.put(inFile.get());
    }

    inFile.close();
    outFile.close();*/

    std::ifstream  src(pathList[0], std::ios::binary);
    std::ofstream  dst(newFile,   std::ios::binary);

    dst << src.rdbuf();

}

int main(int argc, const char **argv) {
    CommonOptionsParser op(argc, argv, ToolingSampleCategory);
    pathList = op.getSourcePathList();
    llvm::outs() << "Input Path:"<<pathList[0]<<"\n";
    RefactoringTool Tool(op.getCompilations(), op.getSourcePathList());
    
    // Set up AST matcher callbacks.
    //  IfStmtHandler HandlerForIf(&Tool.getReplacements());
    BinaryOperatorHandler HandlerForbinOp(&Tool.getReplacements());
    unaryOperatorHandler HandlerForUnaryOp(&Tool.getReplacements());
    MatchFinder Finder;
    Finder.addMatcher(binaryOperator().bind("binaryOperator"), &HandlerForbinOp);
    Finder.addMatcher(unaryOperator().bind("unaryOperator"), &HandlerForUnaryOp);


    // Run the tool and collect a list of replacements. We could call runAndSave,
    // which would destructively overwrite the files with their new contents.
    // However, for demonstration purposes it's interesting to show the
    // replacements.
    if (int Result = Tool.runAndSave(newFrontendActionFactory(&Finder).get())) {
        return Result;
    }
    //createAndWrite2File();
    preprocessing_done = true;
    llvm::outs() << "Replacements collected by the tool:\n";
     for (auto &r : Tool.getReplacements()) {
    llvm::outs() << r.toString() << "\n";
    }
    
    return 0;
}
