
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

static std::string getNextFile(StringRef currFileName, std::string newFileExtension){
      std::string newFile = currFileName.str();
      std::string ext =  newFileExtension+"GlobalID"+std::to_string(no_of_operations++);
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

     if(clang::BinaryOperator::isShiftOp (Operator)){
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Shl)) != true)
            OpCode.push_back(clang::BO_Shl);
        if(Operat_str.equals(clang::BinaryOperator::getOpcodeStr(clang::BO_Shr)) != true)
            OpCode.push_back(clang::BO_Shr);
      
    }

    return OpCode;

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
              std::string newFileExtension= "_Opcode"+operand.str() +"Line"+std::to_string(Result.SourceManager->getSpellingLineNumber(binOp->getExprLoc()))
                  +"Column"+std::to_string(Result.SourceManager->getSpellingColumnNumber (binOp->getExprLoc()));
              for(std::vector<clang::BinaryOperator::Opcode>::iterator op_it = mutant_Ops.begin();op_it != mutant_Ops.end(); ++op_it){
                    new_replacement = getText(*(Result.SourceManager),*lhs)+" "+clang::BinaryOperator::getOpcodeStr(*op_it).str()
                        +" " +getText(*(Result.SourceManager),*rhs);
                    StringRef currFileName =Result.SourceManager->getFilename(binOp->getExprLoc());
                    std::string newFile =getNextFile(currFileName,newFileExtension);
                    Replacement Rep(*(Result.SourceManager), binOp, new_replacement);
                    Replacement Rep1(newFile, Rep.getOffset (), Rep.getLength(),new_replacement);
                    Replace->insert(Rep1);
                    new_replacement.erase();
                    
              }

              
            

                
              if(binOp->isComparisonOp ()){
                   llvm::outs()<<"Comparison Opcode: "<<operand.str()<<"\n";
               }
              if(binOp->isMultiplicativeOp ()){
                   llvm::outs()<<"Multiplicative Opcode: "<<operand.str()<<"\n";
                   
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
            //llvm::outs()<<"Opcode: "<<operand.str()<<"\n";
            clang::UnaryOperator::Opcode UnOpCode = unOp->getOpcode ();

            std::vector<clang::UnaryOperator::Opcode> mutant_Ops;
            Expr * subExpr = unOp->getSubExpr ();
            StringRef Operat_str = clang::UnaryOperator::getOpcodeStr(UnOpCode);

            if((Operat_str.equals(clang::UnaryOperator::getOpcodeStr(clang::UO_PostInc)) != true) || (clang::UnaryOperator::isPrefix(UnOpCode)))
                mutant_Ops.push_back(clang::UO_PostInc);
            if((Operat_str.equals(clang::UnaryOperator::getOpcodeStr(clang::UO_PostDec)) != true) || (clang::UnaryOperator::isPrefix(UnOpCode)))
                mutant_Ops.push_back(clang::UO_PostDec);
            if((Operat_str.equals(clang::UnaryOperator::getOpcodeStr(clang::UO_PreInc)) != true) ||  (clang::UnaryOperator::isPostfix(UnOpCode)))
                mutant_Ops.push_back(clang::UO_PreInc);
            if((Operat_str.equals(clang::UnaryOperator::getOpcodeStr(clang::UO_PreDec)) != true)  ||  (clang::UnaryOperator::isPostfix(UnOpCode)))
                mutant_Ops.push_back(clang::UO_PreDec);

              std::string new_replacement;
              std::string newFileExtension= "_Opcode"+ Operat_str.str() +"Line"+std::to_string(Result.SourceManager->getSpellingLineNumber(unOp->getExprLoc()))
                  +"Column"+std::to_string(Result.SourceManager->getSpellingColumnNumber (unOp->getExprLoc()));
              for(std::vector<clang::UnaryOperator::Opcode>::iterator op_it = mutant_Ops.begin();op_it != mutant_Ops.end(); ++op_it){
                  if(clang::UnaryOperator::isPostfix(*op_it)){
                      new_replacement = clang::UnaryOperator::getOpcodeStr(*op_it).str()
                        +getText(*(Result.SourceManager),*subExpr);
                    
                  }
                  else{
                      new_replacement = getText(*(Result.SourceManager),*subExpr) + clang::UnaryOperator::getOpcodeStr(*op_it).str();
                  }    
                  StringRef currFileName =Result.SourceManager->getFilename(unOp->getExprLoc());
                  std::string newFile =getNextFile(currFileName,newFileExtension);
                  Replacement Rep(*(Result.SourceManager), unOp, new_replacement);
                  Replacement Rep1(newFile, Rep.getOffset (), Rep.getLength(),new_replacement);
                  Replace->insert(Rep1);
                  new_replacement.erase();
              }
       
            if(unOp->isIncrementOp ()){
                llvm::outs()<<"Increment Opcode: "<<Operat_str.str()<<"\n";
            }
            else if(unOp->isDecrementOp ()){
                llvm::outs()<<"Decrement Opcode: "<<Operat_str.str()<<"\n";
            }
            else if(unOp->isIncrementDecrementOp ()){
                llvm::outs()<<"IncrementDecrement Opcode: "<<Operat_str.str()<<"\n";
            }
            else if(unOp->isArithmeticOp ()){
                llvm::outs()<<"Arithmetic Opcode: "<<Operat_str.str()<<"\n";
            }
    }
  }
}

private:
    Replacements *Replace;
};




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
