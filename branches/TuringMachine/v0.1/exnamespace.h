#ifndef EXNAMESPACE_H
#define EXNAMESPACE_H

#include <QRegExp>
#include <QFont>
#include <QTextCharFormat>
#include <QDebug>

namespace io_ex{

enum TOKEN{
    TOKEN_ERROR,
    TOKEN_STATE,
    TOKEN_STATE_SPEC,
    TOKEN_CHARACTER,
    TOKEN_CHARACTER_SPEC,
    TOKEN_COMMAND,
    TOKEN_MACHINE,
    TOKEN_MACHINE_SPEC
};

enum LINE{
    LINE_ERROR,
    LINE_WHITE,
    LINE_VALID,
    LINE_OPTION,
    LINE_COMMENT
};

//Characters
const static QString halt_state = QString("halt");
const static QString error_state = QString("error");
const static QString all_character = QString("*");
const static QString blank_character = QString("#");
const static QString begin_character = QString("@");
const static QString left_command = QString("<");
const static QString right_command = QString(">");
const static QString halt_machine = QString("HALT");

//Tokens
const static QRegExp token = QRegExp("(\\S+)");
const static QRegExp name_option = QRegExp("(#(n|N)(a|A)(m|M)(e|E))");
const static QRegExp init_option = QRegExp("(#(i|I)(n|N)(i|I)(t|T))");
const static QRegExp halt_option = QRegExp("(#(h|H)(a|A)(l|L)(t|T))");
const static QRegExp machine_spec = QRegExp("("+halt_machine+")");
const static QRegExp machine = QRegExp("[A-Z]([a-zA-Z0-9_]*)");
const static QRegExp state_spec = QRegExp("("+halt_state+")");
const static QRegExp state = QRegExp("[a-z]([a-zA-Z0-9_]*)");
const static QRegExp character_spec = QRegExp("["+blank_character+begin_character+all_character+"]");
const static QRegExp character = QRegExp("[a-zA-Z0-9]");
const static QRegExp command = QRegExp("["+left_command+right_command+"]");

const static QRegExp option_line = QRegExp("^("+name_option.pattern()+"|"+init_option.pattern()+"|"+halt_option.pattern()+")(\\s+)(\\S+)(\\s*)$");
//Lines
const static QRegExp comment = QRegExp("^((//(.*))|(/\\*(.*)\\*/))$"/*|(#(.*))*/);
const static QRegExp white_line = QRegExp("^(\\s*)$");
const static QRegExp valid_line = QRegExp("^(\\s*)("+state.pattern()+"|"+machine.pattern()+")"
                                          +"(\\s+)("+character.pattern()+"|"+character_spec.pattern()+")"
                                          +"(\\s+)("+state.pattern()+"|"+machine.pattern()+"|"+state_spec.pattern()+"|"+machine_spec.pattern()+")"
                                          +"(\\s+)("+command.pattern()+"|"+character.pattern()+"|"+character_spec.pattern()+")(\\s*)$");


static inline TOKEN token_type_s(const QString s){
    if(state_spec.exactMatch(s)){
        return TOKEN_STATE_SPEC;
    }else if(state.exactMatch(s)){
        return TOKEN_STATE;
    }else if(machine_spec.exactMatch(s)){
        return TOKEN_MACHINE_SPEC;
    }else if(machine.exactMatch(s)){
        return TOKEN_MACHINE;
    }else if(character_spec.exactMatch(s)){
        return TOKEN_CHARACTER_SPEC;
    }else if(character.exactMatch(s)){
        return TOKEN_CHARACTER;
    }else if(command.exactMatch(s)){
        return TOKEN_COMMAND;
    }
    return TOKEN_ERROR;
}
static inline TOKEN token_type_c(const QString s){
    if(character_spec.exactMatch(s)){
        return TOKEN_CHARACTER_SPEC;
    }else if(character.exactMatch(s)){
        return TOKEN_CHARACTER;
    }else if(state_spec.exactMatch(s)){
        return TOKEN_STATE_SPEC;
    }else if(state.exactMatch(s)){
        return TOKEN_STATE;
    }else if(machine_spec.exactMatch(s)){
        return TOKEN_MACHINE_SPEC;
    }else if(machine.exactMatch(s)){
        return TOKEN_MACHINE;
    }else if(command.exactMatch(s)){
        return TOKEN_COMMAND;
    }
    return TOKEN_ERROR;
}
static inline LINE line_type(const QString s){
    if(white_line.exactMatch(s)){
        return LINE_WHITE;
    }else if(option_line.exactMatch(s)){
        return LINE_OPTION;
    }else if(comment.exactMatch(s)){
        return LINE_COMMENT;
    }else if(valid_line.exactMatch(s)){
        return LINE_VALID;
    }
    return LINE_ERROR;
}

}

namespace io_format{
static QTextCharFormat blank;
static QTextCharFormat comment;
static QTextCharFormat option;
static QTextCharFormat error;
static QTextCharFormat state;
static QTextCharFormat state_spec;
static QTextCharFormat character;
static QTextCharFormat character_spec;
static QTextCharFormat command;
static QTextCharFormat machine;
static QTextCharFormat machine_spec;
}

namespace io_font{
static QFont input = QFont("consolas",12);
}

#endif // EXNAMESPACE_H