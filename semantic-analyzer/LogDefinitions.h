#ifndef LOGDEF_CLASS_H
#define LOGDEF_CLASS_H

enum class LogLevel {
    LEVEL_WARNING,		
    LEVEL_ERROR		
};

enum class LogType {
    TYPE_DUP,	
    TYPE_NOT_DECLR
};

enum class OpType {
    TYPE_ARITH,	
    TYPE_REL,
    TYPE_COND,
    TYPE_EQ
};

enum class IdType {
    TYPE_VAR,	
    TYPE_ARRAY,	
    TYPE_PARAM,
    TYPE_FUNC
};

bool DEBUG = true;

#endif