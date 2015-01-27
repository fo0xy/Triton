
#ifndef   __SYMBOLICENGINE_H__
#define   __SYMBOLICENGINE_H__

#include <list>
#include <sstream>
#include <stdint.h>
#include <string>
#include <utility>

#include "smt2lib_utils.h"


/* Symbolic element */
class symbolicElement {

  private:
    std::stringstream   *source;
    std::stringstream   *destination;
    std::stringstream   *expression;
    uint64_t              id;


  public:
    uint32_t      isTainted;
    std::string   getExpression();
    std::string   getSource();
    uint64_t      getID();

    symbolicElement(std::stringstream &dst, std::stringstream &src, uint64_t id);
    ~symbolicElement();

};

/* Symbolic Engine */
class SymbolicEngine {

  private:

    /* symbolic expression ID */
    uint64_t uniqueID;

    /* Number of symbolic variables used */
    uint64_t numberOfSymVar;

    /*
     * Addresses <-> symbolic expression
     * item1: memory address
     * item2: reference ID
     */
    std::list< std::pair<uint64_t, uint64_t> > memoryReference;

    /*
     * Addresses <-> Z3 Symbolic Variable
     * item1: memory address
     * item2: symbolic variable ID
     */
    std::list< std::pair<uint64_t, uint64_t> > symVarMemoryReference;

    /* List of variables decl in smt2lib */
    std::list<std::string> smt2libVarDeclList;

    /* List of symbolic elements ID */
    std::list<symbolicElement *> symbolicList;


  public:

    /* Symbolic trace */
    uint64_t symbolicReg[25];

    int32_t               isMemoryReference(uint64_t addr);
    uint64_t              getUniqueID();
    uint64_t              getUniqueSymVarID();
    void                addMemoryReference(uint64_t mem, uint64_t id);
    void                addSmt2LibVarDecl(uint64_t symVarID, uint64_t readSize);
    void                addSymVarMemoryReference(uint64_t mem, uint64_t symVarID);
    void                setSymbolicReg(uint64_t reg, uint64_t referenceID);
    symbolicElement     *getElementFromId(uint64_t id);
    std::string         getSmt2LibVarsDecl();
    symbolicElement     *newSymbolicElement(std::stringstream &src);

    SymbolicEngine();
    ~SymbolicEngine();

};

#endif     /* !__SYMBOLICENGINE_H__ */
