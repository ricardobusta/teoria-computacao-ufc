#include "tmsyntax.h"

#include <QDebug>
#include <QTextEdit>

#include "exnamespace.h"

enum SYN_STATE{SYN_ERROR,SYN_SEM_ERROR};

TMSyntax::TMSyntax(QTextEdit *parent) :
    QSyntaxHighlighter(parent)
{
    QColor comment_color = QColor(0,150,0);
    QColor state_color = QColor(0,0,150);
    QColor syntax_error_color = QColor(255,0,0);
    QColor semantic_error_color = QColor(0,255,0);
    QColor character_color = QColor(0,150,150);
    QColor command_color = QColor(150,0,150);
    QColor option_color = QColor(250,0,150);
    QColor machine_color = QColor(150,150,0);

    // White
    // Comment
    io_format::comment.setForeground(QBrush(comment_color));
    //io_format::comment.setFont(io_font::input);

    // Error
    io_format::syntax_error.setUnderlineColor(syntax_error_color);
    io_format::syntax_error.setUnderlineStyle(QTextCharFormat::WaveUnderline);
    //io_format::syntax_error.setFont(io_font::input);

    io_format::semantic_error.setUnderlineColor(semantic_error_color);
    io_format::semantic_error.setUnderlineStyle(QTextCharFormat::WaveUnderline);
    //io_format::semantic_error.setFont(io_font::input);

    // State
    io_format::state.setForeground(QBrush(state_color));
    //io_format::state.setFontItalic(true);
    //io_format::state.setFont(io_font::input);
    // spec
    io_format::state_spec.setForeground(QBrush(state_color));
    io_format::state_spec.setFontWeight(99);
    //io_format::state_spec.setFont(io_font::input);

    // Character
    io_format::character.setForeground(QBrush(character_color));
    //io_format::character.setFont(io_font::input);
    // spec
    io_format::character_spec.setForeground(QBrush(character_color));
    //io_format::character_spec.setFont(io_font::input);

    // Command
    io_format::command.setForeground(QBrush(command_color));
    //io_format::command.setFont(io_font::input);

    // Option
    io_format::option.setForeground(QBrush(option_color));
    //io_format::option.setFont(io_font::input);

    // Machine
    io_format::machine.setForeground(QBrush(machine_color));
    //io_format::machine.setFontItalic(true);
    //io_format::machine.setFont(io_font::input);
    // spec
    io_format::machine_spec.setForeground(QBrush(machine_color));
    io_format::machine_spec.setFontWeight(99);
    //io_format::machine_spec.setFont(io_font::input);
}

void TMSyntax::highlightBlock(const QString &text)
{
    if(previousBlockState()==SYN_ERROR){
        setCurrentBlockState(1);
        setFormat(0,text.size(),io_format::syntax_error);
        return;
    }

    if(currentBlockState()==2){
        //setCurrentBlockState(1);
        setFormat(0,text.size(),io_format::semantic_error);
        return;
    }

    setCurrentBlockState(-1);

    switch(io_ex::line_type(text)){
    case io_ex::LINE_OPTION:
        setFormat(0,text.size(),io_format::option);
        break;

    case io_ex::LINE_VALID_MACHINE:
    case io_ex::LINE_VALID_STATE:
        break_line_token(text);

        switch(token_list[0].type){
        case io_ex::TOKEN_STATE_SPEC:
            setFormat(token_list[0].start, token_list[0].count, io_format::state_spec);
            break;
        case io_ex::TOKEN_STATE:
            setFormat(token_list[0].start,token_list[0].count,io_format::state);
            break;
        case io_ex::TOKEN_MACHINE:
            setFormat(token_list[0].start,token_list[0].count,io_format::machine);
            break;
        default:
            break;
        }

        switch(token_list[1].type){

        case io_ex::TOKEN_CHARACTER_SPEC:
            setFormat(token_list[1].start,token_list[1].count,io_format::character_spec);
            break;
        case io_ex::TOKEN_CHARACTER:
            setFormat(token_list[1].start,token_list[1].count,io_format::character_spec);
            break;
        default:
            break;
        }

        switch (token_list[2].type) {
        case io_ex::TOKEN_STATE_SPEC:
            setFormat(token_list[2].start,token_list[2].count,io_format::state_spec);
            break;
        case io_ex::TOKEN_STATE:
            setFormat(token_list[2].start,token_list[2].count,io_format::state);
            break;
        case io_ex::TOKEN_MACHINE:
            setFormat(token_list[2].start,token_list[2].count,io_format::machine);
            break;
        default:
            break;
        }

        switch (token_list[3].type) {
        case io_ex::TOKEN_COMMAND:
            setFormat(token_list[3].start,token_list[3].count,io_format::command);
            break;
        case io_ex::TOKEN_CHARACTER_SPEC:
            setFormat(token_list[3].start,token_list[3].count,io_format::character_spec);
            break;
        case io_ex::TOKEN_CHARACTER:
            setFormat(token_list[3].start,token_list[3].count,io_format::character);
            break;
        default:
            break;
        }

        break;

    case io_ex::LINE_COMMENT:
        setFormat(0,text.size(),io_format::comment);
        break;

    case io_ex::LINE_WHITE:
        setFormat(0,text.size(),io_format::blank);
        break;

    case io_ex::LINE_ERROR:
    default:
        setFormat(0,text.size(),io_format::syntax_error);
        setCurrentBlockState(1);
        break;
    }
}

