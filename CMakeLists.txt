cmake_minimum_required(VERSION 3.16.3)
project(project_1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)

add_executable(project_1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        Token.cpp
        Token.h
        CommentAutomaton.cpp
        CommentAutomaton.h
        E_O_FAutomaton.cpp
        E_O_FAutomaton.h
        MatcherAutomaton.cpp
        MatcherAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        IDAutomaton.cpp
        IDAutomaton.h
        BlockCommentAutomaton.cpp
        BlockCommentAutomaton.h
        UnclosedStringAutomaton.cpp
        UnclosedStringAutomaton.h
        UnclosedCommentAutomaton.cpp
        UnclosedCommentAutomaton.h
        Parser.cpp
        Parser.h
        DatalogProgram.cpp
        DatalogProgram.h
        Rule.cpp
        Rule.h
        Predicate.cpp
        Predicate.h
        Parameter.cpp
        Parameter.h
        Database.cpp
        Database.h
        Relation.cpp
        Relation.h
        Header.cpp
        Header.h
        Tuple.cpp
        Tuple.h
        Interpreter.cpp
        Interpreter.h
        main.cpp)
